#pragma once
#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#include <nspapi.h>
#include <mswsock.h>
#include <ws2tcpip.h>
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
  [in]      SOCKET   s,
  [out]     sockaddr *addr,
  [in, out] int      *addrlen
);
BOOL __stdcall newAcceptEx(
  [in]  SOCKET       sListenSocket,
  [in]  SOCKET       sAcceptSocket,
  [in]  PVOID        lpOutputBuffer,
  [in]  DWORD        dwReceiveDataLength,
  [in]  DWORD        dwLocalAddressLength,
  [in]  DWORD        dwRemoteAddressLength,
  [out] LPDWORD      lpdwBytesReceived,
  [in]  LPOVERLAPPED lpOverlapped
);
int __stdcall newbind(
  [in] SOCKET         s,
       const sockaddr *addr,
  [in] int            namelen
);
int __stdcall newclosesocket(
  [in] SOCKET s
);
int WSAAPI __stdcall newconnect(
  [in] SOCKET         s,
  [in] const sockaddr *name,
  [in] int            namelen
);

BOOL __stdcall newLpfnConnectex(
  [in]           SOCKET s,
  [in]           const sockaddr *name,
  [in]           int namelen,
  [in, optional] PVOID lpSendBuffer,
  [in]           DWORD dwSendDataLength,
  [out]          LPDWORD lpdwBytesSent,
  [in]           LPOVERLAPPED lpOverlapped
);

