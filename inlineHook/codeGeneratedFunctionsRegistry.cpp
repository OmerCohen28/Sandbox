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

BOOL __stdcall newGetSystemRegistryQuota(
                  PDWORD pdwQuotaAllowed,
                  PDWORD pdwQuotaUsed
){
            char whatToDo = WhatToDoInFunction(*"GetSystemRegistryQuota");
            if(whatToDo == *"b"){
                std::string logMsg("GetSystemRegistryQuota$");logMsg += std::string("pdwQuotaAllowed: ") + generic_log(pdwQuotaAllowed)+std::string("$");
logMsg += std::string("pdwQuotaUsed: ") + generic_log(pdwQuotaUsed)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetSystemRegistryQuota$");logMsg += std::string("pdwQuotaAllowed: ") + generic_log(pdwQuotaAllowed)+std::string("$");
logMsg += std::string("pdwQuotaUsed: ") + generic_log(pdwQuotaUsed)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetSystemRegistryQuota],
    	        	original_bytes[(int)Hook::Functions::GetSystemRegistryQuota], 6, NULL);

            BOOL result = GetSystemRegistryQuota(pdwQuotaAllowed,pdwQuotaUsed);
            Hook reset_hook { Hook::Functions::GetSystemRegistryQuota};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegCloseKey(
       HKEY hKey
){
            char whatToDo = WhatToDoInFunction(*"RegCloseKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegCloseKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegCloseKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegCloseKey],
    	        	original_bytes[(int)Hook::Functions::RegCloseKey], 6, NULL);

            LSTATUS result = RegCloseKey(hKey);
            Hook reset_hook { Hook::Functions::RegCloseKey};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegConnectRegistryA(
                 LPCSTR lpMachineName,
                 HKEY   hKey,
                 PHKEY  phkResult
){
            char whatToDo = WhatToDoInFunction(*"RegConnectRegistryA");
            if(whatToDo == *"b"){
                std::string logMsg("RegConnectRegistryA$");logMsg += std::string("lpMachineName: ") + generic_log(lpMachineName)+std::string("$");
logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegConnectRegistryA$");logMsg += std::string("lpMachineName: ") + generic_log(lpMachineName)+std::string("$");
logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegConnectRegistryA],
    	        	original_bytes[(int)Hook::Functions::RegConnectRegistryA], 6, NULL);

            LSTATUS result = RegConnectRegistryA(lpMachineName,hKey,phkResult);
            Hook reset_hook { Hook::Functions::RegConnectRegistryA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegCopyTreeA(
                 HKEY   hKeySrc,
                 LPCSTR lpSubKey,
                 HKEY   hKeyDest
){
            char whatToDo = WhatToDoInFunction(*"RegCopyTreeA");
            if(whatToDo == *"b"){
                std::string logMsg("RegCopyTreeA$");logMsg += std::string("hKeySrc: ") + generic_log(hKeySrc)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("hKeyDest: ") + generic_log(hKeyDest)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegCopyTreeA$");logMsg += std::string("hKeySrc: ") + generic_log(hKeySrc)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("hKeyDest: ") + generic_log(hKeyDest)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegCopyTreeA],
    	        	original_bytes[(int)Hook::Functions::RegCopyTreeA], 6, NULL);

            LSTATUS result = RegCopyTreeA(hKeySrc,lpSubKey,hKeyDest);
            Hook reset_hook { Hook::Functions::RegCopyTreeA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegCreateKeyExA(
                  HKEY                        hKey,
                  LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
                  LPSTR                       lpClass,
                  DWORD                       dwOptions,
                  REGSAM                      samDesired,
                  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                  PHKEY                       phkResult,
                  LPDWORD                     lpdwDisposition
){
            char whatToDo = WhatToDoInFunction(*"RegCreateKeyExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegCreateKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("dwOptions: ") + generic_log(dwOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");
logMsg += std::string("lpdwDisposition: ") + generic_log(lpdwDisposition)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegCreateKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("dwOptions: ") + generic_log(dwOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");
logMsg += std::string("lpdwDisposition: ") + generic_log(lpdwDisposition)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegCreateKeyExA],
    	        	original_bytes[(int)Hook::Functions::RegCreateKeyExA], 6, NULL);

            LSTATUS result = RegCreateKeyExA(hKey,lpSubKey,Reserved,lpClass,dwOptions,samDesired,lpSecurityAttributes,phkResult,lpdwDisposition);
            Hook reset_hook { Hook::Functions::RegCreateKeyExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegCreateKeyTransactedA(
                  HKEY                        hKey,
                  LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
                  LPSTR                       lpClass,
                  DWORD                       dwOptions,
                  REGSAM                      samDesired,
                  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                  PHKEY                       phkResult,
                  LPDWORD                     lpdwDisposition,
                  HANDLE                      hTransaction,
                  PVOID                       pExtendedParemeter
){
            char whatToDo = WhatToDoInFunction(*"RegCreateKeyTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("RegCreateKeyTransactedA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("dwOptions: ") + generic_log(dwOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");
logMsg += std::string("lpdwDisposition: ") + generic_log(lpdwDisposition)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pExtendedParemeter: ") + generic_log(pExtendedParemeter)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegCreateKeyTransactedA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("dwOptions: ") + generic_log(dwOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");
logMsg += std::string("lpdwDisposition: ") + generic_log(lpdwDisposition)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pExtendedParemeter: ") + generic_log(pExtendedParemeter)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegCreateKeyTransactedA],
    	        	original_bytes[(int)Hook::Functions::RegCreateKeyTransactedA], 6, NULL);

            LSTATUS result = RegCreateKeyTransactedA(hKey,lpSubKey,Reserved,lpClass,dwOptions,samDesired,lpSecurityAttributes,phkResult,lpdwDisposition,hTransaction,pExtendedParemeter);
            Hook reset_hook { Hook::Functions::RegCreateKeyTransactedA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDeleteKeyA(
       HKEY   hKey,
       LPCSTR lpSubKey
){
            char whatToDo = WhatToDoInFunction(*"RegDeleteKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegDeleteKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDeleteKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyA],
    	        	original_bytes[(int)Hook::Functions::RegDeleteKeyA], 6, NULL);

            LSTATUS result = RegDeleteKeyA(hKey,lpSubKey);
            Hook reset_hook { Hook::Functions::RegDeleteKeyA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDeleteKeyExA(
       HKEY   hKey,
       LPCSTR lpSubKey,
       REGSAM samDesired,
       DWORD  Reserved
){
            char whatToDo = WhatToDoInFunction(*"RegDeleteKeyExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegDeleteKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDeleteKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyExA],
    	        	original_bytes[(int)Hook::Functions::RegDeleteKeyExA], 6, NULL);

            LSTATUS result = RegDeleteKeyExA(hKey,lpSubKey,samDesired,Reserved);
            Hook reset_hook { Hook::Functions::RegDeleteKeyExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDeleteKeyTransactedA(
       HKEY   hKey,
       LPCSTR lpSubKey,
       REGSAM samDesired,
       DWORD  Reserved,
       HANDLE hTransaction,
       PVOID  pExtendedParameter
){
            char whatToDo = WhatToDoInFunction(*"RegDeleteKeyTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("RegDeleteKeyTransactedA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pExtendedParameter: ") + generic_log(pExtendedParameter)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDeleteKeyTransactedA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pExtendedParameter: ") + generic_log(pExtendedParameter)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyTransactedA],
    	        	original_bytes[(int)Hook::Functions::RegDeleteKeyTransactedA], 6, NULL);

            LSTATUS result = RegDeleteKeyTransactedA(hKey,lpSubKey,samDesired,Reserved,hTransaction,pExtendedParameter);
            Hook reset_hook { Hook::Functions::RegDeleteKeyTransactedA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDeleteKeyValueA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpValueName
){
            char whatToDo = WhatToDoInFunction(*"RegDeleteKeyValueA");
            if(whatToDo == *"b"){
                std::string logMsg("RegDeleteKeyValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDeleteKeyValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyValueA],
    	        	original_bytes[(int)Hook::Functions::RegDeleteKeyValueA], 6, NULL);

            LSTATUS result = RegDeleteKeyValueA(hKey,lpSubKey,lpValueName);
            Hook reset_hook { Hook::Functions::RegDeleteKeyValueA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDeleteTreeA(
                 HKEY   hKey,
                 LPCSTR lpSubKey
){
            char whatToDo = WhatToDoInFunction(*"RegDeleteTreeA");
            if(whatToDo == *"b"){
                std::string logMsg("RegDeleteTreeA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDeleteTreeA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteTreeA],
    	        	original_bytes[(int)Hook::Functions::RegDeleteTreeA], 6, NULL);

            LSTATUS result = RegDeleteTreeA(hKey,lpSubKey);
            Hook reset_hook { Hook::Functions::RegDeleteTreeA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDeleteValueA(
                 HKEY   hKey,
                 LPCSTR lpValueName
){
            char whatToDo = WhatToDoInFunction(*"RegDeleteValueA");
            if(whatToDo == *"b"){
                std::string logMsg("RegDeleteValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDeleteValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteValueA],
    	        	original_bytes[(int)Hook::Functions::RegDeleteValueA], 6, NULL);

            LSTATUS result = RegDeleteValueA(hKey,lpValueName);
            Hook reset_hook { Hook::Functions::RegDeleteValueA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDisablePredefinedCache(){
            char whatToDo = WhatToDoInFunction(*"RegDisablePredefinedCache");
            if(whatToDo == *"b"){
                std::string logMsg("RegDisablePredefinedCache$");
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDisablePredefinedCache$");
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDisablePredefinedCache],
    	        	original_bytes[(int)Hook::Functions::RegDisablePredefinedCache], 6, NULL);

            LSTATUS result = RegDisablePredefinedCache();
            Hook reset_hook { Hook::Functions::RegDisablePredefinedCache};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegDisablePredefinedCacheEx(){
            char whatToDo = WhatToDoInFunction(*"RegDisablePredefinedCacheEx");
            if(whatToDo == *"b"){
                std::string logMsg("RegDisablePredefinedCacheEx$");
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDisablePredefinedCacheEx$");
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDisablePredefinedCacheEx],
    	        	original_bytes[(int)Hook::Functions::RegDisablePredefinedCacheEx], 6, NULL);

            LSTATUS result = RegDisablePredefinedCacheEx();
            Hook reset_hook { Hook::Functions::RegDisablePredefinedCacheEx};
            reset_hook.deploy_hook();

            return result;

}
LONG __stdcall newRegDisableReflectionKey(
       HKEY hBase
){
            char whatToDo = WhatToDoInFunction(*"RegDisableReflectionKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegDisableReflectionKey$");logMsg += std::string("hBase: ") + generic_log(hBase)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegDisableReflectionKey$");logMsg += std::string("hBase: ") + generic_log(hBase)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegDisableReflectionKey],
    	        	original_bytes[(int)Hook::Functions::RegDisableReflectionKey], 6, NULL);

            LONG result = RegDisableReflectionKey(hBase);
            Hook reset_hook { Hook::Functions::RegDisableReflectionKey};
            reset_hook.deploy_hook();

            return result;

}
LONG __stdcall newRegEnableReflectionKey(
       HKEY hBase
){
            char whatToDo = WhatToDoInFunction(*"RegEnableReflectionKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegEnableReflectionKey$");logMsg += std::string("hBase: ") + generic_log(hBase)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegEnableReflectionKey$");logMsg += std::string("hBase: ") + generic_log(hBase)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegEnableReflectionKey],
    	        	original_bytes[(int)Hook::Functions::RegEnableReflectionKey], 6, NULL);

            LONG result = RegEnableReflectionKey(hBase);
            Hook reset_hook { Hook::Functions::RegEnableReflectionKey};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegEnumKeyExA(
                      HKEY      hKey,
                      DWORD     dwIndex,
                      LPSTR     lpName,
                      LPDWORD   lpcchName,
                      LPDWORD   lpReserved,
                      LPSTR     lpClass,
                      LPDWORD   lpcchClass,
                      PFILETIME lpftLastWriteTime
){
            char whatToDo = WhatToDoInFunction(*"RegEnumKeyExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegEnumKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("dwIndex: ") + generic_log(dwIndex)+std::string("$");
logMsg += std::string("lpName: ") + generic_log(lpName)+std::string("$");
logMsg += std::string("lpcchName: ") + generic_log(lpcchName)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("lpcchClass: ") + generic_log(lpcchClass)+std::string("$");
logMsg += std::string("lpftLastWriteTime: ") + generic_log(lpftLastWriteTime)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegEnumKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("dwIndex: ") + generic_log(dwIndex)+std::string("$");
logMsg += std::string("lpName: ") + generic_log(lpName)+std::string("$");
logMsg += std::string("lpcchName: ") + generic_log(lpcchName)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("lpcchClass: ") + generic_log(lpcchClass)+std::string("$");
logMsg += std::string("lpftLastWriteTime: ") + generic_log(lpftLastWriteTime)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegEnumKeyExA],
    	        	original_bytes[(int)Hook::Functions::RegEnumKeyExA], 6, NULL);

            LSTATUS result = RegEnumKeyExA(hKey,dwIndex,lpName,lpcchName,lpReserved,lpClass,lpcchClass,lpftLastWriteTime);
            Hook reset_hook { Hook::Functions::RegEnumKeyExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegEnumValueA(
                      HKEY    hKey,
                      DWORD   dwIndex,
                      LPSTR   lpValueName,
                      LPDWORD lpcchValueName,
                      LPDWORD lpReserved,
                      LPDWORD lpType,
                      LPBYTE  lpData,
                      LPDWORD lpcbData
){
            char whatToDo = WhatToDoInFunction(*"RegEnumValueA");
            if(whatToDo == *"b"){
                std::string logMsg("RegEnumValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("dwIndex: ") + generic_log(dwIndex)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("lpcchValueName: ") + generic_log(lpcchValueName)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpType: ") + generic_log(lpType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("lpcbData: ") + generic_log(lpcbData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegEnumValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("dwIndex: ") + generic_log(dwIndex)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("lpcchValueName: ") + generic_log(lpcchValueName)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpType: ") + generic_log(lpType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("lpcbData: ") + generic_log(lpcbData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegEnumValueA],
    	        	original_bytes[(int)Hook::Functions::RegEnumValueA], 6, NULL);

            LSTATUS result = RegEnumValueA(hKey,dwIndex,lpValueName,lpcchValueName,lpReserved,lpType,lpData,lpcbData);
            Hook reset_hook { Hook::Functions::RegEnumValueA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegFlushKey(
       HKEY hKey
){
            char whatToDo = WhatToDoInFunction(*"RegFlushKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegFlushKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegFlushKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegFlushKey],
    	        	original_bytes[(int)Hook::Functions::RegFlushKey], 6, NULL);

            LSTATUS result = RegFlushKey(hKey);
            Hook reset_hook { Hook::Functions::RegFlushKey};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegGetKeySecurity(
                  HKEY                 hKey,
                  SECURITY_INFORMATION SecurityInformation,
                  PSECURITY_DESCRIPTOR pSecurityDescriptor,
                  LPDWORD              lpcbSecurityDescriptor
){
            char whatToDo = WhatToDoInFunction(*"RegGetKeySecurity");
            if(whatToDo == *"b"){
                std::string logMsg("RegGetKeySecurity$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("SecurityInformation: ") + generic_log(SecurityInformation)+std::string("$");
logMsg += std::string("pSecurityDescriptor: ") + generic_log(pSecurityDescriptor)+std::string("$");
logMsg += std::string("lpcbSecurityDescriptor: ") + generic_log(lpcbSecurityDescriptor)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegGetKeySecurity$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("SecurityInformation: ") + generic_log(SecurityInformation)+std::string("$");
logMsg += std::string("pSecurityDescriptor: ") + generic_log(pSecurityDescriptor)+std::string("$");
logMsg += std::string("lpcbSecurityDescriptor: ") + generic_log(lpcbSecurityDescriptor)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegGetKeySecurity],
    	        	original_bytes[(int)Hook::Functions::RegGetKeySecurity], 6, NULL);

            LSTATUS result = RegGetKeySecurity(hKey,SecurityInformation,pSecurityDescriptor,lpcbSecurityDescriptor);
            Hook reset_hook { Hook::Functions::RegGetKeySecurity};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegGetValueA(
                      HKEY    hkey,
                      LPCSTR  lpSubKey,
                      LPCSTR  lpValue,
                      DWORD   dwFlags,
                      LPDWORD pdwType,
                      PVOID   pvData,
                      LPDWORD pcbData
){
            char whatToDo = WhatToDoInFunction(*"RegGetValueA");
            if(whatToDo == *"b"){
                std::string logMsg("RegGetValueA$");logMsg += std::string("hkey: ") + generic_log(hkey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpValue: ") + generic_log(lpValue)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("pdwType: ") + generic_log(pdwType)+std::string("$");
logMsg += std::string("pvData: ") + generic_log(pvData)+std::string("$");
logMsg += std::string("pcbData: ") + generic_log(pcbData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegGetValueA$");logMsg += std::string("hkey: ") + generic_log(hkey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpValue: ") + generic_log(lpValue)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("pdwType: ") + generic_log(pdwType)+std::string("$");
logMsg += std::string("pvData: ") + generic_log(pvData)+std::string("$");
logMsg += std::string("pcbData: ") + generic_log(pcbData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegGetValueA],
    	        	original_bytes[(int)Hook::Functions::RegGetValueA], 6, NULL);

            LSTATUS result = RegGetValueA(hkey,lpSubKey,lpValue,dwFlags,pdwType,pvData,pcbData);
            Hook reset_hook { Hook::Functions::RegGetValueA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegLoadKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpFile
){
            char whatToDo = WhatToDoInFunction(*"RegLoadKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegLoadKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegLoadKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegLoadKeyA],
    	        	original_bytes[(int)Hook::Functions::RegLoadKeyA], 6, NULL);

            LSTATUS result = RegLoadKeyA(hKey,lpSubKey,lpFile);
            Hook reset_hook { Hook::Functions::RegLoadKeyA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegLoadMUIStringA(
                  HKEY    hKey,
                  LPCSTR  pszValue,
                  LPSTR   pszOutBuf,
                  DWORD   cbOutBuf,
                  LPDWORD pcbData,
                  DWORD   Flags,
                  LPCSTR  pszDirectory
){
            char whatToDo = WhatToDoInFunction(*"RegLoadMUIStringA");
            if(whatToDo == *"b"){
                std::string logMsg("RegLoadMUIStringA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("pszValue: ") + generic_log(pszValue)+std::string("$");
logMsg += std::string("pszOutBuf: ") + generic_log(pszOutBuf)+std::string("$");
logMsg += std::string("cbOutBuf: ") + generic_log(cbOutBuf)+std::string("$");
logMsg += std::string("pcbData: ") + generic_log(pcbData)+std::string("$");
logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");
logMsg += std::string("pszDirectory: ") + generic_log(pszDirectory)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegLoadMUIStringA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("pszValue: ") + generic_log(pszValue)+std::string("$");
logMsg += std::string("pszOutBuf: ") + generic_log(pszOutBuf)+std::string("$");
logMsg += std::string("cbOutBuf: ") + generic_log(cbOutBuf)+std::string("$");
logMsg += std::string("pcbData: ") + generic_log(pcbData)+std::string("$");
logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");
logMsg += std::string("pszDirectory: ") + generic_log(pszDirectory)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegLoadMUIStringA],
    	        	original_bytes[(int)Hook::Functions::RegLoadMUIStringA], 6, NULL);

            LSTATUS result = RegLoadMUIStringA(hKey,pszValue,pszOutBuf,cbOutBuf,pcbData,Flags,pszDirectory);
            Hook reset_hook { Hook::Functions::RegLoadMUIStringA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegNotifyChangeKeyValue(
                 HKEY   hKey,
                 BOOL   bWatchSubtree,
                 DWORD  dwNotifyFilter,
                 HANDLE hEvent,
                 BOOL   fAsynchronous
){
            char whatToDo = WhatToDoInFunction(*"RegNotifyChangeKeyValue");
            if(whatToDo == *"b"){
                std::string logMsg("RegNotifyChangeKeyValue$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("bWatchSubtree: ") + generic_log(bWatchSubtree)+std::string("$");
logMsg += std::string("dwNotifyFilter: ") + generic_log(dwNotifyFilter)+std::string("$");
logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");
logMsg += std::string("fAsynchronous: ") + generic_log(fAsynchronous)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegNotifyChangeKeyValue$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("bWatchSubtree: ") + generic_log(bWatchSubtree)+std::string("$");
logMsg += std::string("dwNotifyFilter: ") + generic_log(dwNotifyFilter)+std::string("$");
logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");
logMsg += std::string("fAsynchronous: ") + generic_log(fAsynchronous)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegNotifyChangeKeyValue],
    	        	original_bytes[(int)Hook::Functions::RegNotifyChangeKeyValue], 6, NULL);

            LSTATUS result = RegNotifyChangeKeyValue(hKey,bWatchSubtree,dwNotifyFilter,hEvent,fAsynchronous);
            Hook reset_hook { Hook::Functions::RegNotifyChangeKeyValue};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegOpenCurrentUser(
        REGSAM samDesired,
        PHKEY  phkResult
){
            char whatToDo = WhatToDoInFunction(*"RegOpenCurrentUser");
            if(whatToDo == *"b"){
                std::string logMsg("RegOpenCurrentUser$");logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegOpenCurrentUser$");logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenCurrentUser],
    	        	original_bytes[(int)Hook::Functions::RegOpenCurrentUser], 6, NULL);

            LSTATUS result = RegOpenCurrentUser(samDesired,phkResult);
            Hook reset_hook { Hook::Functions::RegOpenCurrentUser};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegOpenKeyExA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 DWORD  ulOptions,
                 REGSAM samDesired,
                 PHKEY  phkResult
){
            char whatToDo = WhatToDoInFunction(*"RegOpenKeyExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegOpenKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("ulOptions: ") + generic_log(ulOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegOpenKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("ulOptions: ") + generic_log(ulOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenKeyExA],
    	        	original_bytes[(int)Hook::Functions::RegOpenKeyExA], 6, NULL);

            LSTATUS result = RegOpenKeyExA(hKey,lpSubKey,ulOptions,samDesired,phkResult);
            Hook reset_hook { Hook::Functions::RegOpenKeyExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegOpenKeyTransactedA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 DWORD  ulOptions,
                 REGSAM samDesired,
                 PHKEY  phkResult,
                 HANDLE hTransaction,
                 PVOID  pExtendedParemeter
){
            char whatToDo = WhatToDoInFunction(*"RegOpenKeyTransactedA");
            if(whatToDo == *"b"){
                std::string logMsg("RegOpenKeyTransactedA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("ulOptions: ") + generic_log(ulOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pExtendedParemeter: ") + generic_log(pExtendedParemeter)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegOpenKeyTransactedA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("ulOptions: ") + generic_log(ulOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");
logMsg += std::string("hTransaction: ") + generic_log(hTransaction)+std::string("$");
logMsg += std::string("pExtendedParemeter: ") + generic_log(pExtendedParemeter)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenKeyTransactedA],
    	        	original_bytes[(int)Hook::Functions::RegOpenKeyTransactedA], 6, NULL);

            LSTATUS result = RegOpenKeyTransactedA(hKey,lpSubKey,ulOptions,samDesired,phkResult,hTransaction,pExtendedParemeter);
            Hook reset_hook { Hook::Functions::RegOpenKeyTransactedA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegOpenUserClassesRoot(
        HANDLE hToken,
        DWORD  dwOptions,
        REGSAM samDesired,
        PHKEY  phkResult
){
            char whatToDo = WhatToDoInFunction(*"RegOpenUserClassesRoot");
            if(whatToDo == *"b"){
                std::string logMsg("RegOpenUserClassesRoot$");logMsg += std::string("hToken: ") + generic_log(hToken)+std::string("$");
logMsg += std::string("dwOptions: ") + generic_log(dwOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegOpenUserClassesRoot$");logMsg += std::string("hToken: ") + generic_log(hToken)+std::string("$");
logMsg += std::string("dwOptions: ") + generic_log(dwOptions)+std::string("$");
logMsg += std::string("samDesired: ") + generic_log(samDesired)+std::string("$");
logMsg += std::string("phkResult: ") + generic_log(phkResult)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenUserClassesRoot],
    	        	original_bytes[(int)Hook::Functions::RegOpenUserClassesRoot], 6, NULL);

            LSTATUS result = RegOpenUserClassesRoot(hToken,dwOptions,samDesired,phkResult);
            Hook reset_hook { Hook::Functions::RegOpenUserClassesRoot};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegOverridePredefKey(
                 HKEY hKey,
                 HKEY hNewHKey
){
            char whatToDo = WhatToDoInFunction(*"RegOverridePredefKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegOverridePredefKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("hNewHKey: ") + generic_log(hNewHKey)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegOverridePredefKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("hNewHKey: ") + generic_log(hNewHKey)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegOverridePredefKey],
    	        	original_bytes[(int)Hook::Functions::RegOverridePredefKey], 6, NULL);

            LSTATUS result = RegOverridePredefKey(hKey,hNewHKey);
            Hook reset_hook { Hook::Functions::RegOverridePredefKey};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegQueryInfoKeyA(
                      HKEY      hKey,
                      LPSTR     lpClass,
                      LPDWORD   lpcchClass,
                      LPDWORD   lpReserved,
                      LPDWORD   lpcSubKeys,
                      LPDWORD   lpcbMaxSubKeyLen,
                      LPDWORD   lpcbMaxClassLen,
                      LPDWORD   lpcValues,
                      LPDWORD   lpcbMaxValueNameLen,
                      LPDWORD   lpcbMaxValueLen,
                      LPDWORD   lpcbSecurityDescriptor,
                      PFILETIME lpftLastWriteTime
){
            char whatToDo = WhatToDoInFunction(*"RegQueryInfoKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegQueryInfoKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("lpcchClass: ") + generic_log(lpcchClass)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpcSubKeys: ") + generic_log(lpcSubKeys)+std::string("$");
logMsg += std::string("lpcbMaxSubKeyLen: ") + generic_log(lpcbMaxSubKeyLen)+std::string("$");
logMsg += std::string("lpcbMaxClassLen: ") + generic_log(lpcbMaxClassLen)+std::string("$");
logMsg += std::string("lpcValues: ") + generic_log(lpcValues)+std::string("$");
logMsg += std::string("lpcbMaxValueNameLen: ") + generic_log(lpcbMaxValueNameLen)+std::string("$");
logMsg += std::string("lpcbMaxValueLen: ") + generic_log(lpcbMaxValueLen)+std::string("$");
logMsg += std::string("lpcbSecurityDescriptor: ") + generic_log(lpcbSecurityDescriptor)+std::string("$");
logMsg += std::string("lpftLastWriteTime: ") + generic_log(lpftLastWriteTime)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegQueryInfoKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpClass: ") + generic_log(lpClass)+std::string("$");
logMsg += std::string("lpcchClass: ") + generic_log(lpcchClass)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpcSubKeys: ") + generic_log(lpcSubKeys)+std::string("$");
logMsg += std::string("lpcbMaxSubKeyLen: ") + generic_log(lpcbMaxSubKeyLen)+std::string("$");
logMsg += std::string("lpcbMaxClassLen: ") + generic_log(lpcbMaxClassLen)+std::string("$");
logMsg += std::string("lpcValues: ") + generic_log(lpcValues)+std::string("$");
logMsg += std::string("lpcbMaxValueNameLen: ") + generic_log(lpcbMaxValueNameLen)+std::string("$");
logMsg += std::string("lpcbMaxValueLen: ") + generic_log(lpcbMaxValueLen)+std::string("$");
logMsg += std::string("lpcbSecurityDescriptor: ") + generic_log(lpcbSecurityDescriptor)+std::string("$");
logMsg += std::string("lpftLastWriteTime: ") + generic_log(lpftLastWriteTime)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryInfoKeyA],
    	        	original_bytes[(int)Hook::Functions::RegQueryInfoKeyA], 6, NULL);

            LSTATUS result = RegQueryInfoKeyA(hKey,lpClass,lpcchClass,lpReserved,lpcSubKeys,lpcbMaxSubKeyLen,lpcbMaxClassLen,lpcValues,lpcbMaxValueNameLen,lpcbMaxValueLen,lpcbSecurityDescriptor,lpftLastWriteTime);
            Hook reset_hook { Hook::Functions::RegQueryInfoKeyA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegQueryMultipleValuesA(
                      HKEY     hKey,
                      PVALENTA val_list,
                      DWORD    num_vals,
                      LPSTR    lpValueBuf,
                      LPDWORD  ldwTotsize
){
            char whatToDo = WhatToDoInFunction(*"RegQueryMultipleValuesA");
            if(whatToDo == *"b"){
                std::string logMsg("RegQueryMultipleValuesA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("val_list: ") + generic_log(val_list)+std::string("$");
logMsg += std::string("num_vals: ") + generic_log(num_vals)+std::string("$");
logMsg += std::string("lpValueBuf: ") + generic_log(lpValueBuf)+std::string("$");
logMsg += std::string("ldwTotsize: ") + generic_log(ldwTotsize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegQueryMultipleValuesA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("val_list: ") + generic_log(val_list)+std::string("$");
logMsg += std::string("num_vals: ") + generic_log(num_vals)+std::string("$");
logMsg += std::string("lpValueBuf: ") + generic_log(lpValueBuf)+std::string("$");
logMsg += std::string("ldwTotsize: ") + generic_log(ldwTotsize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryMultipleValuesA],
    	        	original_bytes[(int)Hook::Functions::RegQueryMultipleValuesA], 6, NULL);

            LSTATUS result = RegQueryMultipleValuesA(hKey,val_list,num_vals,lpValueBuf,ldwTotsize);
            Hook reset_hook { Hook::Functions::RegQueryMultipleValuesA};
            reset_hook.deploy_hook();

            return result;

}
LONG __stdcall newRegQueryReflectionKey(
        HKEY hBase,
        BOOL *bIsReflectionDisabled
){
            char whatToDo = WhatToDoInFunction(*"RegQueryReflectionKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegQueryReflectionKey$");logMsg += std::string("hBase: ") + generic_log(hBase)+std::string("$");
logMsg += std::string("bIsReflectionDisabled: ") + generic_log(bIsReflectionDisabled)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegQueryReflectionKey$");logMsg += std::string("hBase: ") + generic_log(hBase)+std::string("$");
logMsg += std::string("bIsReflectionDisabled: ") + generic_log(bIsReflectionDisabled)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryReflectionKey],
    	        	original_bytes[(int)Hook::Functions::RegQueryReflectionKey], 6, NULL);

            LONG result = RegQueryReflectionKey(hBase,bIsReflectionDisabled);
            Hook reset_hook { Hook::Functions::RegQueryReflectionKey};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegQueryValueExA(
                      HKEY    hKey,
                      LPCSTR  lpValueName,
                      LPDWORD lpReserved,
                      LPDWORD lpType,
                      LPBYTE  lpData,
                      LPDWORD lpcbData
){
            char whatToDo = WhatToDoInFunction(*"RegQueryValueExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegQueryValueExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpType: ") + generic_log(lpType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("lpcbData: ") + generic_log(lpcbData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegQueryValueExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("lpReserved: ") + generic_log(lpReserved)+std::string("$");
logMsg += std::string("lpType: ") + generic_log(lpType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("lpcbData: ") + generic_log(lpcbData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryValueExA],
    	        	original_bytes[(int)Hook::Functions::RegQueryValueExA], 6, NULL);

            LSTATUS result = RegQueryValueExA(hKey,lpValueName,lpReserved,lpType,lpData,lpcbData);
            Hook reset_hook { Hook::Functions::RegQueryValueExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegRenameKey(
  HKEY    hKey,
  LPCWSTR lpSubKeyName,
  LPCWSTR lpNewKeyName
){
            char whatToDo = WhatToDoInFunction(*"RegRenameKey");
            if(whatToDo == *"b"){
                std::string logMsg("RegRenameKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKeyName: ") + generic_log(lpSubKeyName)+std::string("$");
logMsg += std::string("lpNewKeyName: ") + generic_log(lpNewKeyName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegRenameKey$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKeyName: ") + generic_log(lpSubKeyName)+std::string("$");
logMsg += std::string("lpNewKeyName: ") + generic_log(lpNewKeyName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegRenameKey],
    	        	original_bytes[(int)Hook::Functions::RegRenameKey], 6, NULL);

            LSTATUS result = RegRenameKey(hKey,lpSubKeyName,lpNewKeyName);
            Hook reset_hook { Hook::Functions::RegRenameKey};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegReplaceKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpNewFile,
                 LPCSTR lpOldFile
){
            char whatToDo = WhatToDoInFunction(*"RegReplaceKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegReplaceKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpNewFile: ") + generic_log(lpNewFile)+std::string("$");
logMsg += std::string("lpOldFile: ") + generic_log(lpOldFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegReplaceKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpNewFile: ") + generic_log(lpNewFile)+std::string("$");
logMsg += std::string("lpOldFile: ") + generic_log(lpOldFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegReplaceKeyA],
    	        	original_bytes[(int)Hook::Functions::RegReplaceKeyA], 6, NULL);

            LSTATUS result = RegReplaceKeyA(hKey,lpSubKey,lpNewFile,lpOldFile);
            Hook reset_hook { Hook::Functions::RegReplaceKeyA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegRestoreKeyA(
       HKEY   hKey,
       LPCSTR lpFile,
       DWORD  dwFlags
){
            char whatToDo = WhatToDoInFunction(*"RegRestoreKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegRestoreKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegRestoreKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegRestoreKeyA],
    	        	original_bytes[(int)Hook::Functions::RegRestoreKeyA], 6, NULL);

            LSTATUS result = RegRestoreKeyA(hKey,lpFile,dwFlags);
            Hook reset_hook { Hook::Functions::RegRestoreKeyA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegSaveKeyA(
                 HKEY                        hKey,
                 LPCSTR                      lpFile,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes
){
            char whatToDo = WhatToDoInFunction(*"RegSaveKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegSaveKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegSaveKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegSaveKeyA],
    	        	original_bytes[(int)Hook::Functions::RegSaveKeyA], 6, NULL);

            LSTATUS result = RegSaveKeyA(hKey,lpFile,lpSecurityAttributes);
            Hook reset_hook { Hook::Functions::RegSaveKeyA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegSaveKeyExA(
                 HKEY                        hKey,
                 LPCSTR                      lpFile,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                 DWORD                       Flags
){
            char whatToDo = WhatToDoInFunction(*"RegSaveKeyExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegSaveKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegSaveKeyExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpFile: ") + generic_log(lpFile)+std::string("$");
logMsg += std::string("lpSecurityAttributes: ") + generic_log(lpSecurityAttributes)+std::string("$");
logMsg += std::string("Flags: ") + generic_log(Flags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegSaveKeyExA],
    	        	original_bytes[(int)Hook::Functions::RegSaveKeyExA], 6, NULL);

            LSTATUS result = RegSaveKeyExA(hKey,lpFile,lpSecurityAttributes,Flags);
            Hook reset_hook { Hook::Functions::RegSaveKeyExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegSetKeyValueA(
                 HKEY    hKey,
                 LPCSTR  lpSubKey,
                 LPCSTR  lpValueName,
                 DWORD   dwType,
                 LPCVOID lpData,
                 DWORD   cbData
){
            char whatToDo = WhatToDoInFunction(*"RegSetKeyValueA");
            if(whatToDo == *"b"){
                std::string logMsg("RegSetKeyValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("dwType: ") + generic_log(dwType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("cbData: ") + generic_log(cbData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegSetKeyValueA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("dwType: ") + generic_log(dwType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("cbData: ") + generic_log(cbData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegSetKeyValueA],
    	        	original_bytes[(int)Hook::Functions::RegSetKeyValueA], 6, NULL);

            LSTATUS result = RegSetKeyValueA(hKey,lpSubKey,lpValueName,dwType,lpData,cbData);
            Hook reset_hook { Hook::Functions::RegSetKeyValueA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegSetKeySecurity(
       HKEY                 hKey,
       SECURITY_INFORMATION SecurityInformation,
       PSECURITY_DESCRIPTOR pSecurityDescriptor
){
            char whatToDo = WhatToDoInFunction(*"RegSetKeySecurity");
            if(whatToDo == *"b"){
                std::string logMsg("RegSetKeySecurity$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("SecurityInformation: ") + generic_log(SecurityInformation)+std::string("$");
logMsg += std::string("pSecurityDescriptor: ") + generic_log(pSecurityDescriptor)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegSetKeySecurity$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("SecurityInformation: ") + generic_log(SecurityInformation)+std::string("$");
logMsg += std::string("pSecurityDescriptor: ") + generic_log(pSecurityDescriptor)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegSetKeySecurity],
    	        	original_bytes[(int)Hook::Functions::RegSetKeySecurity], 6, NULL);

            LSTATUS result = RegSetKeySecurity(hKey,SecurityInformation,pSecurityDescriptor);
            Hook reset_hook { Hook::Functions::RegSetKeySecurity};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegSetValueExA(
                 HKEY       hKey,
                 LPCSTR     lpValueName,
                 DWORD      Reserved,
                 DWORD      dwType,
                 const BYTE *lpData,
                 DWORD      cbData
){
            char whatToDo = WhatToDoInFunction(*"RegSetValueExA");
            if(whatToDo == *"b"){
                std::string logMsg("RegSetValueExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("dwType: ") + generic_log(dwType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("cbData: ") + generic_log(cbData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegSetValueExA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpValueName: ") + generic_log(lpValueName)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");
logMsg += std::string("dwType: ") + generic_log(dwType)+std::string("$");
logMsg += std::string("lpData: ") + generic_log(lpData)+std::string("$");
logMsg += std::string("cbData: ") + generic_log(cbData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegSetValueExA],
    	        	original_bytes[(int)Hook::Functions::RegSetValueExA], 6, NULL);

            LSTATUS result = RegSetValueExA(hKey,lpValueName,Reserved,dwType,lpData,cbData);
            Hook reset_hook { Hook::Functions::RegSetValueExA};
            reset_hook.deploy_hook();

            return result;

}
LSTATUS __stdcall newRegUnLoadKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey
){
            char whatToDo = WhatToDoInFunction(*"RegUnLoadKeyA");
            if(whatToDo == *"b"){
                std::string logMsg("RegUnLoadKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("RegUnLoadKeyA$");logMsg += std::string("hKey: ") + generic_log(hKey)+std::string("$");
logMsg += std::string("lpSubKey: ") + generic_log(lpSubKey)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::RegUnLoadKeyA],
    	        	original_bytes[(int)Hook::Functions::RegUnLoadKeyA], 6, NULL);

            LSTATUS result = RegUnLoadKeyA(hKey,lpSubKey);
            Hook reset_hook { Hook::Functions::RegUnLoadKeyA};
            reset_hook.deploy_hook();

            return result;

}
UINT __stdcall newGetPrivateProfileInt(
       LPCTSTR lpAppName,
       LPCTSTR lpKeyName,
       INT     nDefault,
       LPCTSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"GetPrivateProfileInt");
            if(whatToDo == *"b"){
                std::string logMsg("GetPrivateProfileInt$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("nDefault: ") + generic_log(nDefault)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetPrivateProfileInt$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("nDefault: ") + generic_log(nDefault)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileInt],
    	        	original_bytes[(int)Hook::Functions::GetPrivateProfileInt], 6, NULL);

            UINT result = GetPrivateProfileInt(lpAppName,lpKeyName,nDefault,lpFileName);
            Hook reset_hook { Hook::Functions::GetPrivateProfileInt};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetPrivateProfileSection(
        LPCTSTR lpAppName,
        LPTSTR  lpReturnedString,
        DWORD   nSize,
        LPCTSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"GetPrivateProfileSection");
            if(whatToDo == *"b"){
                std::string logMsg("GetPrivateProfileSection$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetPrivateProfileSection$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileSection],
    	        	original_bytes[(int)Hook::Functions::GetPrivateProfileSection], 6, NULL);

            DWORD result = GetPrivateProfileSection(lpAppName,lpReturnedString,nSize,lpFileName);
            Hook reset_hook { Hook::Functions::GetPrivateProfileSection};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetPrivateProfileSectionNames(
        LPTSTR  lpszReturnBuffer,
        DWORD   nSize,
        LPCTSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"GetPrivateProfileSectionNames");
            if(whatToDo == *"b"){
                std::string logMsg("GetPrivateProfileSectionNames$");logMsg += std::string("lpszReturnBuffer: ") + generic_log(lpszReturnBuffer)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetPrivateProfileSectionNames$");logMsg += std::string("lpszReturnBuffer: ") + generic_log(lpszReturnBuffer)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileSectionNames],
    	        	original_bytes[(int)Hook::Functions::GetPrivateProfileSectionNames], 6, NULL);

            DWORD result = GetPrivateProfileSectionNames(lpszReturnBuffer,nSize,lpFileName);
            Hook reset_hook { Hook::Functions::GetPrivateProfileSectionNames};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetPrivateProfileString(
        LPCTSTR lpAppName,
        LPCTSTR lpKeyName,
        LPCTSTR lpDefault,
        LPTSTR  lpReturnedString,
        DWORD   nSize,
        LPCTSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"GetPrivateProfileString");
            if(whatToDo == *"b"){
                std::string logMsg("GetPrivateProfileString$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpDefault: ") + generic_log(lpDefault)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetPrivateProfileString$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpDefault: ") + generic_log(lpDefault)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileString],
    	        	original_bytes[(int)Hook::Functions::GetPrivateProfileString], 6, NULL);

            DWORD result = GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,lpFileName);
            Hook reset_hook { Hook::Functions::GetPrivateProfileString};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newGetPrivateProfileStruct(
        LPCTSTR lpszSection,
        LPCTSTR lpszKey,
        LPVOID  lpStruct,
        UINT    uSizeStruct,
        LPCTSTR szFile
){
            char whatToDo = WhatToDoInFunction(*"GetPrivateProfileStruct");
            if(whatToDo == *"b"){
                std::string logMsg("GetPrivateProfileStruct$");logMsg += std::string("lpszSection: ") + generic_log(lpszSection)+std::string("$");
logMsg += std::string("lpszKey: ") + generic_log(lpszKey)+std::string("$");
logMsg += std::string("lpStruct: ") + generic_log(lpStruct)+std::string("$");
logMsg += std::string("uSizeStruct: ") + generic_log(uSizeStruct)+std::string("$");
logMsg += std::string("szFile: ") + generic_log(szFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetPrivateProfileStruct$");logMsg += std::string("lpszSection: ") + generic_log(lpszSection)+std::string("$");
logMsg += std::string("lpszKey: ") + generic_log(lpszKey)+std::string("$");
logMsg += std::string("lpStruct: ") + generic_log(lpStruct)+std::string("$");
logMsg += std::string("uSizeStruct: ") + generic_log(uSizeStruct)+std::string("$");
logMsg += std::string("szFile: ") + generic_log(szFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileStruct],
    	        	original_bytes[(int)Hook::Functions::GetPrivateProfileStruct], 6, NULL);

            BOOL result = GetPrivateProfileStruct(lpszSection,lpszKey,lpStruct,uSizeStruct,szFile);
            Hook reset_hook { Hook::Functions::GetPrivateProfileStruct};
            reset_hook.deploy_hook();

            return result;

}
UINT __stdcall newGetProfileIntA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       INT    nDefault
){
            char whatToDo = WhatToDoInFunction(*"GetProfileIntA");
            if(whatToDo == *"b"){
                std::string logMsg("GetProfileIntA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("nDefault: ") + generic_log(nDefault)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetProfileIntA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("nDefault: ") + generic_log(nDefault)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetProfileIntA],
    	        	original_bytes[(int)Hook::Functions::GetProfileIntA], 6, NULL);

            UINT result = GetProfileIntA(lpAppName,lpKeyName,nDefault);
            Hook reset_hook { Hook::Functions::GetProfileIntA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetProfileSectionA(
        LPCSTR lpAppName,
        LPSTR  lpReturnedString,
        DWORD  nSize
){
            char whatToDo = WhatToDoInFunction(*"GetProfileSectionA");
            if(whatToDo == *"b"){
                std::string logMsg("GetProfileSectionA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetProfileSectionA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetProfileSectionA],
    	        	original_bytes[(int)Hook::Functions::GetProfileSectionA], 6, NULL);

            DWORD result = GetProfileSectionA(lpAppName,lpReturnedString,nSize);
            Hook reset_hook { Hook::Functions::GetProfileSectionA};
            reset_hook.deploy_hook();

            return result;

}
DWORD __stdcall newGetProfileStringA(
        LPCSTR lpAppName,
        LPCSTR lpKeyName,
        LPCSTR lpDefault,
        LPSTR  lpReturnedString,
        DWORD  nSize
){
            char whatToDo = WhatToDoInFunction(*"GetProfileStringA");
            if(whatToDo == *"b"){
                std::string logMsg("GetProfileStringA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpDefault: ") + generic_log(lpDefault)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("GetProfileStringA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpDefault: ") + generic_log(lpDefault)+std::string("$");
logMsg += std::string("lpReturnedString: ") + generic_log(lpReturnedString)+std::string("$");
logMsg += std::string("nSize: ") + generic_log(nSize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::GetProfileStringA],
    	        	original_bytes[(int)Hook::Functions::GetProfileStringA], 6, NULL);

            DWORD result = GetProfileStringA(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize);
            Hook reset_hook { Hook::Functions::GetProfileStringA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWritePrivateProfileSectionA(
       LPCSTR lpAppName,
       LPCSTR lpString,
       LPCSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"WritePrivateProfileSectionA");
            if(whatToDo == *"b"){
                std::string logMsg("WritePrivateProfileSectionA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WritePrivateProfileSectionA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WritePrivateProfileSectionA],
    	        	original_bytes[(int)Hook::Functions::WritePrivateProfileSectionA], 6, NULL);

            BOOL result = WritePrivateProfileSectionA(lpAppName,lpString,lpFileName);
            Hook reset_hook { Hook::Functions::WritePrivateProfileSectionA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWritePrivateProfileStringA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       LPCSTR lpString,
       LPCSTR lpFileName
){
            char whatToDo = WhatToDoInFunction(*"WritePrivateProfileStringA");
            if(whatToDo == *"b"){
                std::string logMsg("WritePrivateProfileStringA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WritePrivateProfileStringA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");
logMsg += std::string("lpFileName: ") + generic_log(lpFileName)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WritePrivateProfileStringA],
    	        	original_bytes[(int)Hook::Functions::WritePrivateProfileStringA], 6, NULL);

            BOOL result = WritePrivateProfileStringA(lpAppName,lpKeyName,lpString,lpFileName);
            Hook reset_hook { Hook::Functions::WritePrivateProfileStringA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWritePrivateProfileStructA(
       LPCSTR lpszSection,
       LPCSTR lpszKey,
       LPVOID lpStruct,
       UINT   uSizeStruct,
       LPCSTR szFile
){
            char whatToDo = WhatToDoInFunction(*"WritePrivateProfileStructA");
            if(whatToDo == *"b"){
                std::string logMsg("WritePrivateProfileStructA$");logMsg += std::string("lpszSection: ") + generic_log(lpszSection)+std::string("$");
logMsg += std::string("lpszKey: ") + generic_log(lpszKey)+std::string("$");
logMsg += std::string("lpStruct: ") + generic_log(lpStruct)+std::string("$");
logMsg += std::string("uSizeStruct: ") + generic_log(uSizeStruct)+std::string("$");
logMsg += std::string("szFile: ") + generic_log(szFile)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WritePrivateProfileStructA$");logMsg += std::string("lpszSection: ") + generic_log(lpszSection)+std::string("$");
logMsg += std::string("lpszKey: ") + generic_log(lpszKey)+std::string("$");
logMsg += std::string("lpStruct: ") + generic_log(lpStruct)+std::string("$");
logMsg += std::string("uSizeStruct: ") + generic_log(uSizeStruct)+std::string("$");
logMsg += std::string("szFile: ") + generic_log(szFile)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WritePrivateProfileStructA],
    	        	original_bytes[(int)Hook::Functions::WritePrivateProfileStructA], 6, NULL);

            BOOL result = WritePrivateProfileStructA(lpszSection,lpszKey,lpStruct,uSizeStruct,szFile);
            Hook reset_hook { Hook::Functions::WritePrivateProfileStructA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWriteProfileSectionA(
       LPCSTR lpAppName,
       LPCSTR lpString
){
            char whatToDo = WhatToDoInFunction(*"WriteProfileSectionA");
            if(whatToDo == *"b"){
                std::string logMsg("WriteProfileSectionA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WriteProfileSectionA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WriteProfileSectionA],
    	        	original_bytes[(int)Hook::Functions::WriteProfileSectionA], 6, NULL);

            BOOL result = WriteProfileSectionA(lpAppName,lpString);
            Hook reset_hook { Hook::Functions::WriteProfileSectionA};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWriteProfileStringA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       LPCSTR lpString
){
            char whatToDo = WhatToDoInFunction(*"WriteProfileStringA");
            if(whatToDo == *"b"){
                std::string logMsg("WriteProfileStringA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WriteProfileStringA$");logMsg += std::string("lpAppName: ") + generic_log(lpAppName)+std::string("$");
logMsg += std::string("lpKeyName: ") + generic_log(lpKeyName)+std::string("$");
logMsg += std::string("lpString: ") + generic_log(lpString)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WriteProfileStringA],
    	        	original_bytes[(int)Hook::Functions::WriteProfileStringA], 6, NULL);

            BOOL result = WriteProfileStringA(lpAppName,lpKeyName,lpString);
            Hook reset_hook { Hook::Functions::WriteProfileStringA};
            reset_hook.deploy_hook();

            return result;

}
}