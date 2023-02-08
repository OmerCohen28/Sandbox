#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#define DLL_EXPORT
#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <sstream>
#include <time.h>
#include <vector>
#include <cstdio>
#include <cstdint>
#include "codeGeneratedFunctionsFileSystem.h"
#include "codeGeneratedFunctionsRegistry.h"
#include "codeGeneratedFunctionsSockets.h"

#define _my_addr_ "192.168.0.120"




std::vector<CHAR*> original_bytes{};
std::vector<FARPROC> hooked_addr{};
time_t begin, end;


HINSTANCE hLibFiles{ LoadLibraryA("kernel32.dll") };
HINSTANCE hLibSock{ LoadLibraryA("Ws2_32.dll") };
HINSTANCE hLibReg{ LoadLibraryA("Advapi32.dll") };

HANDLE LOGfile = CreateFileA(
	"..\\log.txt",
	GENERIC_READ | GENERIC_WRITE,
	0,
	NULL,
	4,
	FILE_ATTRIBUTE_NORMAL,
	NULL
);
bool IsMyCall = false;


void mylog1(const char* buf, int size) {
	IsMyCall = true;
	std::cout << "called my log with msg " << buf << '\n';
	/*static HANDLE file = CreateFileA(
		"..\\log.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);*/
	if (LOGfile == INVALID_HANDLE_VALUE) {
		std::cout << "from mylog nope\n";
		return;
	}
	WriteFile(LOGfile, buf, size, NULL, NULL);
	IsMyCall = false;
	//delete[] buf;
}

void mylog(char* buf, int size) {
	IsMyCall = true;
	std::cout << "called my log with msg " << buf << '\n';
	/*static HANDLE file = CreateFileA(
		"..\\log.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);*/
	if (LOGfile == INVALID_HANDLE_VALUE) {
		std::cout << "from mylog nope\n";
		return;
	}
	WriteFile(LOGfile, buf, size, NULL, NULL);
	IsMyCall = false;
	//delete[] buf;
}


namespace newFunctions {}

SOCKET* SetFunctionsToHookSocket() {
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
	saServer.sin_port = htons(55544);
	iResult = connect(*sock, (SOCKADDR*)&saServer, sizeof(saServer));
	if (iResult == SOCKET_ERROR) {
		std::cout << "error connecting to server\n";
		return nullptr;
	}
	return sock;
}

std::vector<std::string>* getFunctionsToHook() {
	SOCKET* sock = SetFunctionsToHookSocket();
	if(sock){}
	else {
		std::cout << "Error connecting to injectDll server\nterminating\n";
		TerminateProcess(GetCurrentProcess(), 1);
	}
	std::vector<std::string>* vec = new std::vector<std::string>;
	int iResult;
	char* buffer;
	do {
		char size;
		iResult = recv(*sock, &size, 1, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "Error receving size from injectDll server\nterminating\n";
			TerminateProcess(GetCurrentProcess(), 1);
		}

		int i_size = atoi(&size);

		if (i_size == -1) {
			break;
		}

		buffer = new char[i_size];
		iResult = recv(*sock, buffer, i_size, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "Error receving function from injectDll server\nterminating\n";
			TerminateProcess(GetCurrentProcess(), 1);
		}

		vec->push_back(std::string(buffer));

	} while (true);

	return vec;

}



BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved) // Reserved
{
	char* msg;
	HANDLE hMutex{ CreateMutexA(
NULL,
FALSE,
"myMutex"
) };

	auto vec = getFunctionsToHook();

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		//set_up_hook();
		std::cout << "enterd---------------\n";
		WaitForSingleObject(hMutex, INFINITE);
		std::cout << "got mutex :DDDDDDDD\n";
		msg = new char[50] {"---------------\nstarted hooking\n---------------\n\n"};
		Hook::set_up_vars();
		mylog(msg, 49);
		std::cout << "finished setting up vars\n";
		

		for (auto item : *vec) {
			std::cout << item << '\n';
		}


	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		ReleaseMutex(hMutex);
		CloseHandle(hMutex);
		std::cout << "relaed mutex^^^^^^^^^^^^^^^^\n";
		break;
	}
	return TRUE;
}