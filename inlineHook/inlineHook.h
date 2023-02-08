#pragma once
#ifdef DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

#include <vector>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include "codeGeneratedFunctionsFileSystem.h"
#include "codeGeneratedFunctionsRegistry.h"
#include "codeGeneratedFunctionsSockets.h"

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;


extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

void mylog(char* buf, int size);
void mylog1(const char* buf, int size);

class Hook {
public:
	enum class Functions {
    AddUsersToEncryptedFile,
AreFileApisANSI,
CheckNameLegalDOS8Dot3A,
CloseEncryptedFileRaw,
CopyFile,
CopyFile2,
CopyFileExA,
CopyFileTransactedA,
CreateFileA,
CreateFile2,
CreateFileTransactedA,
CreateHardLinkA,
CreateHardLinkTransactedA,
CreateSymbolicLinkA,
CreateSymbolicLinkTransactedA,
DecryptFileA,
DeleteFileA,
DeleteFileTransactedA,
DuplicateEncryptionInfoFile,
EncryptFileA,
EncryptionDisable,
FileEncryptionStatusA,
FindClose,
FindFirstFileA,
FindFirstFileExA,
FindFirstFileNameTransactedW,
FindFirstFileNameW,
FindFirstFileTransactedA,
FindFirstStreamTransactedW,
FindFirstStreamW,
FindNextFileA,
FindNextFileNameW,
FindNextStreamW,
FlushFileBuffers,
FreeEncryptionCertificateHashList,
GetBinaryTypeA,
GetCompressedFileSizeA,
GetCompressedFileSizeTransactedA,
GetExpandedNameA,
GetFileAttributesA,
GetFileAttributesExA,
GetFileAttributesTransactedA,
GetFileBandwidthReservation,
GetFileInformationByHandle,
GetFileInformationByHandleEx,
GetFileSize,
GetFileSizeEx,
GetFileType,
GetFinalPathNameByHandleA,
GetFullPathNameA,
GetFullPathNameTransactedA,
GetLongPathNameA,
GetLongPathNameTransactedA,
GetQueuedCompletionStatus,
GetShortPathNameW,
GetTempFileNameA,
GetTempPathA,
LockFile,
LockFileEx,
LZClose,
LZCopy,
LZInit,
LZOpenFileA,
LZRead,
LZSeek,
MoveFile,
MoveFileExA,
MoveFileTransactedA,
MoveFileWithProgressA,
OpenEncryptedFileRawA,
OpenFile,
OpenFileById,
QueryRecoveryAgentsOnEncryptedFile,
QueryUsersOnEncryptedFile,
ReadEncryptedFileRaw,
ReadFile,
ReadFileEx,
RemoveUsersFromEncryptedFile,
ReOpenFile,
ReplaceFileA,
SearchPathA,
SetEndOfFile,
SetFileApisToANSI,
SetFileApisToOEM,
SetFileAttributesA,
SetFileAttributesTransactedA,
SetFileBandwidthReservation,
SetFileCompletionNotificationModes,
SetFileInformationByHandle,
SetFileIoOverlappedRange,
SetFilePointer,
SetFilePointerEx,
SetFileShortNameA,
SetFileValidData,
SetSearchPathMode,
SetUserFileEncryptionKey,
UnlockFile,
UnlockFileEx,
Wofenumfilesproc,
WofGetDriverVersion,
WofIsExternalFile,
WofSetFileDataLocation,
WofShouldCompressBinaries,
WofWimAddEntry,
WofWimRemoveEntry,
WofWimSuspendEntry,
WofWimUpdateEntry,
Wow64DisableWow64FsRedirection,
Wow64EnableWow64FsRedirection,
Wow64RevertWow64FsRedirection,
WriteEncryptedFileRaw,
WriteFile,
WriteFileEx,
accept,
AcceptEx,
bind,
closesocket,
connect,
LpfnConnectex,
DisconnectEx,
EnumProtocolsA,
freeaddrinfo,
FreeAddrInfoEx,
FreeAddrInfoW,
gai_strerrorA,
GetAcceptExSockaddrs,
GetAddressByNameA,
getaddrinfo,
GetAddrInfoExA,
GetAddrInfoExCancel,
GetAddrInfoExOverlappedResult,
GetAddrInfoW,
gethostname,
GetHostNameW,
getipv4sourcefilter,
GetNameByTypeA,
getnameinfo,
GetNameInfoW,
getpeername,
getprotobyname,
getprotobynumber,
getservbyname,
getservbyport,
GetServiceA,
getsockname,
getsockopt,
getsourcefilter,
GetTypeByNameA,
htons,
inet_addr,
inet_ntoa,
InetNtopW,
InetPtonW,
ioctlsocket,
listen,
ntohd,
ntohf,
ntohl,
ntohs,
recv,
recvfrom,
select,
send,
sendto,
SetAddrInfoExA,
setipv4sourcefilter,
SetServiceA,
SetSocketMediaStreamingMode,
setsockopt,
setsourcefilter,
shutdown,
socket,
TransmitFile,
LpfnTransmitpackets,
WSAAccept,
WSAAddressToStringA,
WSAAsyncGetHostByAddr,
WSAAsyncGetHostByName,
WSAAsyncGetProtoByName,
WSAAsyncGetProtoByNumber,
WSAAsyncGetServByName,
WSAAsyncGetServByPort,
WSAAsyncSelect,
WSACancelAsyncRequest,
WSACleanup,
WSACloseEvent,
WSAConnect,
WSAConnectByList,
WSAConnectByNameA,
WSACreateEvent,
WSADeleteSocketPeerTargetName,
WSADuplicateSocketA,
WSAEnumNameSpaceProvidersA,
WSAEnumNameSpaceProvidersExA,
WSAEnumNetworkEvents,
WSAEnumProtocolsA,
WSAEventSelect,
__WSAFDIsSet,
WSAGetFailConnectOnIcmpError,
WSAGetIcmpErrorInfo,
WSAGetIPUserMtu,
WSAGetLastError,
WSAGetOverlappedResult,
WSAGetQOSByName,
WSAGetServiceClassInfoA,
WSAGetServiceClassNameByClassIdA,
WSAGetUdpRecvMaxCoalescedSize,
WSAGetUdpSendMessageSize,
WSAHtonl,
WSAHtons,
WSAImpersonateSocketPeer,
WSAInstallServiceClassA,
WSAIoctl,
WSAJoinLeaf,
WSALookupServiceBeginA,
WSALookupServiceEnd,
WSALookupServiceNextA,
WSANSPIoctl,
WSANtohl,
WSANtohs,
WSAPoll,
WSAProviderConfigChange,
WSARecv,
WSARecvDisconnect,
WSARecvEx,
WSARecvFrom,
WSARemoveServiceClass,
WSAResetEvent,
WSARevertImpersonation,
WSASend,
WSASendDisconnect,
WSASendMsg,
WSASendTo,
WSASetEvent,
WSASetFailConnectOnIcmpError,
WSASetIPUserMtu,
WSASetLastError,
WSASetServiceA,
WSASetUdpRecvMaxCoalescedSize,
WSASetUdpSendMessageSize,
WSASocketA,
WSAStartup,
WSAStringToAddressA,
WSAWaitForMultipleEvents,
GetSystemRegistryQuota,
RegCloseKey,
RegConnectRegistryA,
RegCopyTreeA,
RegCreateKeyExA,
RegCreateKeyTransactedA,
RegDeleteKeyA,
RegDeleteKeyExA,
RegDeleteKeyTransactedA,
RegDeleteKeyValueA,
RegDeleteTreeA,
RegDeleteValueA,
RegDisablePredefinedCache,
RegDisablePredefinedCacheEx,
RegDisableReflectionKey,
RegEnableReflectionKey,
RegEnumKeyExA,
RegEnumValueA,
RegFlushKey,
RegGetKeySecurity,
RegGetValueA,
RegLoadKeyA,
RegLoadMUIStringA,
RegNotifyChangeKeyValue,
RegOpenCurrentUser,
RegOpenKeyExA,
RegOpenKeyTransactedA,
RegOpenUserClassesRoot,
RegOverridePredefKey,
RegQueryInfoKeyA,
RegQueryMultipleValuesA,
RegQueryReflectionKey,
RegQueryValueExA,
RegRenameKey,
RegReplaceKeyA,
RegRestoreKeyA,
RegSaveKeyA,
RegSaveKeyExA,
RegSetKeyValueA,
RegSetKeySecurity,
RegSetValueExA,
RegUnLoadKeyA,
GetPrivateProfileInt,
GetPrivateProfileSection,
GetPrivateProfileSectionNames,
GetPrivateProfileString,
GetPrivateProfileStruct,
GetProfileIntA,
GetProfileSectionA,
GetProfileStringA,
WritePrivateProfileSectionA,
WritePrivateProfileStringA,
WritePrivateProfileStructA,
WriteProfileSectionA,
WriteProfileStringA,
max_functions_number
    };

