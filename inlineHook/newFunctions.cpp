#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
#include "newFunctions.h"
#include <cstring>
#include <sstream>
#include <time.h>

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;

extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

extern HANDLE LOGfile;
extern bool IsMyCall;

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

	HANDLE __stdcall newCreateFile2(
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
			(LPVOID)hooked_addr[(int)Hook::Functions::CreateFile2],
			original_bytes[(int)Hook::Functions::CreateFile2], 6, NULL);
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

		Hook reset_hook{ Hook::Functions::CreateFile2 };
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

		BOOL result = DeleteFileA(lpFileName);

		Hook reset_hook{ Hook::Functions::DeleteFileA };
		reset_hook.deploy_hook();

		return result;
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