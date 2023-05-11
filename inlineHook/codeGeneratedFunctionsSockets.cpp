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
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }
    if constexpr (std::is_same_v < T, timeval*>) {
        char buffer[32];
        time_t now = (*arg).tv_sec;
        struct tm* timeinfo = localtime(&now);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }
    return "Can't Parse Data";
}

namespace newFunctions {

SOCKET WSAAPI __stdcall newaccept(
            SOCKET   s,
            sockaddr *addr,
            int      *addrlen
){
            char whatToDo = WhatToDoInFunction("accept");
            if(whatToDo == *"b"){
                std::string logMsg("accept$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("addrlen: ") + generic_log(addrlen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("accept$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("addrlen: ") + generic_log(addrlen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::accept],
    	        	original_bytes[(int)Hook::Functions::accept], 6, NULL);

            SOCKET result = accept(s,addr,addrlen);
            Hook reset_hook { Hook::Functions::accept};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newbind(
       SOCKET         s,
       const sockaddr *addr,
       int            namelen
){
            char whatToDo = WhatToDoInFunction("bind");
            if(whatToDo == *"b"){
                std::string logMsg("bind$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("bind$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::bind],
    	        	original_bytes[(int)Hook::Functions::bind], 6, NULL);

            int result = bind(s,addr,namelen);
            Hook reset_hook { Hook::Functions::bind};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newclosesocket(
       SOCKET s
){
            char whatToDo = WhatToDoInFunction("closesocket");
            if(whatToDo == *"b"){
                std::string logMsg("closesocket$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("closesocket$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::closesocket],
    	        	original_bytes[(int)Hook::Functions::closesocket], 6, NULL);

            int result = closesocket(s);
            Hook reset_hook { Hook::Functions::closesocket};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newconnect(
       SOCKET         s,
       const sockaddr *name,
       int            namelen
){
            char whatToDo = WhatToDoInFunction("connect");
            if(whatToDo == *"b"){
                std::string logMsg("connect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("connect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::connect],
    	        	original_bytes[(int)Hook::Functions::connect], 6, NULL);

            int result = connect(s,name,namelen);
            Hook reset_hook { Hook::Functions::connect};
            reset_hook.deploy_hook();

            return result;

}
char* __stdcall newgai_strerrorA(
       int ecode
){
            char whatToDo = WhatToDoInFunction("gai_strerrorA");
            if(whatToDo == *"b"){
                std::string logMsg("gai_strerrorA$");logMsg += std::string("ecode: ") + generic_log(ecode)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("gai_strerrorA$");logMsg += std::string("ecode: ") + generic_log(ecode)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::gai_strerrorA],
    	        	original_bytes[(int)Hook::Functions::gai_strerrorA], 6, NULL);

            char* result = gai_strerrorA(ecode);
            Hook reset_hook { Hook::Functions::gai_strerrorA};
            reset_hook.deploy_hook();

            return result;

}

int __stdcall newgethostname(
        char *name,
        int  namelen
){
            char whatToDo = WhatToDoInFunction("gethostname");
            if(whatToDo == *"b"){
                std::string logMsg("gethostname$");logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("gethostname$");logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::gethostname],
    	        	original_bytes[(int)Hook::Functions::gethostname], 6, NULL);

            int result = gethostname(name,namelen);
            Hook reset_hook { Hook::Functions::gethostname};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newgetpeername(
            SOCKET   s,
            sockaddr *name,
            int      *namelen
){
            char whatToDo = WhatToDoInFunction("getpeername");
            if(whatToDo == *"b"){
                std::string logMsg("getpeername$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getpeername$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getpeername],
    	        	original_bytes[(int)Hook::Functions::getpeername], 6, NULL);

            int result = getpeername(s,name,namelen);
            Hook reset_hook { Hook::Functions::getpeername};
            reset_hook.deploy_hook();

            return result;

}
protoent* __stdcall newgetprotobyname(
       const char *name
){
            char whatToDo = WhatToDoInFunction("getprotobyname");
            if(whatToDo == *"b"){
                std::string logMsg("getprotobyname$");logMsg += std::string("name: ") + generic_log(name)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getprotobyname$");logMsg += std::string("name: ") + generic_log(name)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getprotobyname],
    	        	original_bytes[(int)Hook::Functions::getprotobyname], 6, NULL);

            protoent* result = getprotobyname(name);
            Hook reset_hook { Hook::Functions::getprotobyname};
            reset_hook.deploy_hook();

            return result;

}
protoent* __stdcall newgetprotobynumber(
  int proto
){
            char whatToDo = WhatToDoInFunction("getprotobynumber");
            if(whatToDo == *"b"){
                std::string logMsg("getprotobynumber$");logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getprotobynumber$");logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getprotobynumber],
    	        	original_bytes[(int)Hook::Functions::getprotobynumber], 6, NULL);

            protoent* result = getprotobynumber(proto);
            Hook reset_hook { Hook::Functions::getprotobynumber};
            reset_hook.deploy_hook();

            return result;

}
servent* __stdcall newgetservbyname(
       const char *name,
       const char *proto
){
            char whatToDo = WhatToDoInFunction("getservbyname");
            if(whatToDo == *"b"){
                std::string logMsg("getservbyname$");logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getservbyname$");logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getservbyname],
    	        	original_bytes[(int)Hook::Functions::getservbyname], 6, NULL);

            servent* result = getservbyname(name,proto);
            Hook reset_hook { Hook::Functions::getservbyname};
            reset_hook.deploy_hook();

            return result;

}
servent* __stdcall newgetservbyport(
       int        port,
       const char *proto
){
            char whatToDo = WhatToDoInFunction("getservbyport");
            if(whatToDo == *"b"){
                std::string logMsg("getservbyport$");logMsg += std::string("port: ") + generic_log(port)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getservbyport$");logMsg += std::string("port: ") + generic_log(port)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getservbyport],
    	        	original_bytes[(int)Hook::Functions::getservbyport], 6, NULL);

            servent* result = getservbyport(port,proto);
            Hook reset_hook { Hook::Functions::getservbyport};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newgetsockname(
            SOCKET   s,
            sockaddr *name,
            int      *namelen
){
            char whatToDo = WhatToDoInFunction("getsockname");
            if(whatToDo == *"b"){
                std::string logMsg("getsockname$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getsockname$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getsockname],
    	        	original_bytes[(int)Hook::Functions::getsockname], 6, NULL);

            int result = getsockname(s,name,namelen);
            Hook reset_hook { Hook::Functions::getsockname};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newgetsockopt(
            SOCKET s,
            int    level,
            int    optname,
            char   *optval,
            int    *optlen
){
            char whatToDo = WhatToDoInFunction("getsockopt");
            if(whatToDo == *"b"){
                std::string logMsg("getsockopt$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("level: ") + generic_log(level)+std::string("$");
logMsg += std::string("optname: ") + generic_log(optname)+std::string("$");
logMsg += std::string("optval: ") + generic_log(optval)+std::string("$");
logMsg += std::string("optlen: ") + generic_log(optlen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("getsockopt$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("level: ") + generic_log(level)+std::string("$");
logMsg += std::string("optname: ") + generic_log(optname)+std::string("$");
logMsg += std::string("optval: ") + generic_log(optval)+std::string("$");
logMsg += std::string("optlen: ") + generic_log(optlen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::getsockopt],
    	        	original_bytes[(int)Hook::Functions::getsockopt], 6, NULL);

            int result = getsockopt(s,level,optname,optval,optlen);
            Hook reset_hook { Hook::Functions::getsockopt};
            reset_hook.deploy_hook();

            return result;

}
u_short __stdcall newhtons(
       u_short hostshort
){
            char whatToDo = WhatToDoInFunction("htons");
            if(whatToDo == *"b"){
                std::string logMsg("htons$");logMsg += std::string("hostshort: ") + generic_log(hostshort)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("htons$");logMsg += std::string("hostshort: ") + generic_log(hostshort)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::htons],
    	        	original_bytes[(int)Hook::Functions::htons], 6, NULL);

            u_short result = htons(hostshort);
            Hook reset_hook { Hook::Functions::htons};
            reset_hook.deploy_hook();

            return result;

}
unsigned long WSAAPI __stdcall newinet_addr(
  const char *cp
){
            char whatToDo = WhatToDoInFunction("inet_addr");
            if(whatToDo == *"b"){
                std::string logMsg("inet_addr$");logMsg += std::string("cp: ") + generic_log(cp)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("inet_addr$");logMsg += std::string("cp: ") + generic_log(cp)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::inet_addr],
    	        	original_bytes[(int)Hook::Functions::inet_addr], 6, NULL);

            unsigned result = inet_addr(cp);
            Hook reset_hook { Hook::Functions::inet_addr};
            reset_hook.deploy_hook();

            return result;

}
char *WSAAPI __stdcall newinet_ntoa(
  in_addr in
){
            char whatToDo = WhatToDoInFunction("inet_ntoa");
            if(whatToDo == *"b"){
                std::string logMsg("inet_ntoa$");logMsg += std::string("in: ") + generic_log(in)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("inet_ntoa$");logMsg += std::string("in: ") + generic_log(in)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::inet_ntoa],
    	        	original_bytes[(int)Hook::Functions::inet_ntoa], 6, NULL);

            char* result = inet_ntoa(in);
            Hook reset_hook { Hook::Functions::inet_ntoa};
            reset_hook.deploy_hook();

            return result;

}
PCWSTR WSAAPI __stdcall newInetNtopW(
        INT        Family,
        const VOID *pAddr,
        PWSTR      pStringBuf,
        size_t     StringBufSize
){
            char whatToDo = WhatToDoInFunction("InetNtopW");
            if(whatToDo == *"b"){
                std::string logMsg("InetNtopW$");logMsg += std::string("Family: ") + generic_log(Family)+std::string("$");
logMsg += std::string("pAddr: ") + generic_log(pAddr)+std::string("$");
logMsg += std::string("pStringBuf: ") + generic_log(pStringBuf)+std::string("$");
logMsg += std::string("StringBufSize: ") + generic_log(StringBufSize)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("InetNtopW$");logMsg += std::string("Family: ") + generic_log(Family)+std::string("$");
logMsg += std::string("pAddr: ") + generic_log(pAddr)+std::string("$");
logMsg += std::string("pStringBuf: ") + generic_log(pStringBuf)+std::string("$");
logMsg += std::string("StringBufSize: ") + generic_log(StringBufSize)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::InetNtopW],
    	        	original_bytes[(int)Hook::Functions::InetNtopW], 6, NULL);

            PCWSTR result = InetNtopW(Family,pAddr,pStringBuf,StringBufSize);
            Hook reset_hook { Hook::Functions::InetNtopW};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newInetPtonW(
        INT    Family,
        PCWSTR pszAddrString,
        PVOID  pAddrBuf
){
            char whatToDo = WhatToDoInFunction("InetPtonW");
            if(whatToDo == *"b"){
                std::string logMsg("InetPtonW$");logMsg += std::string("Family: ") + generic_log(Family)+std::string("$");
logMsg += std::string("pszAddrString: ") + generic_log(pszAddrString)+std::string("$");
logMsg += std::string("pAddrBuf: ") + generic_log(pAddrBuf)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("InetPtonW$");logMsg += std::string("Family: ") + generic_log(Family)+std::string("$");
logMsg += std::string("pszAddrString: ") + generic_log(pszAddrString)+std::string("$");
logMsg += std::string("pAddrBuf: ") + generic_log(pAddrBuf)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::InetPtonW],
    	        	original_bytes[(int)Hook::Functions::InetPtonW], 6, NULL);

            INT result = InetPtonW(Family,pszAddrString,pAddrBuf);
            Hook reset_hook { Hook::Functions::InetPtonW};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newioctlsocket(
            SOCKET s,
            long   cmd,
            u_long *argp
){
            char whatToDo = WhatToDoInFunction("ioctlsocket");
            if(whatToDo == *"b"){
                std::string logMsg("ioctlsocket$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("cmd: ") + generic_log(cmd)+std::string("$");
logMsg += std::string("argp: ") + generic_log(argp)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ioctlsocket$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("cmd: ") + generic_log(cmd)+std::string("$");
logMsg += std::string("argp: ") + generic_log(argp)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ioctlsocket],
    	        	original_bytes[(int)Hook::Functions::ioctlsocket], 6, NULL);

            int result = ioctlsocket(s,cmd,argp);
            Hook reset_hook { Hook::Functions::ioctlsocket};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newlisten(
       SOCKET s,
       int    backlog
){
            char whatToDo = WhatToDoInFunction("listen");
            if(whatToDo == *"b"){
                std::string logMsg("listen$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("backlog: ") + generic_log(backlog)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("listen$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("backlog: ") + generic_log(backlog)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::listen],
    	        	original_bytes[(int)Hook::Functions::listen], 6, NULL);

            int result = listen(s,backlog);
            Hook reset_hook { Hook::Functions::listen};
            reset_hook.deploy_hook();

            return result;

}
u_long __stdcall newntohl(
       u_long netlong
){
            char whatToDo = WhatToDoInFunction("ntohl");
            if(whatToDo == *"b"){
                std::string logMsg("ntohl$");logMsg += std::string("netlong: ") + generic_log(netlong)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ntohl$");logMsg += std::string("netlong: ") + generic_log(netlong)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ntohl],
    	        	original_bytes[(int)Hook::Functions::ntohl], 6, NULL);

            u_long result = ntohl(netlong);
            Hook reset_hook { Hook::Functions::ntohl};
            reset_hook.deploy_hook();

            return result;

}
u_short __stdcall newntohs(
       u_short netshort
){
            char whatToDo = WhatToDoInFunction("ntohs");
            if(whatToDo == *"b"){
                std::string logMsg("ntohs$");logMsg += std::string("netshort: ") + generic_log(netshort)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("ntohs$");logMsg += std::string("netshort: ") + generic_log(netshort)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::ntohs],
    	        	original_bytes[(int)Hook::Functions::ntohs], 6, NULL);

            u_short result = ntohs(netshort);
            Hook reset_hook { Hook::Functions::ntohs};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newrecv(
        SOCKET s,
        char   *buf,
        int    len,
        int    flags
){
            char whatToDo = WhatToDoInFunction("recv");
            if(whatToDo == *"b"){
                std::string logMsg("recv$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("recv$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::recv],
    	        	original_bytes[(int)Hook::Functions::recv], 6, NULL);

            int result = recv(s,buf,len,flags);
            Hook reset_hook { Hook::Functions::recv};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newrecvfrom(
                      SOCKET   s,
                      char     *buf,
                      int      len,
                      int      flags,
                      sockaddr *from,
                      int      *fromlen
){
            char whatToDo = WhatToDoInFunction("recvfrom");
            if(whatToDo == *"b"){
                std::string logMsg("recvfrom$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");
logMsg += std::string("from: ") + generic_log(from)+std::string("$");
logMsg += std::string("fromlen: ") + generic_log(fromlen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("recvfrom$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");
logMsg += std::string("from: ") + generic_log(from)+std::string("$");
logMsg += std::string("fromlen: ") + generic_log(fromlen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::recvfrom],
    	        	original_bytes[(int)Hook::Functions::recvfrom], 6, NULL);

            int result = recvfrom(s,buf,len,flags,from,fromlen);
            Hook reset_hook { Hook::Functions::recvfrom};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newselect(
            int           nfds,
            fd_set        *readfds,
            fd_set        *writefds,
            fd_set        *exceptfds,
            const timeval *timeout
){
            char whatToDo = WhatToDoInFunction("select");
            if(whatToDo == *"b"){
                std::string logMsg("select$");logMsg += std::string("nfds: ") + generic_log(nfds)+std::string("$");
logMsg += std::string("readfds: ") + generic_log(readfds)+std::string("$");
logMsg += std::string("writefds: ") + generic_log(writefds)+std::string("$");
logMsg += std::string("exceptfds: ") + generic_log(exceptfds)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("select$");logMsg += std::string("nfds: ") + generic_log(nfds)+std::string("$");
logMsg += std::string("readfds: ") + generic_log(readfds)+std::string("$");
logMsg += std::string("writefds: ") + generic_log(writefds)+std::string("$");
logMsg += std::string("exceptfds: ") + generic_log(exceptfds)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::select],
    	        	original_bytes[(int)Hook::Functions::select], 6, NULL);

            int result = select(nfds,readfds,writefds,exceptfds,timeout);
            Hook reset_hook { Hook::Functions::select};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newsend(
       SOCKET     s,
       const char *buf,
       int        len,
       int        flags
){
            char whatToDo = WhatToDoInFunction("send");
            if(whatToDo == *"b"){
                std::string logMsg("send$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("send$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::send],
    	        	original_bytes[(int)Hook::Functions::send], 6, NULL);

            int result = send(s,buf,len,flags);
            Hook reset_hook { Hook::Functions::send};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newsendto(
       SOCKET         s,
       const char     *buf,
       int            len,
       int            flags,
       const sockaddr *to,
       int            tolen
){
            char whatToDo = WhatToDoInFunction("sendto");
            if(whatToDo == *"b"){
                std::string logMsg("sendto$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");
logMsg += std::string("to: ") + generic_log(to)+std::string("$");
logMsg += std::string("tolen: ") + generic_log(tolen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("sendto$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("flags: ") + generic_log(flags)+std::string("$");
logMsg += std::string("to: ") + generic_log(to)+std::string("$");
logMsg += std::string("tolen: ") + generic_log(tolen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::sendto],
    	        	original_bytes[(int)Hook::Functions::sendto], 6, NULL);

            int result = sendto(s,buf,len,flags,to,tolen);
            Hook reset_hook { Hook::Functions::sendto};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newsetsockopt(
       SOCKET     s,
       int        level,
       int        optname,
       const char *optval,
       int        optlen
){
            char whatToDo = WhatToDoInFunction("setsockopt");
            if(whatToDo == *"b"){
                std::string logMsg("setsockopt$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("level: ") + generic_log(level)+std::string("$");
logMsg += std::string("optname: ") + generic_log(optname)+std::string("$");
logMsg += std::string("optval: ") + generic_log(optval)+std::string("$");
logMsg += std::string("optlen: ") + generic_log(optlen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("setsockopt$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("level: ") + generic_log(level)+std::string("$");
logMsg += std::string("optname: ") + generic_log(optname)+std::string("$");
logMsg += std::string("optval: ") + generic_log(optval)+std::string("$");
logMsg += std::string("optlen: ") + generic_log(optlen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::setsockopt],
    	        	original_bytes[(int)Hook::Functions::setsockopt], 6, NULL);

            int result = setsockopt(s,level,optname,optval,optlen);
            Hook reset_hook { Hook::Functions::setsockopt};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newshutdown(
       SOCKET s,
       int    how
){
            char whatToDo = WhatToDoInFunction("shutdown");
            if(whatToDo == *"b"){
                std::string logMsg("shutdown$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("how: ") + generic_log(how)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("shutdown$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("how: ") + generic_log(how)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::shutdown],
    	        	original_bytes[(int)Hook::Functions::shutdown], 6, NULL);

            int result = shutdown(s,how);
            Hook reset_hook { Hook::Functions::shutdown};
            reset_hook.deploy_hook();

            return result;

}
SOCKET WSAAPI __stdcall newsocket(
       int af,
       int type,
       int protocol
){
            char whatToDo = WhatToDoInFunction("socket");
            if(whatToDo == *"b"){
                std::string logMsg("socket$");logMsg += std::string("af: ") + generic_log(af)+std::string("$");
logMsg += std::string("type: ") + generic_log(type)+std::string("$");
logMsg += std::string("protocol: ") + generic_log(protocol)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("socket$");logMsg += std::string("af: ") + generic_log(af)+std::string("$");
logMsg += std::string("type: ") + generic_log(type)+std::string("$");
logMsg += std::string("protocol: ") + generic_log(protocol)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::socket],
    	        	original_bytes[(int)Hook::Functions::socket], 6, NULL);

            SOCKET result = socket(af,type,protocol);
            Hook reset_hook { Hook::Functions::socket};
            reset_hook.deploy_hook();

            return result;

}
SOCKET WSAAPI __stdcall newWSAAccept(
            SOCKET          s,
            sockaddr        *addr,
            LPINT           addrlen,
            LPCONDITIONPROC lpfnCondition,
            DWORD_PTR       dwCallbackData
){
            char whatToDo = WhatToDoInFunction("WSAAccept");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAccept$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("addrlen: ") + generic_log(addrlen)+std::string("$");
logMsg += std::string("lpfnCondition: ") + generic_log(lpfnCondition)+std::string("$");
logMsg += std::string("dwCallbackData: ") + generic_log(dwCallbackData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAccept$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("addrlen: ") + generic_log(addrlen)+std::string("$");
logMsg += std::string("lpfnCondition: ") + generic_log(lpfnCondition)+std::string("$");
logMsg += std::string("dwCallbackData: ") + generic_log(dwCallbackData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAccept],
    	        	original_bytes[(int)Hook::Functions::WSAAccept], 6, NULL);

            SOCKET result = WSAAccept(s,addr,addrlen,lpfnCondition,dwCallbackData);
            Hook reset_hook { Hook::Functions::WSAAccept};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAAddressToStringA(
                 LPSOCKADDR          lpsaAddress,
                 DWORD               dwAddressLength,
                 LPWSAPROTOCOL_INFOA lpProtocolInfo,
                 LPSTR               lpszAddressString,
                 LPDWORD             lpdwAddressStringLength
){
            char whatToDo = WhatToDoInFunction("WSAAddressToStringA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAddressToStringA$");logMsg += std::string("lpsaAddress: ") + generic_log(lpsaAddress)+std::string("$");
logMsg += std::string("dwAddressLength: ") + generic_log(dwAddressLength)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");
logMsg += std::string("lpszAddressString: ") + generic_log(lpszAddressString)+std::string("$");
logMsg += std::string("lpdwAddressStringLength: ") + generic_log(lpdwAddressStringLength)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAddressToStringA$");logMsg += std::string("lpsaAddress: ") + generic_log(lpsaAddress)+std::string("$");
logMsg += std::string("dwAddressLength: ") + generic_log(dwAddressLength)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");
logMsg += std::string("lpszAddressString: ") + generic_log(lpszAddressString)+std::string("$");
logMsg += std::string("lpdwAddressStringLength: ") + generic_log(lpdwAddressStringLength)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAddressToStringA],
    	        	original_bytes[(int)Hook::Functions::WSAAddressToStringA], 6, NULL);

            INT result = WSAAddressToStringA(lpsaAddress,dwAddressLength,lpProtocolInfo,lpszAddressString,lpdwAddressStringLength);
            Hook reset_hook { Hook::Functions::WSAAddressToStringA};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newWSAAsyncGetHostByAddr(
  HWND       hWnd,
  u_int      wMsg,
  const char *addr,
  int        len,
  int        type,
  char       *buf,
  int        buflen
){
            char whatToDo = WhatToDoInFunction("WSAAsyncGetHostByAddr");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncGetHostByAddr$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("type: ") + generic_log(type)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncGetHostByAddr$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("addr: ") + generic_log(addr)+std::string("$");
logMsg += std::string("len: ") + generic_log(len)+std::string("$");
logMsg += std::string("type: ") + generic_log(type)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncGetHostByAddr],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncGetHostByAddr], 6, NULL);

            HANDLE result = WSAAsyncGetHostByAddr(hWnd,wMsg,addr,len,type,buf,buflen);
            Hook reset_hook { Hook::Functions::WSAAsyncGetHostByAddr};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newWSAAsyncGetHostByName(
  HWND       hWnd,
  u_int      wMsg,
  const char *name,
  char       *buf,
  int        buflen
){
            char whatToDo = WhatToDoInFunction("WSAAsyncGetHostByName");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncGetHostByName$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncGetHostByName$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncGetHostByName],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncGetHostByName], 6, NULL);

            HANDLE result = WSAAsyncGetHostByName(hWnd,wMsg,name,buf,buflen);
            Hook reset_hook { Hook::Functions::WSAAsyncGetHostByName};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newWSAAsyncGetProtoByName(
        HWND       hWnd,
        u_int      wMsg,
        const char *name,
        char       *buf,
        int        buflen
){
            char whatToDo = WhatToDoInFunction("WSAAsyncGetProtoByName");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncGetProtoByName$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncGetProtoByName$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncGetProtoByName],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncGetProtoByName], 6, NULL);

            HANDLE result = WSAAsyncGetProtoByName(hWnd,wMsg,name,buf,buflen);
            Hook reset_hook { Hook::Functions::WSAAsyncGetProtoByName};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newWSAAsyncGetProtoByNumber(
        HWND  hWnd,
        u_int wMsg,
        int   number,
        char  *buf,
        int   buflen
){
            char whatToDo = WhatToDoInFunction("WSAAsyncGetProtoByNumber");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncGetProtoByNumber$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("number: ") + generic_log(number)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncGetProtoByNumber$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("number: ") + generic_log(number)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncGetProtoByNumber],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncGetProtoByNumber], 6, NULL);

            HANDLE result = WSAAsyncGetProtoByNumber(hWnd,wMsg,number,buf,buflen);
            Hook reset_hook { Hook::Functions::WSAAsyncGetProtoByNumber};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newWSAAsyncGetServByName(
        HWND       hWnd,
        u_int      wMsg,
        const char *name,
        const char *proto,
        char       *buf,
        int        buflen
){
            char whatToDo = WhatToDoInFunction("WSAAsyncGetServByName");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncGetServByName$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncGetServByName$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncGetServByName],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncGetServByName], 6, NULL);

            HANDLE result = WSAAsyncGetServByName(hWnd,wMsg,name,proto,buf,buflen);
            Hook reset_hook { Hook::Functions::WSAAsyncGetServByName};
            reset_hook.deploy_hook();

            return result;

}
HANDLE __stdcall newWSAAsyncGetServByPort(
        HWND       hWnd,
        u_int      wMsg,
        int        port,
        const char *proto,
        char       *buf,
        int        buflen
){
            char whatToDo = WhatToDoInFunction("WSAAsyncGetServByPort");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncGetServByPort$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("port: ") + generic_log(port)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncGetServByPort$");logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("port: ") + generic_log(port)+std::string("$");
logMsg += std::string("proto: ") + generic_log(proto)+std::string("$");
logMsg += std::string("buf: ") + generic_log(buf)+std::string("$");
logMsg += std::string("buflen: ") + generic_log(buflen)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncGetServByPort],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncGetServByPort], 6, NULL);

            HANDLE result = WSAAsyncGetServByPort(hWnd,wMsg,port,proto,buf,buflen);
            Hook reset_hook { Hook::Functions::WSAAsyncGetServByPort};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newWSAAsyncSelect(
       SOCKET s,
       HWND   hWnd,
       u_int  wMsg,
       long   lEvent
){
            char whatToDo = WhatToDoInFunction("WSAAsyncSelect");
            if(whatToDo == *"b"){
                std::string logMsg("WSAAsyncSelect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("lEvent: ") + generic_log(lEvent)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAAsyncSelect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hWnd: ") + generic_log(hWnd)+std::string("$");
logMsg += std::string("wMsg: ") + generic_log(wMsg)+std::string("$");
logMsg += std::string("lEvent: ") + generic_log(lEvent)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAAsyncSelect],
    	        	original_bytes[(int)Hook::Functions::WSAAsyncSelect], 6, NULL);

            int result = WSAAsyncSelect(s,hWnd,wMsg,lEvent);
            Hook reset_hook { Hook::Functions::WSAAsyncSelect};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newWSACancelAsyncRequest(
       HANDLE hAsyncTaskHandle
){
            char whatToDo = WhatToDoInFunction("WSACancelAsyncRequest");
            if(whatToDo == *"b"){
                std::string logMsg("WSACancelAsyncRequest$");logMsg += std::string("hAsyncTaskHandle: ") + generic_log(hAsyncTaskHandle)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSACancelAsyncRequest$");logMsg += std::string("hAsyncTaskHandle: ") + generic_log(hAsyncTaskHandle)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSACancelAsyncRequest],
    	        	original_bytes[(int)Hook::Functions::WSACancelAsyncRequest], 6, NULL);

            int result = WSACancelAsyncRequest(hAsyncTaskHandle);
            Hook reset_hook { Hook::Functions::WSACancelAsyncRequest};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newWSACleanup(){
            char whatToDo = WhatToDoInFunction("WSACleanup");
            if(whatToDo == *"b"){
                std::string logMsg("WSACleanup$");
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSACleanup$");
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSACleanup],
    	        	original_bytes[(int)Hook::Functions::WSACleanup], 6, NULL);

            int result = WSACleanup();
            Hook reset_hook { Hook::Functions::WSACleanup};
            reset_hook.deploy_hook();

            return result;

}
BOOL WSAAPI __stdcall newWSACloseEvent(
       WSAEVENT hEvent
){
            char whatToDo = WhatToDoInFunction("WSACloseEvent");
            if(whatToDo == *"b"){
                std::string logMsg("WSACloseEvent$");logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSACloseEvent$");logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSACloseEvent],
    	        	original_bytes[(int)Hook::Functions::WSACloseEvent], 6, NULL);

            BOOL result = WSACloseEvent(hEvent);
            Hook reset_hook { Hook::Functions::WSACloseEvent};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAConnect(
        SOCKET         s,
        const sockaddr *name,
        int            namelen,
        LPWSABUF       lpCallerData,
        LPWSABUF       lpCalleeData,
        LPQOS          lpSQOS,
        LPQOS          lpGQOS
){
            char whatToDo = WhatToDoInFunction("WSAConnect");
            if(whatToDo == *"b"){
                std::string logMsg("WSAConnect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");
logMsg += std::string("lpCallerData: ") + generic_log(lpCallerData)+std::string("$");
logMsg += std::string("lpCalleeData: ") + generic_log(lpCalleeData)+std::string("$");
logMsg += std::string("lpSQOS: ") + generic_log(lpSQOS)+std::string("$");
logMsg += std::string("lpGQOS: ") + generic_log(lpGQOS)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAConnect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");
logMsg += std::string("lpCallerData: ") + generic_log(lpCallerData)+std::string("$");
logMsg += std::string("lpCalleeData: ") + generic_log(lpCalleeData)+std::string("$");
logMsg += std::string("lpSQOS: ") + generic_log(lpSQOS)+std::string("$");
logMsg += std::string("lpGQOS: ") + generic_log(lpGQOS)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAConnect],
    	        	original_bytes[(int)Hook::Functions::WSAConnect], 6, NULL);

            int result = WSAConnect(s,name,namelen,lpCallerData,lpCalleeData,lpSQOS,lpGQOS);
            Hook reset_hook { Hook::Functions::WSAConnect};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWSAConnectByList(
            SOCKET               s,
            PSOCKET_ADDRESS_LIST SocketAddress,
            LPDWORD              LocalAddressLength,
            LPSOCKADDR           LocalAddress,
            LPDWORD              RemoteAddressLength,
            LPSOCKADDR           RemoteAddress,
            const timeval        *timeout,
            LPWSAOVERLAPPED      Reserved
){
            char whatToDo = WhatToDoInFunction("WSAConnectByList");
            if(whatToDo == *"b"){
                std::string logMsg("WSAConnectByList$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("SocketAddress: ") + generic_log(SocketAddress)+std::string("$");
logMsg += std::string("LocalAddressLength: ") + generic_log(LocalAddressLength)+std::string("$");
logMsg += std::string("LocalAddress: ") + generic_log(LocalAddress)+std::string("$");
logMsg += std::string("RemoteAddressLength: ") + generic_log(RemoteAddressLength)+std::string("$");
logMsg += std::string("RemoteAddress: ") + generic_log(RemoteAddress)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAConnectByList$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("SocketAddress: ") + generic_log(SocketAddress)+std::string("$");
logMsg += std::string("LocalAddressLength: ") + generic_log(LocalAddressLength)+std::string("$");
logMsg += std::string("LocalAddress: ") + generic_log(LocalAddress)+std::string("$");
logMsg += std::string("RemoteAddressLength: ") + generic_log(RemoteAddressLength)+std::string("$");
logMsg += std::string("RemoteAddress: ") + generic_log(RemoteAddress)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAConnectByList],
    	        	original_bytes[(int)Hook::Functions::WSAConnectByList], 6, NULL);

            BOOL result = WSAConnectByList(s,SocketAddress,LocalAddressLength,LocalAddress,RemoteAddressLength,RemoteAddress,timeout,Reserved);
            Hook reset_hook { Hook::Functions::WSAConnectByList};
            reset_hook.deploy_hook();

            return result;

}
BOOL __stdcall newWSAConnectByNameA(
            SOCKET          s,
            LPCSTR          nodename,
            LPCSTR          servicename,
            LPDWORD         LocalAddressLength,
            LPSOCKADDR      LocalAddress,
            LPDWORD         RemoteAddressLength,
            LPSOCKADDR      RemoteAddress,
            const timeval   *timeout,
            LPWSAOVERLAPPED Reserved
){
            char whatToDo = WhatToDoInFunction("WSAConnectByNameA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAConnectByNameA$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("nodename: ") + generic_log(nodename)+std::string("$");
logMsg += std::string("servicename: ") + generic_log(servicename)+std::string("$");
logMsg += std::string("LocalAddressLength: ") + generic_log(LocalAddressLength)+std::string("$");
logMsg += std::string("LocalAddress: ") + generic_log(LocalAddress)+std::string("$");
logMsg += std::string("RemoteAddressLength: ") + generic_log(RemoteAddressLength)+std::string("$");
logMsg += std::string("RemoteAddress: ") + generic_log(RemoteAddress)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAConnectByNameA$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("nodename: ") + generic_log(nodename)+std::string("$");
logMsg += std::string("servicename: ") + generic_log(servicename)+std::string("$");
logMsg += std::string("LocalAddressLength: ") + generic_log(LocalAddressLength)+std::string("$");
logMsg += std::string("LocalAddress: ") + generic_log(LocalAddress)+std::string("$");
logMsg += std::string("RemoteAddressLength: ") + generic_log(RemoteAddressLength)+std::string("$");
logMsg += std::string("RemoteAddress: ") + generic_log(RemoteAddress)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");
logMsg += std::string("Reserved: ") + generic_log(Reserved)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAConnectByNameA],
    	        	original_bytes[(int)Hook::Functions::WSAConnectByNameA], 6, NULL);

            BOOL result = WSAConnectByNameA(s,nodename,servicename,LocalAddressLength,LocalAddress,RemoteAddressLength,RemoteAddress,timeout,Reserved);
            Hook reset_hook { Hook::Functions::WSAConnectByNameA};
            reset_hook.deploy_hook();

            return result;

}
WSAEVENT WSAAPI __stdcall newWSACreateEvent(){
            char whatToDo = WhatToDoInFunction("WSACreateEvent");
            if(whatToDo == *"b"){
                std::string logMsg("WSACreateEvent$");
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSACreateEvent$");
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSACreateEvent],
    	        	original_bytes[(int)Hook::Functions::WSACreateEvent], 6, NULL);

            WSAEVENT result = WSACreateEvent();
            Hook reset_hook { Hook::Functions::WSACreateEvent};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSADuplicateSocketA(
        SOCKET              s,
        DWORD               dwProcessId,
        LPWSAPROTOCOL_INFOA lpProtocolInfo
){
            char whatToDo = WhatToDoInFunction("WSADuplicateSocketA");
            if(whatToDo == *"b"){
                std::string logMsg("WSADuplicateSocketA$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("dwProcessId: ") + generic_log(dwProcessId)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSADuplicateSocketA$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("dwProcessId: ") + generic_log(dwProcessId)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSADuplicateSocketA],
    	        	original_bytes[(int)Hook::Functions::WSADuplicateSocketA], 6, NULL);

            int result = WSADuplicateSocketA(s,dwProcessId,lpProtocolInfo);
            Hook reset_hook { Hook::Functions::WSADuplicateSocketA};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAEnumNameSpaceProvidersA(
            LPDWORD              lpdwBufferLength,
            LPWSANAMESPACE_INFOA lpnspBuffer
){
            char whatToDo = WhatToDoInFunction("WSAEnumNameSpaceProvidersA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAEnumNameSpaceProvidersA$");logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");
logMsg += std::string("lpnspBuffer: ") + generic_log(lpnspBuffer)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAEnumNameSpaceProvidersA$");logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");
logMsg += std::string("lpnspBuffer: ") + generic_log(lpnspBuffer)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAEnumNameSpaceProvidersA],
    	        	original_bytes[(int)Hook::Functions::WSAEnumNameSpaceProvidersA], 6, NULL);

            INT result = WSAEnumNameSpaceProvidersA(lpdwBufferLength,lpnspBuffer);
            Hook reset_hook { Hook::Functions::WSAEnumNameSpaceProvidersA};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAEnumNameSpaceProvidersExA(
            LPDWORD                lpdwBufferLength,
            LPWSANAMESPACE_INFOEXA lpnspBuffer
){
            char whatToDo = WhatToDoInFunction("WSAEnumNameSpaceProvidersExA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAEnumNameSpaceProvidersExA$");logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");
logMsg += std::string("lpnspBuffer: ") + generic_log(lpnspBuffer)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAEnumNameSpaceProvidersExA$");logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");
logMsg += std::string("lpnspBuffer: ") + generic_log(lpnspBuffer)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAEnumNameSpaceProvidersExA],
    	        	original_bytes[(int)Hook::Functions::WSAEnumNameSpaceProvidersExA], 6, NULL);

            INT result = WSAEnumNameSpaceProvidersExA(lpdwBufferLength,lpnspBuffer);
            Hook reset_hook { Hook::Functions::WSAEnumNameSpaceProvidersExA};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAEnumNetworkEvents(
        SOCKET             s,
        WSAEVENT           hEventObject,
        LPWSANETWORKEVENTS lpNetworkEvents
){
            char whatToDo = WhatToDoInFunction("WSAEnumNetworkEvents");
            if(whatToDo == *"b"){
                std::string logMsg("WSAEnumNetworkEvents$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hEventObject: ") + generic_log(hEventObject)+std::string("$");
logMsg += std::string("lpNetworkEvents: ") + generic_log(lpNetworkEvents)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAEnumNetworkEvents$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hEventObject: ") + generic_log(hEventObject)+std::string("$");
logMsg += std::string("lpNetworkEvents: ") + generic_log(lpNetworkEvents)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAEnumNetworkEvents],
    	        	original_bytes[(int)Hook::Functions::WSAEnumNetworkEvents], 6, NULL);

            int result = WSAEnumNetworkEvents(s,hEventObject,lpNetworkEvents);
            Hook reset_hook { Hook::Functions::WSAEnumNetworkEvents};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAEnumProtocolsA(
            LPINT               lpiProtocols,
            LPWSAPROTOCOL_INFOA lpProtocolBuffer,
            LPDWORD             lpdwBufferLength
){
            char whatToDo = WhatToDoInFunction("WSAEnumProtocolsA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAEnumProtocolsA$");logMsg += std::string("lpiProtocols: ") + generic_log(lpiProtocols)+std::string("$");
logMsg += std::string("lpProtocolBuffer: ") + generic_log(lpProtocolBuffer)+std::string("$");
logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAEnumProtocolsA$");logMsg += std::string("lpiProtocols: ") + generic_log(lpiProtocols)+std::string("$");
logMsg += std::string("lpProtocolBuffer: ") + generic_log(lpProtocolBuffer)+std::string("$");
logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAEnumProtocolsA],
    	        	original_bytes[(int)Hook::Functions::WSAEnumProtocolsA], 6, NULL);

            int result = WSAEnumProtocolsA(lpiProtocols,lpProtocolBuffer,lpdwBufferLength);
            Hook reset_hook { Hook::Functions::WSAEnumProtocolsA};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAEventSelect(
       SOCKET   s,
       WSAEVENT hEventObject,
       long     lNetworkEvents
){
            char whatToDo = WhatToDoInFunction("WSAEventSelect");
            if(whatToDo == *"b"){
                std::string logMsg("WSAEventSelect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hEventObject: ") + generic_log(hEventObject)+std::string("$");
logMsg += std::string("lNetworkEvents: ") + generic_log(lNetworkEvents)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAEventSelect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hEventObject: ") + generic_log(hEventObject)+std::string("$");
logMsg += std::string("lNetworkEvents: ") + generic_log(lNetworkEvents)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAEventSelect],
    	        	original_bytes[(int)Hook::Functions::WSAEventSelect], 6, NULL);

            int result = WSAEventSelect(s,hEventObject,lNetworkEvents);
            Hook reset_hook { Hook::Functions::WSAEventSelect};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall new__WSAFDIsSet(
  SOCKET unnamedParam1,
  fd_set *unnamedParam2
){
            char whatToDo = WhatToDoInFunction("__WSAFDIsSet");
            if(whatToDo == *"b"){
                std::string logMsg("__WSAFDIsSet$");logMsg += std::string("unnamedParam1: ") + generic_log(unnamedParam1)+std::string("$");
logMsg += std::string("unnamedParam2: ") + generic_log(unnamedParam2)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("__WSAFDIsSet$");logMsg += std::string("unnamedParam1: ") + generic_log(unnamedParam1)+std::string("$");
logMsg += std::string("unnamedParam2: ") + generic_log(unnamedParam2)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::__WSAFDIsSet],
    	        	original_bytes[(int)Hook::Functions::__WSAFDIsSet], 6, NULL);

            int result = __WSAFDIsSet(unnamedParam1,unnamedParam2);
            Hook reset_hook { Hook::Functions::__WSAFDIsSet};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newWSAGetLastError(){
            char whatToDo = WhatToDoInFunction("WSAGetLastError");
            if(whatToDo == *"b"){
                std::string logMsg("WSAGetLastError$");
                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAGetLastError$");
                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAGetLastError],
    	        	original_bytes[(int)Hook::Functions::WSAGetLastError], 6, NULL);

            int result = WSAGetLastError();
            Hook reset_hook { Hook::Functions::WSAGetLastError};
            reset_hook.deploy_hook();

            return result;

}
BOOL WSAAPI __stdcall newWSAGetOverlappedResult(
        SOCKET          s,
        LPWSAOVERLAPPED lpOverlapped,
        LPDWORD         lpcbTransfer,
        BOOL            fWait,
        LPDWORD         lpdwFlags
){
            char whatToDo = WhatToDoInFunction("WSAGetOverlappedResult");
            if(whatToDo == *"b"){
                std::string logMsg("WSAGetOverlappedResult$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpcbTransfer: ") + generic_log(lpcbTransfer)+std::string("$");
logMsg += std::string("fWait: ") + generic_log(fWait)+std::string("$");
logMsg += std::string("lpdwFlags: ") + generic_log(lpdwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAGetOverlappedResult$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpcbTransfer: ") + generic_log(lpcbTransfer)+std::string("$");
logMsg += std::string("fWait: ") + generic_log(fWait)+std::string("$");
logMsg += std::string("lpdwFlags: ") + generic_log(lpdwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAGetOverlappedResult],
    	        	original_bytes[(int)Hook::Functions::WSAGetOverlappedResult], 6, NULL);

            BOOL result = WSAGetOverlappedResult(s,lpOverlapped,lpcbTransfer,fWait,lpdwFlags);
            Hook reset_hook { Hook::Functions::WSAGetOverlappedResult};
            reset_hook.deploy_hook();

            return result;

}
BOOL WSAAPI __stdcall newWSAGetQOSByName(
            SOCKET   s,
            LPWSABUF lpQOSName,
            LPQOS    lpQOS
){
            char whatToDo = WhatToDoInFunction("WSAGetQOSByName");
            if(whatToDo == *"b"){
                std::string logMsg("WSAGetQOSByName$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpQOSName: ") + generic_log(lpQOSName)+std::string("$");
logMsg += std::string("lpQOS: ") + generic_log(lpQOS)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAGetQOSByName$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpQOSName: ") + generic_log(lpQOSName)+std::string("$");
logMsg += std::string("lpQOS: ") + generic_log(lpQOS)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAGetQOSByName],
    	        	original_bytes[(int)Hook::Functions::WSAGetQOSByName], 6, NULL);

            BOOL result = WSAGetQOSByName(s,lpQOSName,lpQOS);
            Hook reset_hook { Hook::Functions::WSAGetQOSByName};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAGetServiceClassInfoA(
            LPGUID                 lpProviderId,
            LPGUID                 lpServiceClassId,
            LPDWORD                lpdwBufSize,
            LPWSASERVICECLASSINFOA lpServiceClassInfo
){
            char whatToDo = WhatToDoInFunction("WSAGetServiceClassInfoA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAGetServiceClassInfoA$");logMsg += std::string("lpProviderId: ") + generic_log(lpProviderId)+std::string("$");
logMsg += std::string("lpServiceClassId: ") + generic_log(lpServiceClassId)+std::string("$");
logMsg += std::string("lpdwBufSize: ") + generic_log(lpdwBufSize)+std::string("$");
logMsg += std::string("lpServiceClassInfo: ") + generic_log(lpServiceClassInfo)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAGetServiceClassInfoA$");logMsg += std::string("lpProviderId: ") + generic_log(lpProviderId)+std::string("$");
logMsg += std::string("lpServiceClassId: ") + generic_log(lpServiceClassId)+std::string("$");
logMsg += std::string("lpdwBufSize: ") + generic_log(lpdwBufSize)+std::string("$");
logMsg += std::string("lpServiceClassInfo: ") + generic_log(lpServiceClassInfo)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAGetServiceClassInfoA],
    	        	original_bytes[(int)Hook::Functions::WSAGetServiceClassInfoA], 6, NULL);

            INT result = WSAGetServiceClassInfoA(lpProviderId,lpServiceClassId,lpdwBufSize,lpServiceClassInfo);
            Hook reset_hook { Hook::Functions::WSAGetServiceClassInfoA};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAGetServiceClassNameByClassIdA(
            LPGUID  lpServiceClassId,
            LPSTR   lpszServiceClassName,
            LPDWORD lpdwBufferLength
){
            char whatToDo = WhatToDoInFunction("WSAGetServiceClassNameByClassIdA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAGetServiceClassNameByClassIdA$");logMsg += std::string("lpServiceClassId: ") + generic_log(lpServiceClassId)+std::string("$");
logMsg += std::string("lpszServiceClassName: ") + generic_log(lpszServiceClassName)+std::string("$");
logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAGetServiceClassNameByClassIdA$");logMsg += std::string("lpServiceClassId: ") + generic_log(lpServiceClassId)+std::string("$");
logMsg += std::string("lpszServiceClassName: ") + generic_log(lpszServiceClassName)+std::string("$");
logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAGetServiceClassNameByClassIdA],
    	        	original_bytes[(int)Hook::Functions::WSAGetServiceClassNameByClassIdA], 6, NULL);