	static void set_up_vars() {
		HINSTANCE* hLib{ &hLibFiles };
		for (int i{ 0 }; i < (int)Functions::max_functions_number; ++i) {
			if (i == (int)Functions::send) {
				hLib = &hLibSock;
			}
			if (i == (int)Functions::RegCreateKeyExA) {
				hLib = &hLibReg;
			}
			CHAR* tmp_og_bytes = new char[6];
			FARPROC tmp_hooked_addr{};
			tmp_hooked_addr = GetProcAddress(*hLib, get_new_func_name(Functions(i)).c_str());
			ReadProcessMemory(GetCurrentProcess(), (LPCVOID)tmp_hooked_addr, tmp_og_bytes, 6, NULL);
			original_bytes.push_back(tmp_og_bytes);
			hooked_addr.push_back(tmp_hooked_addr);
		}

		if (!DeleteFileA("..\\log.txt")) {
			std::cout << "couldn't delete log.txt\n";
		}
		time(&begin);

	}

	Functions func_to_hook{};


	void deploy_hook() {
		VOID* myFncAdrr;
		CHAR patch[6] = { 0 };
		myFncAdrr = get_new_fnc_pointer();
		memcpy_s(patch, 1, "\x68", 1);
		memcpy_s(patch + 1, 4, &myFncAdrr, 4);
		memcpy_s(patch + 5, 1, "\xC3", 1);

		WriteProcessMemory(GetCurrentProcess(), (LPVOID)hooked_addr[(int)func_to_hook], patch, 6, NULL);
	}


	Hook(Functions func) : func_to_hook{ func } {}

private:

