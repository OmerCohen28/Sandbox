#include <iostream>
#include <string>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#define _injectDllPath_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\POC\\injectDll\\Debug\\injectDll.exe"
#define _path_to_log_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\POC\\server\\log.txt"

void send_log_info_to_client(SOCKET sock);


std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}
int main()
{
	//std::wstring path = ExePath();
	//std::wcout << "my directordy is " << path;
	//return 1;
	//starting wsadata
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cout << "wsastartup failed with code: " << iResult << '\n';
		return 1;
	}

	//creating socket
	SOCKET listenSocket{ socket(AF_INET,SOCK_STREAM,IPPROTO_TCP) };
	if (listenSocket == INVALID_SOCKET) {
		std::cout << "listen socket creation failed with error: " << WSAGetLastError() << '\n';
		WSACleanup();
		return 1;
	}
	std::string addr;
	std::cout << "enter adress to bind to: ";
	std::cin >> addr;
	std::cout << '\n';
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
	service.sin_port = htons(50501);

	//binding socket
	if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind failed with error: " << WSAGetLastError() << '\n';
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	if (listen(listenSocket, 1) == SOCKET_ERROR) {
		std::cout << "listen failed with error: " << WSAGetLastError() << '\n';
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "waiting for connection...\n";
	SOCKET acceptSocket{ accept(listenSocket,NULL,NULL) };

	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "accept failed with error: " << WSAGetLastError() << '\n';
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "client connected\n";
	closesocket(listenSocket);

	//getting file size
	char* buf = new char[15];
	iResult = recv(acceptSocket, buf, 15, 0);
	std::cout << "got data\n";
	if (iResult == SOCKET_ERROR) {
		std::cout << "failed to read data 1 with error " << WSAGetLastError() << '\n';
		return 1;
	}
	std::cout << "the size buffer i got is " << buf << '\n';
	//converting size to actual int
	int len{ 0 };
	for (int i{ 0 }; i < 15; ++i) {
		if (*(buf + i) == 'x') {
			break;
		}
		++len;
	}
	char* new_buf = new char[len] {};
	for (int i{ 0 }; i < len; ++i) {
		*(new_buf + i) = *(buf + i);
	}
	int fileSize = std::stoi(std::string(new_buf));
	std::cout << "the actual file size is: " <<fileSize << '\n';

	//getting actual file
	char* fileContent = new char[fileSize] {};
	iResult = recv(acceptSocket, fileContent, fileSize, 0);
	std::cout << "got data\n";
	if (iResult == SOCKET_ERROR) {
		std::cout << "failed to read data 2\n";
		std::cout << "error code: " << WSAGetLastError();
		return 1;
	}
	std::cout << fileContent;

	HANDLE file = CreateFileA(
		"..\\..\\injectDll\\Debug\\virus.exe",
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "opening virus file to write to failed with error " << GetLastError();
		return 1;
	}
	//writing the file contents to the actual file
	if (!WriteFile(
		file,
		fileContent,
		fileSize,
		NULL,
		NULL
	)) {
		std::cout << "failed to create new exe";
		return 1;
	}

	std::cout << "wow!!!!";
	CloseHandle(file);
	//mutex to sync when injectDLL is done and i can procceed
	HANDLE hMutex{ CreateMutexA(
		NULL,
		FALSE,
		"myMutex"
) };

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	char cmd[]{_injectDllPath_ };
	if (!CreateProcessA(
		cmd,
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
		std::cout << "failed to create injectDLL process with error: " << GetLastError() << '\n';
		std::cout << "path was " << cmd;
		return 1;
	}
	std::cout << "waitng for thread to finish\n";
	WaitForSingleObject(pi.hThread, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	std::cout << "waiting for mutex to free\n";
	WaitForSingleObject(hMutex, INFINITE);
	send_log_info_to_client(acceptSocket);

	CloseHandle(hMutex);
}


void send_log_info_to_client(SOCKET sock) {
	std::cout << "started sending log\n";
	char* msg = new char[14] {};
	int iResult = recv(sock, msg, 14, 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "failed to recv hello from client with error " << WSAGetLastError();
		return;
	}
	std::cout << "got from client " << msg << '\n';


	LARGE_INTEGER fileSize{ 0 };

	//opening the log to send
	HANDLE file = CreateFileA(
		_path_to_log_,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "opening log failed with code: " << GetLastError() << '\n';
		return;
	}

	//getting the size of the log so i can read him
	if (!GetFileSizeEx(file, &fileSize)) {
		std::cout << "getting log size failed with code: " << GetLastError() << '\n';
		return;
	}
	std::cout << "the log size is " << fileSize.QuadPart;
	char* buffer = new char[fileSize.QuadPart];
	//reading the log file
	if (!ReadFile(
		file,
		buffer,
		fileSize.QuadPart,
		NULL,
		NULL
	)) {
		std::cout << "reading file failed with code: " << GetLastError() << '\n';
		return;
	}

	//sending size of log to client
	int len = std::to_string(static_cast<int>(fileSize.QuadPart)).length();
	char* size = new char[len + 1] {};
	sprintf(size, "%d", (int)fileSize.QuadPart);
	*(size + len) = 'x';

	while (true) {
		iResult = send(sock, size, len + 1, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "failed to send data\n";
		}
		char msg[11]{};
		iResult = recv(sock, msg, 11, 0);
		if (iResult == SOCKET_ERROR) {;
			std::cout << "faile to recv status from client\n";
			continue;
		}
		std::cout << msg << '\n';
		if (msg  != "send again") {
			std::cout << "sent size succefully\n";
			break;
		}
	}

	//sending actual log to client
	while (true) {
		iResult = send(sock, buffer, fileSize.QuadPart, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "failed to send data\n";
		}
		char msg[11]{};
		iResult = recv(sock, msg, 11, 0);
		if (iResult == SOCKET_ERROR) {
			;
			std::cout << "faile to recv status from client\n";
			continue;
		}

		if (msg != "send again") {
			std::cout << "sent file succefully\n";
			break;
		}
	}
	std::cout << "sent log to client\n";
}