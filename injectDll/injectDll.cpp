#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include "injectDll.h"
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

#define _path_to_virus_ "D:\\Actual sandbox sln\\virus\\Debug\\virus.exe"


SOCKET* SetSocketUp() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return nullptr;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "socket creation failed\n";
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
        return nullptr;
    }

    sockaddr_in saServer;
    saServer.sin_family = AF_INET;
    saServer.sin_addr.S_un.S_addr = inet_addr("192.168.0.120");
    saServer.sin_port = htons(50505);
    iResult = connect(sock, (SOCKADDR*)&saServer, sizeof(saServer));
    if (iResult == SOCKET_ERROR) {
        std::cout << "error connecting to server\n";
        return nullptr;
    }
    return &sock;
}

bool CheckInput(SOCKET& sock,char* buf, int size) {
    int iResult = send(sock, buf, size, 0);
    if (iResult == SOCKET_ERROR) {
        std::cout << "failed to send data\n";
    }
    int code;
    char recv_buf[1];
    iResult = recv(sock, recv_buf, 1, 0);
    if (iResult == SOCKET_ERROR) {
        std::cout << "failed to recv data\n";
    }
    code = atoi(recv_buf);
    if (code == 1) {
        return true;
    }
    return (buf == "fs" || buf == "sock" || buf == "reg") ? true : false;

}


int main()
{
    SOCKET* sock = SetSocketUp();
    if (sock) {
        std::cout << "error connecting to python server\n";
        return 1;
    }

    while (true) {
        std::cout << "what file would you like to run?\n";
        std::cout << "type \"stop\" if you would like to stop execution,\ntype defualt to run the default virus provided by the program\n";
        std::cout << "path: ";
        std::string file{};
        std::cin >> file;
        std::cout << file.c_str() << '\n';
        std::cout << "what is the max size you want to allow for the process? (in MB): ";
        int size;
        std::cin >> size;
        if (file == "stop") {
            break;
        }
        if (file == "default") {
            std::string path{ _path_to_virus_ };
            inject_dll(path, size);
        }
        else {
            inject_dll(file,size);
        }
    }
    std::cout << "thank you for using SafeBox :)\n";
    return 0;
}