	static std::string get_new_func_name(Functions func) {
		switch (func) {
    		case Functions::AddUsersToEncryptedFile: return "AddUsersToEncryptedFile";break;
			case Functions::AreFileApisANSI: return "AreFileApisANSI";break;
			case Functions::CheckNameLegalDOS8Dot3A: return "CheckNameLegalDOS8Dot3A";break;
			case Functions::CloseEncryptedFileRaw: return "CloseEncryptedFileRaw";break;
			case Functions::CopyFile: return "CopyFile";break;
			case Functions::CopyFile2: return "CopyFile2";break;
			case Functions::CopyFileExA: return "CopyFileExA";break;
			case Functions::CopyFileTransactedA: return "CopyFileTransactedA";break;
			case Functions::CreateFileA: return "CreateFileA";break;
			case Functions::CreateFile2: return "CreateFile2";break;
			case Functions::CreateFileTransactedA: return "CreateFileTransactedA";break;
			case Functions::CreateHardLinkA: return "CreateHardLinkA";break;
			case Functions::CreateHardLinkTransactedA: return "CreateHardLinkTransactedA";break;
			case Functions::CreateSymbolicLinkA: return "CreateSymbolicLinkA";break;
			case Functions::CreateSymbolicLinkTransactedA: return "CreateSymbolicLinkTransactedA";break;
			case Functions::DecryptFileA: return "DecryptFileA";break;
			case Functions::DeleteFileA: return "DeleteFileA";break;
			case Functions::DeleteFileTransactedA: return "DeleteFileTransactedA";break;
			case Functions::DuplicateEncryptionInfoFile: return "DuplicateEncryptionInfoFile";break;
			case Functions::EncryptFileA: return "EncryptFileA";break;
			case Functions::EncryptionDisable: return "EncryptionDisable";break;
			case Functions::FileEncryptionStatusA: return "FileEncryptionStatusA";break;
			case Functions::FindClose: return "FindClose";break;
			case Functions::FindFirstFileA: return "FindFirstFileA";break;
			case Functions::FindFirstFileExA: return "FindFirstFileExA";break;
			case Functions::FindFirstFileNameTransactedW: return "FindFirstFileNameTransactedW";break;
			case Functions::FindFirstFileNameW: return "FindFirstFileNameW";break;
			case Functions::FindFirstFileTransactedA: return "FindFirstFileTransactedA";break;
			case Functions::FindFirstStreamTransactedW: return "FindFirstStreamTransactedW";break;
			case Functions::FindFirstStreamW: return "FindFirstStreamW";break;
			case Functions::FindNextFileA: return "FindNextFileA";break;
			case Functions::FindNextFileNameW: return "FindNextFileNameW";break;
			case Functions::FindNextStreamW: return "FindNextStreamW";break;
			case Functions::FlushFileBuffers: return "FlushFileBuffers";break;
			case Functions::FreeEncryptionCertificateHashList: return "FreeEncryptionCertificateHashList";break;
			case Functions::GetBinaryTypeA: return "GetBinaryTypeA";break;
			case Functions::GetCompressedFileSizeA: return "GetCompressedFileSizeA";break;
			case Functions::GetCompressedFileSizeTransactedA: return "GetCompressedFileSizeTransactedA";break;
			case Functions::GetExpandedNameA: return "GetExpandedNameA";break;
			case Functions::GetFileAttributesA: return "GetFileAttributesA";break;
			case Functions::GetFileAttributesExA: return "GetFileAttributesExA";break;
			case Functions::GetFileAttributesTransactedA: return "GetFileAttributesTransactedA";break;
			case Functions::GetFileBandwidthReservation: return "GetFileBandwidthReservation";break;
			case Functions::GetFileInformationByHandle: return "GetFileInformationByHandle";break;
			case Functions::GetFileInformationByHandleEx: return "GetFileInformationByHandleEx";break;
			case Functions::GetFileSize: return "GetFileSize";break;
			case Functions::GetFileSizeEx: return "GetFileSizeEx";break;
			case Functions::GetFileType: return "GetFileType";break;
			case Functions::GetFinalPathNameByHandleA: return "GetFinalPathNameByHandleA";break;
			case Functions::GetFullPathNameA: return "GetFullPathNameA";break;
			case Functions::GetFullPathNameTransactedA: return "GetFullPathNameTransactedA";break;
			case Functions::GetLongPathNameA: return "GetLongPathNameA";break;
			case Functions::GetLongPathNameTransactedA: return "GetLongPathNameTransactedA";break;
			case Functions::GetQueuedCompletionStatus: return "GetQueuedCompletionStatus";break;
			case Functions::GetShortPathNameW: return "GetShortPathNameW";break;
			case Functions::GetTempFileNameA: return "GetTempFileNameA";break;
			case Functions::GetTempPathA: return "GetTempPathA";break;
			case Functions::LockFile: return "LockFile";break;
			case Functions::LockFileEx: return "LockFileEx";break;
			case Functions::LZClose: return "LZClose";break;
			case Functions::LZCopy: return "LZCopy";break;
			case Functions::LZInit: return "LZInit";break;
			case Functions::LZOpenFileA: return "LZOpenFileA";break;
			case Functions::LZRead: return "LZRead";break;
			case Functions::LZSeek: return "LZSeek";break;
			case Functions::MoveFile: return "MoveFile";break;
			case Functions::MoveFileExA: return "MoveFileExA";break;
			case Functions::MoveFileTransactedA: return "MoveFileTransactedA";break;
			case Functions::MoveFileWithProgressA: return "MoveFileWithProgressA";break;
			case Functions::OpenEncryptedFileRawA: return "OpenEncryptedFileRawA";break;
			case Functions::OpenFile: return "OpenFile";break;
			case Functions::OpenFileById: return "OpenFileById";break;
			case Functions::QueryRecoveryAgentsOnEncryptedFile: return "QueryRecoveryAgentsOnEncryptedFile";break;
			case Functions::QueryUsersOnEncryptedFile: return "QueryUsersOnEncryptedFile";break;
			case Functions::ReadEncryptedFileRaw: return "ReadEncryptedFileRaw";break;
			case Functions::ReadFile: return "ReadFile";break;
			case Functions::ReadFileEx: return "ReadFileEx";break;
			case Functions::RemoveUsersFromEncryptedFile: return "RemoveUsersFromEncryptedFile";break;
			case Functions::ReOpenFile: return "ReOpenFile";break;
			case Functions::ReplaceFileA: return "ReplaceFileA";break;
			case Functions::SearchPathA: return "SearchPathA";break;
			case Functions::SetEndOfFile: return "SetEndOfFile";break;
			case Functions::SetFileApisToANSI: return "SetFileApisToANSI";break;
			case Functions::SetFileApisToOEM: return "SetFileApisToOEM";break;
			case Functions::SetFileAttributesA: return "SetFileAttributesA";break;
			case Functions::SetFileAttributesTransactedA: return "SetFileAttributesTransactedA";break;
			case Functions::SetFileBandwidthReservation: return "SetFileBandwidthReservation";break;
			case Functions::SetFileCompletionNotificationModes: return "SetFileCompletionNotificationModes";break;
			case Functions::SetFileInformationByHandle: return "SetFileInformationByHandle";break;
			case Functions::SetFileIoOverlappedRange: return "SetFileIoOverlappedRange";break;
			case Functions::SetFilePointer: return "SetFilePointer";break;
			case Functions::SetFilePointerEx: return "SetFilePointerEx";break;
			case Functions::SetFileShortNameA: return "SetFileShortNameA";break;
			case Functions::SetFileValidData: return "SetFileValidData";break;
			case Functions::SetSearchPathMode: return "SetSearchPathMode";break;
			case Functions::SetUserFileEncryptionKey: return "SetUserFileEncryptionKey";break;
			case Functions::UnlockFile: return "UnlockFile";break;
			case Functions::UnlockFileEx: return "UnlockFileEx";break;
			case Functions::Wofenumfilesproc: return "Wofenumfilesproc";break;
			case Functions::WofGetDriverVersion: return "WofGetDriverVersion";break;
			case Functions::WofIsExternalFile: return "WofIsExternalFile";break;
			case Functions::WofSetFileDataLocation: return "WofSetFileDataLocation";break;
			case Functions::WofShouldCompressBinaries: return "WofShouldCompressBinaries";break;
			case Functions::WofWimAddEntry: return "WofWimAddEntry";break;
			case Functions::WofWimRemoveEntry: return "WofWimRemoveEntry";break;
			case Functions::WofWimSuspendEntry: return "WofWimSuspendEntry";break;
			case Functions::WofWimUpdateEntry: return "WofWimUpdateEntry";break;
			case Functions::Wow64DisableWow64FsRedirection: return "Wow64DisableWow64FsRedirection";break;
			case Functions::Wow64EnableWow64FsRedirection: return "Wow64EnableWow64FsRedirection";break;
			case Functions::Wow64RevertWow64FsRedirection: return "Wow64RevertWow64FsRedirection";break;
			case Functions::WriteEncryptedFileRaw: return "WriteEncryptedFileRaw";break;
			case Functions::WriteFile: return "WriteFile";break;
			case Functions::WriteFileEx: return "WriteFileEx";break;
			case Functions::accept: return "accept";break;
			case Functions::AcceptEx: return "AcceptEx";break;
			case Functions::bind: return "bind";break;
			case Functions::closesocket: return "closesocket";break;
			case Functions::connect: return "connect";break;
			case Functions::LpfnConnectex: return "LpfnConnectex";break;
			case Functions::DisconnectEx: return "DisconnectEx";break;
			case Functions::EnumProtocolsA: return "EnumProtocolsA";break;
			case Functions::freeaddrinfo: return "freeaddrinfo";break;
			case Functions::FreeAddrInfoEx: return "FreeAddrInfoEx";break;
			case Functions::FreeAddrInfoW: return "FreeAddrInfoW";break;
			case Functions::gai_strerrorA: return "gai_strerrorA";break;
			case Functions::GetAcceptExSockaddrs: return "GetAcceptExSockaddrs";break;
			case Functions::GetAddressByNameA: return "GetAddressByNameA";break;
			case Functions::getaddrinfo: return "getaddrinfo";break;
			case Functions::GetAddrInfoExA: return "GetAddrInfoExA";break;
			case Functions::GetAddrInfoExCancel: return "GetAddrInfoExCancel";break;
			case Functions::GetAddrInfoExOverlappedResult: return "GetAddrInfoExOverlappedResult";break;
			case Functions::GetAddrInfoW: return "GetAddrInfoW";break;
			case Functions::gethostname: return "gethostname";break;
			case Functions::GetHostNameW: return "GetHostNameW";break;
			case Functions::getipv4sourcefilter: return "getipv4sourcefilter";break;
			case Functions::GetNameByTypeA: return "GetNameByTypeA";break;
			case Functions::getnameinfo: return "getnameinfo";break;
			case Functions::GetNameInfoW: return "GetNameInfoW";break;
			case Functions::getpeername: return "getpeername";break;
			case Functions::getprotobyname: return "getprotobyname";break;
			case Functions::getprotobynumber: return "getprotobynumber";break;
			case Functions::getservbyname: return "getservbyname";break;
			case Functions::getservbyport: return "getservbyport";break;
			case Functions::GetServiceA: return "GetServiceA";break;
			case Functions::getsockname: return "getsockname";break;
			case Functions::getsockopt: return "getsockopt";break;
			case Functions::getsourcefilter: return "getsourcefilter";break;
			case Functions::GetTypeByNameA: return "GetTypeByNameA";break;
			case Functions::htons: return "htons";break;
			case Functions::inet_addr: return "inet_addr";break;
			case Functions::inet_ntoa: return "inet_ntoa";break;
			case Functions::InetNtopW: return "InetNtopW";break;
			case Functions::InetPtonW: return "InetPtonW";break;
			case Functions::ioctlsocket: return "ioctlsocket";break;
			case Functions::listen: return "listen";break;
			case Functions::ntohd: return "ntohd";break;
			case Functions::ntohf: return "ntohf";break;
			case Functions::ntohl: return "ntohl";break;
			case Functions::ntohs: return "ntohs";break;
			case Functions::recv: return "recv";break;
			case Functions::recvfrom: return "recvfrom";break;
			case Functions::select: return "select";break;
			case Functions::send: return "send";break;
			case Functions::sendto: return "sendto";break;
			case Functions::SetAddrInfoExA: return "SetAddrInfoExA";break;
			case Functions::setipv4sourcefilter: return "setipv4sourcefilter";break;
			case Functions::SetServiceA: return "SetServiceA";break;
			case Functions::SetSocketMediaStreamingMode: return "SetSocketMediaStreamingMode";break;
			case Functions::setsockopt: return "setsockopt";break;
			case Functions::setsourcefilter: return "setsourcefilter";break;
			case Functions::shutdown: return "shutdown";break;
			case Functions::socket: return "socket";break;
			case Functions::TransmitFile: return "TransmitFile";break;
			case Functions::LpfnTransmitpackets: return "LpfnTransmitpackets";break;
			case Functions::WSAAccept: return "WSAAccept";break;
			case Functions::WSAAddressToStringA: return "WSAAddressToStringA";break;
			case Functions::WSAAsyncGetHostByAddr: return "WSAAsyncGetHostByAddr";break;
			case Functions::WSAAsyncGetHostByName: return "WSAAsyncGetHostByName";break;
			case Functions::WSAAsyncGetProtoByName: return "WSAAsyncGetProtoByName";break;
			case Functions::WSAAsyncGetProtoByNumber: return "WSAAsyncGetProtoByNumber";break;
			case Functions::WSAAsyncGetServByName: return "WSAAsyncGetServByName";break;
			case Functions::WSAAsyncGetServByPort: return "WSAAsyncGetServByPort";break;
			case Functions::WSAAsyncSelect: return "WSAAsyncSelect";break;
			case Functions::WSACancelAsyncRequest: return "WSACancelAsyncRequest";break;
			case Functions::WSACleanup: return "WSACleanup";break;
			case Functions::WSACloseEvent: return "WSACloseEvent";break;
			case Functions::WSAConnect: return "WSAConnect";break;
			case Functions::WSAConnectByList: return "WSAConnectByList";break;
			case Functions::WSAConnectByNameA: return "WSAConnectByNameA";break;
			case Functions::WSACreateEvent: return "WSACreateEvent";break;
			case Functions::WSADeleteSocketPeerTargetName: return "WSADeleteSocketPeerTargetName";break;
			case Functions::WSADuplicateSocketA: return "WSADuplicateSocketA";break;
			case Functions::WSAEnumNameSpaceProvidersA: return "WSAEnumNameSpaceProvidersA";break;
			case Functions::WSAEnumNameSpaceProvidersExA: return "WSAEnumNameSpaceProvidersExA";break;
			case Functions::WSAEnumNetworkEvents: return "WSAEnumNetworkEvents";break;
			case Functions::WSAEnumProtocolsA: return "WSAEnumProtocolsA";break;
			case Functions::WSAEventSelect: return "WSAEventSelect";break;
			case Functions::__WSAFDIsSet: return "__WSAFDIsSet";break;
			case Functions::WSAGetFailConnectOnIcmpError: return "WSAGetFailConnectOnIcmpError";break;
			case Functions::WSAGetIcmpErrorInfo: return "WSAGetIcmpErrorInfo";break;
			case Functions::WSAGetIPUserMtu: return "WSAGetIPUserMtu";break;
			case Functions::WSAGetLastError: return "WSAGetLastError";break;
			case Functions::WSAGetOverlappedResult: return "WSAGetOverlappedResult";break;
			case Functions::WSAGetQOSByName: return "WSAGetQOSByName";break;
			case Functions::WSAGetServiceClassInfoA: return "WSAGetServiceClassInfoA";break;
			case Functions::WSAGetServiceClassNameByClassIdA: return "WSAGetServiceClassNameByClassIdA";break;
			case Functions::WSAGetUdpRecvMaxCoalescedSize: return "WSAGetUdpRecvMaxCoalescedSize";break;
			case Functions::WSAGetUdpSendMessageSize: return "WSAGetUdpSendMessageSize";break;
			case Functions::WSAHtonl: return "WSAHtonl";break;
			case Functions::WSAHtons: return "WSAHtons";break;
			case Functions::WSAImpersonateSocketPeer: return "WSAImpersonateSocketPeer";break;
			case Functions::WSAInstallServiceClassA: return "WSAInstallServiceClassA";break;
			case Functions::WSAIoctl: return "WSAIoctl";break;
			case Functions::WSAJoinLeaf: return "WSAJoinLeaf";break;
			case Functions::WSALookupServiceBeginA: return "WSALookupServiceBeginA";break;
			case Functions::WSALookupServiceEnd: return "WSALookupServiceEnd";break;
			case Functions::WSALookupServiceNextA: return "WSALookupServiceNextA";break;
			case Functions::WSANSPIoctl: return "WSANSPIoctl";break;
			case Functions::WSANtohl: return "WSANtohl";break;
			case Functions::WSANtohs: return "WSANtohs";break;
			case Functions::WSAPoll: return "WSAPoll";break;
			case Functions::WSAProviderConfigChange: return "WSAProviderConfigChange";break;
			case Functions::WSARecv: return "WSARecv";break;
			case Functions::WSARecvDisconnect: return "WSARecvDisconnect";break;
			case Functions::WSARecvEx: return "WSARecvEx";break;
			case Functions::WSARecvFrom: return "WSARecvFrom";break;
			case Functions::WSARemoveServiceClass: return "WSARemoveServiceClass";break;
			case Functions::WSAResetEvent: return "WSAResetEvent";break;
			case Functions::WSARevertImpersonation: return "WSARevertImpersonation";break;
			case Functions::WSASend: return "WSASend";break;
			case Functions::WSASendDisconnect: return "WSASendDisconnect";break;
			case Functions::WSASendMsg: return "WSASendMsg";break;
			case Functions::WSASendTo: return "WSASendTo";break;
			case Functions::WSASetEvent: return "WSASetEvent";break;
			case Functions::WSASetFailConnectOnIcmpError: return "WSASetFailConnectOnIcmpError";break;
			case Functions::WSASetIPUserMtu: return "WSASetIPUserMtu";break;
			case Functions::WSASetLastError: return "WSASetLastError";break;
			case Functions::WSASetServiceA: return "WSASetServiceA";break;
			case Functions::WSASetUdpRecvMaxCoalescedSize: return "WSASetUdpRecvMaxCoalescedSize";break;
			case Functions::WSASetUdpSendMessageSize: return "WSASetUdpSendMessageSize";break;
			case Functions::WSASocketA: return "WSASocketA";break;
			case Functions::WSAStartup: return "WSAStartup";break;
			case Functions::WSAStringToAddressA: return "WSAStringToAddressA";break;
			case Functions::WSAWaitForMultipleEvents: return "WSAWaitForMultipleEvents";break;
			case Functions::GetSystemRegistryQuota: return "GetSystemRegistryQuota";break;
			case Functions::RegCloseKey: return "RegCloseKey";break;
			case Functions::RegConnectRegistryA: return "RegConnectRegistryA";break;
			case Functions::RegCopyTreeA: return "RegCopyTreeA";break;
			case Functions::RegCreateKeyExA: return "RegCreateKeyExA";break;
			case Functions::RegCreateKeyTransactedA: return "RegCreateKeyTransactedA";break;
			case Functions::RegDeleteKeyA: return "RegDeleteKeyA";break;
			case Functions::RegDeleteKeyExA: return "RegDeleteKeyExA";break;
			case Functions::RegDeleteKeyTransactedA: return "RegDeleteKeyTransactedA";break;
			case Functions::RegDeleteKeyValueA: return "RegDeleteKeyValueA";break;
			case Functions::RegDeleteTreeA: return "RegDeleteTreeA";break;
			case Functions::RegDeleteValueA: return "RegDeleteValueA";break;
			case Functions::RegDisablePredefinedCache: return "RegDisablePredefinedCache";break;
			case Functions::RegDisablePredefinedCacheEx: return "RegDisablePredefinedCacheEx";break;
			case Functions::RegDisableReflectionKey: return "RegDisableReflectionKey";break;
			case Functions::RegEnableReflectionKey: return "RegEnableReflectionKey";break;
			case Functions::RegEnumKeyExA: return "RegEnumKeyExA";break;
			case Functions::RegEnumValueA: return "RegEnumValueA";break;
			case Functions::RegFlushKey: return "RegFlushKey";break;
			case Functions::RegGetKeySecurity: return "RegGetKeySecurity";break;
			case Functions::RegGetValueA: return "RegGetValueA";break;
			case Functions::RegLoadKeyA: return "RegLoadKeyA";break;
			case Functions::RegLoadMUIStringA: return "RegLoadMUIStringA";break;
			case Functions::RegNotifyChangeKeyValue: return "RegNotifyChangeKeyValue";break;
			case Functions::RegOpenCurrentUser: return "RegOpenCurrentUser";break;
			case Functions::RegOpenKeyExA: return "RegOpenKeyExA";break;
			case Functions::RegOpenKeyTransactedA: return "RegOpenKeyTransactedA";break;
			case Functions::RegOpenUserClassesRoot: return "RegOpenUserClassesRoot";break;
			case Functions::RegOverridePredefKey: return "RegOverridePredefKey";break;
			case Functions::RegQueryInfoKeyA: return "RegQueryInfoKeyA";break;
			case Functions::RegQueryMultipleValuesA: return "RegQueryMultipleValuesA";break;
			case Functions::RegQueryReflectionKey: return "RegQueryReflectionKey";break;
			case Functions::RegQueryValueExA: return "RegQueryValueExA";break;
			case Functions::RegRenameKey: return "RegRenameKey";break;
			case Functions::RegReplaceKeyA: return "RegReplaceKeyA";break;
			case Functions::RegRestoreKeyA: return "RegRestoreKeyA";break;
			case Functions::RegSaveKeyA: return "RegSaveKeyA";break;
			case Functions::RegSaveKeyExA: return "RegSaveKeyExA";break;
			case Functions::RegSetKeyValueA: return "RegSetKeyValueA";break;
			case Functions::RegSetKeySecurity: return "RegSetKeySecurity";break;
			case Functions::RegSetValueExA: return "RegSetValueExA";break;
			case Functions::RegUnLoadKeyA: return "RegUnLoadKeyA";break;
			case Functions::GetPrivateProfileInt: return "GetPrivateProfileInt";break;
			case Functions::GetPrivateProfileSection: return "GetPrivateProfileSection";break;
			case Functions::GetPrivateProfileSectionNames: return "GetPrivateProfileSectionNames";break;
			case Functions::GetPrivateProfileString: return "GetPrivateProfileString";break;
			case Functions::GetPrivateProfileStruct: return "GetPrivateProfileStruct";break;
			case Functions::GetProfileIntA: return "GetProfileIntA";break;
			case Functions::GetProfileSectionA: return "GetProfileSectionA";break;
			case Functions::GetProfileStringA: return "GetProfileStringA";break;
			case Functions::WritePrivateProfileSectionA: return "WritePrivateProfileSectionA";break;
			case Functions::WritePrivateProfileStringA: return "WritePrivateProfileStringA";break;
			case Functions::WritePrivateProfileStructA: return "WritePrivateProfileStructA";break;
			case Functions::WriteProfileSectionA: return "WriteProfileSectionA";break;
			case Functions::WriteProfileStringA: return "WriteProfileStringA";break;
    }
}

