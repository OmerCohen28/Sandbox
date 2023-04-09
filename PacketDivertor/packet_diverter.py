import pydivert
import psutil

'''
infinte loop over pydivert handle and stop all outgoing/incoming packets to said ports

possible solution - 
    for each packet find its process ID, than decide if it can go through or not.
'''


def find_all_open_ports_of_process_id(pid:int)->list[int]:
    result = []
    for conn in psutil.net_connections():
        if conn.pid == pid:
            result.append(conn.laddr.port)
    return result

def find_pid_of_port(port: int, is_outbound: bool) -> int:
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

# SPECIAL_PID = input("what pid to block? ")
process = psutil.process_iter(["pid","name"])
for proc in process:
    if(proc.pid == 12168):
        print(proc.connections())



exit(1)
while True:
    with pydivert.WinDivert("outbound or inbound") as w:
        for packet in w:
            if packet.is_inbound:
                print(f"dst_port: {packet.dst_port}, src_port: {packet.src_port}, pid: {find_pid_of_port(packet.dst_port,packet.is_outbound)}, INBOUND")
                if find_pid_of_port(packet.dst_port,packet.is_outbound) == SPECIAL_PID:
                    print(packet.payload)
                    x = input("walla")
                    '''
                    log stuff
                    '''
                    continue
            else:
                print(f"dst_port: {packet.dst_port}, src_port: {packet.src_port}, pid: {find_pid_of_port(packet.src_port,packet.is_outbound)}, OUTBOUND")
                if find_pid_of_port(packet.src_port,packet.is_outbound) == SPECIAL_PID:
                    print(packet.payload)
                    x = input("walla")
                    '''
                    log stuff
                    '''
                    continue
            w.send(packet)


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