BOOL __stdcall newDisconnectEx(
  _In_ SOCKET hSocket,
  _In_ LPOVERLAPPED lpOverlapped,
  _In_ DWORD dwFlags,
  _In_ DWORD reserved
);
INT __stdcall newEnumProtocolsA(
  [in, optional] LPINT   lpiProtocols,
  [out]          LPVOID  lpProtocolBuffer,
  [in, out]      LPDWORD lpdwBufferLength
);
VOID WSAAPI __stdcall newfreeaddrinfo(
  [in] PADDRINFOA pAddrInfo
);
void WSAAPI __stdcall newFreeAddrInfoEx(
  [in] PADDRINFOEXA pAddrInfoEx
);
VOID WSAAPI __stdcall newFreeAddrInfoW(
  [in] PADDRINFOW pAddrInfo
);
char* __stdcall newgai_strerrorA(
  [in] int ecode
);
void __stdcall newGetAcceptExSockaddrs(
  [in]  PVOID    lpOutputBuffer,
  [in]  DWORD    dwReceiveDataLength,
  [in]  DWORD    dwLocalAddressLength,
  [in]  DWORD    dwRemoteAddressLength,
  [out] sockaddr **LocalSockaddr,
  [out] LPINT    LocalSockaddrLength,
  [out] sockaddr **RemoteSockaddr,
  [out] LPINT    RemoteSockaddrLength
);
INT __stdcall newGetAddressByNameA(
  [in]           DWORD                dwNameSpace,
  [in]           LPGUID               lpServiceType,
  [in, optional] LPSTR                lpServiceName,
  [in, optional] LPINT                lpiProtocols,
  [in]           DWORD                dwResolution,
  [in, optional] LPSERVICE_ASYNC_INFO lpServiceAsyncInfo,
  [out]          LPVOID               lpCsaddrBuffer,
  [in, out]      LPDWORD              lpdwBufferLength,
  [in, out]      LPSTR                lpAliasBuffer,
  [in, out]      LPDWORD              lpdwAliasBufferLength
);
INT WSAAPI __stdcall newgetaddrinfo(
  [in, optional] PCSTR           pNodeName,
  [in, optional] PCSTR           pServiceName,
  [in, optional] const ADDRINFOA *pHints,
  [out]          PADDRINFOA      *ppResult
);
INT WSAAPI __stdcall newGetAddrInfoExA(
  [in, optional]  PCSTR                              pName,
  [in, optional]  PCSTR                              pServiceName,
  [in]            DWORD                              dwNameSpace,
  [in, optional]  LPGUID                             lpNspId,
  [in, optional]  const ADDRINFOEXA                  *hints,
  [out]           PADDRINFOEXA                       *ppResult,
  [in, optional]  timeval                            *timeout,
  [in, optional]  LPOVERLAPPED                       lpOverlapped,
  [in, optional]  LPLOOKUPSERVICE_COMPLETION_ROUTINE lpCompletionRoutine,
  [out, optional] LPHANDLE                           lpNameHandle
);
INT WSAAPI __stdcall newGetAddrInfoExCancel(
  [in] LPHANDLE lpHandle
);
INT WSAAPI __stdcall newGetAddrInfoExOverlappedResult(
  LPOVERLAPPED lpOverlapped
);
INT WSAAPI __stdcall newGetAddrInfoW(
  [in, optional] PCWSTR          pNodeName,
  [in, optional] PCWSTR          pServiceName,
  [in, optional] const ADDRINFOW *pHints,
  [out]          PADDRINFOW      *ppResult
);
int __stdcall newgethostname(
  [out] char *name,
  [in]  int  namelen
);
int WSAAPI __stdcall newGetHostNameW(
  [out] PWSTR name,
  [in]  int   namelen
);
int __stdcall newgetipv4sourcefilter(
  [in]      SOCKET              Socket,
  [in]      IN_ADDR             Interface,
  [in]      IN_ADDR             Group,
  [out]     MULTICAST_MODE_TYPE *FilterMode,
  [in, out] ULONG               *SourceCount,
  [out]     IN_ADDR             *SourceList
);
INT __stdcall newGetNameByTypeA(
  [in]  LPGUID lpServiceType,
  [out] LPSTR  lpServiceName,
  [in]  DWORD  dwNameLength
);
INT WSAAPI __stdcall newgetnameinfo(
  [in]  const SOCKADDR *pSockaddr,
  [in]  socklen_t      SockaddrLength,
  [out] PCHAR          pNodeBuffer,
  [in]  DWORD          NodeBufferSize,
  [out] PCHAR          pServiceBuffer,
  [in]  DWORD          ServiceBufferSize,
  [in]  INT            Flags
);
INT WSAAPI __stdcall newGetNameInfoW(
  [in]  const SOCKADDR *pSockaddr,
  [in]  socklen_t      SockaddrLength,
  [out] PWCHAR         pNodeBuffer,
  [in]  DWORD          NodeBufferSize,
  [out] PWCHAR         pServiceBuffer,
  [in]  DWORD          ServiceBufferSize,
  [in]  INT            Flags
);
int __stdcall newgetpeername(
  [in]      SOCKET   s,
  [out]     sockaddr *name,
  [in, out] int      *namelen
);
protoent* __stdcall newgetprotobyname(
  [in] const char *name
);
protoent* __stdcall newgetprotobynumber(
  int proto
);
servent* __stdcall newgetservbyname(
  [in] const char *name,
  [in] const char *proto
);
servent* __stdcall newgetservbyport(
  [in] int        port,
  [in] const char *proto
);
INT __stdcall newGetServiceA(
  [in]           DWORD                dwNameSpace,
  [in]           LPGUID               lpGuid,
  [in]           LPSTR                lpServiceName,
  [in]           DWORD                dwProperties,
  [out]          LPVOID               lpBuffer,
  [in, out]      LPDWORD              lpdwBufferSize,
  [in, optional] LPSERVICE_ASYNC_INFO lpServiceAsyncInfo
);
int __stdcall newgetsockname(
  [in]      SOCKET   s,
  [out]     sockaddr *name,
  [in, out] int      *namelen
);
int __stdcall newgetsockopt(
  [in]      SOCKET s,
  [in]      int    level,
  [in]      int    optname,
  [out]     char   *optval,
  [in, out] int    *optlen
);
int __stdcall newgetsourcefilter(
  [in]      SOCKET              Socket,
  [in]      ULONG               Interface,
  [in]      const SOCKADDR      *Group,
  [in]      int                 GroupLength,
  [out]     MULTICAST_MODE_TYPE *FilterMode,
  [in, out] ULONG               *SourceCount,
  [out]     SOCKADDR_STORAGE    *SourceList
);
INT __stdcall newGetTypeByNameA(
  [in]      LPSTR  lpServiceName,
  [in, out] LPGUID lpServiceType
);
u_short __stdcall newhtons(
  [in] u_short hostshort
);
unsigned long WSAAPI __stdcall newinet_addr(
  const char *cp
);
char* WSAAPI __stdcall newinet_ntoa(
  in_addr in
);
PCWSTR WSAAPI __stdcall newInetNtopW(
  [in]  INT        Family,
  [in]  const VOID *pAddr,
  [out] PWSTR      pStringBuf,
  [in]  size_t     StringBufSize
);
INT WSAAPI __stdcall newInetPtonW(
  [in]  INT    Family,
  [in]  PCWSTR pszAddrString,
  [out] PVOID  pAddrBuf
);
int __stdcall newioctlsocket(
  [in]      SOCKET s,
  [in]      long   cmd,
  [in, out] u_long *argp
);
int WSAAPI __stdcall newlisten(
  [in] SOCKET s,
  [in] int    backlog
);
double __stdcall newntohd(
  unsigned __int64 Value
);
float __stdcall newntohf(
  unsigned __int32 Value
);
u_long __stdcall newntohl(
  [in] u_long netlong
);
u_short __stdcall newntohs(
  [in] u_short netshort
);
int __stdcall newrecv(
  [in]  SOCKET s,
  [out] char   *buf,
  [in]  int    len,
  [in]  int    flags
);
int __stdcall newrecvfrom(
  [in]                SOCKET   s,
  [out]               char     *buf,
  [in]                int      len,
  [in]                int      flags,
  [out]               sockaddr *from,
  [in, out, optional] int      *fromlen
);

