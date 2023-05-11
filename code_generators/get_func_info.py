import re

'''
gets function data, returns a tupple 
(func_name, return type, params_list)
'''
def get_data(raw):
    raw = raw.strip("\n")
    return_type = raw.split(" ")[0]
    func_name = raw.split("(")[0].split(" ")[-1]
    params = raw.split("(")[1].strip(")")

    pa = params.split(",")
    params_list = []
    params_type_list = []
    for p in pa:
        param = p.split(" ")[-1]
        # print("param",p)
        params_type_list += re.findall(string=p, pattern=r".+?\s+(.{0,}?)\s.+")
        try:
            param.index("[")
            continue
        except:
            pass
        param = param.strip("*")
        param = param.replace("\n","")
        params_list.append(param)
    return (func_name,return_type,params_list,params_type_list)



def get_all_function_names():
    try:
        with open("..\\inlineHook\\codeGeneratedFunctionsFileSystem.h",'r') as file:
            data = file.read()
            data_fs = data.split("{")[1].strip("}").split(";")
    except FileNotFoundError:
        with open("inlineHook\\codeGeneratedFunctionsFileSystem.h",'r') as file:
            data = file.read()
            data_fs = data.split("{")[1].strip("}").split(";")
    try:
        with open("..\\inlineHook\\codeGeneratedFunctionsSockets.h",'r') as file:
            data_socket = file.read().split("{")[1].strip("}").split(";")
    except FileNotFoundError:
        with open("inlineHook\\codeGeneratedFunctionsSockets.h",'r') as file:
            data_socket = file.read().split("{")[1].strip("}").split(";")
    try:
        with open("..\\inlineHook\\codeGeneratedFunctionsRegistry.h",'r') as file:
            data_reg = file.read().split("{")[1].strip("}").split(";")
    except FileNotFoundError:
        with open("inlineHook\\codeGeneratedFunctionsRegistry.h",'r') as file:
            data_reg = file.read().split("{")[1].strip("}").split(";")
    names = []
    f = []
    for func in data_fs:
        try:
            names.append(get_data(func)[0].replace("new","",1))
        except:
            continue
    for func in data_socket:
        try:
            names.append(get_data(func)[0].replace("new","",1))
        except:
            continue
    for func in data_reg:
        try:
            names.append(get_data(func)[0].replace("new","",1))
            f.append(get_data(func)[0].replace("new","",1))
        except:
            continue
    return names

raw = """
BOOL __stdcall newWriteFileEx(
    HANDLE                          hFile,
    LPCVOID                         lpBuffer,
    DWORD                           nNumberOfBytesToWrite,
    LPOVERLAPPED                    lpOverlapped,
    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);"""


# print(get_data(raw)[-1])