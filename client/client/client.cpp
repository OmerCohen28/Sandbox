#include <iostream>
#include <string>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#define _file_to_read_path_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\POC\\client\\client\\virus.exe"
#define _path_to_write_log_ "C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\POC\\client\\log.txt"

void get_log_from_server(SOCKET sock);

std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}
int main()
{
	/*HANDLE gggfile = CreateFileA(
		"D:\\c++ programs\\POC\\client\\client\\omer.exe",
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (gggfile == INVALID_HANDLE_VALUE) {
		std::cout << "didnt creaste file";
	}
	else {
		std::cout << "file created!";
	}
	return 1;*/





	std::wcout << "my directyory is " << ExePath() << '\n';
	WSADATA wsaData = { 0 };
	int iResult{ 0 };

	//wsastartup
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed: " << iResult << '\n';
		return 1;
	}
	//creating socket
	SOCKET sock{ socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) };
	if (sock == INVALID_SOCKET) {
		std::cout << "socket creation failed\n";
		WSACleanup();
		return 1;
	}
	std::string addr;
	std::cout << "enter adress to connect to: ";
	std::cin >> addr;
	std::cout << '\n';
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
	saServer.sin_port = htons(50501);
	//connecting to server
	iResult = connect(sock, (SOCKADDR*)&saServer, sizeof(saServer));
	if (iResult == SOCKET_ERROR) {
		std::cout << "error connecting to server\n";
		return 1;
	}
		LARGE_INTEGER fileSize{ 0 };

		//opening the file to send
		HANDLE file = CreateFileA(
			_file_to_read_path_,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (file == INVALID_HANDLE_VALUE) {
			std::cout << "file opening failed with code: " << GetLastError() << '\n';
			return 1;
		}

		//getting the size of the file so i can read him
		if (!GetFileSizeEx(file, &fileSize)) {
			std::cout << "getting file size failed with code: " << GetLastError() << '\n';
			return 1;
		}
		std::cout << "the file size is " << fileSize.QuadPart;
		char* buffer = new char[fileSize.QuadPart];
		//reading the .exe file
		if (!ReadFile(
			file,
			buffer,
			fileSize.QuadPart,
			NULL,
			NULL
		)) {
			std::cout << "reading file failed with code: " << GetLastError() << '\n';
			return 1;
		}

		//sending size of file to server
		int len = std::to_string(static_cast<int>(fileSize.QuadPart)).length();
		char* size = new char[len + 1] {};
		sprintf(size, "%d", (int)fileSize.QuadPart);
		*(size + len) = 'x';
		iResult = send(sock, size, len + 1, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "failed to send data\n";
		}

		//sending actual file to client
		iResult = send(sock, buffer, fileSize.QuadPart, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "failed to send data\n";
		}

		get_log_from_server(sock);

}

void get_log_from_server(SOCKET sock) {

	char* msg = new char[14] {"hello server!"};
	int iResult = send(sock, msg, 14, 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "failed to send hello server with error " << WSAGetLastError();
		return;
	}
	std::cout << "sent hello to server\n";
	//getting log size
	char* buf = new char[15];
	while (true) {
		iResult = recv(sock, buf, 15, 0);
		std::cout << "got data\n";
		if (iResult == SOCKET_ERROR) {
			std::cout << "failed to read data 1 with error " << WSAGetLastError() << '\n';
			char msg[] = "send again";
			send(sock, msg, 11, 0);
		}
		else {
			char msg[] = "no needddd";
			send(sock, msg, 11, 0);
			std::cout << "sent no need file size again\n";
			break;
		}
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
	std::cout << "the actual log size is: " << fileSize << '\n';

	char* fileContent = new char[fileSize] {};
	int count = 0;
	while (true) {
		++count;
		if (count == 10) { return; }
		//getting actual log
		iResult = recv(sock, fileContent, fileSize, 0);
		std::cout << "got data\n";
		if (iResult == SOCKET_ERROR) {
			std::cout << "failed to read data 2\n";
			std::cout << "error code: " << WSAGetLastError();
			char msg[] = "send again";
			send(sock, msg, 11, 0);
		}
		else {
			char msg[] = "no needddd";
			send(sock, msg, 11, 0);
			std::cout << "sent no need file content again\n";
			break;
		}
	}
	DeleteFileA(_path_to_write_log_);
	HANDLE file = CreateFileA(
		_path_to_write_log_,
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "opening virus file to write to failed with error " << GetLastError();
		return;
	}
	//writing the log contents to the actual file
	if (!WriteFile(
		file,
		fileContent,
		fileSize,
		NULL,
		NULL
	)) {
		std::cout << "failed to create new exe";
		return;
	}
}
