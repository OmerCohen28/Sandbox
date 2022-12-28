#pragma once
#include <Windows.h>
namespace newFunctions {
	HANDLE __stdcall newCreateFileA(LPCSTR lpFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		DWORD  dwCreationDisposition,
		DWORD dwFlagsAndAttributes,
		HANDLE hTemplateFile);

	HANDLE __stdcall newCreateFileW(
		LPCWSTR lpFileName,
		DWORD dwDesiredAccess,
		DWORD dwShareMode,
		LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		DWORD  dwCreationDisposition,
		DWORD dwFlagsAndAttributes,
		HANDLE hTemplateFile
	);

	BOOL __stdcall newDeleteFileA(
		LPCSTR lpFileName
	);

	BOOL __stdcall newDeleteFileW(
		LPCWSTR lpFileName
	);
	BOOL __stdcall newReadFile(
		HANDLE hFile,
		LPVOID lpBuffer,
		DWORD nNumberOfBytesToRead,
		LPDWORD lpNumberOfBytesRead,
		LPOVERLAPPED lpOverlapped
	);
	BOOL __stdcall newReadFileEx(
		HANDLE hFile,
		LPVOID lpBuffer,
		DWORD nNumberOfBytesToRead,
		LPOVERLAPPED lpOverlapped,
		LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	);
	BOOL __stdcall newWriteFile(
		HANDLE hFile,
		LPCVOID lpBuffer,
		DWORD nNumberOfBytesToWrite,
		LPDWORD lpNumberOfBytesWritten,
		LPOVERLAPPED lpOverlapped
	);

	int WSAAPI __stdcall newsend(
		SOCKET s,
		const char* buf,
		int len,
		int flags
	);
	int WSAAPI __stdcall newrecv(
		SOCKET s,
		char* buf,
		int len,
		int flags
	);

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
	);
	LSTATUS __stdcall newRegDeleteKeyA(HKEY hKey, LPCSTR lpSubKey);

	LSTATUS __stdcall newRegDeleteKeyExA(
		HKEY hKey,
		LPCSTR lpSubKey,
		REGSAM samDesired,
		DWORD Reserved
	);
}