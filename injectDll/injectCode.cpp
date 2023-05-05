#include <iostream>
#include <Windows.h>
#include <string>
#include <psapi.h>


struct pass_to_memory_limiter {
    HANDLE hProcess;
    int max_size;
};

SOCKET* SetSocketToGraphics() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return nullptr;
    }

    SOCKET* sock = new SOCKET{ socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) };
    if (*sock == INVALID_SOCKET) {
        std::cout << "socket creation failed\n";
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
        return nullptr;
    }
    sockaddr_in saServer;
    saServer.sin_family = AF_INET;
    saServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //InetPton(AF_INET, (PCWSTR)_my_addr_, &saServer.sin_addr.S_un.S_addr);
    saServer.sin_port = htons(50505);
    iResult = connect(*sock, (SOCKADDR*)&saServer, sizeof(saServer));
    if (iResult == SOCKET_ERROR) {
        std::cout << "error connecting to server\n";
        return nullptr;
    }
    return sock;
}

DWORD WINAPI checkProcessMemory(pass_to_memory_limiter& data) {
    if (data.hProcess == NULL) {
        std::cout << "Failed to open process with error " << GetLastError() << std::endl;
        return 1;
    }
    SOCKET* sock = SetSocketToGraphics();
    if (*sock == INVALID_SOCKET || *sock == NULL || sock == nullptr) {
        std::cout << "error connecting to python server\n";
        return 1;
    }
    while (true) {
        Sleep(10);
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(data.hProcess, &pmc, sizeof(pmc))) {
            int size = pmc.WorkingSetSize / 1024;
            if (size > data.max_size * 1024) {
                std::cout << "PROCESS EXCEEDED ALLOWED MEMORY\n";
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

void inject_dll(std::string& file, int size) {
    const char name[] = { "C:\\Users\\Omer Cohen\\Documents\\Programming\\Actual sandbox sln\\inlineHook\\Debug\\inlineHook.dll" };
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
    pass_to_memory_limiter data{ pi.hProcess,size };
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