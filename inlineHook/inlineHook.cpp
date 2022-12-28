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
void mylog(char* buf, int size);


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


class Hook {
public:
	enum class Functions {
		CreateFileA,
		CreateFileW,
		DeleteFileA,
		DeleteFileW,
		ReadFile,
		ReadFileEx,
		WriteFile,
		WriteFileEx,
		WriteFileGather,
		send,
		recv,
		RegCreateKeyExA,
		RegDeleteKeyA,
		RegDeleteKeyExA,
		max_functions_number
	};

	static void set_up_vars() {
		HINSTANCE* hLib{ &hLibFiles };
		for (int i{ 0 };i < (int)Functions::max_functions_number;++i) {
			if (i == (int)Functions::send) {
				hLib = &hLibSock;
			}
			if (i == (int)Functions::RegCreateKeyExA) {
				hLib = &hLibReg;
			}
			CHAR* tmp_og_bytes = new char[6];
			FARPROC tmp_hooked_addr{};
			tmp_hooked_addr = GetProcAddress(*hLib, get_new_func_name(Functions(i)).c_str());
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)tmp_hooked_addr, tmp_og_bytes, 6, NULL);
			original_bytes.push_back(tmp_og_bytes);
			hooked_addr.push_back(tmp_hooked_addr);
		}

		if (!DeleteFileA("..\\log.txt")) {
			std::cout << "couldn't delete log.txt\n";
		}
		time(&begin);
	}

	Functions func_to_hook{};


	void deploy_hook() {
		VOID* myFncAdrr;
		CHAR patch[6] = { 0 };
		myFncAdrr = get_new_fnc_pointer();
		memcpy_s(patch, 1, "\x68", 1);
		memcpy_s(patch + 1, 4, &myFncAdrr, 4);
		memcpy_s(patch + 5, 1, "\xC3", 1);
		std::cout << "inside set up hook\n";
		std::cout << patch << '\n';
		std::cout << sizeof(patch) << '\n';

		WriteProcessMemory(GetCurrentProcess(), (LPVOID)hooked_addr[(int)func_to_hook], patch, 6, NULL);
	}


	Hook(Functions func) : func_to_hook{ func } {}

private:

	static std::string get_new_func_name(Functions func) {
		switch (func) {
		case Functions::CreateFileA: return "CreateFileA"; break;
		case Functions::CreateFileW:return "CreateFileW";break;
		case Functions::DeleteFileA:return "DeleteFileA";break;
		case Functions::DeleteFileW:return "DeleteFileW";break;
		case Functions::ReadFile:return "ReadFile";break;
		case Functions::ReadFileEx:return"ReadFileEx";break;
		case Functions::WriteFile:return"WriteFile";break;
		case Functions::WriteFileEx:return"WriteFileEx";break;
		case Functions::WriteFileGather:return"WriteFileGather";break;
		case Functions::send:return"send"; break;
		case Functions::recv:return "recv"; break;
		case Functions::RegCreateKeyExA:return "RegCreateKeyExA"; break;
		case Functions::RegDeleteKeyA:return "RegDeleteKeyA"; break;
		case Functions::RegDeleteKeyExA:return "RegDeleteKeyExA"; break;
		}
	}

	void* get_new_fnc_pointer() {
		switch (func_to_hook) {
		case Functions::CreateFileA: return &newFunctions::newCreateFileA; break;
		case Functions::CreateFileW:return &newFunctions::newCreateFileW;break;
		case Functions::DeleteFileA:return &newFunctions::newDeleteFileA;break;
		case Functions::DeleteFileW:return &newFunctions::newDeleteFileW;break;
		case Functions::ReadFile:return &newFunctions::newReadFile;break;
		case Functions::ReadFileEx:return &newFunctions::newReadFileEx;break;
		case Functions::WriteFile:return &newFunctions::newWriteFile;break;
		case Functions::WriteFileEx:return nullptr;break;
		case Functions::WriteFileGather:return nullptr;break;
		case Functions::send:return &newFunctions::newsend; break;
		case Functions::recv:return &newFunctions::newrecv; break;
		case Functions::RegCreateKeyExA:return &newFunctions::newRegCreateKeyExA; break;
		case Functions::RegDeleteKeyA:return &newFunctions::newRegDeleteKeyA; break;
		case Functions::RegDeleteKeyExA:return &newFunctions::newRegDeleteKeyExA; break;
		}

	}

};

