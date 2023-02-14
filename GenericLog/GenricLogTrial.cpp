#include <vector>
#include <iostream>
#include <Windows.h>
#include <sstream>

class Logger {
    std::vector<char> data;
public:
    Logger() {}

    template<typename T>
    Logger(T&& t) {
        if constexpr (std::is_pointer_v<T>) {
            if constexpr (std::is_same_v<T, char*>) {
                std::string str = t;
                for (char c : str) {
                    data.push_back(c);
                }
            }
            else if constexpr (std::is_same_v<T, LPCSTR>) {
                std::string str = t;
                for (char c : str) {
                    data.push_back(c);
                }
            }
            else if constexpr (std::is_same_v<T, HANDLE>) {
                char buffer[50];
                sprintf_s(buffer, 50, "%p", t);
                for (int i = 0; i < strlen(buffer); i++) {
                    data.push_back(buffer[i]);
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
            if constexpr (std::is_same_v<T, int>) {
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
        std::cout << "hello";
    }
    if constexpr (std::is_same_v < T, char*>) {
        char* c = new char[] {"hye"};
        std::cout << c;
    } if constexpr (std::is_same_v < T, DWORD>) {
        char* c = new char[] {"dasdsdsa"};
        std::cout << c;
    }
    if constexpr (std::is_same_v < T, HANDLE>) {
        char* c = new char[] {"!!!!!"};
        std::cout << c;
    }
    if constexpr (std::is_same_v < T, char>) {
        std::cout << arg;
    }
    if constexpr (std::is_same_v < T, PVOID>) {
        std::cout << "nope";
    }
    if constexpr (std::is_same_v < T, void*>) {
        std::cout << "problem";
    }
}

int main()
{
    PVOID p = new char;
    my_func(p);
}
