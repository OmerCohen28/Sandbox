from socket import *
from select import select
from code_generators.get_func_info import get_all_function_names

functions = get_all_function_names()


conn_sock = socket(AF_INET,SOCK_STREAM)
conn_sock.bind(("",50505))
conn_sock.listen(2)

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
    if function_name == "end":break
    try:
        functions.index(function_name)
        sock.send("1".encode())
        functions_to_hook.append(function_name)
    except ValueError:
        sock.send("0".encode())


print("here")
sock,addr = conn_sock.accept()

for name in functions_to_hook:
    stuffed_name = name.ljust(40,"@")
    print(f"sent {stuffed_name}")
    sock.send(stuffed_name.encode())

sock.send("stop".ljust(40,"@").encode())