#pragma once
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
SOCKET WSAAPI __stdcall newaccept(
            SOCKET   s,
            sockaddr *addr,
            int      *addrlen
);
int __stdcall newbind(
       SOCKET         s,
       const sockaddr *addr,
       int            namelen
);
int __stdcall newclosesocket(
       SOCKET s
);
int WSAAPI __stdcall newconnect(
       SOCKET         s,
       const sockaddr *name,
       int            namelen
);
char* __stdcall newgai_strerrorA(
       int ecode
);

int __stdcall newgethostname(
        char *name,
        int  namelen
);
int __stdcall newgetpeername(
            SOCKET   s,
            sockaddr *name,
            int      *namelen
);
protoent* __stdcall newgetprotobyname(
       const char *name
);
protoent* __stdcall newgetprotobynumber(
  int proto
);
servent* __stdcall newgetservbyname(
       const char *name,
       const char *proto
);
servent* __stdcall newgetservbyport(
       int        port,
       const char *proto
);
int __stdcall newgetsockname(
            SOCKET   s,
            sockaddr *name,
            int      *namelen
);
int __stdcall newgetsockopt(
            SOCKET s,
            int    level,
            int    optname,
            char   *optval,
            int    *optlen
);
u_short __stdcall newhtons(
       u_short hostshort
);
unsigned long WSAAPI __stdcall newinet_addr(
  const char *cp
);
char *WSAAPI __stdcall newinet_ntoa(
  in_addr in
);
PCWSTR WSAAPI __stdcall newInetNtopW(
        INT        Family,
        const VOID *pAddr,
        PWSTR      pStringBuf,
        size_t     StringBufSize
);
INT WSAAPI __stdcall newInetPtonW(
        INT    Family,
        PCWSTR pszAddrString,
        PVOID  pAddrBuf
);
int __stdcall newioctlsocket(
            SOCKET s,
            long   cmd,
            u_long *argp
);
int WSAAPI __stdcall newlisten(
       SOCKET s,
       int    backlog
);
u_long __stdcall newntohl(
       u_long netlong
);
u_short __stdcall newntohs(
       u_short netshort
);
int __stdcall newrecv(
        SOCKET s,
        char   *buf,
        int    len,
        int    flags
);
int __stdcall newrecvfrom(
                      SOCKET   s,
                      char     *buf,
                      int      len,
                      int      flags,
                      sockaddr *from,
                      int      *fromlen
);
int WSAAPI __stdcall newselect(
            int           nfds,
            fd_set        *readfds,
            fd_set        *writefds,
            fd_set        *exceptfds,
            const timeval *timeout
);
int WSAAPI __stdcall newsend(
       SOCKET     s,
       const char *buf,
       int        len,
       int        flags
);
int __stdcall newsendto(
       SOCKET         s,
       const char     *buf,
       int            len,
       int            flags,
       const sockaddr *to,
       int            tolen
);
int __stdcall newsetsockopt(
       SOCKET     s,
       int        level,
       int        optname,
       const char *optval,
       int        optlen
);
int __stdcall newshutdown(
       SOCKET s,
       int    how
);
SOCKET WSAAPI __stdcall newsocket(
       int af,
       int type,
       int protocol
);
SOCKET WSAAPI __stdcall newWSAAccept(
            SOCKET          s,
            sockaddr        *addr,
            LPINT           addrlen,
            LPCONDITIONPROC lpfnCondition,
            DWORD_PTR       dwCallbackData
);
INT WSAAPI __stdcall newWSAAddressToStringA(
                 LPSOCKADDR          lpsaAddress,
                 DWORD               dwAddressLength,
                 LPWSAPROTOCOL_INFOA lpProtocolInfo,
                 LPSTR               lpszAddressString,
                 LPDWORD             lpdwAddressStringLength
);
HANDLE __stdcall newWSAAsyncGetHostByAddr(
  HWND       hWnd,
  u_int      wMsg,
  const char *addr,
  int        len,
  int        type,
  char       *buf,
  int        buflen
);
HANDLE __stdcall newWSAAsyncGetHostByName(
  HWND       hWnd,
  u_int      wMsg,
  const char *name,
  char       *buf,
  int        buflen
);
HANDLE __stdcall newWSAAsyncGetProtoByName(
        HWND       hWnd,
        u_int      wMsg,
        const char *name,
        char       *buf,
        int        buflen
);
HANDLE __stdcall newWSAAsyncGetProtoByNumber(
        HWND  hWnd,
        u_int wMsg,
        int   number,
        char  *buf,
        int   buflen
);
HANDLE __stdcall newWSAAsyncGetServByName(
        HWND       hWnd,
        u_int      wMsg,
        const char *name,
        const char *proto,
        char       *buf,
        int        buflen
);
HANDLE __stdcall newWSAAsyncGetServByPort(
        HWND       hWnd,
        u_int      wMsg,
        int        port,
        const char *proto,
        char       *buf,
        int        buflen
);
int __stdcall newWSAAsyncSelect(
       SOCKET s,
       HWND   hWnd,
       u_int  wMsg,
       long   lEvent
);
int __stdcall newWSACancelAsyncRequest(
       HANDLE hAsyncTaskHandle
);
int __stdcall newWSACleanup();
BOOL WSAAPI __stdcall newWSACloseEvent(
       WSAEVENT hEvent
);
int WSAAPI __stdcall newWSAConnect(
        SOCKET         s,
        const sockaddr *name,
        int            namelen,
        LPWSABUF       lpCallerData,
        LPWSABUF       lpCalleeData,
        LPQOS          lpSQOS,
        LPQOS          lpGQOS
);
BOOL __stdcall newWSAConnectByList(
            SOCKET               s,
            PSOCKET_ADDRESS_LIST SocketAddress,
            LPDWORD              LocalAddressLength,
            LPSOCKADDR           LocalAddress,
            LPDWORD              RemoteAddressLength,
            LPSOCKADDR           RemoteAddress,
            const timeval        *timeout,
            LPWSAOVERLAPPED      Reserved
);
BOOL __stdcall newWSAConnectByNameA(
            SOCKET          s,
            LPCSTR          nodename,
            LPCSTR          servicename,
            LPDWORD         LocalAddressLength,
            LPSOCKADDR      LocalAddress,
            LPDWORD         RemoteAddressLength,
            LPSOCKADDR      RemoteAddress,
            const timeval   *timeout,
            LPWSAOVERLAPPED Reserved
);
WSAEVENT WSAAPI __stdcall newWSACreateEvent();
int WSAAPI __stdcall newWSADuplicateSocketA(
        SOCKET              s,
        DWORD               dwProcessId,
        LPWSAPROTOCOL_INFOA lpProtocolInfo
);
INT WSAAPI __stdcall newWSAEnumNameSpaceProvidersA(
            LPDWORD              lpdwBufferLength,
            LPWSANAMESPACE_INFOA lpnspBuffer
);
INT WSAAPI __stdcall newWSAEnumNameSpaceProvidersExA(
            LPDWORD                lpdwBufferLength,
            LPWSANAMESPACE_INFOEXA lpnspBuffer
);
int WSAAPI __stdcall newWSAEnumNetworkEvents(
        SOCKET             s,
        WSAEVENT           hEventObject,
        LPWSANETWORKEVENTS lpNetworkEvents
);
int WSAAPI __stdcall newWSAEnumProtocolsA(
            LPINT               lpiProtocols,
            LPWSAPROTOCOL_INFOA lpProtocolBuffer,
            LPDWORD             lpdwBufferLength
);
int WSAAPI __stdcall newWSAEventSelect(
       SOCKET   s,
       WSAEVENT hEventObject,
       long     lNetworkEvents
);
int __stdcall new__WSAFDIsSet(
  SOCKET unnamedParam1,
  fd_set *unnamedParam2
);
int __stdcall newWSAGetLastError();
BOOL WSAAPI __stdcall newWSAGetOverlappedResult(
        SOCKET          s,
        LPWSAOVERLAPPED lpOverlapped,
        LPDWORD         lpcbTransfer,
        BOOL            fWait,
        LPDWORD         lpdwFlags
);
BOOL WSAAPI __stdcall newWSAGetQOSByName(
            SOCKET   s,
            LPWSABUF lpQOSName,
            LPQOS    lpQOS
);
INT WSAAPI __stdcall newWSAGetServiceClassInfoA(
            LPGUID                 lpProviderId,
            LPGUID                 lpServiceClassId,
            LPDWORD                lpdwBufSize,
            LPWSASERVICECLASSINFOA lpServiceClassInfo
);
INT WSAAPI __stdcall newWSAGetServiceClassNameByClassIdA(
            LPGUID  lpServiceClassId,
            LPSTR   lpszServiceClassName,
            LPDWORD lpdwBufferLength
);
int WSAAPI __stdcall newWSAHtonl(
        SOCKET s,
        u_long hostlong,
        u_long *lpnetlong
);
int WSAAPI __stdcall newWSAHtons(
        SOCKET  s,
        u_short hostshort,
        u_short *lpnetshort
);
INT WSAAPI __stdcall newWSAImpersonateSocketPeer(
                 SOCKET         Socket,
                 const sockaddr *PeerAddr,
                 ULONG          PeerAddrLen
);
INT WSAAPI __stdcall newWSAInstallServiceClassA(
       LPWSASERVICECLASSINFOA lpServiceClassInfo
);
int WSAAPI __stdcall newWSAIoctl(
        SOCKET                             s,
        DWORD                              dwIoControlCode,
        LPVOID                             lpvInBuffer,
        DWORD                              cbInBuffer,
        LPVOID                             lpvOutBuffer,
        DWORD                              cbOutBuffer,
        LPDWORD                            lpcbBytesReturned,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
SOCKET WSAAPI __stdcall newWSAJoinLeaf(
        SOCKET         s,
        const sockaddr *name,
        int            namelen,
        LPWSABUF       lpCallerData,
        LPWSABUF       lpCalleeData,
        LPQOS          lpSQOS,
        LPQOS          lpGQOS,
        DWORD          dwFlags
);
INT WSAAPI __stdcall newWSALookupServiceBeginA(
        LPWSAQUERYSETA lpqsRestrictions,
        DWORD          dwControlFlags,
        LPHANDLE       lphLookup
);
INT WSAAPI __stdcall newWSALookupServiceEnd(
       HANDLE hLookup
);
INT WSAAPI __stdcall newWSALookupServiceNextA(
            HANDLE         hLookup,
            DWORD          dwControlFlags,
            LPDWORD        lpdwBufferLength,
            LPWSAQUERYSETA lpqsResults
);
INT WSAAPI __stdcall newWSANSPIoctl(
            HANDLE          hLookup,
            DWORD           dwControlCode,
            LPVOID          lpvInBuffer,
            DWORD           cbInBuffer,
            LPVOID          lpvOutBuffer,
            DWORD           cbOutBuffer,
            LPDWORD         lpcbBytesReturned,
            LPWSACOMPLETION lpCompletion
);
int WSAAPI __stdcall newWSANtohl(
        SOCKET s,
        u_long netlong,
        u_long *lphostlong
);
int WSAAPI __stdcall newWSANtohs(
        SOCKET  s,
        u_short netshort,
        u_short *lphostshort
);
int WSAAPI __stdcall newWSAPoll(
            LPWSAPOLLFD fdArray,
            ULONG       fds,
            INT         timeout
);
INT WSAAPI __stdcall newWSAProviderConfigChange(
            LPHANDLE                           lpNotificationHandle,
            LPWSAOVERLAPPED                    lpOverlapped,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSARecv(
            SOCKET                             s,
            LPWSABUF                           lpBuffers,
            DWORD                              dwBufferCount,
            LPDWORD                            lpNumberOfBytesRecvd,
            LPDWORD                            lpFlags,
            LPWSAOVERLAPPED                    lpOverlapped,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSARecvDisconnect(
        SOCKET   s,
        LPWSABUF lpInboundDisconnectData
);
int WSAAPI __stdcall newWSARecvFrom(
            SOCKET                             s,
            LPWSABUF                           lpBuffers,
            DWORD                              dwBufferCount,
            LPDWORD                            lpNumberOfBytesRecvd,
            LPDWORD                            lpFlags,
            sockaddr                           *lpFrom,
            LPINT                              lpFromlen,
            LPWSAOVERLAPPED                    lpOverlapped,
            LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
INT WSAAPI __stdcall newWSARemoveServiceClass(
       LPGUID lpServiceClassId
);
BOOL WSAAPI __stdcall newWSAResetEvent(
       WSAEVENT hEvent
);
INT WSAAPI __stdcall newWSARevertImpersonation();
int WSAAPI __stdcall newWSASend(
        SOCKET                             s,
        LPWSABUF                           lpBuffers,
        DWORD                              dwBufferCount,
        LPDWORD                            lpNumberOfBytesSent,
        DWORD                              dwFlags,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSASendDisconnect(
       SOCKET   s,
       LPWSABUF lpOutboundDisconnectData
);
int WSAAPI __stdcall newWSASendMsg(
        SOCKET                             Handle,
        LPWSAMSG                           lpMsg,
        DWORD                              dwFlags,
        LPDWORD                            lpNumberOfBytesSent,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSASendTo(
        SOCKET                             s,
        LPWSABUF                           lpBuffers,
        DWORD                              dwBufferCount,
        LPDWORD                            lpNumberOfBytesSent,
        DWORD                              dwFlags,
        const sockaddr                     *lpTo,
        int                                iTolen,
        LPWSAOVERLAPPED                    lpOverlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
BOOL WSAAPI __stdcall newWSASetEvent(
       WSAEVENT hEvent
);
void __stdcall newWSASetLastError(
       int iError
);
INT WSAAPI __stdcall newWSASetServiceA(
       LPWSAQUERYSETA   lpqsRegInfo,
       WSAESETSERVICEOP essoperation,
       DWORD            dwControlFlags
);
SOCKET WSAAPI __stdcall newWSASocketA(
       int                 af,
       int                 type,
       int                 protocol,
       LPWSAPROTOCOL_INFOA lpProtocolInfo,
       GROUP               g,
       DWORD               dwFlags
);
int __stdcall newWSAStartup(
        WORD      wVersionRequired,
        LPWSADATA lpWSAData
);
INT WSAAPI __stdcall newWSAStringToAddressA(
                 LPSTR               AddressString,
                 INT                 AddressFamily,
                 LPWSAPROTOCOL_INFOA lpProtocolInfo,
                 LPSOCKADDR          lpAddress,
                 LPINT               lpAddressLength
);
DWORD WSAAPI __stdcall newWSAWaitForMultipleEvents(
       DWORD          cEvents,
       const WSAEVENT *lphEvents,
       BOOL           fWaitAll,
       DWORD          dwTimeout,
       BOOL           fAlertable
);
}