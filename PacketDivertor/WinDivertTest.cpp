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
#include <string>
#include "windivert.h"

#define _my_addr_ "127.0.0.1"
#define MAX_PACKET_SIZE 65536

#define INET6_ADDRSTRLEN    45
DWORD WINAPI blockPackets(LPVOID lpParameter);

SOCKET* sock;
HANDLE mutex;
std::vector<UINT16> NOT_ALLOWED_PORTS;

void log(std::string  msg) {

}

void updatePythonProgram(UINT16 port, BOOL remove) {
        std::cout << "got port " << port << '\n';
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

int main(int argc, char* argv[])
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
    const char* filter = "processId == 31860", * err_str;
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
        DWORD result = WaitForSingleObject(mutex, INFINITE);
        if (result != WAIT_OBJECT_0) {
            std::cout << "waiting for mutex failed\n";
            exit(1);
        }
        std::cout << "got event\nlocal port:" << addr.Socket.LocalPort << " remote port: " << addr.Socket.RemotePort << ' ';
        switch (addr.Event)
        {
        case WINDIVERT_EVENT_SOCKET_BIND:
            updatePythonProgram(addr.Socket.LocalPort, false);
            updatePythonProgram(addr.Socket.RemotePort, false);
            printf("BIND");
            break;
        case WINDIVERT_EVENT_SOCKET_LISTEN:
            updatePythonProgram(addr.Socket.LocalPort, false);
            updatePythonProgram(addr.Socket.RemotePort, false);
            printf("LISTEN");
            break;
        case WINDIVERT_EVENT_SOCKET_CONNECT:
            updatePythonProgram(addr.Socket.LocalPort, false);
            updatePythonProgram(addr.Socket.RemotePort, false);
            printf("CONNECT");
            break;
        case WINDIVERT_EVENT_SOCKET_ACCEPT:
            updatePythonProgram(addr.Socket.LocalPort, false);
            updatePythonProgram(addr.Socket.RemotePort, false);
            printf("ACCEPT");
            break;
        case WINDIVERT_EVENT_SOCKET_CLOSE:
            updatePythonProgram(addr.Socket.LocalPort, true);
            updatePythonProgram(addr.Socket.RemotePort, true);
            printf("CLOSE");
            break;
        default:
            ReleaseMutex(mutex);
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

    handle = WinDivertOpen("outbound or inbound", WINDIVERT_LAYER_NETWORK, 0, 0);
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
        PWINDIVERT_TCPHDR tcphdr = NULL;
        PWINDIVERT_UDPHDR udphdr = NULL;
        PWINDIVERT_IPHDR iphdr = NULL;
        PVOID data = NULL;
        UINT data_len;
        WinDivertHelperParsePacket(packet, packetLength, &iphdr, NULL, NULL,
            NULL, NULL, &tcphdr, &udphdr, &data, &data_len, NULL, NULL);


        //UINT16 dstPort = ntohs(*(UINT16*)(packet + 2 + (packet[0] & 0x0F) * 4));
        UINT16 srcPort;
        UINT16 dstPort;
        UINT32 dstAddr;
        UINT32 srcAddr;

        if (tcphdr != NULL) {
            dstPort = ntohs(tcphdr->DstPort);
            srcPort = ntohs(tcphdr->SrcPort);
        }
        else if (udphdr != NULL) {
            dstPort = ntohs(udphdr->DstPort);
            srcPort = ntohs(udphdr->SrcPort);
        }
        else {
            continue;
        }
        DWORD result = WaitForSingleObject(mutex, INFINITE);
        if (result != WAIT_OBJECT_0) {
            std::cout << "Waiting for mutex failed." << std::endl;
            return 0;
        }

        if (std::find(NOT_ALLOWED_PORTS.begin(), NOT_ALLOWED_PORTS.end(), dstPort) != NOT_ALLOWED_PORTS.end() || std::find(NOT_ALLOWED_PORTS.begin(), NOT_ALLOWED_PORTS.end(), srcPort) != NOT_ALLOWED_PORTS.end())
        {
            std::string logMsg = addr.Outbound == 1 ? std::string("outbound$") : std::string("inbound$");
            if (iphdr != NULL) {
                srcAddr = iphdr->SrcAddr;
                dstAddr = iphdr->DstAddr;
                char* src = new char[10];
                WinDivertHelperFormatIPv4Address(srcAddr, src, 10);                
                char* dst = new char[10];
                WinDivertHelperFormatIPv4Address(srcAddr, dst, 10);
                
                logMsg += std::string(src) + ":" + std::to_string(srcPort) + "$";
                logMsg += std::string(dst) + ":" + std::to_string(dstPort) + "$";
            }
            else {
                logMsg += "????:" + std::to_string(srcPort) + "$";
                logMsg += "????:" + std::to_string(dstPort) + "$";
            }
            if (data != NULL) {
                logMsg += std::to_string(*(LPCSTR)data) + "%";
            }
            else {
                logMsg += "%";
            }
            std::cout << logMsg << '\n';
            if (addr.Loopback) {
                std::cout << "loopback!!!\n";
            }
            if (data != NULL) {
                std::cout << "data: " << (LPSTR)data << '\n';
                std::cout << "data length: " << data_len << '\n';
            }
            if (udphdr != NULL) {
                std::cout << "normal " << udphdr->DstPort << " ntohs: " << ntohs(udphdr->DstPort) << "htons " << htons(udphdr->DstPort) << '\n';
            }
            if (tcphdr != NULL) {
                std::cout << "normal " << tcphdr->DstPort << " ntohs: " << ntohs(tcphdr->DstPort) << "htons " << htons(tcphdr->DstPort) << '\n';
                std::cout << "normal " << tcphdr->SrcPort << " ntohs: " << ntohs(tcphdr->SrcPort) << "htons " << htons(tcphdr->SrcPort) << '\n';
            }
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