int WSAAPI __stdcall newselect(
  [in]      int           nfds,
  [in, out] fd_set        *readfds,
  [in, out] fd_set        *writefds,
  [in, out] fd_set        *exceptfds,
  [in]      const timeval *timeout
);
int WSAAPI __stdcall newsend(
  [in] SOCKET     s,
  [in] const char *buf,
  [in] int        len,
  [in] int        flags
);
int __stdcall newsendto(
  [in] SOCKET         s,
  [in] const char     *buf,
  [in] int            len,
  [in] int            flags,
  [in] const sockaddr *to,
  [in] int            tolen
);
INT WSAAPI __stdcall newSetAddrInfoExA(
  [in]            PCSTR                              pName,
  [in]            PCSTR                              pServiceName,
  [in, out]       SOCKET_ADDRESS                     *pAddresses,
  [in]            DWORD                              dwAddressCount,
  [in, optional]  LPBLOB                             lpBlob,
  [in]            DWORD                              dwFlags,
  [in]            DWORD                              dwNameSpace,
  [in, optional]  LPGUID                             lpNspId,
  [in, optional]  timeval                            *timeout,
  [in, optional]  LPOVERLAPPED                       lpOverlapped,
  [in, optional]  LPLOOKUPSERVICE_COMPLETION_ROUTINE lpCompletionRoutine,
  [out, optional] LPHANDLE                           lpNameHandle
);
int __stdcall newsetipv4sourcefilter(
  [in] SOCKET              Socket,
  [in] IN_ADDR             Interface,
  [in] IN_ADDR             Group,
  [in] MULTICAST_MODE_TYPE FilterMode,
  [in] ULONG               SourceCount,
  [in] const IN_ADDR       *SourceList
);
INT __stdcall newSetServiceA(
  [in]           DWORD                dwNameSpace,
  [in]           DWORD                dwOperation,
  [in]           DWORD                dwFlags,
  [in]           LPSERVICE_INFOA      lpServiceInfo,
  [in, optional] LPSERVICE_ASYNC_INFO lpServiceAsyncInfo,
  [out]          LPDWORD              lpdwStatusFlags
);
HRESULT __stdcall newSetSocketMediaStreamingMode(
  BOOL value
);
int __stdcall newsetsockopt(
  [in] SOCKET     s,
  [in] int        level,
  [in] int        optname,
  [in] const char *optval,
  [in] int        optlen
);
int __stdcall newsetsourcefilter(
  [in] SOCKET                 Socket,
  [in] ULONG                  Interface,
  [in] const SOCKADDR         *Group,
  [in] int                    GroupLength,
  [in] MULTICAST_MODE_TYPE    FilterMode,
  [in] ULONG                  SourceCount,
  [in] const SOCKADDR_STORAGE *SourceList
);
int __stdcall newshutdown(
  [in] SOCKET s,
  [in] int    how
);
SOCKET WSAAPI __stdcall newsocket(
  [in] int af,
  [in] int type,
  [in] int protocol
);
BOOL __stdcall newTransmitFile(
  SOCKET                  hSocket,
  HANDLE                  hFile,
  DWORD                   nNumberOfBytesToWrite,
  DWORD                   nNumberOfBytesPerSend,
  LPOVERLAPPED            lpOverlapped,
  LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,
  DWORD                   dwReserved
);

