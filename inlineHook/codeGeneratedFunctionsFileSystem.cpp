#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable : 4996)

#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <ws2tcpip.h> 
#include <locale>
#include <codecvt>
#include <ctime>
#include <iomanip>

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;

extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

extern HANDLE LOGfile;
extern bool IsMyCall;

std::string ToStringSocket(SOCKET s)
{
    SOCKADDR_IN src_addr, dst_addr;
    int src_len = sizeof(src_addr), dst_len = sizeof(dst_addr);
    std::string result;

    if (getsockname(s, (SOCKADDR*)&src_addr, &src_len) == SOCKET_ERROR) {
        result = "Error getting local endpoint address and port.";
        return result;
    }
    if (getpeername(s, (SOCKADDR*)&dst_addr, &dst_len) == SOCKET_ERROR) {
        result = "Error getting remote endpoint address and port.";
        return result;
    }

    char src_ip[16], dst_ip[16];
    inet_ntop(AF_INET, &src_addr.sin_addr, src_ip, sizeof(src_ip));
    inet_ntop(AF_INET, &dst_addr.sin_addr, dst_ip, sizeof(dst_ip));

    result = std::string(src_ip) + ":" + std::to_string(ntohs(src_addr.sin_port))
        + " -> " + std::string(dst_ip) + ":" + std::to_string(ntohs(dst_addr.sin_port));

    return result;
}

std::string sockaddrToString(const sockaddr* sa) {
    std::stringstream ss;
    if (sa->sa_family == AF_INET) {
        // IPv4
        const sockaddr_in* sin = reinterpret_cast<const sockaddr_in*>(sa);
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sin->sin_addr), ip, INET_ADDRSTRLEN);
        ss << ip << ":" << ntohs(sin->sin_port);
    }
    else if (sa->sa_family == AF_INET6) {
        // IPv6
        const sockaddr_in6* sin6 = reinterpret_cast<const sockaddr_in6*>(sa);
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(sin6->sin6_addr), ip, INET6_ADDRSTRLEN);
        ss << "[" << ip << "]:" << ntohs(sin6->sin6_port);
    }
    else {
        ss << "Unknown family type: " << sa->sa_family;
    }
    return ss.str();
}


template <typename T>
std::string generic_log(T arg) {
    if constexpr (std::is_same_v<T, int>) {
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, char*>) {
        return std::string(arg);
    }
    if constexpr (std::is_same_v < T, DWORD>) {
        return std::to_string(static_cast<unsigned long>(arg));
    }
    if constexpr (std::is_same_v < T, char>) {
        return std::string(1, arg);
    }
    if constexpr (std::is_same_v < T, LPCTSTR>) {
        std::wstring wstr(arg);
        return std::string(wstr.begin(), wstr.end());
    }
    if constexpr (std::is_same_v < T, LPCSTR>) {
        return std::string(arg);
    }
    if constexpr (std::is_same_v < T, UINT>) {
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, BYTE>) {
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, LPBYTE>) {
        std::stringstream ss;
        for (int i = 0; i < sizeof(arg); i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)arg[i];
        }
        return ss.str();
    }
    if constexpr (std::is_same_v < T, LPDWORD>) {
        return std::to_string(*arg);
    }
    if constexpr (std::is_same_v < T, SOCKET*>) {
        return ToStringSocket(*arg);
    }
    if constexpr (std::is_same_v < T, sockaddr>) {
        return sockaddrToString(&arg);
    }
    if constexpr (std::is_same_v < T, sockaddr*>) {
        return sockaddrToString(arg);
    }
    if constexpr (std::is_same_v < T, LPINT>) {
        std::stringstream ss;
        ss << *arg;
        return ss.str();
    }
    if constexpr (std::is_same_v < T, PWSTR>) {
        std::wstring wide(arg);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wide);
    }
    if constexpr (std::is_same_v < T, size_t>) {
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, long>) {
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, u_long>) {
        in_addr addr;
        addr.s_addr = arg;
        char* ip = inet_ntoa(addr);
        return std::string(ip);
    }
    if constexpr (std::is_same_v < T, timeval>) {
        char buffer[32];
        time_t now = arg.tv_sec;
        struct tm* timeinfo = localtime(&now);
        strftime(buffer, sizeof(buffer), %Y-%m-%d %H:%M:%S, timeinfo);
        return std::string(buffer);
    }
    if constexpr (std::is_same_v < T, timeval*>) {
        char buffer[32];
        time_t now = (*arg).tv_sec;
        struct tm* timeinfo = localtime(&now);
        strftime(buffer, sizeof(buffer), %Y-%m-%d %H:%M:%S, timeinfo);
        return std::string(buffer);
    }
    return "Can't Parse Data";
}

namespace newFunctions {

DWORD __stdcall newAddUsersToEncryptedFile(
    LPCWSTR                      lpFileName,
    PENCRYPTION_CERTIFICATE_LIST pEncryptionCertificates
){
            char whatToDo = WhatToDoInFunction(*"AddUsersToEncryptedFile");
            if(whatToDo == *"b"){
                std::string logMsg("AddUsersToEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pEncryptionCertificates: ") + generic_log(pEncryptionCertificates)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("AddUsersToEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pEncryptionCertificates: ") + generic_log(pEncryptionCertificates)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::AddUsersToEncryptedFile],
    	        	original_bytes[(int)Hook::Functions::AddUsersToEncryptedFile], 6, NULL);

