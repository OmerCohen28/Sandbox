#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>
#include <stdio.h>
#include <ws2tcpip.h> 
#include <locale>
#include <codecvt>
#include <ctime>
#include <sys/time.h>

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
    } else if (sa->sa_family == AF_INET6) {
        // IPv6
        const sockaddr_in6* sin6 = reinterpret_cast<const sockaddr_in6*>(sa);
        char ip[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(sin6->sin6_addr), ip, INET6_ADDRSTRLEN);
        ss << "[" << ip << "]:" << ntohs(sin6->sin6_port);
    } else {
        ss << "Unknown family type: " << sa->sa_family;
    }
    return ss.str();
}


template <typename T>
std::string my_func(T arg) {
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
        return std::string(arg);
    }
    if constexpr (std::is_same_v < T, LPCTSTR>) {
        std::wstring wstr(arg);
        return std::string(wstr.begin(),wstr.end());
    }
    if constexpr (std::is_same_v < T, LPCSTR>) {
        return std::string(arg);
    }
    if constexpr (std::is_same_v < T, UINT>) {
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, BYTE>){
        return std::to_string(arg);
    }
    if constexpr (std::is_same_v < T, LPBYTE>) {
        int length = 0;
        while (arg[length] != '\0') {
            length++;
        }
        std::string s(arg, arg + length);
    }
    if constexpr (std::is_same_v < T, LPDWORD>) {
        return std::to_string(*arg);
    }
    if constexpr (std::is_same_v < T, SOCKET>) {
        return ToStringSocket(arg);
    }
    if constexpr (std::is_same_v < T, SOCKET*>) {
        return ToStringSocket(*arg);
    }
    if constexpr (std::is_same_v < T, sockaddr>) {
        return sockaddrToString(arg);
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

int main()
{
    PSTR h{(CHAR*)"hello"};
    BYTE b{};
    HKEY k{};
    int y = 6;
    int* x{ &y };
    const sockaddr addr{};
    LPHANDLE l{};
    PWSTR w{ (WCHAR*)L"h" };
    LPSTR s{};
    bool hello{ true };
    int x1{ 5 };
    void* ptr{&x1};
    std::cout << my_func(ptr);
}
