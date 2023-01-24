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
#include "newFunctions.h"
#include <cstring>
#include <sstream>
#include <time.h>





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

namespace newFunctions {}


CHAR noriginal_bytes[6];
FARPROC nhooked_addr;
HANDLE __stdcall new_func(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD  dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
) {

	//unhook function
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)nhooked_addr, noriginal_bytes, 6, NULL);
	constexpr char msg[] = { "finished hooking function" };
	HANDLE file = CreateFileA(
		"..\\hooked.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	return file;
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

void set_up_hook() {
	HINSTANCE hLib;
	VOID* myFncAdrr;
	CHAR patch[6] = { 0 };

	hLib = LoadLibraryA("kernel32.dll");
	nhooked_addr = GetProcAddress(hLib, "CreateFileA");

	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)nhooked_addr, noriginal_bytes, 6, NULL);
	myFncAdrr = &new_func;

	memcpy_s(patch, 1, "\x68", 1);
	memcpy_s(patch + 1, 4, &myFncAdrr, 4);
	memcpy_s(patch + 5, 1, "\xC3", 1);


	WriteProcessMemory(GetCurrentProcess(), (LPVOID)nhooked_addr, patch, 6, NULL);
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
		Hook{ Hook::Functions::CreateFileA }.deploy_hook();
		std::cout << "finished deploying createfilea hook\n";
		//Hook{ Hook::Functions::CreateFileW }.deploy_hook();
		//Hook{ Hook::Functions::DeleteFileA }.deploy_hook();
		//Hook{ Hook::Functions::DeleteFileW }.deploy_hook();
		Hook{ Hook::Functions::ReadFile }.deploy_hook();
		//Hook{ Hook::Functions::ReadFileEx }.deploy_hook();
		Hook{ Hook::Functions::WriteFile }.deploy_hook();
		Hook{ Hook::Functions::send }.deploy_hook();
		Hook{ Hook::Functions::recv }.deploy_hook();
		Hook{ Hook::Functions::RegCreateKeyExA }.deploy_hook();
		Hook{ Hook::Functions::RegDeleteKeyExA }.deploy_hook();


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