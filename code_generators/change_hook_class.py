from get_func_info import get_all_function_names
def change_namespace():
    names = get_all_function_names()
    old = """enum class Functions {
		CreateFileA,
		CreateFileW,
		DeleteFileA,
		DeleteFileW,
		ReadFile,
		ReadFileEx,
		WriteFile,
		WriteFileEx,
		WriteFileGather,
		send,
		recv,
		RegCreateKeyExA,
		RegDeleteKeyA,
		RegDeleteKeyExA,
		max_functions_number
	};"""
    patch = """enum class Functions {
    """

    for name in names:
        patch+=name
        patch+=",\n"


    patch+="""max_functions_number
    };"""
    
    with open("..\\inlineHook\\inlineHook.h",'r') as file:
        data = file.read()
        data = data.replace(old,patch)
        
    with open("..\\inlineHook\\inlineHook.h",'w') as file:
        file.write(data)

change_namespace()