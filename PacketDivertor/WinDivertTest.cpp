#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#include <psapi.h>
#include <shlwapi.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "windivert.h"

#define _my_addr_ "127.0.0.1"
#define MAX_PACKET_SIZE 65536

#define INET6_ADDRSTRLEN    45
DWORD WINAPI blockPackets(LPVOID lpParameter);

SOCKET* sock;
HANDLE mutex;
std::vector<UINT16> NOT_ALLOWED_PORTS;


void updatePythonProgram(UINT16 port, BOOL remove) {
    DWORD result = WaitForSingleObject(mutex, INFINITE);
    if (result == WAIT_OBJECT_0) {
        // Convert value to network byte order
        UINT16 networkValue = htons(port);
        std::cout << "added " << networkValue << " to not allowed ports\n";
        if (remove) {
            NOT_ALLOWED_PORTS.erase(std::remove(NOT_ALLOWED_PORTS.begin(), NOT_ALLOWED_PORTS.end(), networkValue), NOT_ALLOWED_PORTS.end());
            NOT_ALLOWED_PORTS.erase(std::remove(NOT_ALLOWED_PORTS.begin(), NOT_ALLOWED_PORTS.end(), port), NOT_ALLOWED_PORTS.end());
        }
        else {
            NOT_ALLOWED_PORTS.push_back(port);
            NOT_ALLOWED_PORTS.push_back(networkValue);
        }
        
        ReleaseMutex(mutex);
        
    }
    else {
        // Failed to wait for mutex
        std::cout << "waiting for mutex failed\n";
        exit(1);
    }
}

int main()
{
    NOT_ALLOWED_PORTS = {};
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

    HANDLE handle, process;
    INT16 priority = 1121;          // Arbitrary.
    const char* filter = "processId == 20100", * err_str;
    //const char* filter = "processId == 15320 || processId == 14376 || processId == 8040 || processId == 5840 || processId == 15320 || processId == 10660 || processId == 10188 || processId == 6000 || processId == 15296 || processId == 19812 || processId == 3712 || processId == 19380 || processId == 13596 || processId == 19604 || processId == 19720", * err_str;
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

    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&blockPackets, NULL, 0, NULL);
    if (hThread == NULL) {
        std::cout << "creating blocking thread failed with code " << GetLastError();
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
            updatePythonProgram(addr.Socket.LocalPort, false);
            printf("BIND");
            break;
        case WINDIVERT_EVENT_SOCKET_LISTEN:
            updatePythonProgram(addr.Socket.LocalPort, false);
            printf("LISTEN");
            break;
        case WINDIVERT_EVENT_SOCKET_CONNECT:
            updatePythonProgram(addr.Socket.LocalPort, false);
            printf("CONNECT");
            break;
        case WINDIVERT_EVENT_SOCKET_ACCEPT:
            updatePythonProgram(addr.Socket.LocalPort, false);
            printf("ACCEPT");
            break;
        case WINDIVERT_EVENT_SOCKET_CLOSE:
            updatePythonProgram(addr.Socket.LocalPort, true);
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



DWORD WINAPI blockPackets(LPVOID lpParameter) {
    HANDLE handle;
    WINDIVERT_ADDRESS addr;
    char packet[MAX_PACKET_SIZE];
    UINT packetLength;

    handle = WinDivertOpen("true", WINDIVERT_LAYER_NETWORK, 0, 0);
    if (handle == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to open Windivert handle." << std::endl;
        return 0;
    }

    std::cout << "Packet interception started. Press Ctrl+C to stop." << std::endl;

    while (true)
    {
        if (!WinDivertRecv(handle, packet, sizeof(packet), &packetLength, &addr))
        {
            std::cerr << "Failed to read packet." << std::endl;
            continue;
        }

        //UINT16 dstPort = htons(addr.Socket.LocalPort);
        UINT16 dstPort = ntohs(*(UINT16*)(packet + 2 + (packet[0] & 0x0F) * 4));


        DWORD result = WaitForSingleObject(mutex, INFINITE);
        if (result != WAIT_OBJECT_0) {
            std::cout << "Waiting for mutex failed." << std::endl;
            return 0;
        }

        if (std::find(NOT_ALLOWED_PORTS.begin(), NOT_ALLOWED_PORTS.end(), dstPort) != NOT_ALLOWED_PORTS.end())
        {
            std::cout << "Blocked packet with destination port: " << dstPort << std::endl;
            continue; // Skip forwarding the packet
        }

        ReleaseMutex(mutex);

        // Forward the packet
        if (!WinDivertSend(handle, packet, packetLength, NULL, &addr))
        {
            std::cerr << "Failed to forward packet." << std::endl;
            continue;
        }
    }

    // Close the Windivert handle
    WinDivertClose(handle);
    return 0;
}