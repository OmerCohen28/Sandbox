import pydivert
import psutil

'''
infinte loop over pydivert handle and stop all outgoing/ingoing packets to said ports

possible solution - 
    for each packet find its process ID, than decide if it can go through or not.
'''


def find_all_open_ports_of_process_id(pid:int)->list[int]:
    result = []
    for conn in psutil.net_connections():
        if conn.pid == pid:
            result.append(conn.laddr.port)
    return result

def find_pid_of_port(port:int)->int:
    for conn in psutil.net_connections():
        if(conn.laddr.port == port):
            return conn.pid



