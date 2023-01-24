#pragma once
#ifdef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

#include <vector>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "newFunctions.h"

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;


extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

void set_up_hook();
void mylog(char* buf, int size);
void mylog1(const char* buf, int size);

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
		for (int i{ 0 }; i < (int)Functions::max_functions_number; ++i) {
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
		case Functions::CreateFileW:return "CreateFileW"; break;
		case Functions::DeleteFileA:return "DeleteFileA"; break;
		case Functions::DeleteFileW:return "DeleteFileW"; break;
		case Functions::ReadFile:return "ReadFile"; break;
		case Functions::ReadFileEx:return"ReadFileEx"; break;
		case Functions::WriteFile:return"WriteFile"; break;
		case Functions::WriteFileEx:return"WriteFileEx"; break;
		case Functions::WriteFileGather:return"WriteFileGather"; break;
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
		case Functions::CreateFileW:return &newFunctions::newCreateFileW; break;
		case Functions::DeleteFileA:return &newFunctions::newDeleteFileA; break;
		case Functions::DeleteFileW:return &newFunctions::newDeleteFileW; break;
		case Functions::ReadFile:return &newFunctions::newReadFile; break;
		case Functions::ReadFileEx:return &newFunctions::newReadFileEx; break;
		case Functions::WriteFile:return &newFunctions::newWriteFile; break;
		case Functions::WriteFileEx:return nullptr; break;
		case Functions::WriteFileGather:return nullptr; break;
		case Functions::send:return &newFunctions::newsend; break;
		case Functions::recv:return &newFunctions::newrecv; break;
		case Functions::RegCreateKeyExA:return &newFunctions::newRegCreateKeyExA; break;
		case Functions::RegDeleteKeyA:return &newFunctions::newRegDeleteKeyA; break;
		case Functions::RegDeleteKeyExA:return &newFunctions::newRegDeleteKeyExA; break;
		}

	}

};