namespace newFunctions {

	HANDLE __stdcall newCreateFileA(
		LPCSTR lpFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		DWORD  dwCreationDisposition,
		DWORD dwFlagsAndAttributes,
		HANDLE hTemplateFile
	) {
		std::cout << "inside hook function\n";
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::CreateFileA],
			original_bytes[(int)Hook::Functions::CreateFileA], 6, NULL);
		std::cout << "unloaded hook\n";
		HANDLE file;
		if (!IsMyCall) {
			file = CreateFileA(
				"..\\hooked.txt",
				dwDesiredAccess,
				dwShareMode,
				lpSecurityAttributes,
				dwCreationDisposition,
				dwFlagsAndAttributes,
				hTemplateFile
			);
		}
		else {
			file = CreateFileA(
				lpFileName,
				dwDesiredAccess,
				dwShareMode,
				lpSecurityAttributes,
				dwCreationDisposition,
				dwFlagsAndAttributes,
				hTemplateFile
			);
		}

		Hook reset_hook{ Hook::Functions::CreateFileA };
		reset_hook.deploy_hook();

		if (!IsMyCall) {
			time(&end);
			std::string* msg = new std::string{ "---------------\nhooked from CreateFileA\n---------------\n\n" };

			msg->append("time called since start (s) : ");

			time_t elapsed = end - begin;
			std::stringstream ss;
			ss << elapsed;
			std::string ts = ss.str();

			msg->append(ts);

			msg->append("\narguemtns given to function -\n");
			msg->append("File Name: ");
			msg->append(std::string((char*)lpFileName));
			msg->append("\n\n");
			mylog1(msg->c_str(), msg->size());
		}

		return file;
	}

	HANDLE __stdcall newCreateFileW(
		LPCWSTR lpFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		DWORD  dwCreationDisposition,
		DWORD dwFlagsAndAttributes,
		HANDLE hTemplateFile
	) {
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::CreateFileW],
			original_bytes[(int)Hook::Functions::CreateFileW], 6, NULL);
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

		Hook reset_hook{ Hook::Functions::CreateFileW };
		reset_hook.deploy_hook();

		return file;
	}

	BOOL __stdcall newDeleteFileA(
		LPCSTR lpFileName
	) {
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileA],
			original_bytes[(int)Hook::Functions::DeleteFileA], 6, NULL);

		Hook reset_hook{ Hook::Functions::DeleteFileA };
		reset_hook.deploy_hook();

		return true;
	}

	BOOL __stdcall newDeleteFileW(
		LPCWSTR lpFileName
	) {
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileW],
			original_bytes[(int)Hook::Functions::DeleteFileW], 6, NULL);

		Hook reset_hook{ Hook::Functions::DeleteFileW };
		reset_hook.deploy_hook();

		return true;
	}

	BOOL __stdcall newReadFile(
		HANDLE hFile,
		LPVOID lpBuffer,
		DWORD nNumberOfBytesToRead,
		LPDWORD lpNumberOfBytesRead,
		LPOVERLAPPED lpOverlapped
	) {
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::ReadFile],
			original_bytes[(int)Hook::Functions::ReadFile], 6, NULL);
		/*HANDLE file = CreateFileA(
			"..\\hooked.txt",
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			4,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);*/
		BOOL result = ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);

		Hook reset_hook{ Hook::Functions::ReadFile };
		reset_hook.deploy_hook();

		return result;
	}

	BOOL __stdcall newReadFileEx(
		HANDLE hFile,
		LPVOID lpBuffer,
		DWORD nNumberOfBytesToRead,
		LPOVERLAPPED lpOverlapped,
		LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	) {
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::ReadFileEx],
			original_bytes[(int)Hook::Functions::ReadFileEx], 6, NULL);

		BOOL result = ReadFileEx(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);

		Hook reset_hook{ Hook::Functions::ReadFileEx };
		reset_hook.deploy_hook();

		return result;
	}

	BOOL __stdcall newWriteFile(
		HANDLE hFile,
		LPCVOID lpBuffer,
		DWORD nNumberOfBytesToWrite,
		LPDWORD lpNumberOfBytesWritten,
		LPOVERLAPPED lpOverlapped
	) {
		//unhook function
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::WriteFile],
			original_bytes[(int)Hook::Functions::WriteFile], 6, NULL);
		BOOL result;
		if (!IsMyCall) {
			const char msg[7] = "hooked";
			char* hooked = new char[nNumberOfBytesToWrite + 7] {};
			std::cout << "copying\n";
			strcpy_s(hooked, 7, msg);
			strcpy_s(hooked + 6, nNumberOfBytesToWrite + 1, (CHAR*)lpBuffer);
			std::cout << hooked << '\n';
			result = WriteFile(hFile, hooked, nNumberOfBytesToWrite + 7, lpNumberOfBytesWritten, lpOverlapped);
			std::cout << "wrote from hooked\n";
			delete[] hooked;
		}
		else {
			result = WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
		}
		Hook reset_hook{ Hook::Functions::WriteFile };
		reset_hook.deploy_hook();

		if (!IsMyCall) {
			time(&end);

			std::string* msg = new std::string{ "---------------\nhooked from WriteFile\n---------------\n\n" };
			msg->append("time called since start (s) : ");

			time_t elapsed = end - begin;
			std::stringstream ss;
			ss << elapsed;
			std::string ts = ss.str();

			msg->append(ts);

			msg->append("\narguemtns given to function -\n");
			msg->append("Handle Location: ");
			std::ostringstream oss;
			oss << hFile;
			msg->append(oss.str());
			msg->append("\nData buffer: ");
			msg->append(std::string((char*)lpBuffer));
			msg->append("\n");

			mylog1(msg->c_str(), msg->size());
		}

		return result;
	}

	//add writefileEx after writefile hook proves to work

	int WSAAPI __stdcall newsend(
		SOCKET s,
		const char* buf,
		int len,
		int flags
	) {
		//unhook func
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::send],
			original_bytes[(int)Hook::Functions::send], 6, NULL);

		const char msg[7] = "hooked";
		char* hooked = new char[len + 7] {};
		std::cout << "copying\n";
		strcpy_s(hooked, 7, msg);
		strcpy_s(hooked + 6, len, (CHAR*)buf);
		std::cout << "finished copying vars\n";

		int result = send(s, hooked, len + 7, flags);

		Hook reset_hook{ Hook::Functions::send };
		reset_hook.deploy_hook();

		if (!IsMyCall) {
			time(&end);
			std::string* msg = new std::string{ "---------------\nhooked socket.send\n---------------\n\n" };
			msg->append("time called since start (s) : ");

			time_t elapsed = end - begin;
			std::stringstream ss;
			ss << elapsed;
			std::string ts = ss.str();

			msg->append(ts);

			msg->append("\narguemtns given to function -\n");
			msg->append("Handle Location: ");
			std::ostringstream oss;
			oss << s;
			msg->append(oss.str());
			msg->append("\nData buffer: ");
			msg->append(std::string((char*)buf));
			msg->append("\n");


			mylog1(msg->c_str(), msg->size());
		}

		return result;
	}

	int WSAAPI __stdcall newrecv(
		SOCKET s,
		char* buf,
		int len,
		int flags
	) {
		//unhook func
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::recv],
			original_bytes[(int)Hook::Functions::recv], 6, NULL);
		std::cout << "in hooked recv\n";
		char* new_msg = new char[len];
		char tmp = 'o';
		for (int i{ 0 }; i < len; ++i) {
			new_msg[i] = tmp;
		}
		memccpy(buf, new_msg, 0, len);
		Hook reset_hook{ Hook::Functions::recv };
		reset_hook.deploy_hook();

		if (!IsMyCall) {
			time(&end);

			std::string* msg = new std::string{ "---------------\nhooked socket.recv\n---------------\n\n" };

			msg->append("time called since start (s) : ");

			time_t elapsed = end - begin;
			std::stringstream ss;
			ss << elapsed;
			std::string ts = ss.str();

			msg->append(ts);

			msg->append("\narguemtns given to function -\n");
			msg->append("Handle Location: ");
			std::ostringstream oss;
			oss << s;
			msg->append(oss.str());
			msg->append("\n");


			mylog1(msg->c_str(), msg->size());
		}
		return 0;
	}

	LSTATUS __stdcall newRegCreateKeyExA(
		HKEY hKey,
		LPCSTR lpSubKey,
		DWORD Reserved,
		LPSTR lpClass,
		DWORD dwOptions,
		REGSAM samDesired,
		const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		PHKEY phkResult,
		LPDWORD lpdwDisposition
	) {
		//unhook func
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::RegCreateKeyExA],
			original_bytes[(int)Hook::Functions::RegCreateKeyExA], 6, NULL);
		time(&end);

		std::string* msg = new std::string{ "---------------\nhooked RegCreateKeyExA\n---------------\n\n" };

		msg->append("time called since start (s) : ");

		time_t elapsed = end - begin;
		std::stringstream ss;
		ss << elapsed;
		std::string ts = ss.str();

		msg->append(ts);

		msg->append("\narguemtns given to function -\n");
		msg->append("Handle Location: ");
		std::ostringstream oss;
		oss << hKey;
		msg->append(oss.str());
		msg->append("\nkey: ");
		msg->append(std::to_string((char)*lpSubKey));
		msg->append("\nclass: ");
		msg->append(std::to_string((char)*lpClass));

		msg->append("\n");


		mylog1(msg->c_str(), msg->size());

		Hook reset_hook{ Hook::Functions::RegCreateKeyExA };
		reset_hook.deploy_hook();

		return ERROR_SUCCESS;
	}

	LSTATUS __stdcall newRegDeleteKeyA(HKEY hKey, LPCSTR lpSubKey) {
		//unhook func
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyA],
			original_bytes[(int)Hook::Functions::RegDeleteKeyA], 6, NULL);

		time(&end);

		std::string* msg = new std::string{ "---------------\nhooked RegDeleteKeyA\n---------------\n\n" };

		msg->append("time called since start (s) : ");

		time_t elapsed = end - begin;
		std::stringstream ss;
		ss << elapsed;
		std::string ts = ss.str();

		msg->append(ts);

		msg->append("\narguemtns given to function -\n");
		msg->append("Handle Location: ");
		std::ostringstream oss;
		oss << hKey;
		msg->append(oss.str());
		msg->append("\nkey: ");
		msg->append(std::to_string((char)*lpSubKey));

		msg->append("\n");


		mylog1(msg->c_str(), msg->size());


		Hook reset_hook{ Hook::Functions::RegDeleteKeyA };
		reset_hook.deploy_hook();

		return ERROR_SUCCESS;

	}

	LSTATUS __stdcall newRegDeleteKeyExA(
		HKEY hKey,
		LPCSTR lpSubKey,
		REGSAM samDesired,
		DWORD Reserved
	) {
		//unhook func
		WriteProcessMemory(GetCurrentProcess(),
			(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyExA],
			original_bytes[(int)Hook::Functions::RegDeleteKeyExA], 6, NULL);
		std::cout << "dkjeisdfjiasdlfjilsfas";
		time(&end);

		std::string* msg = new std::string{ "---------------\nhooked RegDeleteKeyExA\n---------------\n\n" };

		msg->append("time called since start (s) : ");

		time_t elapsed = end - begin;
		std::stringstream ss;
		ss << elapsed;
		std::string ts = ss.str();

		msg->append(ts);

		msg->append("\narguemtns given to function -\n");
		msg->append("Handle Location: ");
		std::ostringstream oss;
		oss << hKey;
		msg->append(oss.str());
		msg->append("\nkey: ");
		msg->append(std::to_string((char)*lpSubKey));

		msg->append("\n");


		mylog1(msg->c_str(), msg->size());


		Hook reset_hook{ Hook::Functions::RegDeleteKeyExA };
		reset_hook.deploy_hook();

		return ERROR_SUCCESS;
	}

};


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