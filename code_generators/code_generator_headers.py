import re
code = """#pragma once
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <sstream>
#include <time.h>

namespace newFunctions {
"""

with open("functions_sockets.txt",'r') as file:
    data = file.read().split(";")
    #print(data.split(";"))

add = " __stdcall new"

for raw  in data:
    add1 = "WSAAPI __stdcall new"
    add2 = " __stdcall new"
    try:
        raw.index("WSAAPI")
        raw = raw.replace("WSAAPI ",add1,1)

    except ValueError:
        raw = raw.replace(" ",add2,1)

    
    
    forbidden = ["[in]","[out]","[optional]","[in, out]","[in, out, optional]","[out, optional]","[in, optional]"]
    for forb in forbidden:
        raw = raw.replace(forb," "*len(forb))

    raw+=";"
    code+=raw


print(code)

with open("inlineHook\\codeGeneratedFunctionsSockets.h",'w') as file:
    file.write(code)


raw = """BOOL AcceptEx(
  [in]  SOCKET       sListenSocket,
  [in]  SOCKET       sAcceptSocket,
  [in]  PVOID        lpOutputBuffer,
  [in]  DWORD        dwReceiveDataLength,
  [in]  DWORD        dwLocalAddressLength,
  [in]  DWORD        dwRemoteAddressLength,
  [out] LPDWORD      lpdwBytesReceived,
  [in]  LPOVERLAPPED lpOverlapped
);"""

pattren = re.compile("^.+? ()")

index = re.search(pattern=pattren,string=raw)

add1 = "WSAAPI __stdcall new"
add2 = " __stdcall new"
try:
    raw.index("WSAAPI")
    raw = raw.replace("WSAAPI ",add1,1)

except ValueError:
    raw = raw.replace(" ",add2,1)
print(raw)


