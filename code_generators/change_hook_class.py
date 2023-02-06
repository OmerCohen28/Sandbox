from get_func_info import get_all_function_names
def change():
    names = get_all_function_names()
    old = """void* get_new_fnc_pointer() {
		switch (func_to_hook) {
		case Functions::CreateFileA: return &newFunctions::newCreateFileA; break;
		case Functions::CreateFile2:return &newFunctions::newCreateFileW; break;
		case Functions::DeleteFileA:return &newFunctions::newDeleteFileA; break;
		case Functions::ReadFile:return &newFunctions::newReadFile; break;
		case Functions::ReadFileEx:return &newFunctions::newReadFileEx; break;
		case Functions::WriteFile:return &newFunctions::newWriteFile; break;
		case Functions::WriteFileEx:return nullptr; break;
		case Functions::send:return &newFunctions::newsend; break;
		case Functions::recv:return &newFunctions::newrecv; break;
		case Functions::RegCreateKeyExA:return &newFunctions::newRegCreateKeyExA; break;
		case Functions::RegDeleteKeyA:return &newFunctions::newRegDeleteKeyA; break;
		case Functions::RegDeleteKeyExA:return &newFunctions::newRegDeleteKeyExA; break;
		}

	}"""
    patch = """		void* get_new_fnc_pointer() {
		switch (func_to_hook) {
    """

    for name in names:
        case = f"			case Functions::{name}: return &newFunctions::new{name};break;\n"
        patch+=case


    patch+="""
    }
}"""
    
    with open("..\\inlineHook\\inlineHook.h",'r') as file:
        data = file.read()
        data = data.replace(old,patch)
        
    with open("..\\inlineHook\\inlineHook.h",'w') as file:
        file.write(data)

change()