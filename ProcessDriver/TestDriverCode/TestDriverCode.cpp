#include <Windows.h>
#include <iostream>
#include "Header.h"
void DisplayInfo(BYTE* buffer, DWORD size);

int main() {
	auto hFile = ::CreateFile(L"\\\\.\\SysMon", GENERIC_READ | GENERIC_WRITE, 0,
		nullptr, OPEN_EXISTING, 0, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open file\n";
		return 1;
	}
	int x = 5;
	if (!::WriteFile(hFile,(LPCVOID)x,sizeof(int),NULL,NULL)) {
		std::cout << "Writing to driver failed\n";
		std::cout << GetLastError() << '\n';
		return 1;
	}
	BYTE* buffer = new BYTE[1 << 16]; // 64KB buffer
	int count=0;
	while (true) {
		DWORD bytes;
		if (!::ReadFile(hFile, buffer, sizeof(buffer), &bytes, nullptr)) {
			std::cout << "Failed to read\n";
			return 1;
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
