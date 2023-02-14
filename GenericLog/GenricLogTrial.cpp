#include <vector>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>

class Logger {
    std::vector<char> data;
public:
    Logger() {}

    template<typename T>
    Logger(T&& t) {
        if constexpr (std::is_pointer_v<T>) {
            if constexpr (std::is_same_v<T, HANDLE>) {
                char buffer[50];
                sprintf_s(buffer, 50, "%p", t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
            else if constexpr (std::is_same_v<T, LPCSTR>) {
                std::string str = t;
                for (char c : str) {
                    data.push_back(c);
                }
            }
            else if constexpr (std::is_same_v<T, char*>) {
                std::string str = t;
                for (char c : str) {
                    data.push_back(c);
                }
            }
            else {
                char buffer[50];
                sprintf_s(buffer, 50, "%p", *t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
        }
        else {
            if constexpr (std::is_same_v<T, HANDLE>) {
                char buffer[50];
                sprintf_s(buffer, 50, "%p", t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
            else if constexpr (std::is_same_v<T, int>) {
                char buffer[50];
                sprintf_s(buffer, 50, "%d", t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
            else if constexpr (std::is_same_v<T, DWORD>) {
                char buffer[50];
                sprintf_s(buffer, 50, "%lu", t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
            else if constexpr (std::is_same_v<T, bool>) {
                char buffer[50];
                sprintf_s(buffer, 50, "%d", t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
            else {
                char buffer[50];
                sprintf_s(buffer, 50, "Unable to cast %s to char array", typeid(t).name());
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
                }
            }
        }
    }

    std::string get_str() {
        std::string str;
        for (char c : data) {
            str.push_back(c);
        }
        return str;
    }
};

template <typename T>
void my_func(T arg) {
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "int";
    }
    if constexpr (std::is_same_v < T, char*>) {
        char* c = new char[] {"char*"};
        std::cout << c;
    } 
    if constexpr (std::is_same_v < T, DWORD>) {
        char* c = new char[] {"DWORD"};
        std::cout << c;
    }
    if constexpr (std::is_same_v < T, char>) {
        std::cout << arg;
    }
    if constexpr (std::is_same_v < T, void*>) {
        std::cout << "void*";
        if (auto char_ptr = static_cast<char*>(arg)) {
            std::cout << (char*)arg;
        }
    }
    if constexpr (std::is_same_v < T, LPCTSTR>) {
        std::cout << "LPCTSTR";
    }
    if constexpr (std::is_same_v < T, LPCSTR>) {
        std::cout << "LPCSTR";
    }
    if constexpr (std::is_same_v < T, UINT>) {
        std::cout << "UINT";
    }
    if constexpr (std::is_same_v < T, BYTE>){
        std::cout << "BYTE";
    }
    if constexpr (std::is_same_v < T, HKEY>) {
        std::cout << "HKEY";
    }
    if constexpr (std::is_same_v < T, LPCVOID>) {
        std::cout << "LPCVOID";
    }
    if constexpr (std::is_same_v < T, LPBYTE>) {
        std::cout << "LPBYTE";
    }
    if constexpr (std::is_same_v < T, LPDWORD>) {
        std::cout << "LPDWORD";
    }
    if constexpr (std::is_same_v < T, SOCKET>) {
        std::cout << "SOCKET";
    }
    if constexpr (std::is_same_v < T, SOCKET*>) {
        std::cout << "SOCKET*";
    }
    if constexpr (std::is_same_v < T, HANDLE*>) {
        std::cout << "HANDLE*";
    }
    if constexpr (std::is_same_v < T, sockaddr>) {
        std::cout << "sockaddr";
    }
    if constexpr (std::is_same_v < T, sockaddr*>) {
        std::cout << "sockaddr*";
    }
    if constexpr (std::is_same_v < T, LPINT>) {
        std::cout << "LPINT";
    }
    if constexpr (std::is_same_v < T, PADDRINFOEXA>) {
        std::cout << "PADDRINFOEXA";
    }
    if constexpr (std::is_same_v < T, ADDRINFOEXA>) {
        std::cout << "ADDRINFOEXA";
    }
    if constexpr (std::is_same_v < T, PWSTR>) {
        std::cout << "PWSTR";
    }
    if constexpr (std::is_same_v < T, size_t>) {
        std::cout << "size_t";
    }
    if constexpr (std::is_same_v < T, long>) {
        std::cout << "long";
    }
    if constexpr (std::is_same_v < T, u_long>) {
        std::cout << "u_long";
    }
    if constexpr (std::is_same_v < T, timeval>) {
        std::cout << "timeval";
    }
    if constexpr (std::is_same_v < T, timeval*>) {
        std::cout << "timeval*";
    }
}

int main()
{
    PSTR h{(CHAR*)"hello"};
    BYTE b{};
    HKEY k{};
    int y = 6;
    int* x{ &y };
    const sockaddr addr{};
    PADDRINFOEXA p{};
    LPHANDLE l{};
    PWSTR w{ (WCHAR*)L"h" };
    LPSTR s{};
    char hello[]{ "hello" };
    void* ptr{&hello};
    my_func(ptr);
}
