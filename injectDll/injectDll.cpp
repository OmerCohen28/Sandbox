#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define dad
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "injectDll.h"
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

#define _path_to_virus_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Actual sandbox sln\\virus\\Debug\\virus.exe"
#define _my_addr_ "192.168.0.120"

#ifdef mom
#define _path_to_virus_ "D:\\Actual sandbox sln\\virus\\Debug\\virus.exe"
#else
#define _path_to_virus_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Actual sandbox sln\\virus\\Debug\\virus.exe"
#endif


SOCKET* SetSocketUp() {
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
    saServer.sin_addr.S_un.S_addr = inet_addr(_my_addr_);
    //InetPton(AF_INET, (PCWSTR)_my_addr_, &saServer.sin_addr.S_un.S_addr);
    saServer.sin_port = htons(50505);
    iResult = connect(*sock, (SOCKADDR*)&saServer, sizeof(saServer));
    if (iResult == SOCKET_ERROR) {
        std::cout << "error connecting to server\n";
        return nullptr;
    }
    return sock;
}

bool CheckInput(SOCKET& sock, const char* buf, int size) {
    std::cout << "verifier got " << buf << '\n';
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
    std::cout << "code is: " << code << '\n';
    if (code == 1) {
        return true;
    }
    return false;

}

void GetFunctionsToHook(SOCKET* sock) {
    std::cout << "Enter the function name you would like to use, dont forget to use capital letters!\n";
    std::cout << "Alternitavly you can select one of these function families:\n";
    std::cout << "fs - File System\nsock - Sockets and communication\nreg - registry\n";
    std::cout << "enter \"stop\" if you are finished\n";
    do {
        std::string* func = new std::string;
        std::cout << "function name: ";
        std::cin >> *func;
        std::cout << '\n';
        if (CheckInput(*sock, func->c_str(), func->size())) {
        }
        else {
            if (strstr(func->data(),"stop")!=NULL) { break; }
            std::cout << "Invalid function name of function family\n";
            std::cout << "you entered: " << func->data() << '\n';
        }

    } while (true);
    closesocket(*sock);
}


int main()
{
    SOCKET* sock = SetSocketUp();
    if (*sock == INVALID_SOCKET || *sock == NULL || sock == nullptr) {
        std::cout << "error connecting to python server\n";
        return 1;
    }

    while (true) {
        std::cout << "what file would you like to run?\n";
        std::cout << "type \"stop\" if you would like to stop execution,\ntype defualt to run the default virus provided by the program\n";
        std::cout << "path: ";
        std::string file{};
        //std::cin >> file;
        std::getline(std::cin, file);
        std::cout << file.c_str() << '\n';
        std::cout << "what is the max size you want to allow for the process? (in MB): ";
        int size;
        std::cin >> size;
        if (file == "stop") {
            break;
        }
        GetFunctionsToHook(sock);
        if (file == "default") {
            std::string path{ _path_to_virus_ };
            inject_dll(path, size);
        }
        else {
            inject_dll(file, size);
        }
    }
    std::cout << "thank you for using SafeBox :)\n";
    return 0;
}