BOOL __stdcall newLpfnTransmitpackets(
  SOCKET hSocket,
  LPTRANSMIT_PACKETS_ELEMENT lpPacketArray,
  DWORD nElementCount,
  DWORD nSendSize,
  LPOVERLAPPED lpOverlapped,
  DWORD dwFlags
);

SOCKET WSAAPI __stdcall newWSAAccept(
  [in]      SOCKET          s,
  [out]     sockaddr        *addr,
  [in, out] LPINT           addrlen,
  [in]      LPCONDITIONPROC lpfnCondition,
  [in]      DWORD_PTR       dwCallbackData
);
INT WSAAPI __stdcall newWSAAddressToStringA(
  [in]           LPSOCKADDR          lpsaAddress,
  [in]           DWORD               dwAddressLength,
  [in, optional] LPWSAPROTOCOL_INFOA lpProtocolInfo,
  [in, out]      LPSTR               lpszAddressString,
  [in, out]      LPDWORD             lpdwAddressStringLength
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
  [in]  HWND       hWnd,
  [in]  u_int      wMsg,
  [in]  const char *name,
  [out] char       *buf,
  [out] int        buflen
);
HANDLE __stdcall newWSAAsyncGetProtoByNumber(
  [in]  HWND  hWnd,
  [in]  u_int wMsg,
  [in]  int   number,
  [out] char  *buf,
  [in]  int   buflen
);
HANDLE __stdcall newWSAAsyncGetServByName(
  [in]  HWND       hWnd,
  [in]  u_int      wMsg,
  [in]  const char *name,
  [in]  const char *proto,
  [out] char       *buf,
  [in]  int        buflen
);
HANDLE __stdcall newWSAAsyncGetServByPort(
  [in]  HWND       hWnd,
  [in]  u_int      wMsg,
  [in]  int        port,
  [in]  const char *proto,
  [out] char       *buf,
  [in]  int        buflen
);
int __stdcall newWSAAsyncSelect(
  [in] SOCKET s,
  [in] HWND   hWnd,
  [in] u_int  wMsg,
  [in] long   lEvent
);
int __stdcall newWSACancelAsyncRequest(
  [in] HANDLE hAsyncTaskHandle
);
int __stdcall newWSACleanup();
BOOL WSAAPI __stdcall newWSACloseEvent(
  [in] WSAEVENT hEvent
);
int WSAAPI __stdcall newWSAConnect(
  [in]  SOCKET         s,
  [in]  const sockaddr *name,
  [in]  int            namelen,
  [in]  LPWSABUF       lpCallerData,
  [out] LPWSABUF       lpCalleeData,
  [in]  LPQOS          lpSQOS,
  [in]  LPQOS          lpGQOS
);
BOOL __stdcall newWSAConnectByList(
  [in]      SOCKET               s,
  [in]      PSOCKET_ADDRESS_LIST SocketAddress,
  [in, out] LPDWORD              LocalAddressLength,
  [out]     LPSOCKADDR           LocalAddress,
  [in, out] LPDWORD              RemoteAddressLength,
  [out]     LPSOCKADDR           RemoteAddress,
  [in]      const timeval        *timeout,
  [in]      LPWSAOVERLAPPED      Reserved
);
BOOL __stdcall newWSAConnectByNameA(
  [in]      SOCKET          s,
  [in]      LPCSTR          nodename,
  [in]      LPCSTR          servicename,
  [in, out] LPDWORD         LocalAddressLength,
  [out]     LPSOCKADDR      LocalAddress,
  [in, out] LPDWORD         RemoteAddressLength,
  [out]     LPSOCKADDR      RemoteAddress,
  [in]      const timeval   *timeout,
            LPWSAOVERLAPPED Reserved
);
WSAEVENT WSAAPI __stdcall newWSACreateEvent();
INT WSAAPI __stdcall newWSADeleteSocketPeerTargetName(
  [in]           SOCKET                             Socket,
  [in]           const sockaddr                     *PeerAddr,
  [in]           ULONG                              PeerAddrLen,
  [in, optional] LPWSAOVERLAPPED                    Overlapped,
  [in, optional] LPWSAOVERLAPPED_COMPLETION_ROUTINE CompletionRoutine
);
int WSAAPI __stdcall newWSADuplicateSocketA(
  [in]  SOCKET              s,
  [in]  DWORD               dwProcessId,
  [out] LPWSAPROTOCOL_INFOA lpProtocolInfo
);
INT WSAAPI __stdcall newWSAEnumNameSpaceProvidersA(
  [in, out] LPDWORD              lpdwBufferLength,
  [out]     LPWSANAMESPACE_INFOA lpnspBuffer
);
INT WSAAPI __stdcall newWSAEnumNameSpaceProvidersExA(
  [in, out] LPDWORD                lpdwBufferLength,
  [out]     LPWSANAMESPACE_INFOEXA lpnspBuffer
);
int WSAAPI __stdcall newWSAEnumNetworkEvents(
  [in]  SOCKET             s,
  [in]  WSAEVENT           hEventObject,
  [out] LPWSANETWORKEVENTS lpNetworkEvents
);
int WSAAPI __stdcall newWSAEnumProtocolsA(
  [in]      LPINT               lpiProtocols,
  [out]     LPWSAPROTOCOL_INFOA lpProtocolBuffer,
  [in, out] LPDWORD             lpdwBufferLength
);
int WSAAPI __stdcall newWSAEventSelect(
  [in] SOCKET   s,
  [in] WSAEVENT hEventObject,
  [in] long     lNetworkEvents
);
int __stdcall new__WSAFDIsSet(
  SOCKET unnamedParam1,
  fd_set *unnamedParam2
);
INT __stdcall newWSAGetFailConnectOnIcmpError(
  [in]  SOCKET Socket,
  [out] DWORD  *Enabled
);
INT __stdcall newWSAGetIcmpErrorInfo(
  [in]  SOCKET          Socket,
  [out] ICMP_ERROR_INFO *Info
);
INT __stdcall newWSAGetIPUserMtu(
  [in]  SOCKET Socket,
  [out] DWORD  *Mtu
);
int __stdcall newWSAGetLastError();
BOOL WSAAPI __stdcall newWSAGetOverlappedResult(
  [in]  SOCKET          s,
  [in]  LPWSAOVERLAPPED lpOverlapped,
  [out] LPDWORD         lpcbTransfer,
  [in]  BOOL            fWait,
  [out] LPDWORD         lpdwFlags
);
BOOL WSAAPI __stdcall newWSAGetQOSByName(
  [in]      SOCKET   s,
  [in, out] LPWSABUF lpQOSName,
  [out]     LPQOS    lpQOS
);
INT WSAAPI __stdcall newWSAGetServiceClassInfoA(
  [in]      LPGUID                 lpProviderId,
  [in]      LPGUID                 lpServiceClassId,
  [in, out] LPDWORD                lpdwBufSize,
  [out]     LPWSASERVICECLASSINFOA lpServiceClassInfo
);
INT WSAAPI __stdcall newWSAGetServiceClassNameByClassIdA(
  [in]      LPGUID  lpServiceClassId,
  [out]     LPSTR   lpszServiceClassName,
  [in, out] LPDWORD lpdwBufferLength
);
INT __stdcall newWSAGetUdpRecvMaxCoalescedSize(
  [in]  SOCKET Socket,
  [out] DWORD  *MaxCoalescedMsgSize
);
INT __stdcall newWSAGetUdpSendMessageSize(
  [in]  SOCKET Socket,
  [out] DWORD  *MsgSize
);
int WSAAPI __stdcall newWSAHtonl(
  [in]  SOCKET s,
  [in]  u_long hostlong,
  [out] u_long *lpnetlong
);
int WSAAPI __stdcall newWSAHtons(
  [in]  SOCKET  s,
  [in]  u_short hostshort,
  [out] u_short *lpnetshort
);
INT WSAAPI __stdcall newWSAImpersonateSocketPeer(
  [in]           SOCKET         Socket,
  [in, optional] const sockaddr *PeerAddr,
  [in]           ULONG          PeerAddrLen
);
INT WSAAPI __stdcall newWSAInstallServiceClassA(
  [in] LPWSASERVICECLASSINFOA lpServiceClassInfo
);
int WSAAPI __stdcall newWSAIoctl(
  [in]  SOCKET                             s,
  [in]  DWORD                              dwIoControlCode,
  [in]  LPVOID                             lpvInBuffer,
  [in]  DWORD                              cbInBuffer,
  [out] LPVOID                             lpvOutBuffer,
  [in]  DWORD                              cbOutBuffer,
  [out] LPDWORD                            lpcbBytesReturned,
  [in]  LPWSAOVERLAPPED                    lpOverlapped,
  [in]  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
SOCKET WSAAPI __stdcall newWSAJoinLeaf(
  [in]  SOCKET         s,
  [in]  const sockaddr *name,
  [in]  int            namelen,
  [in]  LPWSABUF       lpCallerData,
  [out] LPWSABUF       lpCalleeData,
  [in]  LPQOS          lpSQOS,
  [in]  LPQOS          lpGQOS,
  [in]  DWORD          dwFlags
);
INT WSAAPI __stdcall newWSALookupServiceBeginA(
  [in]  LPWSAQUERYSETA lpqsRestrictions,
  [in]  DWORD          dwControlFlags,
  [out] LPHANDLE       lphLookup
);
INT WSAAPI __stdcall newWSALookupServiceEnd(
  [in] HANDLE hLookup
);
INT WSAAPI __stdcall newWSALookupServiceNextA(
  [in]      HANDLE         hLookup,
  [in]      DWORD          dwControlFlags,
  [in, out] LPDWORD        lpdwBufferLength,
  [out]     LPWSAQUERYSETA lpqsResults
);
INT WSAAPI __stdcall newWSANSPIoctl(
  [in]      HANDLE          hLookup,
  [in]      DWORD           dwControlCode,
  [in]      LPVOID          lpvInBuffer,
  [in, out] DWORD           cbInBuffer,
  [out]     LPVOID          lpvOutBuffer,
  [in]      DWORD           cbOutBuffer,
  [out]     LPDWORD         lpcbBytesReturned,
  [in]      LPWSACOMPLETION lpCompletion
);
int WSAAPI __stdcall newWSANtohl(
  [in]  SOCKET s,
  [in]  u_long netlong,
  [out] u_long *lphostlong
);
int WSAAPI __stdcall newWSANtohs(
  [in]  SOCKET  s,
  [in]  u_short netshort,
  [out] u_short *lphostshort
);
int WSAAPI __stdcall newWSAPoll(
  [in, out] LPWSAPOLLFD fdArray,
  [in]      ULONG       fds,
  [in]      INT         timeout
);
INT WSAAPI __stdcall newWSAProviderConfigChange(
  [in, out] LPHANDLE                           lpNotificationHandle,
  [in]      LPWSAOVERLAPPED                    lpOverlapped,
  [in]      LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSARecv(
  [in]      SOCKET                             s,
  [in, out] LPWSABUF                           lpBuffers,
  [in]      DWORD                              dwBufferCount,
  [out]     LPDWORD                            lpNumberOfBytesRecvd,
  [in, out] LPDWORD                            lpFlags,
  [in]      LPWSAOVERLAPPED                    lpOverlapped,
  [in]      LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSARecvDisconnect(
  [in]  SOCKET   s,
  [out] LPWSABUF lpInboundDisconnectData
);
int __stdcall newWSARecvEx(
  [in]      SOCKET s,
  [out]     char   *buf,
  [in]      int    len,
  [in, out] int    *flags
);
int WSAAPI __stdcall newWSARecvFrom(
  [in]      SOCKET                             s,
  [in, out] LPWSABUF                           lpBuffers,
  [in]      DWORD                              dwBufferCount,
  [out]     LPDWORD                            lpNumberOfBytesRecvd,
  [in, out] LPDWORD                            lpFlags,
  [out]     sockaddr                           *lpFrom,
  [in, out] LPINT                              lpFromlen,
  [in]      LPWSAOVERLAPPED                    lpOverlapped,
  [in]      LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
INT WSAAPI __stdcall newWSARemoveServiceClass(
  [in] LPGUID lpServiceClassId
);
BOOL WSAAPI __stdcall newWSAResetEvent(
  [in] WSAEVENT hEvent
);
INT WSAAPI __stdcall newWSARevertImpersonation();
int WSAAPI __stdcall newWSASend(
  [in]  SOCKET                             s,
  [in]  LPWSABUF                           lpBuffers,
  [in]  DWORD                              dwBufferCount,
  [out] LPDWORD                            lpNumberOfBytesSent,
  [in]  DWORD                              dwFlags,
  [in]  LPWSAOVERLAPPED                    lpOverlapped,
  [in]  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSASendDisconnect(
  [in] SOCKET   s,
  [in] LPWSABUF lpOutboundDisconnectData
);
int WSAAPI __stdcall newWSASendMsg(
  [in]  SOCKET                             Handle,
  [in]  LPWSAMSG                           lpMsg,
  [in]  DWORD                              dwFlags,
  [out] LPDWORD                            lpNumberOfBytesSent,
  [in]  LPWSAOVERLAPPED                    lpOverlapped,
  [in]  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
int WSAAPI __stdcall newWSASendTo(
  [in]  SOCKET                             s,
  [in]  LPWSABUF                           lpBuffers,
  [in]  DWORD                              dwBufferCount,
  [out] LPDWORD                            lpNumberOfBytesSent,
  [in]  DWORD                              dwFlags,
  [in]  const sockaddr                     *lpTo,
  [in]  int                                iTolen,
  [in]  LPWSAOVERLAPPED                    lpOverlapped,
  [in]  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
BOOL WSAAPI __stdcall newWSASetEvent(
  [in] WSAEVENT hEvent
);
INT __stdcall newWSASetFailConnectOnIcmpError(
  [in] SOCKET Socket,
  [in] DWORD  Enabled
);
INT __stdcall newWSASetIPUserMtu(
  [in] SOCKET Socket,
  [in] DWORD  Mtu
);
void __stdcall newWSASetLastError(
  [in] int iError
);
INT WSAAPI __stdcall newWSASetServiceA(
  [in] LPWSAQUERYSETA   lpqsRegInfo,
  [in] WSAESETSERVICEOP essoperation,
  [in] DWORD            dwControlFlags
);
INT __stdcall newWSASetUdpRecvMaxCoalescedSize(
  [in] SOCKET Socket,
  [in] DWORD  MaxCoalescedMsgSize
);
INT __stdcall newWSASetUdpSendMessageSize(
  [in] SOCKET Socket,
  [in] DWORD  MsgSize
);
SOCKET WSAAPI __stdcall newWSASocketA(
  [in] int                 af,
  [in] int                 type,
  [in] int                 protocol,
  [in] LPWSAPROTOCOL_INFOA lpProtocolInfo,
  [in] GROUP               g,
  [in] DWORD               dwFlags
);
int __stdcall newWSAStartup(
        WORD      wVersionRequired,
  [out] LPWSADATA lpWSAData
);
INT WSAAPI __stdcall newWSAStringToAddressA(
  [in]           LPSTR               AddressString,
  [in]           INT                 AddressFamily,
  [in, optional] LPWSAPROTOCOL_INFOA lpProtocolInfo,
  [out]          LPSOCKADDR          lpAddress,
  [in, out]      LPINT               lpAddressLength
);
DWORD WSAAPI __stdcall newWSAWaitForMultipleEvents(
  [in] DWORD          cEvents,
  [in] const WSAEVENT *lphEvents,
  [in] BOOL           fWaitAll,
  [in] DWORD          dwTimeout,
  [in] BOOL           fAlertable
);
}