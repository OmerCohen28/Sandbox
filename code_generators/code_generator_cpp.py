from get_func_info import get_data

insert = "\"%Y-%m-%d %H:%M:%S\""

code = """#include <iostream>
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
        strftime(buffer, sizeof(buffer), """+insert+""", timeinfo);
        return std::string(buffer);
    }
    if constexpr (std::is_same_v < T, timeval*>) {
        char buffer[32];
        time_t now = (*arg).tv_sec;
        struct tm* timeinfo = localtime(&now);
        strftime(buffer, sizeof(buffer), """+insert+""", timeinfo);
        return std::string(buffer);
    }
    return "Can't Parse Data";
}

namespace newFunctions {
"""


'''

HANDLE __stdcall newCreateFileA(){
    	//unhook function
    
    char do = WhatToDo();
    if(do == "b"){
        //char* msg = new msg{whatever}
         //log1(msg,msg.len)
        return NULL;
    }
    if(do == "w"){
        WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::{func}],
		original_bytes[(int)Hook::Functions::{func}], 6, NULL);
        {return type} result = {func}({params});
        Hook reset_hook { Hook::Functions::{func}};
        reset_hook.deploy_hook()

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)
        Hook.set_hook();
    }
}



'''
x= {""}
with open("..\\inlineHook\\codeGeneratedFunctionsSockets.h",'r') as file:
    data = file.read().split("{")[1].strip("}").split(";")
for func in data:
    try:
        func_name,return_type,params_list,params_type_list = get_data(func)
        for type in params_type_list:
            x.add(type)
    except:
        continue
    added_code = "std::string logMsg(\"func$\");"
    for param in params_list:
        if param:
            added_code+= f"logMsg += std::string(\"{param}: \") + generic_log({param})+std::string(\"$\");\n"
    if return_type != "void":
        func+="""{
            char whatToDo = WhatToDoInFunction(\"func\");
            if(whatToDo == *\"b\"){
                """ + added_code + """
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *\"w\"){    	       
                """+added_code+"""
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::func],
    	        	original_bytes[(int)Hook::Functions::func], 6, NULL);

            return_type result = func(params);
            Hook reset_hook { Hook::Functions::func};
            reset_hook.deploy_hook();

            return result;

}"""
    else:
        func+="""{
            char whatToDo = WhatToDoInFunction(\"func\");
            if(whatToDo == *\"b\"){
                """+added_code+"""
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *\"w\"){    	       
                """+added_code+"""
                log(logMsg);
            }
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::func],
    		original_bytes[(int)Hook::Functions::func], 6, NULL);

        func(params);
        Hook reset_hook { Hook::Functions::func};
        reset_hook.deploy_hook();

}"""

    func_name = func_name.replace("new","",1)
    print(func_name)
    func = func.replace("func",func_name)
    func = func.replace("return_type",return_type)
    func = func.replace("params",",".join(params_list))
    code+=func

code+="\n}"

with open("..\\inlineHook\\codeGeneratedFunctionsSockets.cpp",'w') as file:
    file.write(code)