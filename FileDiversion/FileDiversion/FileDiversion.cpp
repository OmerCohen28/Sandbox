#include <iostream>
#define DLL_EXPORT 
#include "FileDiversion.h"
#include <Windows.h>

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved) {
	
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: 
		//A process is loading the DLL	
		break;
	case DLL_THREAD_ATTACH:
		//A process is creating a new thread
		break;
	case DLL_THREAD_DETACH:
		//A thread exits normally
		break;
	case DLL_PROCESS_DETACH:
		//A process unloads the DLL
		break;
	
	}
	return TRUE;

}
