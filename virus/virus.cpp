#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

void test_sock();
void test_read_write_cratefile();

int main()
{
	std::cout << "its new me!\n";
	Sleep(2000);
	test_read_write_cratefile();
	test_sock();

	//LoadLibraryA("D:\\c++ programs\\POC\\inlineHook\\Debug\\inlineHook.dll");

}

//sending/receiving data works!
void test_sock() {

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //call in the winsock DLL (it's needed for some reason LUL try to read more bout it)
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup function failed with error: %d\n", iResult);
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "socket creation failed\n";
		wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
		return;
	}

	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = inet_addr("192.168.0.120");
	saServer.sin_port = htons(50500);
	iResult = connect(sock, (SOCKADDR*)&saServer, sizeof(saServer));
	if (iResult == SOCKET_ERROR) {
		std::cout << "error connecting to server\n";
		return;
	}
	char* buf = new char[13]{ "hello world!" };
	iResult = send(sock, buf, 13, 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "failed to send data\n";
	}
	delete[] buf;

	buf = new char[15];
	iResult = recv(sock, buf, 15, 0);
	std::cout << "got data\n";
	if (iResult == SOCKET_ERROR) {
		std::cout << "failed to read data\n";
		return;
	}
	std::cout << buf;
}


void test(HANDLE& file) {
	char* name = new char[100];
	GetFinalPathNameByHandleA(file, name, 100, 0);
	std::cout << name << '\n';
}

void test_read_write_cratefile() {
	HANDLE file = CreateFileA(
		"..\\test.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << " from virus nope\n";
	}
	char* buf = new char[13]{ "nami swannn\n" };
	//WriteFile(file, buf, 100, NULL, NULL);
	std::cout << WriteFile(file, buf, 12, NULL, NULL) << '\n';
	SetFilePointer(
		file,
		0,
		NULL,
		FILE_BEGIN
	);
	//test(file);
	std::cout << "wrote to file\n";
	delete[] buf;
	char* readbuf = new char[10];
	std::cout << ReadFile(
		file,
		readbuf,
		10,
		NULL,
		NULL
	) << '\n';
	std::cout << readbuf;
}

