#include <iostream>
#include <Windows.h>
#include <string>


void inject_dll(std::string& file) {
    const char name[] = { "D:\\Actual sandbox sln\\inlineHook\\Debug\\inlineHook.dll" };
    unsigned int len{ sizeof(name) + 1 };
    DWORD result = GetFullPathNameA(name, 0, NULL, NULL);
    char* buf = new char[result];
    result = GetFullPathNameA(name, result, buf, NULL);

    PVOID addrLoadLibrary = (PVOID)GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");
    if (addrLoadLibrary == NULL) {
        std::cout << "loadlibrary a failed\n";
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
        std::cout << "failed to create new process with error: " << GetLastError() << '\n';
    }
    std::cout << "created new process\n";
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
        std::cout << "failed to allocate virtual memory";
        DWORD err = GetLastError();
        std::cout << err;
    }

    if (!WriteProcessMemory(
        pi.hProcess,
        memAddr,
        buf,
        result,
        NULL
    )) {
        DWORD err = GetLastError();
        std::cout << "failed to write process memory";
        std::cout << err;
        std::cout << "eror";
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
        std::cout << "failed to create remote thread\n";
    }
    std::cout << "injected the DLL\n";
    ResumeThread(pi.hThread);
    WaitForSingleObject(remote_thread, INFINITE);
    CloseHandle(remote_thread);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
}