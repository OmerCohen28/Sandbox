#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#include <psapi.h>
#include <shlwapi.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "windivert.h"

#define _my_addr_ "192.168.0.120"

#define INET6_ADDRSTRLEN    45
SOCKET* sock;
HANDLE mutex;

SOCKET* SetPythonSocket() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return nullptr;
    }

    SOCKET* sock = new SOCKET{ socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) };
    if (*sock == INVALID_SOCKET) {
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
        return nullptr;
    }
    sockaddr_in saServer;
    saServer.sin_family = AF_INET;
    saServer.sin_addr.S_un.S_addr = inet_addr(_my_addr_);
    //InetPton(AF_INET, (PCWSTR)_my_addr_, &saServer.sin_addr.S_un.S_addr);
    saServer.sin_port = htons(50123);
    iResult = connect(*sock, (SOCKADDR*)&saServer, sizeof(saServer));
    if (iResult == SOCKET_ERROR) {
        std::cout << "error connecting to server\n";
        return nullptr;
    }
    return sock;
}

void updatePythonProgram(UINT16 port,BOOL remove) {
    DWORD result = WaitForSingleObject(mutex, INFINITE);
    if (result == WAIT_OBJECT_0) {
        // Convert value to network byte order
        UINT16 networkValue = htons(port);

        // Copy networkValue into buffer
        char buffer[sizeof(UINT16)+sizeof(char)];
        memcpy(buffer, (remove?"x":"y"), sizeof(char));
        memcpy(buffer+sizeof(char), &networkValue, sizeof(UINT16));
        send(*sock, buffer, sizeof(UINT16) + sizeof(char), 0);
        ReleaseMutex(mutex);
    } else {
        // Failed to wait for mutex
        std::cout << "waiting for mutex failed\n";
        exit(1);
    }
}

int main()
{
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.lpSecurityDescriptor = NULL;
    securityAttributes.bInheritHandle = FALSE;
    mutex = CreateMutexA(&securityAttributes, FALSE, "portMutex11");
    if (mutex == NULL) {
        // Failed to open mutex
        std::cout << "opening mutex failed\n";
        return 1;
    }
    ReleaseMutex(mutex);
    std::cout << "released mutex\n";
    sock = SetPythonSocket();
    if (sock == nullptr || *sock == INVALID_SOCKET || *sock == NULL) {
        std::cout << "error connecting to python server\n";
        TerminateProcess(GetCurrentProcess(), 1);
    }

    HANDLE handle, process;
    INT16 priority = 1121;          // Arbitrary.
    const char* filter = "processId == 8452", * err_str;
    char path[MAX_PATH + 1];
    char local_str[INET6_ADDRSTRLEN + 1], remote_str[INET6_ADDRSTRLEN + 1];
    char* filename;
    DWORD path_len;
    WINDIVERT_ADDRESS addr;

    handle = WinDivertOpen(filter, WINDIVERT_LAYER_SOCKET, priority, WINDIVERT_FLAG_SNIFF | WINDIVERT_FLAG_RECV_ONLY);
    if (handle == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_INVALID_PARAMETER &&
            !WinDivertHelperCompileFilter(filter, WINDIVERT_LAYER_SOCKET,
                NULL, 0, &err_str, NULL))
        {
            fprintf(stderr, "error: invalid filter \"%s\"\n", err_str);
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "error: failed to open the WinDivert device (%d)\n",
            GetLastError());
        return EXIT_FAILURE;
    }

    while (TRUE) {
        if (!WinDivertRecv(handle, NULL, 0, NULL, &addr))
        {
            fprintf(stderr, "failed to read packet (%d)\n", GetLastError());
            continue;
        }

        std::cout << "got event\nport:" << addr.Socket.LocalPort << ' ';
        switch (addr.Event)
        {
        case WINDIVERT_EVENT_SOCKET_BIND:
            printf("BIND");
            break;
        case WINDIVERT_EVENT_SOCKET_LISTEN:
            printf("LISTEN");
            break;
        case WINDIVERT_EVENT_SOCKET_CONNECT:
            printf("CONNECT");
            break;
        case WINDIVERT_EVENT_SOCKET_ACCEPT:
            printf("ACCEPT");
            break;
        case WINDIVERT_EVENT_SOCKET_CLOSE:
            printf("CLOSE");
            break;
        default:
            printf("???");
            break;
        }

        std::cout << '\n';

       // WinDivertSend(handle, nullptr, 0, NULL, &addr);
    }
    CloseHandle(mutex);
    return 0;
}