from socket import *
import os
print(os.getpid())
x = input("c")
conn_sock = socket(AF_INET,SOCK_STREAM)
conn_sock.bind(("192.168.0.120",50500))
conn_sock.listen(2)

sock,addr = conn_sock.accept()
print(sock.getpeername())
print(sock.getsockname())
data = sock.recv(1054)
print(data)
sock.send(data)