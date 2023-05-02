import pydivert
import psutil
import win32event
import _thread
from socket import *
import datetime


NOT_ALLOWED_PORTS = []

GLOBAL_MUTEX = win32event.CreateMutex(None,False,"portMutex11")

conn_sock = socket(AF_INET,SOCK_STREAM)
conn_sock.bind(("172.17.158.237",50123))
conn_sock.listen(1)
sock,addr = conn_sock.accept()

def update_not_allowed_ports():
    print("here")
    size = sock.recv(1).decode()
    print(size)
    try:
        data = sock.recv(int(size)).decode()
    except ValueError:
        print("was not able to convert packet size to int")
        return
    print(data)
    sign,port = data[0],data[1:]
    if(sign == "x"):
        return
        try:
            NOT_ALLOWED_PORTS.remove(port)
        except ValueError:
            pass
    else:
        if(NOT_ALLOWED_PORTS.count(port) == 0):
            NOT_ALLOWED_PORTS.append(port)



def find_all_open_ports_of_process_id(pid:int)->list[int]:
    result = []
    for conn in psutil.net_connections():
        if conn.pid == pid:
            result.append(conn.laddr.port)
    return result


'''
def is_port_allowed(port: int, is_outbound: bool) -> int:
    if port is None:
        return None
    for conn in psutil.net_connections():
        if is_outbound:
            if conn.laddr and conn.laddr.port == port:
                return conn.pid
        else:
            if conn.raddr and conn.raddr.port == port:
                return conn.pid
    return None
'''

def log(pakcet,sock:socket):
    now = datetime.datetime.now()
    date_string = now.strftime(r"%Y-%m-%d %H:%M:%S")

    direction = "inbound" if packet.is_inbound else "outbound"
    msg = f"packet is {direction}.src adress: {packet.src_addr}:{packet.src_port}.\
        dst adress: {packet.dst_addr}:{packet.dst_port}.protocol: {packet.protocol} .timestamp: {date_string}"
    print(msg)


def is_port_allowed(port: int) -> bool:
    if port is None:
        return True
    result = win32event.WaitForSingleObject(GLOBAL_MUTEX, 0)
    if result == win32event.WAIT_OBJECT_0:
        win32event.ReleaseMutex(GLOBAL_MUTEX)
        if(NOT_ALLOWED_PORTS.count(port) == 0):
            return True
        return False
    elif result == win32event.WAIT_TIMEOUT:
        update_not_allowed_ports()
        return is_port_allowed(port)
    


while True:
    with pydivert.WinDivert("outbound or inbound") as w:
        for packet in w:
            log(packet,None)
            exit(1)
            if packet.is_inbound:
                #print(f"dst_port: {packet.dst_port}, src_port: {packet.src_port}, pid: {is_port_allowed(packet.dst_port,packet.is_outbound)}, INBOUND")
                if not is_port_allowed(packet.dst_port):
                    print(packet.dst_port)
                    print(NOT_ALLOWED_PORTS)
                    print(packet.payload)
                    x = input("walla")
                    '''
                    log stuff
                    '''
                    continue
            else:
                #print(f"dst_port: {packet.dst_port}, src_port: {packet.src_port}, pid: {is_port_allowed(packet.src_port,packet.is_outbound)}, OUTBOUND")
                if not is_port_allowed(packet.src_port):
                    print(packet.src_port)
                    print(packet.payload)
                    x = input("walla")
                    '''
                    log stuff
                    '''
                    continue
            try:
                w.send(packet)
            except OSError as e:
                print(f"Eror: {e}")


# for conn in psutil.net_connections():
#     if conn.pid == 11780:
#         print(conn)


'''
1st scenario - 
    incoming packet - 
        what to do - 
            send an empty buffer instead
        how to recognize - 
            ?
        log - 
            time, payload, port, ip
        
    outgoing packet - 
        what to do - 
            dispose of packet and leave as is
        how to recognize - 
            ?
        log - 
            time, payload, dst_ip,dst_port,src_port


'''