            DWORD result = AddUsersToEncryptedFile(lpFileName,pEncryptionCertificates);
            Hook reset_hook { Hook::Functions::AddUsersToEncryptedFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newAreFileApisANSI(){
            char whatToDo = WhatToDoInFunction(*"AreFileApisANSI");
            if(whatToDo == *"b"){
                std::string logMsg("AreFileApisANSI$");
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("AreFileApisANSI$");
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::AreFileApisANSI],
    	        	original_bytes[(int)Hook::Functions::AreFileApisANSI], 6, NULL);

            BOOL result = AreFileApisANSI();
            Hook reset_hook { Hook::Functions::AreFileApisANSI};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newCheckNameLegalDOS8Dot3A(
    LPCSTR lpName,
    LPSTR  lpOemName,
    DWORD  OemNameSize,
    PBOOL  pbNameContainsSpaces,
    PBOOL  pbNameLegal
){
            char whatToDo = WhatToDoInFunction(*"CheckNameLegalDOS8Dot3A");
            if(whatToDo == *"b"){
                std::string logMsg("CheckNameLegalDOS8Dot3A$");logMsg += std::string("lpName: ") + generic_log(lpName)+std::string("$");
logMsg += std::string("lpOemName: ") + generic_log(lpOemName)+std::string("$");
logMsg += std::string("OemNameSize: ") + generic_log(OemNameSize)+std::string("$");
logMsg += std::string("pbNameContainsSpaces: ") + generic_log(pbNameContainsSpaces)+std::string("$");
logMsg += std::string("pbNameLegal: ") + generic_log(pbNameLegal)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CheckNameLegalDOS8Dot3A$");logMsg += std::string("lpName: ") + generic_log(lpName)+std::string("$");
logMsg += std::string("lpOemName: ") + generic_log(lpOemName)+std::string("$");
logMsg += std::string("OemNameSize: ") + generic_log(OemNameSize)+std::string("$");
logMsg += std::string("pbNameContainsSpaces: ") + generic_log(pbNameContainsSpaces)+std::string("$");
logMsg += std::string("pbNameLegal: ") + generic_log(pbNameLegal)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CheckNameLegalDOS8Dot3A],
    	        	original_bytes[(int)Hook::Functions::CheckNameLegalDOS8Dot3A], 6, NULL);

            BOOL result = CheckNameLegalDOS8Dot3A(lpName,lpOemName,OemNameSize,pbNameContainsSpaces,pbNameLegal);
            Hook reset_hook { Hook::Functions::CheckNameLegalDOS8Dot3A};
            reset_hook.deploy_hook();

            return result;

}
void __stdcall newCloseEncryptedFileRaw(
    PVOID pvContext
){
            char whatToDo = WhatToDoInFunction(*"CloseEncryptedFileRaw");
            if(whatToDo == *"b"){
                std::string logMsg("CloseEncryptedFileRaw$");logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CloseEncryptedFileRaw$");logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
            }
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::CloseEncryptedFileRaw],
    		original_bytes[(int)Hook::Functions::CloseEncryptedFileRaw], 6, NULL);

        CloseEncryptedFileRaw(pvContext);
        Hook reset_hook { Hook::Functions::CloseEncryptedFileRaw};
        reset_hook.deploy_hook();

}
BOOL __stdcall newCopyFile(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName,
    BOOL    bFailIfExists
){
            char whatToDo = WhatToDoInFunction(*"CopyFile");
            if(whatToDo == *"b"){
                std::string logMsg("CopyFile$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("bFailIfExists: ") + generic_log(bFailIfExists)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CopyFile$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("bFailIfExists: ") + generic_log(bFailIfExists)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CopyFile],
    	        	original_bytes[(int)Hook::Functions::CopyFile], 6, NULL);

            BOOL result = CopyFile(lpExistingFileName,lpNewFileName,bFailIfExists);
            Hook reset_hook { Hook::Functions::CopyFile};
            reset_hook.deploy_hook();

            return result;

}
HRESULT __stdcall newCopyFile2(
    PCWSTR                        pwszExistingFileName,
    PCWSTR                        pwszNewFileName,
    COPYFILE2_EXTENDED_PARAMETERS* pExtendedParameters
){
            char whatToDo = WhatToDoInFunction(*"CopyFile2");
            if(whatToDo == *"b"){
                std::string logMsg("CopyFile2$");logMsg += std::string("pwszExistingFileName: ") + generic_log(pwszExistingFileName)+std::string("$");
logMsg += std::string("pwszNewFileName: ") + generic_log(pwszNewFileName)+std::string("$");
logMsg += std::string("pExtendedParameters: ") + generic_log(pExtendedParameters)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CopyFile2$");logMsg += std::string("pwszExistingFileName: ") + generic_log(pwszExistingFileName)+std::string("$");
logMsg += std::string("pwszNewFileName: ") + generic_log(pwszNewFileName)+std::string("$");
logMsg += std::string("pExtendedParameters: ") + generic_log(pExtendedParameters)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CopyFile2],
    	        	original_bytes[(int)Hook::Functions::CopyFile2], 6, NULL);

            HRESULT result = CopyFile2(pwszExistingFileName,pwszNewFileName,pExtendedParameters);
            Hook reset_hook { Hook::Functions::CopyFile2};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newCopyFileExA(
    LPCSTR             lpExistingFileName,
    LPCSTR             lpNewFileName,
    LPPROGRESS_ROUTINE lpProgressRoutine,
    LPVOID             lpData,
    LPBOOL             pbCancel,
    DWORD              dwCopyFlags
){
            char whatToDo = WhatToDoInFunction(*"CopyFileExA");
            if(whatToDo == *"b"){
                std::string logMsg("CopyFileExA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("pbCancel: ") + generic_log(pbCancel)+std::string("$");
logMsg += std::string("dwCopyFlags: ") + generic_log(dwCopyFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CopyFileExA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("pbCancel: ") + generic_log(pbCancel)+std::string("$");
logMsg += std::string("dwCopyFlags: ") + generic_log(dwCopyFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CopyFileExA],
    	        	original_bytes[(int)Hook::Functions::CopyFileExA], 6, NULL);

            BOOL result = CopyFileExA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,pbCancel,dwCopyFlags);
            Hook reset_hook { Hook::Functions::CopyFileExA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newCopyFileTransactedA(
    LPCSTR             lpExistingFileName,
    LPCSTR             lpNewFileName,
    LPPROGRESS_ROUTINE lpProgressRoutine,
    LPVOID             lpData,
    LPBOOL             pbCancel,
    DWORD              dwCopyFlags,
    HANDLE             hTransaction
){
            char whatToDo = WhatToDoInFunction(*"CopyFileTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("CopyFileTransactedA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("pbCancel: ") + generic_log(pbCancel)+std::string("$");
logMsg += std::string("dwCopyFlags: ") + generic_log(dwCopyFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CopyFileTransactedA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("pbCancel: ") + generic_log(pbCancel)+std::string("$");
logMsg += std::string("dwCopyFlags: ") + generic_log(dwCopyFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CopyFileTransactedA],
    	        	original_bytes[(int)Hook::Functions::CopyFileTransactedA], 6, NULL);

            BOOL result = CopyFileTransactedA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,pbCancel,dwCopyFlags,hTransaction);
            Hook reset_hook { Hook::Functions::CopyFileTransactedA};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newCreateFileA(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile
){
            char whatToDo = WhatToDoInFunction(*"CreateFileA");
            if(whatToDo == *"b"){
                std::string logMsg("CreateFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("dwCreationDisposition: ") + generic_log(dwCreationDisposition)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");
logMsg += std::string("hTemplateFile: ") + generic_log(hTemplateFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("dwCreationDisposition: ") + generic_log(dwCreationDisposition)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");
logMsg += std::string("hTemplateFile: ") + generic_log(hTemplateFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateFileA],
    	        	original_bytes[(int)Hook::Functions::CreateFileA], 6, NULL);

            HANDLE result = CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
            Hook reset_hook { Hook::Functions::CreateFileA};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newCreateFile2(
    LPCWSTR                           lpFileName,
    DWORD                             dwDesiredAccess,
    DWORD                             dwShareMode,
    DWORD                             dwCreationDisposition,
    LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams
){
            char whatToDo = WhatToDoInFunction(*"CreateFile2");
            if(whatToDo == *"b"){
                std::string logMsg("CreateFile2$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("dwCreationDisposition: ") + generic_log(dwCreationDisposition)+std::string("$");
logMsg += std::string("pCreateExParams: ") + generic_log(pCreateExParams)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateFile2$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("dwCreationDisposition: ") + generic_log(dwCreationDisposition)+std::string("$");
logMsg += std::string("pCreateExParams: ") + generic_log(pCreateExParams)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateFile2],
    	        	original_bytes[(int)Hook::Functions::CreateFile2], 6, NULL);

            HANDLE result = CreateFile2(lpFileName,dwDesiredAccess,dwShareMode,dwCreationDisposition,pCreateExParams);
            Hook reset_hook { Hook::Functions::CreateFile2};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newCreateFileTransactedA(
    LPCSTR                lpFileName,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwCreationDisposition,
    DWORD                 dwFlagsAndAttributes,
    HANDLE                hTemplateFile,
    HANDLE                hTransaction,
    PUSHORT               pusMiniVersion,
    PVOID                 lpExtendedParameter
){
            char whatToDo = WhatToDoInFunction(*"CreateFileTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("CreateFileTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("dwCreationDisposition: ") + generic_log(dwCreationDisposition)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");
logMsg += std::string("hTemplateFile: ") + generic_log(hTemplateFile)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pusMiniVersion: ") + generic_log(pusMiniVersion)+std::string("$");
logMsg += std::string("lpExtendedParameter: ") + generic_log(lpExtendedParameter)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateFileTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("dwCreationDisposition: ") + generic_log(dwCreationDisposition)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");
logMsg += std::string("hTemplateFile: ") + generic_log(hTemplateFile)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pusMiniVersion: ") + generic_log(pusMiniVersion)+std::string("$");
logMsg += std::string("lpExtendedParameter: ") + generic_log(lpExtendedParameter)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateFileTransactedA],
    	        	original_bytes[(int)Hook::Functions::CreateFileTransactedA], 6, NULL);

            HANDLE result = CreateFileTransactedA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile,hTransaction,pusMiniVersion,lpExtendedParameter);
            Hook reset_hook { Hook::Functions::CreateFileTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newCreateHardLinkA(
    LPCSTR                lpFileName,
    LPCSTR                lpExistingFileName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
){
            char whatToDo = WhatToDoInFunction(*"CreateHardLinkA");
            if(whatToDo == *"b"){
                std::string logMsg("CreateHardLinkA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateHardLinkA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateHardLinkA],
    	        	original_bytes[(int)Hook::Functions::CreateHardLinkA], 6, NULL);

            BOOL result = CreateHardLinkA(lpFileName,lpExistingFileName,lpSecurityAttributes);
            Hook reset_hook { Hook::Functions::CreateHardLinkA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newCreateHardLinkTransactedA(
    LPCSTR                lpFileName,
    LPCSTR                lpExistingFileName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    HANDLE                hTransaction
){
            char whatToDo = WhatToDoInFunction(*"CreateHardLinkTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("CreateHardLinkTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateHardLinkTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateHardLinkTransactedA],
    	        	original_bytes[(int)Hook::Functions::CreateHardLinkTransactedA], 6, NULL);

            BOOL result = CreateHardLinkTransactedA(lpFileName,lpExistingFileName,lpSecurityAttributes,hTransaction);
            Hook reset_hook { Hook::Functions::CreateHardLinkTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOLEAN __stdcall newCreateSymbolicLinkA(
    LPCSTR lpSymlinkFileName,
    LPCSTR lpTargetFileName,
    DWORD  dwFlags
){
            char whatToDo = WhatToDoInFunction(*"CreateSymbolicLinkA");
            if(whatToDo == *"b"){
                std::string logMsg("CreateSymbolicLinkA$");logMsg += std::string("lpSymlinkFileName: ") + generic_log(lpSymlinkFileName)+std::string("$");
logMsg += std::string("lpTargetFileName: ") + generic_log(lpTargetFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateSymbolicLinkA$");logMsg += std::string("lpSymlinkFileName: ") + generic_log(lpSymlinkFileName)+std::string("$");
logMsg += std::string("lpTargetFileName: ") + generic_log(lpTargetFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateSymbolicLinkA],
    	        	original_bytes[(int)Hook::Functions::CreateSymbolicLinkA], 6, NULL);

            BOOLEAN result = CreateSymbolicLinkA(lpSymlinkFileName,lpTargetFileName,dwFlags);
            Hook reset_hook { Hook::Functions::CreateSymbolicLinkA};
            reset_hook.deploy_hook();

            return result;

}
BOOLEAN __stdcall newCreateSymbolicLinkTransactedA(
    LPCSTR lpSymlinkFileName,
    LPCSTR lpTargetFileName,
    DWORD  dwFlags,
    HANDLE hTransaction
){
            char whatToDo = WhatToDoInFunction(*"CreateSymbolicLinkTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("CreateSymbolicLinkTransactedA$");logMsg += std::string("lpSymlinkFileName: ") + generic_log(lpSymlinkFileName)+std::string("$");
logMsg += std::string("lpTargetFileName: ") + generic_log(lpTargetFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("CreateSymbolicLinkTransactedA$");logMsg += std::string("lpSymlinkFileName: ") + generic_log(lpSymlinkFileName)+std::string("$");
logMsg += std::string("lpTargetFileName: ") + generic_log(lpTargetFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::CreateSymbolicLinkTransactedA],
    	        	original_bytes[(int)Hook::Functions::CreateSymbolicLinkTransactedA], 6, NULL);

            BOOLEAN result = CreateSymbolicLinkTransactedA(lpSymlinkFileName,lpTargetFileName,dwFlags,hTransaction);
            Hook reset_hook { Hook::Functions::CreateSymbolicLinkTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newDecryptFileA(
    LPCSTR lpFileName,
    DWORD  dwReserved
){
            char whatToDo = WhatToDoInFunction(*"DecryptFileA");
            if(whatToDo == *"b"){
                std::string logMsg("DecryptFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwReserved: ") + generic_log(dwReserved)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("DecryptFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwReserved: ") + generic_log(dwReserved)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::DecryptFileA],
    	        	original_bytes[(int)Hook::Functions::DecryptFileA], 6, NULL);

            BOOL result = DecryptFileA(lpFileName,dwReserved);
            Hook reset_hook { Hook::Functions::DecryptFileA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newDeleteFileA(
    LPCSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"DeleteFileA");
            if(whatToDo == *"b"){
                std::string logMsg("DeleteFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("DeleteFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileA],
    	        	original_bytes[(int)Hook::Functions::DeleteFileA], 6, NULL);

            BOOL result = DeleteFileA(lpFileName);
            Hook reset_hook { Hook::Functions::DeleteFileA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newDeleteFileTransactedA(
    LPCSTR lpFileName,
    HANDLE hTransaction
){
            char whatToDo = WhatToDoInFunction(*"DeleteFileTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("DeleteFileTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("DeleteFileTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileTransactedA],
    	        	original_bytes[(int)Hook::Functions::DeleteFileTransactedA], 6, NULL);

            BOOL result = DeleteFileTransactedA(lpFileName,hTransaction);
            Hook reset_hook { Hook::Functions::DeleteFileTransactedA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newDuplicateEncryptionInfoFile(
    LPCWSTR                     SrcFileName,
    LPCWSTR                     DstFileName,
    DWORD                       dwCreationDistribution,
    DWORD                       dwAttributes,
    const LPSECURITY_ATTRIBUTES lpSecurityAttributes
){
            char whatToDo = WhatToDoInFunction(*"DuplicateEncryptionInfoFile");
            if(whatToDo == *"b"){
                std::string logMsg("DuplicateEncryptionInfoFile$");logMsg += std::string("SrcFileName: ") + generic_log(SrcFileName)+std::string("$");
logMsg += std::string("DstFileName: ") + generic_log(DstFileName)+std::string("$");
logMsg += std::string("dwCreationDistribution: ") + generic_log(dwCreationDistribution)+std::string("$");
logMsg += std::string("dwAttributes: ") + generic_log(dwAttributes)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("DuplicateEncryptionInfoFile$");logMsg += std::string("SrcFileName: ") + generic_log(SrcFileName)+std::string("$");
logMsg += std::string("DstFileName: ") + generic_log(DstFileName)+std::string("$");
logMsg += std::string("dwCreationDistribution: ") + generic_log(dwCreationDistribution)+std::string("$");
logMsg += std::string("dwAttributes: ") + generic_log(dwAttributes)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::DuplicateEncryptionInfoFile],
    	        	original_bytes[(int)Hook::Functions::DuplicateEncryptionInfoFile], 6, NULL);

            DWORD result = DuplicateEncryptionInfoFile(SrcFileName,DstFileName,dwCreationDistribution,dwAttributes,lpSecurityAttributes);
            Hook reset_hook { Hook::Functions::DuplicateEncryptionInfoFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newEncryptFileA(
    LPCSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"EncryptFileA");
            if(whatToDo == *"b"){
                std::string logMsg("EncryptFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("EncryptFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::EncryptFileA],
    	        	original_bytes[(int)Hook::Functions::EncryptFileA], 6, NULL);

            BOOL result = EncryptFileA(lpFileName);
            Hook reset_hook { Hook::Functions::EncryptFileA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newEncryptionDisable(
    LPCWSTR DirPath,
    BOOL    Disable
){
            char whatToDo = WhatToDoInFunction(*"EncryptionDisable");
            if(whatToDo == *"b"){
                std::string logMsg("EncryptionDisable$");logMsg += std::string("DirPath: ") + generic_log(DirPath)+std::string("$");
logMsg += std::string("Disable: ") + generic_log(Disable)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("EncryptionDisable$");logMsg += std::string("DirPath: ") + generic_log(DirPath)+std::string("$");
logMsg += std::string("Disable: ") + generic_log(Disable)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::EncryptionDisable],
    	        	original_bytes[(int)Hook::Functions::EncryptionDisable], 6, NULL);

            BOOL result = EncryptionDisable(DirPath,Disable);
            Hook reset_hook { Hook::Functions::EncryptionDisable};
            reset_hook.deploy_hook();

            return result;

}
BOOL newFileEncryptionStatusA(
    LPCSTR  lpFileName,
    LPDWORD lpStatus
){
            char whatToDo = WhatToDoInFunction(*"FileEncryptionStatusA");
            if(whatToDo == *"b"){
                std::string logMsg("FileEncryptionStatusA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpStatus: ") + generic_log(lpStatus)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FileEncryptionStatusA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpStatus: ") + generic_log(lpStatus)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FileEncryptionStatusA],
    	        	original_bytes[(int)Hook::Functions::FileEncryptionStatusA], 6, NULL);

            BOOL result = FileEncryptionStatusA(lpFileName,lpStatus);
            Hook reset_hook { Hook::Functions::FileEncryptionStatusA};
            reset_hook.deploy_hook();

            return result;

}
BOOL newFindClose(
    HANDLE hFindFile
){
            char whatToDo = WhatToDoInFunction(*"FindClose");
            if(whatToDo == *"b"){
                std::string logMsg("FindClose$");logMsg += std::string("hFindFile: ") + generic_log(hFindFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindClose$");logMsg += std::string("hFindFile: ") + generic_log(hFindFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindClose],
    	        	original_bytes[(int)Hook::Functions::FindClose], 6, NULL);

            BOOL result = FindClose(hFindFile);
            Hook reset_hook { Hook::Functions::FindClose};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstFileA(
    LPCSTR             lpFileName,
    LPWIN32_FIND_DATAA lpFindFileData
){
            char whatToDo = WhatToDoInFunction(*"FindFirstFileA");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstFileA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileA],
    	        	original_bytes[(int)Hook::Functions::FindFirstFileA], 6, NULL);

            HANDLE result = FindFirstFileA(lpFileName,lpFindFileData);
            Hook reset_hook { Hook::Functions::FindFirstFileA};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstFileExA(
    LPCSTR             lpFileName,
    FINDEX_INFO_LEVELS fInfoLevelId,
    LPVOID             lpFindFileData,
    FINDEX_SEARCH_OPS  fSearchOp,
    LPVOID             lpSearchFilter,
    DWORD              dwAdditionalFlags
){
            char whatToDo = WhatToDoInFunction(*"FindFirstFileExA");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstFileExA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");
logMsg += std::string("fSearchOp: ") + generic_log(fSearchOp)+std::string("$");
logMsg += std::string("lpSearchFilter: ") + generic_log(lpSearchFilter)+std::string("$");
logMsg += std::string("dwAdditionalFlags: ") + generic_log(dwAdditionalFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstFileExA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");
logMsg += std::string("fSearchOp: ") + generic_log(fSearchOp)+std::string("$");
logMsg += std::string("lpSearchFilter: ") + generic_log(lpSearchFilter)+std::string("$");
logMsg += std::string("dwAdditionalFlags: ") + generic_log(dwAdditionalFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileExA],
    	        	original_bytes[(int)Hook::Functions::FindFirstFileExA], 6, NULL);

            HANDLE result = FindFirstFileExA(lpFileName,fInfoLevelId,lpFindFileData,fSearchOp,lpSearchFilter,dwAdditionalFlags);
            Hook reset_hook { Hook::Functions::FindFirstFileExA};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstFileNameTransactedW(
    LPCWSTR lpFileName,
    DWORD   dwFlags,
    LPDWORD StringLength,
    PWSTR   LinkName,
    HANDLE  hTransaction
){
            char whatToDo = WhatToDoInFunction(*"FindFirstFileNameTransactedW");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstFileNameTransactedW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("StringLength: ") + generic_log(StringLength)+std::string("$");
logMsg += std::string("LinkName: ") + generic_log(LinkName)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstFileNameTransactedW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("StringLength: ") + generic_log(StringLength)+std::string("$");
logMsg += std::string("LinkName: ") + generic_log(LinkName)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileNameTransactedW],
    	        	original_bytes[(int)Hook::Functions::FindFirstFileNameTransactedW], 6, NULL);

            HANDLE result = FindFirstFileNameTransactedW(lpFileName,dwFlags,StringLength,LinkName,hTransaction);
            Hook reset_hook { Hook::Functions::FindFirstFileNameTransactedW};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstFileNameW(
    LPCWSTR lpFileName,
    DWORD   dwFlags,
    LPDWORD StringLength,
    PWSTR   LinkName
){
            char whatToDo = WhatToDoInFunction(*"FindFirstFileNameW");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstFileNameW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("StringLength: ") + generic_log(StringLength)+std::string("$");
logMsg += std::string("LinkName: ") + generic_log(LinkName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstFileNameW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("StringLength: ") + generic_log(StringLength)+std::string("$");
logMsg += std::string("LinkName: ") + generic_log(LinkName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileNameW],
    	        	original_bytes[(int)Hook::Functions::FindFirstFileNameW], 6, NULL);

            HANDLE result = FindFirstFileNameW(lpFileName,dwFlags,StringLength,LinkName);
            Hook reset_hook { Hook::Functions::FindFirstFileNameW};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstFileTransactedA(
    LPCSTR             lpFileName,
    FINDEX_INFO_LEVELS fInfoLevelId,
    LPVOID             lpFindFileData,
    FINDEX_SEARCH_OPS  fSearchOp,
    LPVOID             lpSearchFilter,
    DWORD              dwAdditionalFlags,
    HANDLE             hTransaction
){
            char whatToDo = WhatToDoInFunction(*"FindFirstFileTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstFileTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");
logMsg += std::string("fSearchOp: ") + generic_log(fSearchOp)+std::string("$");
logMsg += std::string("lpSearchFilter: ") + generic_log(lpSearchFilter)+std::string("$");
logMsg += std::string("dwAdditionalFlags: ") + generic_log(dwAdditionalFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstFileTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");
logMsg += std::string("fSearchOp: ") + generic_log(fSearchOp)+std::string("$");
logMsg += std::string("lpSearchFilter: ") + generic_log(lpSearchFilter)+std::string("$");
logMsg += std::string("dwAdditionalFlags: ") + generic_log(dwAdditionalFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileTransactedA],
    	        	original_bytes[(int)Hook::Functions::FindFirstFileTransactedA], 6, NULL);

            HANDLE result = FindFirstFileTransactedA(lpFileName,fInfoLevelId,lpFindFileData,fSearchOp,lpSearchFilter,dwAdditionalFlags,hTransaction);
            Hook reset_hook { Hook::Functions::FindFirstFileTransactedA};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstStreamTransactedW(
    LPCWSTR            lpFileName,
    STREAM_INFO_LEVELS InfoLevel,
    LPVOID             lpFindStreamData,
    DWORD              dwFlags,
    HANDLE             hTransaction
){
            char whatToDo = WhatToDoInFunction(*"FindFirstStreamTransactedW");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstStreamTransactedW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("InfoLevel: ") + generic_log(InfoLevel)+std::string("$");
logMsg += std::string("lpFindStreamData: ") + generic_log(lpFindStreamData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstStreamTransactedW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("InfoLevel: ") + generic_log(InfoLevel)+std::string("$");
logMsg += std::string("lpFindStreamData: ") + generic_log(lpFindStreamData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstStreamTransactedW],
    	        	original_bytes[(int)Hook::Functions::FindFirstStreamTransactedW], 6, NULL);

            HANDLE result = FindFirstStreamTransactedW(lpFileName,InfoLevel,lpFindStreamData,dwFlags,hTransaction);
            Hook reset_hook { Hook::Functions::FindFirstStreamTransactedW};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newFindFirstStreamW(
    LPCWSTR            lpFileName,
    STREAM_INFO_LEVELS InfoLevel,
    LPVOID             lpFindStreamData,
    DWORD              dwFlags
){
            char whatToDo = WhatToDoInFunction(*"FindFirstStreamW");
            if(whatToDo == *"b"){
                std::string logMsg("FindFirstStreamW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("InfoLevel: ") + generic_log(InfoLevel)+std::string("$");
logMsg += std::string("lpFindStreamData: ") + generic_log(lpFindStreamData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindFirstStreamW$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("InfoLevel: ") + generic_log(InfoLevel)+std::string("$");
logMsg += std::string("lpFindStreamData: ") + generic_log(lpFindStreamData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstStreamW],
    	        	original_bytes[(int)Hook::Functions::FindFirstStreamW], 6, NULL);

            HANDLE result = FindFirstStreamW(lpFileName,InfoLevel,lpFindStreamData,dwFlags);
            Hook reset_hook { Hook::Functions::FindFirstStreamW};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newFindNextFileA(
    HANDLE             hFindFile,
    LPWIN32_FIND_DATAA lpFindFileData
){
            char whatToDo = WhatToDoInFunction(*"FindNextFileA");
            if(whatToDo == *"b"){
                std::string logMsg("FindNextFileA$");logMsg += std::string("hFindFile: ") + generic_log(hFindFile)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindNextFileA$");logMsg += std::string("hFindFile: ") + generic_log(hFindFile)+std::string("$");
logMsg += std::string("lpFindFileData: ") + generic_log(lpFindFileData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindNextFileA],
    	        	original_bytes[(int)Hook::Functions::FindNextFileA], 6, NULL);

            BOOL result = FindNextFileA(hFindFile,lpFindFileData);
            Hook reset_hook { Hook::Functions::FindNextFileA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newFindNextFileNameW(
    HANDLE  hFindStream,
    LPDWORD StringLength,
    PWSTR   LinkName
){
            char whatToDo = WhatToDoInFunction(*"FindNextFileNameW");
            if(whatToDo == *"b"){
                std::string logMsg("FindNextFileNameW$");logMsg += std::string("hFindStream: ") + generic_log(hFindStream)+std::string("$");
logMsg += std::string("StringLength: ") + generic_log(StringLength)+std::string("$");
logMsg += std::string("LinkName: ") + generic_log(LinkName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindNextFileNameW$");logMsg += std::string("hFindStream: ") + generic_log(hFindStream)+std::string("$");
logMsg += std::string("StringLength: ") + generic_log(StringLength)+std::string("$");
logMsg += std::string("LinkName: ") + generic_log(LinkName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindNextFileNameW],
    	        	original_bytes[(int)Hook::Functions::FindNextFileNameW], 6, NULL);

            BOOL result = FindNextFileNameW(hFindStream,StringLength,LinkName);
            Hook reset_hook { Hook::Functions::FindNextFileNameW};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newFindNextStreamW(
    HANDLE hFindStream,
    LPVOID lpFindStreamData
){
            char whatToDo = WhatToDoInFunction(*"FindNextStreamW");
            if(whatToDo == *"b"){
                std::string logMsg("FindNextStreamW$");logMsg += std::string("hFindStream: ") + generic_log(hFindStream)+std::string("$");
logMsg += std::string("lpFindStreamData: ") + generic_log(lpFindStreamData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FindNextStreamW$");logMsg += std::string("hFindStream: ") + generic_log(hFindStream)+std::string("$");
logMsg += std::string("lpFindStreamData: ") + generic_log(lpFindStreamData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FindNextStreamW],
    	        	original_bytes[(int)Hook::Functions::FindNextStreamW], 6, NULL);

            BOOL result = FindNextStreamW(hFindStream,lpFindStreamData);
            Hook reset_hook { Hook::Functions::FindNextStreamW};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newFlushFileBuffers(
    HANDLE hFile
){
            char whatToDo = WhatToDoInFunction(*"FlushFileBuffers");
            if(whatToDo == *"b"){
                std::string logMsg("FlushFileBuffers$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FlushFileBuffers$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::FlushFileBuffers],
    	        	original_bytes[(int)Hook::Functions::FlushFileBuffers], 6, NULL);

            BOOL result = FlushFileBuffers(hFile);
            Hook reset_hook { Hook::Functions::FlushFileBuffers};
            reset_hook.deploy_hook();

            return result;

}
void __stdcall newFreeEncryptionCertificateHashList(
    PENCRYPTION_CERTIFICATE_HASH_LIST pUsers
){
            char whatToDo = WhatToDoInFunction(*"FreeEncryptionCertificateHashList");
            if(whatToDo == *"b"){
                std::string logMsg("FreeEncryptionCertificateHashList$");logMsg += std::string("pUsers: ") + generic_log(pUsers)+std::string("$");

                log(logMsg);
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("FreeEncryptionCertificateHashList$");logMsg += std::string("pUsers: ") + generic_log(pUsers)+std::string("$");

                log(logMsg);
            }
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::FreeEncryptionCertificateHashList],
    		original_bytes[(int)Hook::Functions::FreeEncryptionCertificateHashList], 6, NULL);

        FreeEncryptionCertificateHashList(pUsers);
        Hook reset_hook { Hook::Functions::FreeEncryptionCertificateHashList};
        reset_hook.deploy_hook();

}
BOOL __stdcall newGetBinaryTypeA(
    LPCSTR  lpApplicationName,
    LPDWORD lpBinaryType
){
            char whatToDo = WhatToDoInFunction(*"GetBinaryTypeA");
            if(whatToDo == *"b"){
                std::string logMsg("GetBinaryTypeA$");logMsg += std::string("lpApplicationName: ") + generic_log(lpApplicationName)+std::string("$");
logMsg += std::string("lpBinaryType: ") + generic_log(lpBinaryType)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetBinaryTypeA$");logMsg += std::string("lpApplicationName: ") + generic_log(lpApplicationName)+std::string("$");
logMsg += std::string("lpBinaryType: ") + generic_log(lpBinaryType)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetBinaryTypeA],
    	        	original_bytes[(int)Hook::Functions::GetBinaryTypeA], 6, NULL);

            BOOL result = GetBinaryTypeA(lpApplicationName,lpBinaryType);
            Hook reset_hook { Hook::Functions::GetBinaryTypeA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetCompressedFileSizeA(
    LPCSTR  lpFileName,
    LPDWORD lpFileSizeHigh
){
            char whatToDo = WhatToDoInFunction(*"GetCompressedFileSizeA");
            if(whatToDo == *"b"){
                std::string logMsg("GetCompressedFileSizeA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpFileSizeHigh: ") + generic_log(lpFileSizeHigh)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetCompressedFileSizeA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpFileSizeHigh: ") + generic_log(lpFileSizeHigh)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetCompressedFileSizeA],
    	        	original_bytes[(int)Hook::Functions::GetCompressedFileSizeA], 6, NULL);

            DWORD result = GetCompressedFileSizeA(lpFileName,lpFileSizeHigh);
            Hook reset_hook { Hook::Functions::GetCompressedFileSizeA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetCompressedFileSizeTransactedA(
    LPCSTR  lpFileName,
    LPDWORD lpFileSizeHigh,
    HANDLE  hTransaction
){
            char whatToDo = WhatToDoInFunction(*"GetCompressedFileSizeTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("GetCompressedFileSizeTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpFileSizeHigh: ") + generic_log(lpFileSizeHigh)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetCompressedFileSizeTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpFileSizeHigh: ") + generic_log(lpFileSizeHigh)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetCompressedFileSizeTransactedA],
    	        	original_bytes[(int)Hook::Functions::GetCompressedFileSizeTransactedA], 6, NULL);

            DWORD result = GetCompressedFileSizeTransactedA(lpFileName,lpFileSizeHigh,hTransaction);
            Hook reset_hook { Hook::Functions::GetCompressedFileSizeTransactedA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetFileAttributesA(
    LPCSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"GetFileAttributesA");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileAttributesA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileAttributesA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesA],
    	        	original_bytes[(int)Hook::Functions::GetFileAttributesA], 6, NULL);

            DWORD result = GetFileAttributesA(lpFileName);
            Hook reset_hook { Hook::Functions::GetFileAttributesA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetFileAttributesExA(
    LPCSTR                 lpFileName,
    GET_FILEEX_INFO_LEVELS fInfoLevelId,
    LPVOID                 lpFileInformation
){
            char whatToDo = WhatToDoInFunction(*"GetFileAttributesExA");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileAttributesExA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileAttributesExA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesExA],
    	        	original_bytes[(int)Hook::Functions::GetFileAttributesExA], 6, NULL);

            BOOL result = GetFileAttributesExA(lpFileName,fInfoLevelId,lpFileInformation);
            Hook reset_hook { Hook::Functions::GetFileAttributesExA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetFileAttributesTransactedA(
    LPCSTR                 lpFileName,
    GET_FILEEX_INFO_LEVELS fInfoLevelId,
    LPVOID                 lpFileInformation,
    HANDLE                 hTransaction
){
            char whatToDo = WhatToDoInFunction(*"GetFileAttributesTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileAttributesTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileAttributesTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("fInfoLevelId: ") + generic_log(fInfoLevelId)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesTransactedA],
    	        	original_bytes[(int)Hook::Functions::GetFileAttributesTransactedA], 6, NULL);

            BOOL result = GetFileAttributesTransactedA(lpFileName,fInfoLevelId,lpFileInformation,hTransaction);
            Hook reset_hook { Hook::Functions::GetFileAttributesTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetFileBandwidthReservation(
    HANDLE  hFile,
    LPDWORD lpPeriodMilliseconds,
    LPDWORD lpBytesPerPeriod,
    LPBOOL  pDiscardable,
    LPDWORD lpTransferSize,
    LPDWORD lpNumOutstandingRequests
){
            char whatToDo = WhatToDoInFunction(*"GetFileBandwidthReservation");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileBandwidthReservation$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpPeriodMilliseconds: ") + generic_log(lpPeriodMilliseconds)+std::string("$");
logMsg += std::string("lpBytesPerPeriod: ") + generic_log(lpBytesPerPeriod)+std::string("$");
logMsg += std::string("pDiscardable: ") + generic_log(pDiscardable)+std::string("$");
logMsg += std::string("lpTransferSize: ") + generic_log(lpTransferSize)+std::string("$");
logMsg += std::string("lpNumOutstandingRequests: ") + generic_log(lpNumOutstandingRequests)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileBandwidthReservation$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpPeriodMilliseconds: ") + generic_log(lpPeriodMilliseconds)+std::string("$");
logMsg += std::string("lpBytesPerPeriod: ") + generic_log(lpBytesPerPeriod)+std::string("$");
logMsg += std::string("pDiscardable: ") + generic_log(pDiscardable)+std::string("$");
logMsg += std::string("lpTransferSize: ") + generic_log(lpTransferSize)+std::string("$");
logMsg += std::string("lpNumOutstandingRequests: ") + generic_log(lpNumOutstandingRequests)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileBandwidthReservation],
    	        	original_bytes[(int)Hook::Functions::GetFileBandwidthReservation], 6, NULL);

            BOOL result = GetFileBandwidthReservation(hFile,lpPeriodMilliseconds,lpBytesPerPeriod,pDiscardable,lpTransferSize,lpNumOutstandingRequests);
            Hook reset_hook { Hook::Functions::GetFileBandwidthReservation};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetFileInformationByHandle(
    HANDLE                       hFile,
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation
){
            char whatToDo = WhatToDoInFunction(*"GetFileInformationByHandle");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileInformationByHandle$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileInformationByHandle$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileInformationByHandle],
    	        	original_bytes[(int)Hook::Functions::GetFileInformationByHandle], 6, NULL);

            BOOL result = GetFileInformationByHandle(hFile,lpFileInformation);
            Hook reset_hook { Hook::Functions::GetFileInformationByHandle};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetFileInformationByHandleEx(
    HANDLE                    hFile,
    FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    LPVOID                    lpFileInformation,
    DWORD                     dwBufferSize
){
            char whatToDo = WhatToDoInFunction(*"GetFileInformationByHandleEx");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileInformationByHandleEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("FileInformationClass: ") + generic_log(FileInformationClass)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");
logMsg += std::string("dwBufferSize: ") + generic_log(dwBufferSize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileInformationByHandleEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("FileInformationClass: ") + generic_log(FileInformationClass)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");
logMsg += std::string("dwBufferSize: ") + generic_log(dwBufferSize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileInformationByHandleEx],
    	        	original_bytes[(int)Hook::Functions::GetFileInformationByHandleEx], 6, NULL);

            BOOL result = GetFileInformationByHandleEx(hFile,FileInformationClass,lpFileInformation,dwBufferSize);
            Hook reset_hook { Hook::Functions::GetFileInformationByHandleEx};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetFileSize(
    HANDLE  hFile,
    LPDWORD lpFileSizeHigh
){
            char whatToDo = WhatToDoInFunction(*"GetFileSize");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileSize$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpFileSizeHigh: ") + generic_log(lpFileSizeHigh)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileSize$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpFileSizeHigh: ") + generic_log(lpFileSizeHigh)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileSize],
    	        	original_bytes[(int)Hook::Functions::GetFileSize], 6, NULL);

            DWORD result = GetFileSize(hFile,lpFileSizeHigh);
            Hook reset_hook { Hook::Functions::GetFileSize};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetFileSizeEx(
    HANDLE         hFile,
    PLARGE_INTEGER lpFileSize
){
            char whatToDo = WhatToDoInFunction(*"GetFileSizeEx");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileSizeEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpFileSize: ") + generic_log(lpFileSize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileSizeEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpFileSize: ") + generic_log(lpFileSize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileSizeEx],
    	        	original_bytes[(int)Hook::Functions::GetFileSizeEx], 6, NULL);

            BOOL result = GetFileSizeEx(hFile,lpFileSize);
            Hook reset_hook { Hook::Functions::GetFileSizeEx};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetFileType(
    HANDLE hFile
){
            char whatToDo = WhatToDoInFunction(*"GetFileType");
            if(whatToDo == *"b"){
                std::string logMsg("GetFileType$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFileType$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFileType],
    	        	original_bytes[(int)Hook::Functions::GetFileType], 6, NULL);

            DWORD result = GetFileType(hFile);
            Hook reset_hook { Hook::Functions::GetFileType};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetFinalPathNameByHandleA(
    HANDLE hFile,
    LPSTR  lpszFilePath,
    DWORD  cchFilePath,
    DWORD  dwFlags
){
            char whatToDo = WhatToDoInFunction(*"GetFinalPathNameByHandleA");
            if(whatToDo == *"b"){
                std::string logMsg("GetFinalPathNameByHandleA$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpszFilePath: ") + generic_log(lpszFilePath)+std::string("$");
logMsg += std::string("cchFilePath: ") + generic_log(cchFilePath)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFinalPathNameByHandleA$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpszFilePath: ") + generic_log(lpszFilePath)+std::string("$");
logMsg += std::string("cchFilePath: ") + generic_log(cchFilePath)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFinalPathNameByHandleA],
    	        	original_bytes[(int)Hook::Functions::GetFinalPathNameByHandleA], 6, NULL);

            DWORD result = GetFinalPathNameByHandleA(hFile,lpszFilePath,cchFilePath,dwFlags);
            Hook reset_hook { Hook::Functions::GetFinalPathNameByHandleA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetFullPathNameA(
    LPCSTR lpFileName,
    DWORD  nBufferLength,
    LPSTR  lpBuffer,
    LPSTR* lpFilePart
){
            char whatToDo = WhatToDoInFunction(*"GetFullPathNameA");
            if(whatToDo == *"b"){
                std::string logMsg("GetFullPathNameA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("lpFilePart: ") + generic_log(lpFilePart)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFullPathNameA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("lpFilePart: ") + generic_log(lpFilePart)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFullPathNameA],
    	        	original_bytes[(int)Hook::Functions::GetFullPathNameA], 6, NULL);

            DWORD result = GetFullPathNameA(lpFileName,nBufferLength,lpBuffer,lpFilePart);
            Hook reset_hook { Hook::Functions::GetFullPathNameA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetFullPathNameTransactedA(
    LPCSTR lpFileName,
    DWORD  nBufferLength,
    LPSTR  lpBuffer,
    LPSTR* lpFilePart,
    HANDLE hTransaction
){
            char whatToDo = WhatToDoInFunction(*"GetFullPathNameTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("GetFullPathNameTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("lpFilePart: ") + generic_log(lpFilePart)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetFullPathNameTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("lpFilePart: ") + generic_log(lpFilePart)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetFullPathNameTransactedA],
    	        	original_bytes[(int)Hook::Functions::GetFullPathNameTransactedA], 6, NULL);

            DWORD result = GetFullPathNameTransactedA(lpFileName,nBufferLength,lpBuffer,lpFilePart,hTransaction);
            Hook reset_hook { Hook::Functions::GetFullPathNameTransactedA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetLongPathNameA(
    LPCSTR lpszShortPath,
    LPSTR  lpszLongPath,
    DWORD  cchBuffer
){
            char whatToDo = WhatToDoInFunction(*"GetLongPathNameA");
            if(whatToDo == *"b"){
                std::string logMsg("GetLongPathNameA$");logMsg += std::string("lpszShortPath: ") + generic_log(lpszShortPath)+std::string("$");
logMsg += std::string("lpszLongPath: ") + generic_log(lpszLongPath)+std::string("$");
logMsg += std::string("cchBuffer: ") + generic_log(cchBuffer)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetLongPathNameA$");logMsg += std::string("lpszShortPath: ") + generic_log(lpszShortPath)+std::string("$");
logMsg += std::string("lpszLongPath: ") + generic_log(lpszLongPath)+std::string("$");
logMsg += std::string("cchBuffer: ") + generic_log(cchBuffer)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetLongPathNameA],
    	        	original_bytes[(int)Hook::Functions::GetLongPathNameA], 6, NULL);

            DWORD result = GetLongPathNameA(lpszShortPath,lpszLongPath,cchBuffer);
            Hook reset_hook { Hook::Functions::GetLongPathNameA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetLongPathNameTransactedA(
    LPCSTR lpszShortPath,
    LPSTR  lpszLongPath,
    DWORD  cchBuffer,
    HANDLE hTransaction
){
            char whatToDo = WhatToDoInFunction(*"GetLongPathNameTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("GetLongPathNameTransactedA$");logMsg += std::string("lpszShortPath: ") + generic_log(lpszShortPath)+std::string("$");
logMsg += std::string("lpszLongPath: ") + generic_log(lpszLongPath)+std::string("$");
logMsg += std::string("cchBuffer: ") + generic_log(cchBuffer)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetLongPathNameTransactedA$");logMsg += std::string("lpszShortPath: ") + generic_log(lpszShortPath)+std::string("$");
logMsg += std::string("lpszLongPath: ") + generic_log(lpszLongPath)+std::string("$");
logMsg += std::string("cchBuffer: ") + generic_log(cchBuffer)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetLongPathNameTransactedA],
    	        	original_bytes[(int)Hook::Functions::GetLongPathNameTransactedA], 6, NULL);

            DWORD result = GetLongPathNameTransactedA(lpszShortPath,lpszLongPath,cchBuffer,hTransaction);
            Hook reset_hook { Hook::Functions::GetLongPathNameTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetQueuedCompletionStatus(
    HANDLE       CompletionPort,
    LPDWORD      lpNumberOfBytesTransferred,
    PULONG_PTR   lpCompletionKey,
    LPOVERLAPPED* lpOverlapped,
    DWORD        dwMilliseconds
){
            char whatToDo = WhatToDoInFunction(*"GetQueuedCompletionStatus");
            if(whatToDo == *"b"){
                std::string logMsg("GetQueuedCompletionStatus$");logMsg += std::string("CompletionPort: ") + generic_log(CompletionPort)+std::string("$");
logMsg += std::string("lpNumberOfBytesTransferred: ") + generic_log(lpNumberOfBytesTransferred)+std::string("$");
logMsg += std::string("lpCompletionKey: ") + generic_log(lpCompletionKey)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("dwMilliseconds: ") + generic_log(dwMilliseconds)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetQueuedCompletionStatus$");logMsg += std::string("CompletionPort: ") + generic_log(CompletionPort)+std::string("$");
logMsg += std::string("lpNumberOfBytesTransferred: ") + generic_log(lpNumberOfBytesTransferred)+std::string("$");
logMsg += std::string("lpCompletionKey: ") + generic_log(lpCompletionKey)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("dwMilliseconds: ") + generic_log(dwMilliseconds)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetQueuedCompletionStatus],
    	        	original_bytes[(int)Hook::Functions::GetQueuedCompletionStatus], 6, NULL);

            BOOL result = GetQueuedCompletionStatus(CompletionPort,lpNumberOfBytesTransferred,lpCompletionKey,lpOverlapped,dwMilliseconds);
            Hook reset_hook { Hook::Functions::GetQueuedCompletionStatus};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetShortPathNameW(
    LPCWSTR lpszLongPath,
    LPWSTR  lpszShortPath,
    DWORD   cchBuffer
){
            char whatToDo = WhatToDoInFunction(*"GetShortPathNameW");
            if(whatToDo == *"b"){
                std::string logMsg("GetShortPathNameW$");logMsg += std::string("lpszLongPath: ") + generic_log(lpszLongPath)+std::string("$");
logMsg += std::string("lpszShortPath: ") + generic_log(lpszShortPath)+std::string("$");
logMsg += std::string("cchBuffer: ") + generic_log(cchBuffer)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetShortPathNameW$");logMsg += std::string("lpszLongPath: ") + generic_log(lpszLongPath)+std::string("$");
logMsg += std::string("lpszShortPath: ") + generic_log(lpszShortPath)+std::string("$");
logMsg += std::string("cchBuffer: ") + generic_log(cchBuffer)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetShortPathNameW],
    	        	original_bytes[(int)Hook::Functions::GetShortPathNameW], 6, NULL);

            DWORD result = GetShortPathNameW(lpszLongPath,lpszShortPath,cchBuffer);
            Hook reset_hook { Hook::Functions::GetShortPathNameW};
            reset_hook.deploy_hook();

            return result;

}
UINT __stdcall newGetTempFileNameA(
    LPCSTR lpPathName,
    LPCSTR lpPrefixString,
    UINT   uUnique,
    LPSTR  lpTempFileName
){
            char whatToDo = WhatToDoInFunction(*"GetTempFileNameA");
            if(whatToDo == *"b"){
                std::string logMsg("GetTempFileNameA$");logMsg += std::string("lpPathName: ") + generic_log(lpPathName)+std::string("$");
logMsg += std::string("lpPrefixString: ") + generic_log(lpPrefixString)+std::string("$");
logMsg += std::string("uUnique: ") + generic_log(uUnique)+std::string("$");
logMsg += std::string("lpTempFileName: ") + generic_log(lpTempFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetTempFileNameA$");logMsg += std::string("lpPathName: ") + generic_log(lpPathName)+std::string("$");
logMsg += std::string("lpPrefixString: ") + generic_log(lpPrefixString)+std::string("$");
logMsg += std::string("uUnique: ") + generic_log(uUnique)+std::string("$");
logMsg += std::string("lpTempFileName: ") + generic_log(lpTempFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetTempFileNameA],
    	        	original_bytes[(int)Hook::Functions::GetTempFileNameA], 6, NULL);

            UINT result = GetTempFileNameA(lpPathName,lpPrefixString,uUnique,lpTempFileName);
            Hook reset_hook { Hook::Functions::GetTempFileNameA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetTempPathA(
    DWORD nBufferLength,
    LPSTR lpBuffer
){
            char whatToDo = WhatToDoInFunction(*"GetTempPathA");
            if(whatToDo == *"b"){
                std::string logMsg("GetTempPathA$");logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetTempPathA$");logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetTempPathA],
    	        	original_bytes[(int)Hook::Functions::GetTempPathA], 6, NULL);

            DWORD result = GetTempPathA(nBufferLength,lpBuffer);
            Hook reset_hook { Hook::Functions::GetTempPathA};
            reset_hook.deploy_hook();

            return result;

}
BOOL newLockFile(
    HANDLE hFile,
    DWORD  dwFileOffsetLow,
    DWORD  dwFileOffsetHigh,
    DWORD  nNumberOfBytesToLockLow,
    DWORD  nNumberOfBytesToLockHigh
){
            char whatToDo = WhatToDoInFunction(*"LockFile");
            if(whatToDo == *"b"){
                std::string logMsg("LockFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwFileOffsetLow: ") + generic_log(dwFileOffsetLow)+std::string("$");
logMsg += std::string("dwFileOffsetHigh: ") + generic_log(dwFileOffsetHigh)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockLow: ") + generic_log(nNumberOfBytesToLockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockHigh: ") + generic_log(nNumberOfBytesToLockHigh)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("LockFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwFileOffsetLow: ") + generic_log(dwFileOffsetLow)+std::string("$");
logMsg += std::string("dwFileOffsetHigh: ") + generic_log(dwFileOffsetHigh)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockLow: ") + generic_log(nNumberOfBytesToLockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockHigh: ") + generic_log(nNumberOfBytesToLockHigh)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::LockFile],
    	        	original_bytes[(int)Hook::Functions::LockFile], 6, NULL);

            BOOL result = LockFile(hFile,dwFileOffsetLow,dwFileOffsetHigh,nNumberOfBytesToLockLow,nNumberOfBytesToLockHigh);
            Hook reset_hook { Hook::Functions::LockFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newLockFileEx(
    HANDLE       hFile,
    DWORD        dwFlags,
    DWORD        dwReserved,
    DWORD        nNumberOfBytesToLockLow,
    DWORD        nNumberOfBytesToLockHigh,
    LPOVERLAPPED lpOverlapped
){
            char whatToDo = WhatToDoInFunction(*"LockFileEx");
            if(whatToDo == *"b"){
                std::string logMsg("LockFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("dwReserved: ") + generic_log(dwReserved)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockLow: ") + generic_log(nNumberOfBytesToLockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockHigh: ") + generic_log(nNumberOfBytesToLockHigh)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("LockFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("dwReserved: ") + generic_log(dwReserved)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockLow: ") + generic_log(nNumberOfBytesToLockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToLockHigh: ") + generic_log(nNumberOfBytesToLockHigh)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::LockFileEx],
    	        	original_bytes[(int)Hook::Functions::LockFileEx], 6, NULL);

            BOOL result = LockFileEx(hFile,dwFlags,dwReserved,nNumberOfBytesToLockLow,nNumberOfBytesToLockHigh,lpOverlapped);
            Hook reset_hook { Hook::Functions::LockFileEx};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newMoveFile(
    LPCTSTR lpExistingFileName,
    LPCTSTR lpNewFileName
){
            char whatToDo = WhatToDoInFunction(*"MoveFile");
            if(whatToDo == *"b"){
                std::string logMsg("MoveFile$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("MoveFile$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::MoveFile],
    	        	original_bytes[(int)Hook::Functions::MoveFile], 6, NULL);

            BOOL result = MoveFile(lpExistingFileName,lpNewFileName);
            Hook reset_hook { Hook::Functions::MoveFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newMoveFileExA(
    LPCSTR lpExistingFileName,
    LPCSTR lpNewFileName,
    DWORD  dwFlags
){
            char whatToDo = WhatToDoInFunction(*"MoveFileExA");
            if(whatToDo == *"b"){
                std::string logMsg("MoveFileExA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("MoveFileExA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::MoveFileExA],
    	        	original_bytes[(int)Hook::Functions::MoveFileExA], 6, NULL);

            BOOL result = MoveFileExA(lpExistingFileName,lpNewFileName,dwFlags);
            Hook reset_hook { Hook::Functions::MoveFileExA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newMoveFileTransactedA(
    LPCSTR             lpExistingFileName,
    LPCSTR             lpNewFileName,
    LPPROGRESS_ROUTINE lpProgressRoutine,
    LPVOID             lpData,
    DWORD              dwFlags,
    HANDLE             hTransaction
){
            char whatToDo = WhatToDoInFunction(*"MoveFileTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("MoveFileTransactedA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("MoveFileTransactedA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::MoveFileTransactedA],
    	        	original_bytes[(int)Hook::Functions::MoveFileTransactedA], 6, NULL);

            BOOL result = MoveFileTransactedA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,dwFlags,hTransaction);
            Hook reset_hook { Hook::Functions::MoveFileTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newMoveFileWithProgressA(
    LPCSTR             lpExistingFileName,
    LPCSTR             lpNewFileName,
    LPPROGRESS_ROUTINE lpProgressRoutine,
    LPVOID             lpData,
    DWORD              dwFlags
){
            char whatToDo = WhatToDoInFunction(*"MoveFileWithProgressA");
            if(whatToDo == *"b"){
                std::string logMsg("MoveFileWithProgressA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("MoveFileWithProgressA$");logMsg += std::string("lpExistingFileName: ") + generic_log(lpExistingFileName)+std::string("$");
logMsg += std::string("lpNewFileName: ") + generic_log(lpNewFileName)+std::string("$");
logMsg += std::string("lpProgressRoutine: ") + generic_log(lpProgressRoutine)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::MoveFileWithProgressA],
    	        	original_bytes[(int)Hook::Functions::MoveFileWithProgressA], 6, NULL);

            BOOL result = MoveFileWithProgressA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,dwFlags);
            Hook reset_hook { Hook::Functions::MoveFileWithProgressA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newOpenEncryptedFileRawA(
    LPCSTR lpFileName,
    ULONG  ulFlags,
    PVOID* pvContext
){
            char whatToDo = WhatToDoInFunction(*"OpenEncryptedFileRawA");
            if(whatToDo == *"b"){
                std::string logMsg("OpenEncryptedFileRawA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("ulFlags: ") + generic_log(ulFlags)+std::string("$");
logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("OpenEncryptedFileRawA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("ulFlags: ") + generic_log(ulFlags)+std::string("$");
logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::OpenEncryptedFileRawA],
    	        	original_bytes[(int)Hook::Functions::OpenEncryptedFileRawA], 6, NULL);

            DWORD result = OpenEncryptedFileRawA(lpFileName,ulFlags,pvContext);
            Hook reset_hook { Hook::Functions::OpenEncryptedFileRawA};
            reset_hook.deploy_hook();

            return result;

}
HFILE __stdcall newOpenFile(
    LPCSTR     lpFileName,
    LPOFSTRUCT lpReOpenBuff,
    UINT       uStyle
){
            char whatToDo = WhatToDoInFunction(*"OpenFile");
            if(whatToDo == *"b"){
                std::string logMsg("OpenFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpReOpenBuff: ") + generic_log(lpReOpenBuff)+std::string("$");
logMsg += std::string("uStyle: ") + generic_log(uStyle)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("OpenFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpReOpenBuff: ") + generic_log(lpReOpenBuff)+std::string("$");
logMsg += std::string("uStyle: ") + generic_log(uStyle)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::OpenFile],
    	        	original_bytes[(int)Hook::Functions::OpenFile], 6, NULL);

            HFILE result = OpenFile(lpFileName,lpReOpenBuff,uStyle);
            Hook reset_hook { Hook::Functions::OpenFile};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newOpenFileById(
    HANDLE                hVolumeHint,
    LPFILE_ID_DESCRIPTOR  lpFileId,
    DWORD                 dwDesiredAccess,
    DWORD                 dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD                 dwFlagsAndAttributes
){
            char whatToDo = WhatToDoInFunction(*"OpenFileById");
            if(whatToDo == *"b"){
                std::string logMsg("OpenFileById$");logMsg += std::string("hVolumeHint: ") + generic_log(hVolumeHint)+std::string("$");
logMsg += std::string("lpFileId: ") + generic_log(lpFileId)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("OpenFileById$");logMsg += std::string("hVolumeHint: ") + generic_log(hVolumeHint)+std::string("$");
logMsg += std::string("lpFileId: ") + generic_log(lpFileId)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::OpenFileById],
    	        	original_bytes[(int)Hook::Functions::OpenFileById], 6, NULL);

            HANDLE result = OpenFileById(hVolumeHint,lpFileId,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwFlagsAndAttributes);
            Hook reset_hook { Hook::Functions::OpenFileById};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newQueryRecoveryAgentsOnEncryptedFile(
    LPCWSTR                           lpFileName,
    PENCRYPTION_CERTIFICATE_HASH_LIST* pRecoveryAgents
){
            char whatToDo = WhatToDoInFunction(*"QueryRecoveryAgentsOnEncryptedFile");
            if(whatToDo == *"b"){
                std::string logMsg("QueryRecoveryAgentsOnEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pRecoveryAgents: ") + generic_log(pRecoveryAgents)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("QueryRecoveryAgentsOnEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pRecoveryAgents: ") + generic_log(pRecoveryAgents)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::QueryRecoveryAgentsOnEncryptedFile],
    	        	original_bytes[(int)Hook::Functions::QueryRecoveryAgentsOnEncryptedFile], 6, NULL);

            DWORD result = QueryRecoveryAgentsOnEncryptedFile(lpFileName,pRecoveryAgents);
            Hook reset_hook { Hook::Functions::QueryRecoveryAgentsOnEncryptedFile};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newQueryUsersOnEncryptedFile(
    LPCWSTR                           lpFileName,
    PENCRYPTION_CERTIFICATE_HASH_LIST* pUsers
){
            char whatToDo = WhatToDoInFunction(*"QueryUsersOnEncryptedFile");
            if(whatToDo == *"b"){
                std::string logMsg("QueryUsersOnEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pUsers: ") + generic_log(pUsers)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("QueryUsersOnEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pUsers: ") + generic_log(pUsers)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::QueryUsersOnEncryptedFile],
    	        	original_bytes[(int)Hook::Functions::QueryUsersOnEncryptedFile], 6, NULL);

            DWORD result = QueryUsersOnEncryptedFile(lpFileName,pUsers);
            Hook reset_hook { Hook::Functions::QueryUsersOnEncryptedFile};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newReadEncryptedFileRaw(
    PFE_EXPORT_FUNC pfExportCallback,
    PVOID           pvCallbackContext,
    PVOID           pvContext
){
            char whatToDo = WhatToDoInFunction(*"ReadEncryptedFileRaw");
            if(whatToDo == *"b"){
                std::string logMsg("ReadEncryptedFileRaw$");logMsg += std::string("pfExportCallback: ") + generic_log(pfExportCallback)+std::string("$");
logMsg += std::string("pvCallbackContext: ") + generic_log(pvCallbackContext)+std::string("$");
logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ReadEncryptedFileRaw$");logMsg += std::string("pfExportCallback: ") + generic_log(pfExportCallback)+std::string("$");
logMsg += std::string("pvCallbackContext: ") + generic_log(pvCallbackContext)+std::string("$");
logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ReadEncryptedFileRaw],
    	        	original_bytes[(int)Hook::Functions::ReadEncryptedFileRaw], 6, NULL);

            DWORD result = ReadEncryptedFileRaw(pfExportCallback,pvCallbackContext,pvContext);
            Hook reset_hook { Hook::Functions::ReadEncryptedFileRaw};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newReadFile(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
){
            char whatToDo = WhatToDoInFunction(*"ReadFile");
            if(whatToDo == *"b"){
                std::string logMsg("ReadFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToRead: ") + generic_log(nNumberOfBytesToRead)+std::string("$");
logMsg += std::string("lpNumberOfBytesRead: ") + generic_log(lpNumberOfBytesRead)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ReadFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToRead: ") + generic_log(nNumberOfBytesToRead)+std::string("$");
logMsg += std::string("lpNumberOfBytesRead: ") + generic_log(lpNumberOfBytesRead)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ReadFile],
    	        	original_bytes[(int)Hook::Functions::ReadFile], 6, NULL);

            BOOL result = ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
            Hook reset_hook { Hook::Functions::ReadFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newReadFileEx(
    HANDLE                          hFile,
    LPVOID                          lpBuffer,
    DWORD                           nNumberOfBytesToRead,
    LPOVERLAPPED                    lpOverlapped,
    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction(*"ReadFileEx");
            if(whatToDo == *"b"){
                std::string logMsg("ReadFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToRead: ") + generic_log(nNumberOfBytesToRead)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ReadFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToRead: ") + generic_log(nNumberOfBytesToRead)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ReadFileEx],
    	        	original_bytes[(int)Hook::Functions::ReadFileEx], 6, NULL);

            BOOL result = ReadFileEx(hFile,lpBuffer,nNumberOfBytesToRead,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::ReadFileEx};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newRemoveUsersFromEncryptedFile(
    LPCWSTR                           lpFileName,
    PENCRYPTION_CERTIFICATE_HASH_LIST pHashes
){
            char whatToDo = WhatToDoInFunction(*"RemoveUsersFromEncryptedFile");
            if(whatToDo == *"b"){
                std::string logMsg("RemoveUsersFromEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pHashes: ") + generic_log(pHashes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RemoveUsersFromEncryptedFile$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("pHashes: ") + generic_log(pHashes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RemoveUsersFromEncryptedFile],
    	        	original_bytes[(int)Hook::Functions::RemoveUsersFromEncryptedFile], 6, NULL);

            DWORD result = RemoveUsersFromEncryptedFile(lpFileName,pHashes);
            Hook reset_hook { Hook::Functions::RemoveUsersFromEncryptedFile};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newReOpenFile(
    HANDLE hOriginalFile,
    DWORD  dwDesiredAccess,
    DWORD  dwShareMode,
    DWORD  dwFlagsAndAttributes
){
            char whatToDo = WhatToDoInFunction(*"ReOpenFile");
            if(whatToDo == *"b"){
                std::string logMsg("ReOpenFile$");logMsg += std::string("hOriginalFile: ") + generic_log(hOriginalFile)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ReOpenFile$");logMsg += std::string("hOriginalFile: ") + generic_log(hOriginalFile)+std::string("$");
logMsg += std::string("dwDesiredAccess: ") + generic_log(dwDesiredAccess)+std::string("$");
logMsg += std::string("dwShareMode: ") + generic_log(dwShareMode)+std::string("$");
logMsg += std::string("dwFlagsAndAttributes: ") + generic_log(dwFlagsAndAttributes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ReOpenFile],
    	        	original_bytes[(int)Hook::Functions::ReOpenFile], 6, NULL);

            HANDLE result = ReOpenFile(hOriginalFile,dwDesiredAccess,dwShareMode,dwFlagsAndAttributes);
            Hook reset_hook { Hook::Functions::ReOpenFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newReplaceFileA(
    LPCSTR lpReplacedFileName,
    LPCSTR lpReplacementFileName,
    LPCSTR lpBackupFileName,
    DWORD  dwReplaceFlags,
    LPVOID lpExclude,
    LPVOID lpReserved
){
            char whatToDo = WhatToDoInFunction(*"ReplaceFileA");
            if(whatToDo == *"b"){
                std::string logMsg("ReplaceFileA$");logMsg += std::string("lpReplacedFileName: ") + generic_log(lpReplacedFileName)+std::string("$");
logMsg += std::string("lpReplacementFileName: ") + generic_log(lpReplacementFileName)+std::string("$");
logMsg += std::string("lpBackupFileName: ") + generic_log(lpBackupFileName)+std::string("$");
logMsg += std::string("dwReplaceFlags: ") + generic_log(dwReplaceFlags)+std::string("$");
logMsg += std::string("lpExclude: ") + generic_log(lpExclude)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ReplaceFileA$");logMsg += std::string("lpReplacedFileName: ") + generic_log(lpReplacedFileName)+std::string("$");
logMsg += std::string("lpReplacementFileName: ") + generic_log(lpReplacementFileName)+std::string("$");
logMsg += std::string("lpBackupFileName: ") + generic_log(lpBackupFileName)+std::string("$");
logMsg += std::string("dwReplaceFlags: ") + generic_log(dwReplaceFlags)+std::string("$");
logMsg += std::string("lpExclude: ") + generic_log(lpExclude)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ReplaceFileA],
    	        	original_bytes[(int)Hook::Functions::ReplaceFileA], 6, NULL);

            BOOL result = ReplaceFileA(lpReplacedFileName,lpReplacementFileName,lpBackupFileName,dwReplaceFlags,lpExclude,lpReserved);
            Hook reset_hook { Hook::Functions::ReplaceFileA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newSearchPathA(
    LPCSTR lpPath,
    LPCSTR lpFileName,
    LPCSTR lpExtension,
    DWORD  nBufferLength,
    LPSTR  lpBuffer,
    LPSTR* lpFilePart
){
            char whatToDo = WhatToDoInFunction(*"SearchPathA");
            if(whatToDo == *"b"){
                std::string logMsg("SearchPathA$");logMsg += std::string("lpPath: ") + generic_log(lpPath)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpExtension: ") + generic_log(lpExtension)+std::string("$");
logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("lpFilePart: ") + generic_log(lpFilePart)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SearchPathA$");logMsg += std::string("lpPath: ") + generic_log(lpPath)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("lpExtension: ") + generic_log(lpExtension)+std::string("$");
logMsg += std::string("nBufferLength: ") + generic_log(nBufferLength)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("lpFilePart: ") + generic_log(lpFilePart)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SearchPathA],
    	        	original_bytes[(int)Hook::Functions::SearchPathA], 6, NULL);

            DWORD result = SearchPathA(lpPath,lpFileName,lpExtension,nBufferLength,lpBuffer,lpFilePart);
            Hook reset_hook { Hook::Functions::SearchPathA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetEndOfFile(
    HANDLE hFile
){
            char whatToDo = WhatToDoInFunction(*"SetEndOfFile");
            if(whatToDo == *"b"){
                std::string logMsg("SetEndOfFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetEndOfFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetEndOfFile],
    	        	original_bytes[(int)Hook::Functions::SetEndOfFile], 6, NULL);

            BOOL result = SetEndOfFile(hFile);
            Hook reset_hook { Hook::Functions::SetEndOfFile};
            reset_hook.deploy_hook();

            return result;

}
void __stdcall newSetFileApisToANSI(){
            char whatToDo = WhatToDoInFunction(*"SetFileApisToANSI");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileApisToANSI$");
                log(logMsg);
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileApisToANSI$");
                log(logMsg);
            }
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileApisToANSI],
    		original_bytes[(int)Hook::Functions::SetFileApisToANSI], 6, NULL);

        SetFileApisToANSI();
        Hook reset_hook { Hook::Functions::SetFileApisToANSI};
        reset_hook.deploy_hook();

}
void __stdcall newSetFileApisToOEM(){
            char whatToDo = WhatToDoInFunction(*"SetFileApisToOEM");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileApisToOEM$");
                log(logMsg);
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileApisToOEM$");
                log(logMsg);
            }
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileApisToOEM],
    		original_bytes[(int)Hook::Functions::SetFileApisToOEM], 6, NULL);

        SetFileApisToOEM();
        Hook reset_hook { Hook::Functions::SetFileApisToOEM};
        reset_hook.deploy_hook();

}
BOOL __stdcall newSetFileAttributesA(
    LPCSTR lpFileName,
    DWORD  dwFileAttributes
){
            char whatToDo = WhatToDoInFunction(*"SetFileAttributesA");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileAttributesA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFileAttributes: ") + generic_log(dwFileAttributes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileAttributesA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFileAttributes: ") + generic_log(dwFileAttributes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileAttributesA],
    	        	original_bytes[(int)Hook::Functions::SetFileAttributesA], 6, NULL);

            BOOL result = SetFileAttributesA(lpFileName,dwFileAttributes);
            Hook reset_hook { Hook::Functions::SetFileAttributesA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileAttributesTransactedA(
    LPCSTR lpFileName,
    DWORD  dwFileAttributes,
    HANDLE hTransaction
){
            char whatToDo = WhatToDoInFunction(*"SetFileAttributesTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileAttributesTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFileAttributes: ") + generic_log(dwFileAttributes)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileAttributesTransactedA$");logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");
logMsg += std::string("dwFileAttributes: ") + generic_log(dwFileAttributes)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileAttributesTransactedA],
    	        	original_bytes[(int)Hook::Functions::SetFileAttributesTransactedA], 6, NULL);

            BOOL result = SetFileAttributesTransactedA(lpFileName,dwFileAttributes,hTransaction);
            Hook reset_hook { Hook::Functions::SetFileAttributesTransactedA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileBandwidthReservation(
    HANDLE  hFile,
    DWORD   nPeriodMilliseconds,
    DWORD   nBytesPerPeriod,
    BOOL    bDiscardable,
    LPDWORD lpTransferSize,
    LPDWORD lpNumOutstandingRequests
){
            char whatToDo = WhatToDoInFunction(*"SetFileBandwidthReservation");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileBandwidthReservation$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("nPeriodMilliseconds: ") + generic_log(nPeriodMilliseconds)+std::string("$");
logMsg += std::string("nBytesPerPeriod: ") + generic_log(nBytesPerPeriod)+std::string("$");
logMsg += std::string("bDiscardable: ") + generic_log(bDiscardable)+std::string("$");
logMsg += std::string("lpTransferSize: ") + generic_log(lpTransferSize)+std::string("$");
logMsg += std::string("lpNumOutstandingRequests: ") + generic_log(lpNumOutstandingRequests)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileBandwidthReservation$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("nPeriodMilliseconds: ") + generic_log(nPeriodMilliseconds)+std::string("$");
logMsg += std::string("nBytesPerPeriod: ") + generic_log(nBytesPerPeriod)+std::string("$");
logMsg += std::string("bDiscardable: ") + generic_log(bDiscardable)+std::string("$");
logMsg += std::string("lpTransferSize: ") + generic_log(lpTransferSize)+std::string("$");
logMsg += std::string("lpNumOutstandingRequests: ") + generic_log(lpNumOutstandingRequests)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileBandwidthReservation],
    	        	original_bytes[(int)Hook::Functions::SetFileBandwidthReservation], 6, NULL);

            BOOL result = SetFileBandwidthReservation(hFile,nPeriodMilliseconds,nBytesPerPeriod,bDiscardable,lpTransferSize,lpNumOutstandingRequests);
            Hook reset_hook { Hook::Functions::SetFileBandwidthReservation};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileCompletionNotificationModes(
    HANDLE FileHandle,
    UCHAR  Flags
){
            char whatToDo = WhatToDoInFunction(*"SetFileCompletionNotificationModes");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileCompletionNotificationModes$");logMsg += std::string("FileHandle: ") + generic_log(FileHandle)+std::string("$");
logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileCompletionNotificationModes$");logMsg += std::string("FileHandle: ") + generic_log(FileHandle)+std::string("$");
logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileCompletionNotificationModes],
    	        	original_bytes[(int)Hook::Functions::SetFileCompletionNotificationModes], 6, NULL);

            BOOL result = SetFileCompletionNotificationModes(FileHandle,Flags);
            Hook reset_hook { Hook::Functions::SetFileCompletionNotificationModes};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileInformationByHandle(
    HANDLE                    hFile,
    FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    LPVOID                    lpFileInformation,
    DWORD                     dwBufferSize
){
            char whatToDo = WhatToDoInFunction(*"SetFileInformationByHandle");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileInformationByHandle$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("FileInformationClass: ") + generic_log(FileInformationClass)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");
logMsg += std::string("dwBufferSize: ") + generic_log(dwBufferSize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileInformationByHandle$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("FileInformationClass: ") + generic_log(FileInformationClass)+std::string("$");
logMsg += std::string("lpFileInformation: ") + generic_log(lpFileInformation)+std::string("$");
logMsg += std::string("dwBufferSize: ") + generic_log(dwBufferSize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileInformationByHandle],
    	        	original_bytes[(int)Hook::Functions::SetFileInformationByHandle], 6, NULL);

            BOOL result = SetFileInformationByHandle(hFile,FileInformationClass,lpFileInformation,dwBufferSize);
            Hook reset_hook { Hook::Functions::SetFileInformationByHandle};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileIoOverlappedRange(
    HANDLE FileHandle,
    PUCHAR OverlappedRangeStart,
    ULONG  Length
){
            char whatToDo = WhatToDoInFunction(*"SetFileIoOverlappedRange");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileIoOverlappedRange$");logMsg += std::string("FileHandle: ") + generic_log(FileHandle)+std::string("$");
logMsg += std::string("OverlappedRangeStart: ") + generic_log(OverlappedRangeStart)+std::string("$");
logMsg += std::string("Length: ") + generic_log(Length)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileIoOverlappedRange$");logMsg += std::string("FileHandle: ") + generic_log(FileHandle)+std::string("$");
logMsg += std::string("OverlappedRangeStart: ") + generic_log(OverlappedRangeStart)+std::string("$");
logMsg += std::string("Length: ") + generic_log(Length)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileIoOverlappedRange],
    	        	original_bytes[(int)Hook::Functions::SetFileIoOverlappedRange], 6, NULL);

            BOOL result = SetFileIoOverlappedRange(FileHandle,OverlappedRangeStart,Length);
            Hook reset_hook { Hook::Functions::SetFileIoOverlappedRange};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newSetFilePointer(
    HANDLE hFile,
    LONG   lDistanceToMove,
    PLONG  lpDistanceToMoveHigh,
    DWORD  dwMoveMethod
){
            char whatToDo = WhatToDoInFunction(*"SetFilePointer");
            if(whatToDo == *"b"){
                std::string logMsg("SetFilePointer$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lDistanceToMove: ") + generic_log(lDistanceToMove)+std::string("$");
logMsg += std::string("lpDistanceToMoveHigh: ") + generic_log(lpDistanceToMoveHigh)+std::string("$");
logMsg += std::string("dwMoveMethod: ") + generic_log(dwMoveMethod)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFilePointer$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lDistanceToMove: ") + generic_log(lDistanceToMove)+std::string("$");
logMsg += std::string("lpDistanceToMoveHigh: ") + generic_log(lpDistanceToMoveHigh)+std::string("$");
logMsg += std::string("dwMoveMethod: ") + generic_log(dwMoveMethod)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFilePointer],
    	        	original_bytes[(int)Hook::Functions::SetFilePointer], 6, NULL);

            DWORD result = SetFilePointer(hFile,lDistanceToMove,lpDistanceToMoveHigh,dwMoveMethod);
            Hook reset_hook { Hook::Functions::SetFilePointer};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFilePointerEx(
    HANDLE         hFile,
    LARGE_INTEGER  liDistanceToMove,
    PLARGE_INTEGER lpNewFilePointer,
    DWORD          dwMoveMethod
){
            char whatToDo = WhatToDoInFunction(*"SetFilePointerEx");
            if(whatToDo == *"b"){
                std::string logMsg("SetFilePointerEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("liDistanceToMove: ") + generic_log(liDistanceToMove)+std::string("$");
logMsg += std::string("lpNewFilePointer: ") + generic_log(lpNewFilePointer)+std::string("$");
logMsg += std::string("dwMoveMethod: ") + generic_log(dwMoveMethod)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFilePointerEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("liDistanceToMove: ") + generic_log(liDistanceToMove)+std::string("$");
logMsg += std::string("lpNewFilePointer: ") + generic_log(lpNewFilePointer)+std::string("$");
logMsg += std::string("dwMoveMethod: ") + generic_log(dwMoveMethod)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFilePointerEx],
    	        	original_bytes[(int)Hook::Functions::SetFilePointerEx], 6, NULL);

            BOOL result = SetFilePointerEx(hFile,liDistanceToMove,lpNewFilePointer,dwMoveMethod);
            Hook reset_hook { Hook::Functions::SetFilePointerEx};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileShortNameA(
    HANDLE hFile,
    LPCSTR lpShortName
){
            char whatToDo = WhatToDoInFunction(*"SetFileShortNameA");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileShortNameA$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpShortName: ") + generic_log(lpShortName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileShortNameA$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpShortName: ") + generic_log(lpShortName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileShortNameA],
    	        	original_bytes[(int)Hook::Functions::SetFileShortNameA], 6, NULL);

            BOOL result = SetFileShortNameA(hFile,lpShortName);
            Hook reset_hook { Hook::Functions::SetFileShortNameA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetFileValidData(
    HANDLE   hFile,
    LONGLONG ValidDataLength
){
            char whatToDo = WhatToDoInFunction(*"SetFileValidData");
            if(whatToDo == *"b"){
                std::string logMsg("SetFileValidData$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("ValidDataLength: ") + generic_log(ValidDataLength)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetFileValidData$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("ValidDataLength: ") + generic_log(ValidDataLength)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetFileValidData],
    	        	original_bytes[(int)Hook::Functions::SetFileValidData], 6, NULL);

            BOOL result = SetFileValidData(hFile,ValidDataLength);
            Hook reset_hook { Hook::Functions::SetFileValidData};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newSetSearchPathMode(
    DWORD Flags
){
            char whatToDo = WhatToDoInFunction(*"SetSearchPathMode");
            if(whatToDo == *"b"){
                std::string logMsg("SetSearchPathMode$");logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetSearchPathMode$");logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetSearchPathMode],
    	        	original_bytes[(int)Hook::Functions::SetSearchPathMode], 6, NULL);

            BOOL result = SetSearchPathMode(Flags);
            Hook reset_hook { Hook::Functions::SetSearchPathMode};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newSetUserFileEncryptionKey(
    PENCRYPTION_CERTIFICATE pEncryptionCertificate
){
            char whatToDo = WhatToDoInFunction(*"SetUserFileEncryptionKey");
            if(whatToDo == *"b"){
                std::string logMsg("SetUserFileEncryptionKey$");logMsg += std::string("pEncryptionCertificate: ") + generic_log(pEncryptionCertificate)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("SetUserFileEncryptionKey$");logMsg += std::string("pEncryptionCertificate: ") + generic_log(pEncryptionCertificate)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::SetUserFileEncryptionKey],
    	        	original_bytes[(int)Hook::Functions::SetUserFileEncryptionKey], 6, NULL);

            DWORD result = SetUserFileEncryptionKey(pEncryptionCertificate);
            Hook reset_hook { Hook::Functions::SetUserFileEncryptionKey};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newUnlockFile(
    HANDLE hFile,
    DWORD  dwFileOffsetLow,
    DWORD  dwFileOffsetHigh,
    DWORD  nNumberOfBytesToUnlockLow,
    DWORD  nNumberOfBytesToUnlockHigh
){
            char whatToDo = WhatToDoInFunction(*"UnlockFile");
            if(whatToDo == *"b"){
                std::string logMsg("UnlockFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwFileOffsetLow: ") + generic_log(dwFileOffsetLow)+std::string("$");
logMsg += std::string("dwFileOffsetHigh: ") + generic_log(dwFileOffsetHigh)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockLow: ") + generic_log(nNumberOfBytesToUnlockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockHigh: ") + generic_log(nNumberOfBytesToUnlockHigh)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("UnlockFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwFileOffsetLow: ") + generic_log(dwFileOffsetLow)+std::string("$");
logMsg += std::string("dwFileOffsetHigh: ") + generic_log(dwFileOffsetHigh)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockLow: ") + generic_log(nNumberOfBytesToUnlockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockHigh: ") + generic_log(nNumberOfBytesToUnlockHigh)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::UnlockFile],
    	        	original_bytes[(int)Hook::Functions::UnlockFile], 6, NULL);

            BOOL result = UnlockFile(hFile,dwFileOffsetLow,dwFileOffsetHigh,nNumberOfBytesToUnlockLow,nNumberOfBytesToUnlockHigh);
            Hook reset_hook { Hook::Functions::UnlockFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newUnlockFileEx(
    HANDLE       hFile,
    DWORD        dwReserved,
    DWORD        nNumberOfBytesToUnlockLow,
    DWORD        nNumberOfBytesToUnlockHigh,
    LPOVERLAPPED lpOverlapped
){
            char whatToDo = WhatToDoInFunction(*"UnlockFileEx");
            if(whatToDo == *"b"){
                std::string logMsg("UnlockFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwReserved: ") + generic_log(dwReserved)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockLow: ") + generic_log(nNumberOfBytesToUnlockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockHigh: ") + generic_log(nNumberOfBytesToUnlockHigh)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("UnlockFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("dwReserved: ") + generic_log(dwReserved)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockLow: ") + generic_log(nNumberOfBytesToUnlockLow)+std::string("$");
logMsg += std::string("nNumberOfBytesToUnlockHigh: ") + generic_log(nNumberOfBytesToUnlockHigh)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::UnlockFileEx],
    	        	original_bytes[(int)Hook::Functions::UnlockFileEx], 6, NULL);

            BOOL result = UnlockFileEx(hFile,dwReserved,nNumberOfBytesToUnlockLow,nNumberOfBytesToUnlockHigh,lpOverlapped);
            Hook reset_hook { Hook::Functions::UnlockFileEx};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWow64DisableWow64FsRedirection(
    PVOID* OldValue
){
            char whatToDo = WhatToDoInFunction(*"Wow64DisableWow64FsRedirection");
            if(whatToDo == *"b"){
                std::string logMsg("Wow64DisableWow64FsRedirection$");logMsg += std::string("OldValue: ") + generic_log(OldValue)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("Wow64DisableWow64FsRedirection$");logMsg += std::string("OldValue: ") + generic_log(OldValue)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::Wow64DisableWow64FsRedirection],
    	        	original_bytes[(int)Hook::Functions::Wow64DisableWow64FsRedirection], 6, NULL);

            BOOL result = Wow64DisableWow64FsRedirection(OldValue);
            Hook reset_hook { Hook::Functions::Wow64DisableWow64FsRedirection};
            reset_hook.deploy_hook();

            return result;

}
BOOLEAN __stdcall newWow64EnableWow64FsRedirection(
    BOOLEAN Wow64FsEnableRedirection
){
            char whatToDo = WhatToDoInFunction(*"Wow64EnableWow64FsRedirection");
            if(whatToDo == *"b"){
                std::string logMsg("Wow64EnableWow64FsRedirection$");logMsg += std::string("Wow64FsEnableRedirection: ") + generic_log(Wow64FsEnableRedirection)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("Wow64EnableWow64FsRedirection$");logMsg += std::string("Wow64FsEnableRedirection: ") + generic_log(Wow64FsEnableRedirection)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::Wow64EnableWow64FsRedirection],
    	        	original_bytes[(int)Hook::Functions::Wow64EnableWow64FsRedirection], 6, NULL);

            BOOLEAN result = Wow64EnableWow64FsRedirection(Wow64FsEnableRedirection);
            Hook reset_hook { Hook::Functions::Wow64EnableWow64FsRedirection};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWow64RevertWow64FsRedirection(
    PVOID OlValue
){
            char whatToDo = WhatToDoInFunction(*"Wow64RevertWow64FsRedirection");
            if(whatToDo == *"b"){
                std::string logMsg("Wow64RevertWow64FsRedirection$");logMsg += std::string("OlValue: ") + generic_log(OlValue)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("Wow64RevertWow64FsRedirection$");logMsg += std::string("OlValue: ") + generic_log(OlValue)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::Wow64RevertWow64FsRedirection],
    	        	original_bytes[(int)Hook::Functions::Wow64RevertWow64FsRedirection], 6, NULL);

            BOOL result = Wow64RevertWow64FsRedirection(OlValue);
            Hook reset_hook { Hook::Functions::Wow64RevertWow64FsRedirection};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newWriteEncryptedFileRaw(
    PFE_IMPORT_FUNC pfImportCallback,
    PVOID           pvCallbackContext,
    PVOID           pvContext
){
            char whatToDo = WhatToDoInFunction(*"WriteEncryptedFileRaw");
            if(whatToDo == *"b"){
                std::string logMsg("WriteEncryptedFileRaw$");logMsg += std::string("pfImportCallback: ") + generic_log(pfImportCallback)+std::string("$");
logMsg += std::string("pvCallbackContext: ") + generic_log(pvCallbackContext)+std::string("$");
logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WriteEncryptedFileRaw$");logMsg += std::string("pfImportCallback: ") + generic_log(pfImportCallback)+std::string("$");
logMsg += std::string("pvCallbackContext: ") + generic_log(pvCallbackContext)+std::string("$");
logMsg += std::string("pvContext: ") + generic_log(pvContext)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WriteEncryptedFileRaw],
    	        	original_bytes[(int)Hook::Functions::WriteEncryptedFileRaw], 6, NULL);

            DWORD result = WriteEncryptedFileRaw(pfImportCallback,pvCallbackContext,pvContext);
            Hook reset_hook { Hook::Functions::WriteEncryptedFileRaw};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWriteFile(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
){
            char whatToDo = WhatToDoInFunction(*"WriteFile");
            if(whatToDo == *"b"){
                std::string logMsg("WriteFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToWrite: ") + generic_log(nNumberOfBytesToWrite)+std::string("$");
logMsg += std::string("lpNumberOfBytesWritten: ") + generic_log(lpNumberOfBytesWritten)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WriteFile$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToWrite: ") + generic_log(nNumberOfBytesToWrite)+std::string("$");
logMsg += std::string("lpNumberOfBytesWritten: ") + generic_log(lpNumberOfBytesWritten)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WriteFile],
    	        	original_bytes[(int)Hook::Functions::WriteFile], 6, NULL);

            BOOL result = WriteFile(hFile,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
            Hook reset_hook { Hook::Functions::WriteFile};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWriteFileEx(
    HANDLE                          hFile,
    LPCVOID                         lpBuffer,
    DWORD                           nNumberOfBytesToWrite,
    LPOVERLAPPED                    lpOverlapped,
    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction(*"WriteFileEx");
            if(whatToDo == *"b"){
                std::string logMsg("WriteFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToWrite: ") + generic_log(nNumberOfBytesToWrite)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WriteFileEx$");logMsg += std::string("hFile: ") + generic_log(hFile)+std::string("$");
logMsg += std::string("lpBuffer: ") + generic_log(lpBuffer)+std::string("$");
logMsg += std::string("nNumberOfBytesToWrite: ") + generic_log(nNumberOfBytesToWrite)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WriteFileEx],
    	        	original_bytes[(int)Hook::Functions::WriteFileEx], 6, NULL);

            BOOL result = WriteFileEx(hFile,lpBuffer,nNumberOfBytesToWrite,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WriteFileEx};
            reset_hook.deploy_hook();

            return result;

}
}