            INT result = WSAGetServiceClassNameByClassIdA(lpServiceClassId,lpszServiceClassName,lpdwBufferLength);
            Hook reset_hook { Hook::Functions::WSAGetServiceClassNameByClassIdA};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAHtonl(
        SOCKET s,
        u_long hostlong,
        u_long *lpnetlong
){
            char whatToDo = WhatToDoInFunction("WSAHtonl");
            if(whatToDo == *"b"){
                std::string logMsg("WSAHtonl$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hostlong: ") + generic_log(hostlong)+std::string("$");
logMsg += std::string("lpnetlong: ") + generic_log(lpnetlong)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAHtonl$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hostlong: ") + generic_log(hostlong)+std::string("$");
logMsg += std::string("lpnetlong: ") + generic_log(lpnetlong)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAHtonl],
    	        	original_bytes[(int)Hook::Functions::WSAHtonl], 6, NULL);

            int result = WSAHtonl(s,hostlong,lpnetlong);
            Hook reset_hook { Hook::Functions::WSAHtonl};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAHtons(
        SOCKET  s,
        u_short hostshort,
        u_short *lpnetshort
){
            char whatToDo = WhatToDoInFunction("WSAHtons");
            if(whatToDo == *"b"){
                std::string logMsg("WSAHtons$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hostshort: ") + generic_log(hostshort)+std::string("$");
logMsg += std::string("lpnetshort: ") + generic_log(lpnetshort)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAHtons$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("hostshort: ") + generic_log(hostshort)+std::string("$");
logMsg += std::string("lpnetshort: ") + generic_log(lpnetshort)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAHtons],
    	        	original_bytes[(int)Hook::Functions::WSAHtons], 6, NULL);

