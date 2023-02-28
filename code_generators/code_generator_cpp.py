from get_func_info import get_data


code = """#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
#include "newFunctions.h"
#include <cstring>
#include <sstream>
#include <time.h>

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;

extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

extern HANDLE LOGfile;
extern bool IsMyCall;

namespace newFunctions {
"""


'''

HANDLE __stdcall newCreateFileA(){
    	//unhook function
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



'''

with open("C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\inlineHook\\codeGeneratedFunctionsRegistry.h",'r') as file:
    data = file.read().split("{")[1].strip("}").split(";")
for func in data:
    try:
        func_name,return_type,params_list = get_data(func)
    except:
        continue
    if return_type != "void":
        func+="""{
        	//unhook function
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::func],
    		original_bytes[(int)Hook::Functions::func], 6, NULL);

        return_type result = func(params);
        Hook reset_hook { Hook::Functions::func};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}"""
    else:
        func+="""{
        	//unhook function
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::func],
    		original_bytes[(int)Hook::Functions::func], 6, NULL);

        func(params);
        Hook reset_hook { Hook::Functions::func};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

}"""

    func_name = func_name.replace("new","",1)
    print(func_name)
    func = func.replace("func",func_name)
    func = func.replace("return_type",return_type)
    func = func.replace("params",",".join(params_list))
    code+=func


with open("C:\\Users\\Omer Cohen\\Documents\\Programming\\Sandbox\\inlineHook\\codeGeneratedFunctionsRegistry.cpp",'w') as file:
    file.write(code)