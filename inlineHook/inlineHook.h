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
#include "newFunctions.h"
#include "codeGeneratedFunctionsFileSystem.h"
#include "codeGeneratedFunctionsRegistry.h"
#include "codeGeneratedFunctionsSockets.h"

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;


extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

void set_up_hook();
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
		case Functions::CreateFileA: return "CreateFileA"; break;
		case Functions::CreateFile2:return "CreateFileW"; break;
		case Functions::DeleteFileA:return "DeleteFileA"; break;
		case Functions::ReadFile:return "ReadFile"; break;
		case Functions::ReadFileEx:return"ReadFileEx"; break;
		case Functions::WriteFile:return"WriteFile"; break;
		case Functions::WriteFileEx:return"WriteFileEx"; break;
		case Functions::send:return"send"; break;
		case Functions::recv:return "recv"; break;
		case Functions::RegCreateKeyExA:return "RegCreateKeyExA"; break;
		case Functions::RegDeleteKeyA:return "RegDeleteKeyA"; break;
		case Functions::RegDeleteKeyExA:return "RegDeleteKeyExA"; break;
		}
	}

	void* get_new_fnc_pointer() {
		switch (func_to_hook) {
		case Functions::CreateFileA: return &newFunctions::newCreateFileA; break;
		case Functions::CreateFile2:return &newFunctions::newCreateFileW; break;
		case Functions::DeleteFileA:return &newFunctions::newDeleteFileA; break;
		case Functions::ReadFile:return &newFunctions::newReadFile; break;
		case Functions::ReadFileEx:return &newFunctions::newReadFileEx; break;
		case Functions::WriteFile:return &newFunctions::newWriteFile; break;
		case Functions::WriteFileEx:return nullptr; break;
		case Functions::send:return &newFunctions::newsend; break;
		case Functions::recv:return &newFunctions::newrecv; break;
		case Functions::RegCreateKeyExA:return &newFunctions::newRegCreateKeyExA; break;
		case Functions::RegDeleteKeyA:return &newFunctions::newRegDeleteKeyA; break;
		case Functions::RegDeleteKeyExA:return &newFunctions::newRegDeleteKeyExA; break;
		}

	}

};
