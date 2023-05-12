#include <iostream>
#include <Windows.h>
#include <string>
#include <psapi.h>
#include <fstream>


struct pass_to_memory_limiter {
    HANDLE hProcess;
    int max_size;
    std::ofstream& outputFile;
};

DWORD WINAPI checkProcessMemory(pass_to_memory_limiter& data) {
    if (data.hProcess == NULL) {
        data.outputFile << "Failed to open process with error " << GetLastError() << std::endl;
        return 1;
    }
    while (true) {
        Sleep(10);
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(data.hProcess, &pmc, sizeof(pmc))) {
            int size = pmc.WorkingSetSize / 1024;
            if (size > data.max_size * 1024) {
                data.outputFile << "PROCESS EXCEEDED ALLOWED MEMORY\n";
                TerminateProcess(data.hProcess, 1);
                ExitProcess(1);
            }
        }
        else {
            continue;
        }
    }
    return 0;
}

void inject_dll(const std::string& file, int size, std::ofstream& outputFile) {
    const char name[] = { "D:\\Actual sandbox sln\\inlineHook\\Debug\\inlineHook.dll" };
    unsigned int len{ sizeof(name) + 1 };
    DWORD result = GetFullPathNameA(name, 0, NULL, NULL);
    char* buf = new char[result];
    result = GetFullPathNameA(name, result, buf, NULL);

    PVOID addrLoadLibrary = (PVOID)GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");
    if (addrLoadLibrary == NULL) {
        outputFile << "loadlibrary a failed\n";
    }
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(
        file.c_str(),
        NULL,
        NULL,
        NULL,
        FALSE,
        NORMAL_PRIORITY_CLASS,
        NULL,
        NULL,
        (LPSTARTUPINFOA)&si,
        &pi
    )) {
        outputFile << "failed to create new process with error: " << GetLastError() << '\n';
    }
    outputFile << "created new process\n";
    SuspendThread(pi.hThread);
    //std::cout << pi.hProcess << '\n';
    //std::cout << "yo";
    PVOID memAddr = (PVOID)VirtualAllocEx(
        pi.hProcess,
        NULL,
        result,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );
    if (memAddr == NULL) {
        outputFile << "failed to allocate virtual memory";
        DWORD err = GetLastError();
        outputFile << err;
    }

    if (!WriteProcessMemory(
        pi.hProcess,
        memAddr,
        buf,
        result,
        NULL
    )) {
        DWORD err = GetLastError();
        outputFile << "failed to write process memory with code: ";
        outputFile << err;
    }
    HANDLE remote_thread = CreateRemoteThread(
        pi.hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)addrLoadLibrary,
        memAddr,
        0,
        NULL
    );
    if (remote_thread == NULL) {
        outputFile << "failed to create remote thread\n";
    }
    outputFile << "injected the DLL\n";
    pass_to_memory_limiter data{ pi.hProcess,size,outputFile };
    HANDLE hThread = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)checkProcessMemory,
        (LPVOID)&data,
        0,
        NULL
    );

    ResumeThread(pi.hThread);
    WaitForSingleObject(remote_thread, INFINITE);
    CloseHandle(remote_thread);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(hThread);
}