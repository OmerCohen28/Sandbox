#include <iostream>
#include <Windows.h>
#include <string>
#include "injectDll.h"
#define _path_to_virus_ "D:\\Actual sandbox sln\\virus\\Debug\\virus.exe"

int main()
{
    while (true) {
        std::cout << "what file would you like to run?\n";
        std::cout << "type \"stop\" if you would like to stop execution,\ntype defualt to run the default virus provided by the program\n";
        std::cout << "path: ";
        std::string file{};
        std::cin >> file;
        std::cout << file.c_str() << '\n';
        if (file == "stop") {
            break;
        }
        if (file == "default") {
            std::string path{ _path_to_virus_ };
            inject_dll(path);
        }
        else {
            inject_dll(file);
        }
    }
    std::cout << "thank you for using SafeBox :)\n";
    return 0;
}
