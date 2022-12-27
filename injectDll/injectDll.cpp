#include <iostream>
#include <Windows.h>
#define _path_to_virus_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\POC\\injectDll\\Debug\\virus.exe"


int main()
{
    const char name[] = { "C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\POC\\inlineHook\\Debug\\inlineHook.dll" };
    unsigned int len{ sizeof(name) + 1 };
    DWORD result = GetFullPathNameA(name, 0, NULL, NULL);
    char* buf = new char[result];
    result = GetFullPathNameA(name, result, buf, NULL);

    PVOID addrLoadLibrary = (PVOID)GetProcAddress(GetModuleHandleA("kernel32"), "LoadLibraryA");

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(
        _path_to_virus_,
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
        return 1;
    }
    std::cout << "created new process\n";
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
        std::cout << "here";
        DWORD err = GetLastError();
        std::cout << err;
        return 0;
    }

    if (!WriteProcessMemory(
        pi.hProcess,
        memAddr,
        buf,    
        result,
        NULL
    )) {
        DWORD err = GetLastError();
        std::cout << "sup";
        std::cout << err;
        std::cout << "eror";
        return 0;
    }
    HANDLE remote_thread = CreateRemoteThread(
        pi.hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE )addrLoadLibrary,
        memAddr,
        0,
        NULL
    );
    WaitForSingleObject(remote_thread, INFINITE);
    CloseHandle(remote_thread);
    WaitForSingleObject(pi.hProcess,INFINITE);
    CloseHandle(pi.hProcess);
    return 0;
}