            int result = WSAHtons(s,hostshort,lpnetshort);
            Hook reset_hook { Hook::Functions::WSAHtons};
            reset_hook.deploy_hook();

            return result;

}

INT WSAAPI __stdcall newWSAInstallServiceClassA(
       LPWSASERVICECLASSINFOA lpServiceClassInfo
){
            char whatToDo = WhatToDoInFunction("WSAInstallServiceClassA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAInstallServiceClassA$");logMsg += std::string("lpServiceClassInfo: ") + generic_log(lpServiceClassInfo)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAInstallServiceClassA$");logMsg += std::string("lpServiceClassInfo: ") + generic_log(lpServiceClassInfo)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAInstallServiceClassA],
    	        	original_bytes[(int)Hook::Functions::WSAInstallServiceClassA], 6, NULL);

            INT result = WSAInstallServiceClassA(lpServiceClassInfo);
            Hook reset_hook { Hook::Functions::WSAInstallServiceClassA};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAIoctl(
        SOCKET                             s,
        DWORD                              dwIoControlCode,
        LPVOID                             lpvInBuffer,
        DWORD                              cbInBuffer,
        LPVOID                             lpvOutBuffer,
        DWORD                              cbOutBuffer,
        LPDWORD                            lpcbBytesReturned,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSAIoctl");
            if(whatToDo == *"b"){
                std::string logMsg("WSAIoctl$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("dwIoControlCode: ") + generic_log(dwIoControlCode)+std::string("$");
logMsg += std::string("lpvInBuffer: ") + generic_log(lpvInBuffer)+std::string("$");
logMsg += std::string("cbInBuffer: ") + generic_log(cbInBuffer)+std::string("$");
logMsg += std::string("lpvOutBuffer: ") + generic_log(lpvOutBuffer)+std::string("$");
logMsg += std::string("cbOutBuffer: ") + generic_log(cbOutBuffer)+std::string("$");
logMsg += std::string("lpcbBytesReturned: ") + generic_log(lpcbBytesReturned)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAIoctl$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("dwIoControlCode: ") + generic_log(dwIoControlCode)+std::string("$");
logMsg += std::string("lpvInBuffer: ") + generic_log(lpvInBuffer)+std::string("$");
logMsg += std::string("cbInBuffer: ") + generic_log(cbInBuffer)+std::string("$");
logMsg += std::string("lpvOutBuffer: ") + generic_log(lpvOutBuffer)+std::string("$");
logMsg += std::string("cbOutBuffer: ") + generic_log(cbOutBuffer)+std::string("$");
logMsg += std::string("lpcbBytesReturned: ") + generic_log(lpcbBytesReturned)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAIoctl],
    	        	original_bytes[(int)Hook::Functions::WSAIoctl], 6, NULL);

            int result = WSAIoctl(s,dwIoControlCode,lpvInBuffer,cbInBuffer,lpvOutBuffer,cbOutBuffer,lpcbBytesReturned,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSAIoctl};
            reset_hook.deploy_hook();

            return result;

}
SOCKET WSAAPI __stdcall newWSAJoinLeaf(
        SOCKET         s,
        const sockaddr *name,
        int            namelen,
        LPWSABUF       lpCallerData,
        LPWSABUF       lpCalleeData,
        LPQOS          lpSQOS,
        LPQOS          lpGQOS,
        DWORD          dwFlags
){
            char whatToDo = WhatToDoInFunction("WSAJoinLeaf");
            if(whatToDo == *"b"){
                std::string logMsg("WSAJoinLeaf$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");
logMsg += std::string("lpCallerData: ") + generic_log(lpCallerData)+std::string("$");
logMsg += std::string("lpCalleeData: ") + generic_log(lpCalleeData)+std::string("$");
logMsg += std::string("lpSQOS: ") + generic_log(lpSQOS)+std::string("$");
logMsg += std::string("lpGQOS: ") + generic_log(lpGQOS)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAJoinLeaf$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("name: ") + generic_log(name)+std::string("$");
logMsg += std::string("namelen: ") + generic_log(namelen)+std::string("$");
logMsg += std::string("lpCallerData: ") + generic_log(lpCallerData)+std::string("$");
logMsg += std::string("lpCalleeData: ") + generic_log(lpCalleeData)+std::string("$");
logMsg += std::string("lpSQOS: ") + generic_log(lpSQOS)+std::string("$");
logMsg += std::string("lpGQOS: ") + generic_log(lpGQOS)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAJoinLeaf],
    	        	original_bytes[(int)Hook::Functions::WSAJoinLeaf], 6, NULL);

            SOCKET result = WSAJoinLeaf(s,name,namelen,lpCallerData,lpCalleeData,lpSQOS,lpGQOS,dwFlags);
            Hook reset_hook { Hook::Functions::WSAJoinLeaf};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSALookupServiceBeginA(
        LPWSAQUERYSETA lpqsRestrictions,
        DWORD          dwControlFlags,
        LPHANDLE       lphLookup
){
            char whatToDo = WhatToDoInFunction("WSALookupServiceBeginA");
            if(whatToDo == *"b"){
                std::string logMsg("WSALookupServiceBeginA$");logMsg += std::string("lpqsRestrictions: ") + generic_log(lpqsRestrictions)+std::string("$");
logMsg += std::string("dwControlFlags: ") + generic_log(dwControlFlags)+std::string("$");
logMsg += std::string("lphLookup: ") + generic_log(lphLookup)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSALookupServiceBeginA$");logMsg += std::string("lpqsRestrictions: ") + generic_log(lpqsRestrictions)+std::string("$");
logMsg += std::string("dwControlFlags: ") + generic_log(dwControlFlags)+std::string("$");
logMsg += std::string("lphLookup: ") + generic_log(lphLookup)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSALookupServiceBeginA],
    	        	original_bytes[(int)Hook::Functions::WSALookupServiceBeginA], 6, NULL);

            INT result = WSALookupServiceBeginA(lpqsRestrictions,dwControlFlags,lphLookup);
            Hook reset_hook { Hook::Functions::WSALookupServiceBeginA};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSALookupServiceEnd(
       HANDLE hLookup
){
            char whatToDo = WhatToDoInFunction("WSALookupServiceEnd");
            if(whatToDo == *"b"){
                std::string logMsg("WSALookupServiceEnd$");logMsg += std::string("hLookup: ") + generic_log(hLookup)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSALookupServiceEnd$");logMsg += std::string("hLookup: ") + generic_log(hLookup)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSALookupServiceEnd],
    	        	original_bytes[(int)Hook::Functions::WSALookupServiceEnd], 6, NULL);

            INT result = WSALookupServiceEnd(hLookup);
            Hook reset_hook { Hook::Functions::WSALookupServiceEnd};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSALookupServiceNextA(
            HANDLE         hLookup,
            DWORD          dwControlFlags,
            LPDWORD        lpdwBufferLength,
            LPWSAQUERYSETA lpqsResults
){
            char whatToDo = WhatToDoInFunction("WSALookupServiceNextA");
            if(whatToDo == *"b"){
                std::string logMsg("WSALookupServiceNextA$");logMsg += std::string("hLookup: ") + generic_log(hLookup)+std::string("$");
logMsg += std::string("dwControlFlags: ") + generic_log(dwControlFlags)+std::string("$");
logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");
logMsg += std::string("lpqsResults: ") + generic_log(lpqsResults)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSALookupServiceNextA$");logMsg += std::string("hLookup: ") + generic_log(hLookup)+std::string("$");
logMsg += std::string("dwControlFlags: ") + generic_log(dwControlFlags)+std::string("$");
logMsg += std::string("lpdwBufferLength: ") + generic_log(lpdwBufferLength)+std::string("$");
logMsg += std::string("lpqsResults: ") + generic_log(lpqsResults)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSALookupServiceNextA],
    	        	original_bytes[(int)Hook::Functions::WSALookupServiceNextA], 6, NULL);

            INT result = WSALookupServiceNextA(hLookup,dwControlFlags,lpdwBufferLength,lpqsResults);
            Hook reset_hook { Hook::Functions::WSALookupServiceNextA};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSANSPIoctl(
            HANDLE          hLookup,
            DWORD           dwControlCode,
            LPVOID          lpvInBuffer,
            DWORD           cbInBuffer,
            LPVOID          lpvOutBuffer,
            DWORD           cbOutBuffer,
            LPDWORD         lpcbBytesReturned,
            LPWSACOMPLETION lpCompletion
){
            char whatToDo = WhatToDoInFunction("WSANSPIoctl");
            if(whatToDo == *"b"){
                std::string logMsg("WSANSPIoctl$");logMsg += std::string("hLookup: ") + generic_log(hLookup)+std::string("$");
logMsg += std::string("dwControlCode: ") + generic_log(dwControlCode)+std::string("$");
logMsg += std::string("lpvInBuffer: ") + generic_log(lpvInBuffer)+std::string("$");
logMsg += std::string("cbInBuffer: ") + generic_log(cbInBuffer)+std::string("$");
logMsg += std::string("lpvOutBuffer: ") + generic_log(lpvOutBuffer)+std::string("$");
logMsg += std::string("cbOutBuffer: ") + generic_log(cbOutBuffer)+std::string("$");
logMsg += std::string("lpcbBytesReturned: ") + generic_log(lpcbBytesReturned)+std::string("$");
logMsg += std::string("lpCompletion: ") + generic_log(lpCompletion)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSANSPIoctl$");logMsg += std::string("hLookup: ") + generic_log(hLookup)+std::string("$");
logMsg += std::string("dwControlCode: ") + generic_log(dwControlCode)+std::string("$");
logMsg += std::string("lpvInBuffer: ") + generic_log(lpvInBuffer)+std::string("$");
logMsg += std::string("cbInBuffer: ") + generic_log(cbInBuffer)+std::string("$");
logMsg += std::string("lpvOutBuffer: ") + generic_log(lpvOutBuffer)+std::string("$");
logMsg += std::string("cbOutBuffer: ") + generic_log(cbOutBuffer)+std::string("$");
logMsg += std::string("lpcbBytesReturned: ") + generic_log(lpcbBytesReturned)+std::string("$");
logMsg += std::string("lpCompletion: ") + generic_log(lpCompletion)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSANSPIoctl],
    	        	original_bytes[(int)Hook::Functions::WSANSPIoctl], 6, NULL);

            INT result = WSANSPIoctl(hLookup,dwControlCode,lpvInBuffer,cbInBuffer,lpvOutBuffer,cbOutBuffer,lpcbBytesReturned,lpCompletion);
            Hook reset_hook { Hook::Functions::WSANSPIoctl};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSANtohl(
        SOCKET s,
        u_long netlong,
        u_long *lphostlong
){
            char whatToDo = WhatToDoInFunction("WSANtohl");
            if(whatToDo == *"b"){
                std::string logMsg("WSANtohl$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("netlong: ") + generic_log(netlong)+std::string("$");
logMsg += std::string("lphostlong: ") + generic_log(lphostlong)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSANtohl$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("netlong: ") + generic_log(netlong)+std::string("$");
logMsg += std::string("lphostlong: ") + generic_log(lphostlong)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSANtohl],
    	        	original_bytes[(int)Hook::Functions::WSANtohl], 6, NULL);

            int result = WSANtohl(s,netlong,lphostlong);
            Hook reset_hook { Hook::Functions::WSANtohl};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSANtohs(
        SOCKET  s,
        u_short netshort,
        u_short *lphostshort
){
            char whatToDo = WhatToDoInFunction("WSANtohs");
            if(whatToDo == *"b"){
                std::string logMsg("WSANtohs$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("netshort: ") + generic_log(netshort)+std::string("$");
logMsg += std::string("lphostshort: ") + generic_log(lphostshort)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSANtohs$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("netshort: ") + generic_log(netshort)+std::string("$");
logMsg += std::string("lphostshort: ") + generic_log(lphostshort)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSANtohs],
    	        	original_bytes[(int)Hook::Functions::WSANtohs], 6, NULL);

            int result = WSANtohs(s,netshort,lphostshort);
            Hook reset_hook { Hook::Functions::WSANtohs};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSAPoll(
            LPWSAPOLLFD fdArray,
            ULONG       fds,
            INT         timeout
){
            char whatToDo = WhatToDoInFunction("WSAPoll");
            if(whatToDo == *"b"){
                std::string logMsg("WSAPoll$");logMsg += std::string("fdArray: ") + generic_log(fdArray)+std::string("$");
logMsg += std::string("fds: ") + generic_log(fds)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAPoll$");logMsg += std::string("fdArray: ") + generic_log(fdArray)+std::string("$");
logMsg += std::string("fds: ") + generic_log(fds)+std::string("$");
logMsg += std::string("timeout: ") + generic_log(timeout)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAPoll],
    	        	original_bytes[(int)Hook::Functions::WSAPoll], 6, NULL);

            int result = WSAPoll(fdArray,fds,timeout);
            Hook reset_hook { Hook::Functions::WSAPoll};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAProviderConfigChange(
            LPHANDLE                           lpNotificationHandle,
            LPWSAOVERLAPPED                    lpOverlapped,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSAProviderConfigChange");
            if(whatToDo == *"b"){
                std::string logMsg("WSAProviderConfigChange$");logMsg += std::string("lpNotificationHandle: ") + generic_log(lpNotificationHandle)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAProviderConfigChange$");logMsg += std::string("lpNotificationHandle: ") + generic_log(lpNotificationHandle)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAProviderConfigChange],
    	        	original_bytes[(int)Hook::Functions::WSAProviderConfigChange], 6, NULL);

            INT result = WSAProviderConfigChange(lpNotificationHandle,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSAProviderConfigChange};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSARecv(
            SOCKET                             s,
            LPWSABUF                           lpBuffers,
            DWORD                              dwBufferCount,
            LPDWORD                            lpNumberOfBytesRecvd,
            LPDWORD                            lpFlags,
            LPWSAOVERLAPPED                    lpOverlapped,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSARecv");
            if(whatToDo == *"b"){
                std::string logMsg("WSARecv$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesRecvd: ") + generic_log(lpNumberOfBytesRecvd)+std::string("$");
logMsg += std::string("lpFlags: ") + generic_log(lpFlags)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSARecv$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesRecvd: ") + generic_log(lpNumberOfBytesRecvd)+std::string("$");
logMsg += std::string("lpFlags: ") + generic_log(lpFlags)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSARecv],
    	        	original_bytes[(int)Hook::Functions::WSARecv], 6, NULL);

            int result = WSARecv(s,lpBuffers,dwBufferCount,lpNumberOfBytesRecvd,lpFlags,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSARecv};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSARecvDisconnect(
        SOCKET   s,
        LPWSABUF lpInboundDisconnectData
){
            char whatToDo = WhatToDoInFunction("WSARecvDisconnect");
            if(whatToDo == *"b"){
                std::string logMsg("WSARecvDisconnect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpInboundDisconnectData: ") + generic_log(lpInboundDisconnectData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSARecvDisconnect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpInboundDisconnectData: ") + generic_log(lpInboundDisconnectData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSARecvDisconnect],
    	        	original_bytes[(int)Hook::Functions::WSARecvDisconnect], 6, NULL);

            int result = WSARecvDisconnect(s,lpInboundDisconnectData);
            Hook reset_hook { Hook::Functions::WSARecvDisconnect};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSARecvFrom(
            SOCKET                             s,
            LPWSABUF                           lpBuffers,
            DWORD                              dwBufferCount,
            LPDWORD                            lpNumberOfBytesRecvd,
            LPDWORD                            lpFlags,
            sockaddr                           *lpFrom,
            LPINT                              lpFromlen,
            LPWSAOVERLAPPED                    lpOverlapped,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSARecvFrom");
            if(whatToDo == *"b"){
                std::string logMsg("WSARecvFrom$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesRecvd: ") + generic_log(lpNumberOfBytesRecvd)+std::string("$");
logMsg += std::string("lpFlags: ") + generic_log(lpFlags)+std::string("$");
logMsg += std::string("lpFrom: ") + generic_log(lpFrom)+std::string("$");
logMsg += std::string("lpFromlen: ") + generic_log(lpFromlen)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSARecvFrom$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesRecvd: ") + generic_log(lpNumberOfBytesRecvd)+std::string("$");
logMsg += std::string("lpFlags: ") + generic_log(lpFlags)+std::string("$");
logMsg += std::string("lpFrom: ") + generic_log(lpFrom)+std::string("$");
logMsg += std::string("lpFromlen: ") + generic_log(lpFromlen)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSARecvFrom],
    	        	original_bytes[(int)Hook::Functions::WSARecvFrom], 6, NULL);

            int result = WSARecvFrom(s,lpBuffers,dwBufferCount,lpNumberOfBytesRecvd,lpFlags,lpFrom,lpFromlen,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSARecvFrom};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSARemoveServiceClass(
       LPGUID lpServiceClassId
){
            char whatToDo = WhatToDoInFunction("WSARemoveServiceClass");
            if(whatToDo == *"b"){
                std::string logMsg("WSARemoveServiceClass$");logMsg += std::string("lpServiceClassId: ") + generic_log(lpServiceClassId)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSARemoveServiceClass$");logMsg += std::string("lpServiceClassId: ") + generic_log(lpServiceClassId)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSARemoveServiceClass],
    	        	original_bytes[(int)Hook::Functions::WSARemoveServiceClass], 6, NULL);

            INT result = WSARemoveServiceClass(lpServiceClassId);
            Hook reset_hook { Hook::Functions::WSARemoveServiceClass};
            reset_hook.deploy_hook();

            return result;

}
BOOL WSAAPI __stdcall newWSAResetEvent(
       WSAEVENT hEvent
){
            char whatToDo = WhatToDoInFunction("WSAResetEvent");
            if(whatToDo == *"b"){
                std::string logMsg("WSAResetEvent$");logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAResetEvent$");logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAResetEvent],
    	        	original_bytes[(int)Hook::Functions::WSAResetEvent], 6, NULL);

            BOOL result = WSAResetEvent(hEvent);
            Hook reset_hook { Hook::Functions::WSAResetEvent};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSASend(
        SOCKET                             s,
        LPWSABUF                           lpBuffers,
        DWORD                              dwBufferCount,
        LPDWORD                            lpNumberOfBytesSent,
        DWORD                              dwFlags,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSASend");
            if(whatToDo == *"b"){
                std::string logMsg("WSASend$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesSent: ") + generic_log(lpNumberOfBytesSent)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASend$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesSent: ") + generic_log(lpNumberOfBytesSent)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASend],
    	        	original_bytes[(int)Hook::Functions::WSASend], 6, NULL);

            int result = WSASend(s,lpBuffers,dwBufferCount,lpNumberOfBytesSent,dwFlags,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSASend};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSASendDisconnect(
       SOCKET   s,
       LPWSABUF lpOutboundDisconnectData
){
            char whatToDo = WhatToDoInFunction("WSASendDisconnect");
            if(whatToDo == *"b"){
                std::string logMsg("WSASendDisconnect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpOutboundDisconnectData: ") + generic_log(lpOutboundDisconnectData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASendDisconnect$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpOutboundDisconnectData: ") + generic_log(lpOutboundDisconnectData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASendDisconnect],
    	        	original_bytes[(int)Hook::Functions::WSASendDisconnect], 6, NULL);

            int result = WSASendDisconnect(s,lpOutboundDisconnectData);
            Hook reset_hook { Hook::Functions::WSASendDisconnect};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSASendMsg(
        SOCKET                             Handle,
        LPWSAMSG                           lpMsg,
        DWORD                              dwFlags,
        LPDWORD                            lpNumberOfBytesSent,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSASendMsg");
            if(whatToDo == *"b"){
                std::string logMsg("WSASendMsg$");logMsg += std::string("Handle: ") + generic_log(Handle)+std::string("$");
logMsg += std::string("lpMsg: ") + generic_log(lpMsg)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("lpNumberOfBytesSent: ") + generic_log(lpNumberOfBytesSent)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASendMsg$");logMsg += std::string("Handle: ") + generic_log(Handle)+std::string("$");
logMsg += std::string("lpMsg: ") + generic_log(lpMsg)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("lpNumberOfBytesSent: ") + generic_log(lpNumberOfBytesSent)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASendMsg],
    	        	original_bytes[(int)Hook::Functions::WSASendMsg], 6, NULL);

            int result = WSASendMsg(Handle,lpMsg,dwFlags,lpNumberOfBytesSent,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSASendMsg};
            reset_hook.deploy_hook();

            return result;

}
int WSAAPI __stdcall newWSASendTo(
        SOCKET                             s,
        LPWSABUF                           lpBuffers,
        DWORD                              dwBufferCount,
        LPDWORD                            lpNumberOfBytesSent,
        DWORD                              dwFlags,
        const sockaddr                     *lpTo,
        int                                iTolen,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
            char whatToDo = WhatToDoInFunction("WSASendTo");
            if(whatToDo == *"b"){
                std::string logMsg("WSASendTo$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesSent: ") + generic_log(lpNumberOfBytesSent)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("lpTo: ") + generic_log(lpTo)+std::string("$");
logMsg += std::string("iTolen: ") + generic_log(iTolen)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASendTo$");logMsg += std::string("s: ") + generic_log(s)+std::string("$");
logMsg += std::string("lpBuffers: ") + generic_log(lpBuffers)+std::string("$");
logMsg += std::string("dwBufferCount: ") + generic_log(dwBufferCount)+std::string("$");
logMsg += std::string("lpNumberOfBytesSent: ") + generic_log(lpNumberOfBytesSent)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");
logMsg += std::string("lpTo: ") + generic_log(lpTo)+std::string("$");
logMsg += std::string("iTolen: ") + generic_log(iTolen)+std::string("$");
logMsg += std::string("lpOverlapped: ") + generic_log(lpOverlapped)+std::string("$");
logMsg += std::string("lpCompletionRoutine: ") + generic_log(lpCompletionRoutine)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASendTo],
    	        	original_bytes[(int)Hook::Functions::WSASendTo], 6, NULL);

            int result = WSASendTo(s,lpBuffers,dwBufferCount,lpNumberOfBytesSent,dwFlags,lpTo,iTolen,lpOverlapped,lpCompletionRoutine);
            Hook reset_hook { Hook::Functions::WSASendTo};
            reset_hook.deploy_hook();

            return result;

}
BOOL WSAAPI __stdcall newWSASetEvent(
       WSAEVENT hEvent
){
            char whatToDo = WhatToDoInFunction("WSASetEvent");
            if(whatToDo == *"b"){
                std::string logMsg("WSASetEvent$");logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASetEvent$");logMsg += std::string("hEvent: ") + generic_log(hEvent)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASetEvent],
    	        	original_bytes[(int)Hook::Functions::WSASetEvent], 6, NULL);

            BOOL result = WSASetEvent(hEvent);
            Hook reset_hook { Hook::Functions::WSASetEvent};
            reset_hook.deploy_hook();

            return result;

}
void __stdcall newWSASetLastError(
       int iError
){
            char whatToDo = WhatToDoInFunction("WSASetLastError");
            if(whatToDo == *"b"){
                std::string logMsg("WSASetLastError$");logMsg += std::string("iError: ") + generic_log(iError)+std::string("$");

                log(logMsg);
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASetLastError$");logMsg += std::string("iError: ") + generic_log(iError)+std::string("$");

                log(logMsg);
            }
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::WSASetLastError],
    		original_bytes[(int)Hook::Functions::WSASetLastError], 6, NULL);

        WSASetLastError(iError);
        Hook reset_hook { Hook::Functions::WSASetLastError};
        reset_hook.deploy_hook();

}
INT WSAAPI __stdcall newWSASetServiceA(
       LPWSAQUERYSETA   lpqsRegInfo,
       WSAESETSERVICEOP essoperation,
       DWORD            dwControlFlags
){
            char whatToDo = WhatToDoInFunction("WSASetServiceA");
            if(whatToDo == *"b"){
                std::string logMsg("WSASetServiceA$");logMsg += std::string("lpqsRegInfo: ") + generic_log(lpqsRegInfo)+std::string("$");
logMsg += std::string("essoperation: ") + generic_log(essoperation)+std::string("$");
logMsg += std::string("dwControlFlags: ") + generic_log(dwControlFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASetServiceA$");logMsg += std::string("lpqsRegInfo: ") + generic_log(lpqsRegInfo)+std::string("$");
logMsg += std::string("essoperation: ") + generic_log(essoperation)+std::string("$");
logMsg += std::string("dwControlFlags: ") + generic_log(dwControlFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASetServiceA],
    	        	original_bytes[(int)Hook::Functions::WSASetServiceA], 6, NULL);

            INT result = WSASetServiceA(lpqsRegInfo,essoperation,dwControlFlags);
            Hook reset_hook { Hook::Functions::WSASetServiceA};
            reset_hook.deploy_hook();

            return result;

}
SOCKET WSAAPI __stdcall newWSASocketA(
       int                 af,
       int                 type,
       int                 protocol,
       LPWSAPROTOCOL_INFOA lpProtocolInfo,
       GROUP               g,
       DWORD               dwFlags
){
            char whatToDo = WhatToDoInFunction("WSASocketA");
            if(whatToDo == *"b"){
                std::string logMsg("WSASocketA$");logMsg += std::string("af: ") + generic_log(af)+std::string("$");
logMsg += std::string("type: ") + generic_log(type)+std::string("$");
logMsg += std::string("protocol: ") + generic_log(protocol)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");
logMsg += std::string("g: ") + generic_log(g)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSASocketA$");logMsg += std::string("af: ") + generic_log(af)+std::string("$");
logMsg += std::string("type: ") + generic_log(type)+std::string("$");
logMsg += std::string("protocol: ") + generic_log(protocol)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");
logMsg += std::string("g: ") + generic_log(g)+std::string("$");
logMsg += std::string("dwFlags: ") + generic_log(dwFlags)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSASocketA],
    	        	original_bytes[(int)Hook::Functions::WSASocketA], 6, NULL);

            SOCKET result = WSASocketA(af,type,protocol,lpProtocolInfo,g,dwFlags);
            Hook reset_hook { Hook::Functions::WSASocketA};
            reset_hook.deploy_hook();

            return result;

}
int __stdcall newWSAStartup(
        WORD      wVersionRequired,
        LPWSADATA lpWSAData
){
            char whatToDo = WhatToDoInFunction("WSAStartup");
            if(whatToDo == *"b"){
                std::string logMsg("WSAStartup$");logMsg += std::string("wVersionRequired: ") + generic_log(wVersionRequired)+std::string("$");
logMsg += std::string("lpWSAData: ") + generic_log(lpWSAData)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAStartup$");logMsg += std::string("wVersionRequired: ") + generic_log(wVersionRequired)+std::string("$");
logMsg += std::string("lpWSAData: ") + generic_log(lpWSAData)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAStartup],
    	        	original_bytes[(int)Hook::Functions::WSAStartup], 6, NULL);

            int result = WSAStartup(wVersionRequired,lpWSAData);
            Hook reset_hook { Hook::Functions::WSAStartup};
            reset_hook.deploy_hook();

            return result;

}
INT WSAAPI __stdcall newWSAStringToAddressA(
                 LPSTR               AddressString,
                 INT                 AddressFamily,
                 LPWSAPROTOCOL_INFOA lpProtocolInfo,
                 LPSOCKADDR          lpAddress,
                 LPINT               lpAddressLength
){
            char whatToDo = WhatToDoInFunction("WSAStringToAddressA");
            if(whatToDo == *"b"){
                std::string logMsg("WSAStringToAddressA$");logMsg += std::string("AddressString: ") + generic_log(AddressString)+std::string("$");
logMsg += std::string("AddressFamily: ") + generic_log(AddressFamily)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");
logMsg += std::string("lpAddress: ") + generic_log(lpAddress)+std::string("$");
logMsg += std::string("lpAddressLength: ") + generic_log(lpAddressLength)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAStringToAddressA$");logMsg += std::string("AddressString: ") + generic_log(AddressString)+std::string("$");
logMsg += std::string("AddressFamily: ") + generic_log(AddressFamily)+std::string("$");
logMsg += std::string("lpProtocolInfo: ") + generic_log(lpProtocolInfo)+std::string("$");
logMsg += std::string("lpAddress: ") + generic_log(lpAddress)+std::string("$");
logMsg += std::string("lpAddressLength: ") + generic_log(lpAddressLength)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAStringToAddressA],
    	        	original_bytes[(int)Hook::Functions::WSAStringToAddressA], 6, NULL);

            INT result = WSAStringToAddressA(AddressString,AddressFamily,lpProtocolInfo,lpAddress,lpAddressLength);
            Hook reset_hook { Hook::Functions::WSAStringToAddressA};
            reset_hook.deploy_hook();

            return result;

}
DWORD WSAAPI __stdcall newWSAWaitForMultipleEvents(
       DWORD          cEvents,
       const WSAEVENT *lphEvents,
       BOOL           fWaitAll,
       DWORD          dwTimeout,
       BOOL           fAlertable
){
            char whatToDo = WhatToDoInFunction("WSAWaitForMultipleEvents");
            if(whatToDo == *"b"){
                std::string logMsg("WSAWaitForMultipleEvents$");logMsg += std::string("cEvents: ") + generic_log(cEvents)+std::string("$");
logMsg += std::string("lphEvents: ") + generic_log(lphEvents)+std::string("$");
logMsg += std::string("fWaitAll: ") + generic_log(fWaitAll)+std::string("$");
logMsg += std::string("dwTimeout: ") + generic_log(dwTimeout)+std::string("$");
logMsg += std::string("fAlertable: ") + generic_log(fAlertable)+std::string("$");

                log(logMsg);
                return NULL;
            }
            if(whatToDo == *"w"){    	       
                std::string logMsg("WSAWaitForMultipleEvents$");logMsg += std::string("cEvents: ") + generic_log(cEvents)+std::string("$");
logMsg += std::string("lphEvents: ") + generic_log(lphEvents)+std::string("$");
logMsg += std::string("fWaitAll: ") + generic_log(fWaitAll)+std::string("$");
logMsg += std::string("dwTimeout: ") + generic_log(dwTimeout)+std::string("$");
logMsg += std::string("fAlertable: ") + generic_log(fAlertable)+std::string("$");

                log(logMsg);
            }
             WriteProcessMemory(GetCurrentProcess(),
    	        	(LPVOID)hooked_addr[(int)Hook::Functions::WSAWaitForMultipleEvents],
    	        	original_bytes[(int)Hook::Functions::WSAWaitForMultipleEvents], 6, NULL);

            DWORD result = WSAWaitForMultipleEvents(cEvents,lphEvents,fWaitAll,dwTimeout,fAlertable);
            Hook reset_hook { Hook::Functions::WSAWaitForMultipleEvents};
            reset_hook.deploy_hook();

            return result;

}
}