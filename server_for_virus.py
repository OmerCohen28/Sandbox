from socket import *

conn_sock = socket(AF_INET,SOCK_STREAM)
conn_sock.bind(("10.100.102.5",50500))
conn_sock.listen(2)

sock,addr = conn_sock.accept()

data = sock.recv(1054)
print(data)
sock.send(data)