#include <Windows.h>
#include <iostream>
#include "Header.h"
void DisplayInfo(BYTE* buffer, DWORD size);

bool WriteProcessIDToBuffer() {
	HANDLE hFile = CreateFileA(
		"C:\\temp\\id.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "failed to open file to write process ID with code " << GetLastError() << '\n';
		return false;
	}
	std::cout << GetCurrentProcessId() << '\n';
	DWORD processID = GetCurrentProcessId();
	char procID[10];
	sprintf_s(procID, "%d", processID);
	std::cout << procID << '\n';
	if (!WriteFile(
		hFile,
		(LPCVOID)procID,
		sizeof(DWORD),
		NULL,
		NULL
	)) {
		std::cout << "failed writing to file process ID wtih code " << GetLastError() << '\n';
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);

}

DWORD WINAPI f(LPVOID lpParameter) {
	std::cout << "inside new funcution for thread\n";
	return 1;
}


int main() {

	if (!WriteProcessIDToBuffer()) {
		return 1;
	}
	HANDLE hThread = CreateThread(NULL, 0, f, NULL, 0, NULL);
	if (hThread == NULL) {
		std::cout << "thread creation failed with error: " << GetLastError() << '\n';
		return 1;
	}
	std::cout << "when would you like to continue? ";
	int x;
	std::cin >> x;
	std::cin >> x;



	auto hFile = ::CreateFile(L"\\\\.\\SysMon", GENERIC_READ | GENERIC_WRITE, 0,
		nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open file\n";
		return 1;
	}

	BYTE* buffer = new BYTE[1 << 16]; // 64KB buffer
	int count=0;
	std::cout << "started reading\n";
	int x1 = 1 << 16;
	std::cout << x1 << '\n';
	while (true) {
		DWORD bytes;
		if (!::ReadFile(hFile, buffer, x1, &bytes, nullptr)) {
			std::cout << "Failed to read\n";
			return 1;
		}
		else {
			std::cout << "read from driver " << bytes << " bytes\n";
		}
		if (bytes != 0)
			DisplayInfo(buffer, bytes);
		::Sleep(200);
	}
}

void DisplayTime(const LARGE_INTEGER& time) {
	SYSTEMTIME st;
	::FileTimeToSystemTime((FILETIME*)&time, &st);
	printf("%02d:%02d:%02d.%03d: ",
		st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}


void DisplayInfo(BYTE* buffer, DWORD size) {
	auto count = size;
	while (count > 0) {
		auto header = (ItemHeader*)buffer;
		switch (header->Type) {
		case ItemType::ProcessExit:
		{
			DisplayTime(header->Time);
			auto info = (ProcessExitInfo*)buffer;
			printf("Process %d Exited\n", info->ProcessId);
			break;
		}
		case ItemType::ProcessCreate:
		{
			/*DisplayTime(header->Time);
			auto info = (ProcessCreateInfo*)buffer;
			std::wstring commandline((WCHAR*)(buffer + info->CommandLineOffset),
				info->CommandLineLength);
			printf("Process %d Created. Command line: %ws\n", info->ProcessId,
				commandline.c_str());*/
			break;
		}
		case ItemType::ThreadCreate:
		{
			DisplayTime(header->Time);
			auto info = (ThreadCreateExitInfo*)buffer;
			printf("Thread %d Created in process %d\n",
				info->ThreadId, info->ProcessId);
			break;
		}
		case ItemType::ThreadExit:
		{
			DisplayTime(header->Time);
			auto info = (ThreadCreateExitInfo*)buffer;
			printf("Thread %d Exited from process %d\n",
				info->ThreadId, info->ProcessId);
			break;
		}

		default:
			break;
		}
		buffer += header->Size;
		count -= header->Size;
	}
}
