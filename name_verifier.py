from socket import *
from select import select
from code_generators.get_func_info import get_all_function_names

functions = get_all_function_names()

conn_sock = socket(AF_INET,SOCK_STREAM)
conn_sock.bind(("",50505))
conn_sock.listen(1)

sock,addr = conn_sock.accept()
while True:
    function_name = sock.recv(1054).decode().strip("\n").strip("\0")
    try:
        functions.index(function_name)
        sock.send("1".encode())
    except ValueError:
        sock.send("0".encode())

