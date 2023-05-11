from socket import *
from select import select
from code_generators.get_func_info import get_all_function_names

functions = get_all_function_names()


conn_sock = socket(AF_INET,SOCK_STREAM)
conn_sock.bind(("127.0.0.1",50505))
conn_sock.listen(2)
conn_sock2 = socket(AF_INET,SOCK_STREAM)
conn_sock2.bind(("127.0.0.1",50512))
conn_sock2.listen(2)

sock,addr = conn_sock.accept()

functions_to_hook = []

while True:
    try:
        function_name = sock.recv(1054)
    except ConnectionAbortedError:
        break
    if not function_name:
        break
    function_name = function_name.decode().strip("\n").strip("\0")
    if function_name == "stop":
        sock.send("0".encode())
        break
    try:
        functions.index(function_name[1:])
        sock.send("1".encode())
        functions_to_hook.append(function_name)
    except ValueError:
        print(function_name)
        if function_name[1:] == "fs" or function_name[1:] == "reg" or function_name[1:] == "sock":
            print("wow")
            sock.send("1".encode())
            functions_to_hook.append(function_name)
        else:
            sock.send("0".encode())


print("here")
sock,addr = conn_sock2.accept()

for name in functions_to_hook:
    stuffed_name = "b"
    stuffed_name+=name
    stuffed_name = stuffed_name.ljust(40,"@")
    print(f"sent {stuffed_name}")
    sock.send(stuffed_name.encode())

sock.send("stop".ljust(40,"@").encode())