			void* get_new_fnc_pointer() {
		switch (func_to_hook) {
		//case Functions::AddUsersToEncryptedFile: return &newAddUsersToEncryptedFile;break;
			/*case Functions::AreFileApisANSI: return &newFunctions::newAreFileApisANSI; break;
			case Functions::CheckNameLegalDOS8Dot3A: return &newFunctions::newCheckNameLegalDOS8Dot3A;break;
			case Functions::CloseEncryptedFileRaw: return &newFunctions::newCloseEncryptedFileRaw;break;
			case Functions::CopyFile: return &newFunctions::newCopyFile;break;
			case Functions::CopyFile2: return &newFunctions::newCopyFile2;break;
			case Functions::CopyFileExA: return &newFunctions::newCopyFileExA;break;
			case Functions::CopyFileTransactedA: return &newFunctions::newCopyFileTransactedA;break;
			case Functions::CreateFileA: return &newFunctions::newCreateFileA;break;
			case Functions::CreateFile2: return &newFunctions::newCreateFile2;break;
			case Functions::CreateFileTransactedA: return &newFunctions::newCreateFileTransactedA;break;
			case Functions::CreateHardLinkA: return &newFunctions::newCreateHardLinkA;break;
			case Functions::CreateHardLinkTransactedA: return &newFunctions::newCreateHardLinkTransactedA;break;
			case Functions::CreateSymbolicLinkA: return &newFunctions::newCreateSymbolicLinkA;break;
			case Functions::CreateSymbolicLinkTransactedA: return &newFunctions::newCreateSymbolicLinkTransactedA;break;
			case Functions::DecryptFileA: return &newFunctions::newDecryptFileA;break;
			case Functions::DeleteFileA: return &newFunctions::newDeleteFileA;break;
			case Functions::DeleteFileTransactedA: return &newFunctions::newDeleteFileTransactedA;break;
			case Functions::DuplicateEncryptionInfoFile: return &newFunctions::newDuplicateEncryptionInfoFile;break;
			case Functions::EncryptFileA: return &newFunctions::newEncryptFileA;break;
			case Functions::EncryptionDisable: return &newFunctions::newEncryptionDisable;break;
			case Functions::FindFirstFileA: return &newFunctions::newFindFirstFileA;break;
			case Functions::FindFirstFileExA: return &newFunctions::newFindFirstFileExA;break;
			case Functions::FindFirstFileNameTransactedW: return &newFunctions::newFindFirstFileNameTransactedW;break;
			case Functions::FindFirstFileNameW: return &newFunctions::newFindFirstFileNameW;break;
			case Functions::FindFirstFileTransactedA: return &newFunctions::newFindFirstFileTransactedA;break;
			case Functions::FindFirstStreamTransactedW: return &newFunctions::newFindFirstStreamTransactedW;break;
			case Functions::FindFirstStreamW: return &newFunctions::newFindFirstStreamW;break;
			case Functions::FindNextFileA: return &newFunctions::newFindNextFileA;break;
			case Functions::FindNextFileNameW: return &newFunctions::newFindNextFileNameW;break;
			case Functions::FindNextStreamW: return &newFunctions::newFindNextStreamW;break;
			case Functions::FlushFileBuffers: return &newFunctions::newFlushFileBuffers;break;
			case Functions::FreeEncryptionCertificateHashList: return &newFunctions::newFreeEncryptionCertificateHashList;break;
			case Functions::GetBinaryTypeA: return &newFunctions::newGetBinaryTypeA;break;
			case Functions::GetCompressedFileSizeA: return &newFunctions::newGetCompressedFileSizeA;break;
			case Functions::GetCompressedFileSizeTransactedA: return &newFunctions::newGetCompressedFileSizeTransactedA;break;
			case Functions::GetExpandedNameA: return &newFunctions::newGetExpandedNameA;break;
			case Functions::GetFileAttributesA: return &newFunctions::newGetFileAttributesA;break;
			case Functions::GetFileAttributesExA: return &newFunctions::newGetFileAttributesExA;break;
			case Functions::GetFileAttributesTransactedA: return &newFunctions::newGetFileAttributesTransactedA;break;
			case Functions::GetFileBandwidthReservation: return &newFunctions::newGetFileBandwidthReservation;break;
			case Functions::GetFileInformationByHandle: return &newFunctions::newGetFileInformationByHandle;break;
			case Functions::GetFileInformationByHandleEx: return &newFunctions::newGetFileInformationByHandleEx;break;
			case Functions::GetFileSize: return &newFunctions::newGetFileSize;break;
			case Functions::GetFileSizeEx: return &newFunctions::newGetFileSizeEx;break;
			case Functions::GetFileType: return &newFunctions::newGetFileType;break;
			case Functions::GetFinalPathNameByHandleA: return &newFunctions::newGetFinalPathNameByHandleA;break;
			case Functions::GetFullPathNameA: return &newFunctions::newGetFullPathNameA;break;
			case Functions::GetFullPathNameTransactedA: return &newFunctions::newGetFullPathNameTransactedA;break;
			case Functions::GetLongPathNameA: return &newFunctions::newGetLongPathNameA;break;
			case Functions::GetLongPathNameTransactedA: return &newFunctions::newGetLongPathNameTransactedA;break;
			case Functions::GetQueuedCompletionStatus: return &newFunctions::newGetQueuedCompletionStatus;break;
			case Functions::GetShortPathNameW: return &newFunctions::newGetShortPathNameW;break;
			case Functions::GetTempFileNameA: return &newFunctions::newGetTempFileNameA;break;
			case Functions::GetTempPathA: return &newFunctions::newGetTempPathA;break;
			case Functions::LockFileEx: return &newFunctions::newLockFileEx;break;
			case Functions::LZClose: return &newFunctions::newLZClose;break;
			case Functions::LZCopy: return &newFunctions::newLZCopy;break;
			case Functions::LZInit: return &newFunctions::newLZInit;break;
			case Functions::LZOpenFileA: return &newFunctions::newLZOpenFileA;break;
			case Functions::LZRead: return &newFunctions::newLZRead;break;
			case Functions::LZSeek: return &newFunctions::newLZSeek;break;
			case Functions::MoveFile: return &newFunctions::newMoveFile;break;
			case Functions::MoveFileExA: return &newFunctions::newMoveFileExA;break;
			case Functions::MoveFileTransactedA: return &newFunctions::newMoveFileTransactedA;break;
			case Functions::MoveFileWithProgressA: return &newFunctions::newMoveFileWithProgressA;break;
			case Functions::OpenEncryptedFileRawA: return &newFunctions::newOpenEncryptedFileRawA;break;
			case Functions::OpenFile: return &newFunctions::newOpenFile;break;
			case Functions::OpenFileById: return &newFunctions::newOpenFileById;break;
			case Functions::QueryRecoveryAgentsOnEncryptedFile: return &newFunctions::newQueryRecoveryAgentsOnEncryptedFile;break;
			case Functions::QueryUsersOnEncryptedFile: return &newFunctions::newQueryUsersOnEncryptedFile;break;
			case Functions::ReadEncryptedFileRaw: return &newFunctions::newReadEncryptedFileRaw;break;
			case Functions::ReadFile: return &newFunctions::newReadFile;break;
			case Functions::ReadFileEx: return &newFunctions::newReadFileEx;break;
			case Functions::RemoveUsersFromEncryptedFile: return &newFunctions::newRemoveUsersFromEncryptedFile;break;
			case Functions::ReOpenFile: return &newFunctions::newReOpenFile;break;
			case Functions::ReplaceFileA: return &newFunctions::newReplaceFileA;break;
			case Functions::SearchPathA: return &newFunctions::newSearchPathA;break;
			case Functions::SetEndOfFile: return &newFunctions::newSetEndOfFile;break;
			case Functions::SetFileApisToANSI: return &newFunctions::newSetFileApisToANSI;break;
			case Functions::SetFileApisToOEM: return &newFunctions::newSetFileApisToOEM;break;
			case Functions::SetFileAttributesA: return &newFunctions::newSetFileAttributesA;break;
			case Functions::SetFileAttributesTransactedA: return &newFunctions::newSetFileAttributesTransactedA;break;
			case Functions::SetFileBandwidthReservation: return &newFunctions::newSetFileBandwidthReservation;break;
			case Functions::SetFileCompletionNotificationModes: return &newFunctions::newSetFileCompletionNotificationModes;break;
			case Functions::SetFileInformationByHandle: return &newFunctions::newSetFileInformationByHandle;break;
			case Functions::SetFileIoOverlappedRange: return &newFunctions::newSetFileIoOverlappedRange;break;
			case Functions::SetFilePointer: return &newFunctions::newSetFilePointer;break;
			case Functions::SetFilePointerEx: return &newFunctions::newSetFilePointerEx;break;
			case Functions::SetFileShortNameA: return &newFunctions::newSetFileShortNameA;break;
			case Functions::SetFileValidData: return &newFunctions::newSetFileValidData;break;
			case Functions::SetSearchPathMode: return &newFunctions::newSetSearchPathMode;break;
			case Functions::SetUserFileEncryptionKey: return &newFunctions::newSetUserFileEncryptionKey;break;
			case Functions::UnlockFile: return &newFunctions::newUnlockFile;break;
			case Functions::UnlockFileEx: return &newFunctions::newUnlockFileEx;break;
			case Functions::WofGetDriverVersion: return &newFunctions::newWofGetDriverVersion;break;
			case Functions::WofIsExternalFile: return &newFunctions::newWofIsExternalFile;break;
			case Functions::WofSetFileDataLocation: return &newFunctions::newWofSetFileDataLocation;break;
			case Functions::WofShouldCompressBinaries: return &newFunctions::newWofShouldCompressBinaries;break;
			case Functions::WofWimAddEntry: return &newFunctions::newWofWimAddEntry;break;
			case Functions::WofWimRemoveEntry: return &newFunctions::newWofWimRemoveEntry;break;
			case Functions::WofWimSuspendEntry: return &newFunctions::newWofWimSuspendEntry;break;
			case Functions::WofWimUpdateEntry: return &newFunctions::newWofWimUpdateEntry;break;
			case Functions::Wow64DisableWow64FsRedirection: return &newFunctions::newWow64DisableWow64FsRedirection;break;
			case Functions::Wow64EnableWow64FsRedirection: return &newFunctions::newWow64EnableWow64FsRedirection;break;
			case Functions::Wow64RevertWow64FsRedirection: return &newFunctions::newWow64RevertWow64FsRedirection;break;
			case Functions::WriteEncryptedFileRaw: return &newFunctions::newWriteEncryptedFileRaw;break;
			case Functions::WriteFile: return &newFunctions::newWriteFile;break;
			case Functions::WriteFileEx: return &newFunctions::newWriteFileEx;break;*/
			/*case Functions::accept: return &newFunctions::newaccept; break;
			case Functions::AcceptEx: return &newFunctions::newAcceptEx;break;
			case Functions::bind: return &newFunctions::newbind;break;
			case Functions::closesocket: return &newFunctions::newclosesocket;break;
			case Functions::connect: return &newFunctions::newconnect;break;
			case Functions::EnumProtocolsA: return &newFunctions::newEnumProtocolsA;break;
			case Functions::freeaddrinfo: return &newFunctions::newfreeaddrinfo;break;
			case Functions::FreeAddrInfoEx: return &newFunctions::newFreeAddrInfoEx;break;
			case Functions::FreeAddrInfoW: return &newFunctions::newFreeAddrInfoW;break;
			case Functions::gai_strerrorA: return &newFunctions::newgai_strerrorA;break;
			case Functions::GetAcceptExSockaddrs: return &newFunctions::newGetAcceptExSockaddrs;break;
			case Functions::getaddrinfo: return &newFunctions::newgetaddrinfo;break;
			case Functions::GetAddrInfoExCancel: return &newFunctions::newGetAddrInfoExCancel;break;
			case Functions::GetAddrInfoExOverlappedResult: return &newFunctions::newGetAddrInfoExOverlappedResult;break;
			case Functions::GetAddrInfoW: return &newFunctions::newGetAddrInfoW;break;
			case Functions::gethostname: return &newFunctions::newgethostname;break;
			case Functions::GetHostNameW: return &newFunctions::newGetHostNameW;break;
			case Functions::GetNameByTypeA: return &newFunctions::newGetNameByTypeA;break;
			case Functions::getpeername: return &newFunctions::newgetpeername;break;
			case Functions::getprotobyname: return &newFunctions::newgetprotobyname;break;
			case Functions::getprotobynumber: return &newFunctions::newgetprotobynumber;break;
			case Functions::getservbyname: return &newFunctions::newgetservbyname;break;
			case Functions::getservbyport: return &newFunctions::newgetservbyport;break;
			case Functions::getsockname: return &newFunctions::newgetsockname;break;
			case Functions::getsockopt: return &newFunctions::newgetsockopt;break;
			case Functions::GetTypeByNameA: return &newFunctions::newGetTypeByNameA;break;
			case Functions::htons: return &newFunctions::newhtons;break;
			case Functions::inet_addr: return &newFunctions::newinet_addr;break;
			case Functions::inet_ntoa: return &newFunctions::newinet_ntoa;break;
			case Functions::InetNtopW: return &newFunctions::newInetNtopW;break;
			case Functions::InetPtonW: return &newFunctions::newInetPtonW;break;
			case Functions::ioctlsocket: return &newFunctions::newioctlsocket;break;
			case Functions::listen: return &newFunctions::newlisten;break;
			case Functions::ntohd: return &newFunctions::newntohd;break;
			case Functions::ntohf: return &newFunctions::newntohf;break;
			case Functions::ntohl: return &newFunctions::newntohl;break;
			case Functions::ntohs: return &newFunctions::newntohs;break;
			case Functions::recv: return &newFunctions::newrecv;break;
			case Functions::recvfrom: return &newFunctions::newrecvfrom;break;
			case Functions::select: return &newFunctions::newselect;break;
			case Functions::send: return &newFunctions::newsend;break;
			case Functions::sendto: return &newFunctions::newsendto;break;
			case Functions::SetSocketMediaStreamingMode: return &newFunctions::newSetSocketMediaStreamingMode;break;
			case Functions::setsockopt: return &newFunctions::newsetsockopt;break;
			case Functions::shutdown: return &newFunctions::newshutdown;break;
			case Functions::socket: return &newFunctions::newsocket;break;
			case Functions::WSAAccept: return &newFunctions::newWSAAccept;break;
			case Functions::WSAAddressToStringA: return &newFunctions::newWSAAddressToStringA;break;
			case Functions::WSAAsyncGetHostByAddr: return &newFunctions::newWSAAsyncGetHostByAddr;break;
			case Functions::WSAAsyncGetHostByName: return &newFunctions::newWSAAsyncGetHostByName;break;
			case Functions::WSAAsyncGetProtoByName: return &newFunctions::newWSAAsyncGetProtoByName;break;
			case Functions::WSAAsyncGetProtoByNumber: return &newFunctions::newWSAAsyncGetProtoByNumber;break;
			case Functions::WSAAsyncGetServByName: return &newFunctions::newWSAAsyncGetServByName;break;
			case Functions::WSAAsyncGetServByPort: return &newFunctions::newWSAAsyncGetServByPort;break;
			case Functions::WSAAsyncSelect: return &newFunctions::newWSAAsyncSelect;break;
			case Functions::WSACancelAsyncRequest: return &newFunctions::newWSACancelAsyncRequest;break;
			case Functions::WSACleanup: return &newFunctions::newWSACleanup;break;
			case Functions::WSACloseEvent: return &newFunctions::newWSACloseEvent;break;
			case Functions::WSAConnect: return &newFunctions::newWSAConnect;break;
			case Functions::WSAConnectByList: return &newFunctions::newWSAConnectByList;break;
			case Functions::WSAConnectByNameA: return &newFunctions::newWSAConnectByNameA;break;
			case Functions::WSACreateEvent: return &newFunctions::newWSACreateEvent;break;
			case Functions::WSADeleteSocketPeerTargetName: return &newFunctions::newWSADeleteSocketPeerTargetName;break;
			case Functions::WSADuplicateSocketA: return &newFunctions::newWSADuplicateSocketA;break;
			case Functions::WSAEnumNameSpaceProvidersA: return &newFunctions::newWSAEnumNameSpaceProvidersA;break;
			case Functions::WSAEnumNameSpaceProvidersExA: return &newFunctions::newWSAEnumNameSpaceProvidersExA;break;
			case Functions::WSAEnumNetworkEvents: return &newFunctions::newWSAEnumNetworkEvents;break;
			case Functions::WSAEnumProtocolsA: return &newFunctions::newWSAEnumProtocolsA;break;
			case Functions::WSAEventSelect: return &newFunctions::newWSAEventSelect;break;
			case Functions::__WSAFDIsSet: return &newFunctions::new__WSAFDIsSet;break;
			case Functions::WSAGetFailConnectOnIcmpError: return &newFunctions::newWSAGetFailConnectOnIcmpError;break;
			case Functions::WSAGetIPUserMtu: return &newFunctions::newWSAGetIPUserMtu;break;
			case Functions::WSAGetLastError: return &newFunctions::newWSAGetLastError;break;
			case Functions::WSAGetOverlappedResult: return &newFunctions::newWSAGetOverlappedResult;break;
			case Functions::WSAGetQOSByName: return &newFunctions::newWSAGetQOSByName;break;
			case Functions::WSAGetServiceClassInfoA: return &newFunctions::newWSAGetServiceClassInfoA;break;
			case Functions::WSAGetServiceClassNameByClassIdA: return &newFunctions::newWSAGetServiceClassNameByClassIdA;break;
			case Functions::WSAGetUdpRecvMaxCoalescedSize: return &newFunctions::newWSAGetUdpRecvMaxCoalescedSize;break;
			case Functions::WSAGetUdpSendMessageSize: return &newFunctions::newWSAGetUdpSendMessageSize;break;
			case Functions::WSAHtonl: return &newFunctions::newWSAHtonl;break;
			case Functions::WSAHtons: return &newFunctions::newWSAHtons;break;
			case Functions::WSAImpersonateSocketPeer: return &newFunctions::newWSAImpersonateSocketPeer;break;
			case Functions::WSAInstallServiceClassA: return &newFunctions::newWSAInstallServiceClassA;break;
			case Functions::WSAIoctl: return &newFunctions::newWSAIoctl;break;
			case Functions::WSAJoinLeaf: return &newFunctions::newWSAJoinLeaf;break;
			case Functions::WSALookupServiceBeginA: return &newFunctions::newWSALookupServiceBeginA;break;
			case Functions::WSALookupServiceEnd: return &newFunctions::newWSALookupServiceEnd;break;
			case Functions::WSALookupServiceNextA: return &newFunctions::newWSALookupServiceNextA;break;
			case Functions::WSANSPIoctl: return &newFunctions::newWSANSPIoctl;break;
			case Functions::WSANtohl: return &newFunctions::newWSANtohl;break;
			case Functions::WSANtohs: return &newFunctions::newWSANtohs;break;
			case Functions::WSAPoll: return &newFunctions::newWSAPoll;break;
			case Functions::WSAProviderConfigChange: return &newFunctions::newWSAProviderConfigChange;break;
			case Functions::WSARecv: return &newFunctions::newWSARecv;break;
			case Functions::WSARecvDisconnect: return &newFunctions::newWSARecvDisconnect;break;
			case Functions::WSARecvEx: return &newFunctions::newWSARecvEx;break;
			case Functions::WSARecvFrom: return &newFunctions::newWSARecvFrom;break;
			case Functions::WSARemoveServiceClass: return &newFunctions::newWSARemoveServiceClass;break;
			case Functions::WSAResetEvent: return &newFunctions::newWSAResetEvent;break;
			case Functions::WSARevertImpersonation: return &newFunctions::newWSARevertImpersonation;break;
			case Functions::WSASend: return &newFunctions::newWSASend;break;
			case Functions::WSASendDisconnect: return &newFunctions::newWSASendDisconnect;break;
			case Functions::WSASendMsg: return &newFunctions::newWSASendMsg;break;
			case Functions::WSASendTo: return &newFunctions::newWSASendTo;break;
			case Functions::WSASetEvent: return &newFunctions::newWSASetEvent;break;
			case Functions::WSASetFailConnectOnIcmpError: return &newFunctions::newWSASetFailConnectOnIcmpError;break;
			case Functions::WSASetIPUserMtu: return &newFunctions::newWSASetIPUserMtu;break;
			case Functions::WSASetLastError: return &newFunctions::newWSASetLastError;break;
			case Functions::WSASetServiceA: return &newFunctions::newWSASetServiceA;break;
			case Functions::WSASetUdpRecvMaxCoalescedSize: return &newFunctions::newWSASetUdpRecvMaxCoalescedSize;break;
			case Functions::WSASetUdpSendMessageSize: return &newFunctions::newWSASetUdpSendMessageSize;break;
			case Functions::WSASocketA: return &newFunctions::newWSASocketA;break;
			case Functions::WSAStartup: return &newFunctions::newWSAStartup;break;
			case Functions::WSAStringToAddressA: return &newFunctions::newWSAStringToAddressA;break;
			case Functions::WSAWaitForMultipleEvents: return &newFunctions::newWSAWaitForMultipleEvents;break;
			case Functions::GetSystemRegistryQuota: return &newFunctions::newGetSystemRegistryQuota;break;
			case Functions::RegCloseKey: return &newFunctions::newRegCloseKey;break;
			case Functions::RegConnectRegistryA: return &newFunctions::newRegConnectRegistryA;break;
			case Functions::RegCopyTreeA: return &newFunctions::newRegCopyTreeA;break;
			case Functions::RegCreateKeyExA: return &newFunctions::newRegCreateKeyExA;break;
			case Functions::RegCreateKeyTransactedA: return &newFunctions::newRegCreateKeyTransactedA;break;
			case Functions::RegDeleteKeyA: return &newFunctions::newRegDeleteKeyA;break;
			case Functions::RegDeleteKeyExA: return &newFunctions::newRegDeleteKeyExA;break;
			case Functions::RegDeleteKeyTransactedA: return &newFunctions::newRegDeleteKeyTransactedA;break;
			case Functions::RegDeleteKeyValueA: return &newFunctions::newRegDeleteKeyValueA;break;
			case Functions::RegDeleteTreeA: return &newFunctions::newRegDeleteTreeA;break;
			case Functions::RegDeleteValueA: return &newFunctions::newRegDeleteValueA;break;
			case Functions::RegDisablePredefinedCache: return &newFunctions::newRegDisablePredefinedCache;break;
			case Functions::RegDisablePredefinedCacheEx: return &newFunctions::newRegDisablePredefinedCacheEx;break;
			case Functions::RegDisableReflectionKey: return &newFunctions::newRegDisableReflectionKey;break;
			case Functions::RegEnableReflectionKey: return &newFunctions::newRegEnableReflectionKey;break;
			case Functions::RegEnumKeyExA: return &newFunctions::newRegEnumKeyExA;break;
			case Functions::RegEnumValueA: return &newFunctions::newRegEnumValueA;break;
			case Functions::RegFlushKey: return &newFunctions::newRegFlushKey;break;
			case Functions::RegGetKeySecurity: return &newFunctions::newRegGetKeySecurity;break;
			case Functions::RegGetValueA: return &newFunctions::newRegGetValueA;break;
			case Functions::RegLoadKeyA: return &newFunctions::newRegLoadKeyA;break;
			case Functions::RegLoadMUIStringA: return &newFunctions::newRegLoadMUIStringA;break;
			case Functions::RegNotifyChangeKeyValue: return &newFunctions::newRegNotifyChangeKeyValue;break;
			case Functions::RegOpenCurrentUser: return &newFunctions::newRegOpenCurrentUser;break;
			case Functions::RegOpenKeyExA: return &newFunctions::newRegOpenKeyExA;break;
			case Functions::RegOpenKeyTransactedA: return &newFunctions::newRegOpenKeyTransactedA;break;
			case Functions::RegOpenUserClassesRoot: return &newFunctions::newRegOpenUserClassesRoot;break;
			case Functions::RegOverridePredefKey: return &newFunctions::newRegOverridePredefKey;break;
			case Functions::RegQueryInfoKeyA: return &newFunctions::newRegQueryInfoKeyA;break;
			case Functions::RegQueryMultipleValuesA: return &newFunctions::newRegQueryMultipleValuesA;break;
			case Functions::RegQueryReflectionKey: return &newFunctions::newRegQueryReflectionKey;break;
			case Functions::RegQueryValueExA: return &newFunctions::newRegQueryValueExA;break;
			case Functions::RegRenameKey: return &newFunctions::newRegRenameKey;break;
			case Functions::RegReplaceKeyA: return &newFunctions::newRegReplaceKeyA;break;
			case Functions::RegRestoreKeyA: return &newFunctions::newRegRestoreKeyA;break;
			case Functions::RegSaveKeyA: return &newFunctions::newRegSaveKeyA;break;
			case Functions::RegSaveKeyExA: return &newFunctions::newRegSaveKeyExA;break;
			case Functions::RegSetKeyValueA: return &newFunctions::newRegSetKeyValueA;break;
			case Functions::RegSetKeySecurity: return &newFunctions::newRegSetKeySecurity;break;
			case Functions::RegSetValueExA: return &newFunctions::newRegSetValueExA;break;
			case Functions::RegUnLoadKeyA: return &newFunctions::newRegUnLoadKeyA;break;
			case Functions::GetPrivateProfileInt: return &newFunctions::newGetPrivateProfileInt;break;
			case Functions::GetPrivateProfileSection: return &newFunctions::newGetPrivateProfileSection;break;
			case Functions::GetPrivateProfileSectionNames: return &newFunctions::newGetPrivateProfileSectionNames;break;
			case Functions::GetPrivateProfileString: return &newFunctions::newGetPrivateProfileString;break;
			case Functions::GetPrivateProfileStruct: return &newFunctions::newGetPrivateProfileStruct;break;
			case Functions::GetProfileIntA: return &newFunctions::newGetProfileIntA;break;
			case Functions::GetProfileSectionA: return &newFunctions::newGetProfileSectionA;break;
			case Functions::GetProfileStringA: return &newFunctions::newGetProfileStringA;break;
			case Functions::WritePrivateProfileSectionA: return &newFunctions::newWritePrivateProfileSectionA;break;
			case Functions::WritePrivateProfileStringA: return &newFunctions::newWritePrivateProfileStringA;break;
			case Functions::WritePrivateProfileStructA: return &newFunctions::newWritePrivateProfileStructA;break;
			case Functions::WriteProfileSectionA: return &newFunctions::newWriteProfileSectionA;break;
			case Functions::WriteProfileStringA: return &newFunctions::newWriteProfileStringA;break;*/

			}
			return nullptr;
	}

};
