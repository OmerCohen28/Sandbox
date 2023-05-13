#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#define DLL_EXPORT
#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <sstream>
#include <time.h>
#include <vector>
#include <cstdio>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdarg>
#include <time.h>
#include <stdio.h>
#include <ws2tcpip.h> 
#include <locale>
#include <codecvt>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "codeGeneratedFunctionsFileSystem.h"
#include "codeGeneratedFunctionsRegistry.h"
#include "codeGeneratedFunctionsRegistry.h"

#define _my_addr_ "127.0.0.1"




std::vector<CHAR*> original_bytes{};
std::vector<FARPROC> hooked_addr{};
std::vector<std::string>* functions;
time_t begin, end;
std::vector<std::string> fs_functions;
std::vector<std::string> reg_functions;
std::vector<std::string> sock_functions;
char WhatToDoSock;
char WhatToDoFs;
char WhatToDoReg;


HINSTANCE hLibFiles{ LoadLibraryA("kernel32.dll") };
HINSTANCE hLibSock{ LoadLibraryA("Ws2_32.dll") };
HINSTANCE hLibReg{ LoadLibraryA("Advapi32.dll") };

HANDLE LOGfile = CreateFileA(
	"C:\\Users\\Omer Cohen\\Documents\\Programming\\Actual sandbox sln\\log.txt",
	GENERIC_READ | GENERIC_WRITE,
	FILE_SHARE_READ | FILE_SHARE_DELETE,
	NULL,
	CREATE_ALWAYS,
	FILE_ATTRIBUTE_NORMAL,
	NULL
);
bool IsMyCall = false;


void mylog1(const char* buf, int size) {
	IsMyCall = true;
	std::cout << "called my log with msg " << buf << '\n';
	/*static HANDLE file = CreateFileA(
		"..\\log.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);*/
	if (LOGfile == INVALID_HANDLE_VALUE) {
		std::cout << "from mylog nope\n";
		return;
	}
	WriteFile(LOGfile, buf, size, NULL, NULL);
	IsMyCall = false;
	//delete[] buf;
}

void mylog(char* buf, int size) {
	IsMyCall = true;
	std::cout << "called my log with msg " << buf << '\n';
	/*static HANDLE file = CreateFileA(
		"..\\log.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		4,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);*/
	if (LOGfile == INVALID_HANDLE_VALUE) {
		std::cout << "from mylog nope\n";
		return;
	}
	WriteFile(LOGfile, buf, size, NULL, NULL);
	IsMyCall = false;
	//delete[] buf;
}

void log(std::string buffer){
	if (LOGfile == INVALID_HANDLE_VALUE) {
		std::cout << "Log file could not be opened\n";
		return;
	}
	IsMyCall = true;
	std::cout << "right here inside of log about to log data\n";
	buffer.at(buffer.size()-1) = *"%";
	WriteFile(LOGfile,buffer.data(),buffer.size(),NULL,NULL);
	std::cout << "finished logging\n";
	IsMyCall = false;
}

std::string ToStringSocket(SOCKET s)
{
	SOCKADDR_IN src_addr, dst_addr;
	int src_len = sizeof(src_addr), dst_len = sizeof(dst_addr);
	std::string result;

	if (getsockname(s, (SOCKADDR*)&src_addr, &src_len) == SOCKET_ERROR) {
		result = "Error getting local endpoint address and port.";
		return result;
	}
	if (getpeername(s, (SOCKADDR*)&dst_addr, &dst_len) == SOCKET_ERROR) {
		result = "Error getting remote endpoint address and port.";
		return result;
	}

	char src_ip[16], dst_ip[16];
	inet_ntop(AF_INET, &src_addr.sin_addr, src_ip, sizeof(src_ip));
	inet_ntop(AF_INET, &dst_addr.sin_addr, dst_ip, sizeof(dst_ip));

	result = std::string(src_ip) + ":" + std::to_string(ntohs(src_addr.sin_port))
		+ " -> " + std::string(dst_ip) + ":" + std::to_string(ntohs(dst_addr.sin_port));

	return result;
}

std::string sockaddrToString(const sockaddr* sa) {
	std::stringstream ss;
	if (sa->sa_family == AF_INET) {
		// IPv4
		const sockaddr_in* sin = reinterpret_cast<const sockaddr_in*>(sa);
		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(sin->sin_addr), ip, INET_ADDRSTRLEN);
		ss << ip << ":" << ntohs(sin->sin_port);
	}
	else if (sa->sa_family == AF_INET6) {
		// IPv6
		const sockaddr_in6* sin6 = reinterpret_cast<const sockaddr_in6*>(sa);
		char ip[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &(sin6->sin6_addr), ip, INET6_ADDRSTRLEN);
		ss << "[" << ip << "]:" << ntohs(sin6->sin6_port);
	}
	else {
		ss << "Unknown family type: " << sa->sa_family;
	}
	return ss.str();
}


void* Hook::get_new_fnc_pointer() {
	switch (func_to_hook) {
	case Functions::AddUsersToEncryptedFile: return &newFunctions::newAddUsersToEncryptedFile; break;
	case Functions::AreFileApisANSI: return &newFunctions::newAreFileApisANSI; break;
	case Functions::CheckNameLegalDOS8Dot3A: return &newFunctions::newCheckNameLegalDOS8Dot3A; break;
	case Functions::CloseEncryptedFileRaw: return &newFunctions::newCloseEncryptedFileRaw; break;
	case Functions::CopyFile: return &newFunctions::newCopyFile; break;
	case Functions::CopyFile2: return &newFunctions::newCopyFile2; break;
	case Functions::CopyFileExA: return &newFunctions::newCopyFileExA; break;
	case Functions::CopyFileTransactedA: return &newFunctions::newCopyFileTransactedA; break;
	case Functions::CreateFileA: return &newFunctions::newCreateFileA; break;
	case Functions::CreateFile2: return &newFunctions::newCreateFile2; break;
	case Functions::CreateFileTransactedA: return &newFunctions::newCreateFileTransactedA; break;
	case Functions::CreateHardLinkA: return &newFunctions::newCreateHardLinkA; break;
	case Functions::CreateHardLinkTransactedA: return &newFunctions::newCreateHardLinkTransactedA; break;
	case Functions::CreateSymbolicLinkA: return &newFunctions::newCreateSymbolicLinkA; break;
	case Functions::CreateSymbolicLinkTransactedA: return &newFunctions::newCreateSymbolicLinkTransactedA; break;
	case Functions::DecryptFileA: return &newFunctions::newDecryptFileA; break;
	case Functions::DeleteFileA: return &newFunctions::newDeleteFileA; break;
	case Functions::DeleteFileTransactedA: return &newFunctions::newDeleteFileTransactedA; break;
	case Functions::DuplicateEncryptionInfoFile: return &newFunctions::newDuplicateEncryptionInfoFile; break;
	case Functions::EncryptFileA: return &newFunctions::newEncryptFileA; break;
	case Functions::EncryptionDisable: return &newFunctions::newEncryptionDisable; break;
	case Functions::FindFirstFileA: return &newFunctions::newFindFirstFileA; break;
	case Functions::FindFirstFileExA: return &newFunctions::newFindFirstFileExA; break;
	case Functions::FindFirstFileNameTransactedW: return &newFunctions::newFindFirstFileNameTransactedW; break;
	case Functions::FindFirstFileNameW: return &newFunctions::newFindFirstFileNameW; break;
	case Functions::FindFirstFileTransactedA: return &newFunctions::newFindFirstFileTransactedA; break;
	case Functions::FindFirstStreamTransactedW: return &newFunctions::newFindFirstStreamTransactedW; break;
	case Functions::FindFirstStreamW: return &newFunctions::newFindFirstStreamW; break;
	case Functions::FindNextFileA: return &newFunctions::newFindNextFileA; break;
	case Functions::FindNextFileNameW: return &newFunctions::newFindNextFileNameW; break;
	case Functions::FindNextStreamW: return &newFunctions::newFindNextStreamW; break;
	case Functions::FlushFileBuffers: return &newFunctions::newFlushFileBuffers; break;
	case Functions::FreeEncryptionCertificateHashList: return &newFunctions::newFreeEncryptionCertificateHashList; break;
	case Functions::GetBinaryTypeA: return &newFunctions::newGetBinaryTypeA; break;
	case Functions::GetCompressedFileSizeA: return &newFunctions::newGetCompressedFileSizeA; break;
	case Functions::GetCompressedFileSizeTransactedA: return &newFunctions::newGetCompressedFileSizeTransactedA; break;
	case Functions::GetFileAttributesA: return &newFunctions::newGetFileAttributesA; break;
	case Functions::GetFileAttributesExA: return &newFunctions::newGetFileAttributesExA; break;
	case Functions::GetFileAttributesTransactedA: return &newFunctions::newGetFileAttributesTransactedA; break;
	case Functions::GetFileBandwidthReservation: return &newFunctions::newGetFileBandwidthReservation; break;
	case Functions::GetFileInformationByHandle: return &newFunctions::newGetFileInformationByHandle; break;
	case Functions::GetFileInformationByHandleEx: return &newFunctions::newGetFileInformationByHandleEx; break;
	case Functions::GetFileSize: return &newFunctions::newGetFileSize; break;
	case Functions::GetFileSizeEx: return &newFunctions::newGetFileSizeEx; break;
	case Functions::GetFileType: return &newFunctions::newGetFileType; break;
	case Functions::GetFinalPathNameByHandleA: return &newFunctions::newGetFinalPathNameByHandleA; break;
	case Functions::GetFullPathNameA: return &newFunctions::newGetFullPathNameA; break;
	case Functions::GetFullPathNameTransactedA: return &newFunctions::newGetFullPathNameTransactedA; break;
	case Functions::GetLongPathNameA: return &newFunctions::newGetLongPathNameA; break;
	case Functions::GetLongPathNameTransactedA: return &newFunctions::newGetLongPathNameTransactedA; break;
	case Functions::GetQueuedCompletionStatus: return &newFunctions::newGetQueuedCompletionStatus; break;
	case Functions::GetShortPathNameW: return &newFunctions::newGetShortPathNameW; break;
	case Functions::GetTempFileNameA: return &newFunctions::newGetTempFileNameA; break;
	case Functions::GetTempPathA: return &newFunctions::newGetTempPathA; break;
	case Functions::LockFileEx: return &newFunctions::newLockFileEx; break;
	case Functions::MoveFile: return &newFunctions::newMoveFile; break;
	case Functions::MoveFileExA: return &newFunctions::newMoveFileExA; break;
	case Functions::MoveFileTransactedA: return &newFunctions::newMoveFileTransactedA; break;
	case Functions::MoveFileWithProgressA: return &newFunctions::newMoveFileWithProgressA; break;
	case Functions::OpenEncryptedFileRawA: return &newFunctions::newOpenEncryptedFileRawA; break;
	case Functions::OpenFile: return &newFunctions::newOpenFile; break;
	case Functions::OpenFileById: return &newFunctions::newOpenFileById; break;
	case Functions::QueryRecoveryAgentsOnEncryptedFile: return &newFunctions::newQueryRecoveryAgentsOnEncryptedFile; break;
	case Functions::QueryUsersOnEncryptedFile: return &newFunctions::newQueryUsersOnEncryptedFile; break;
	case Functions::ReadEncryptedFileRaw: return &newFunctions::newReadEncryptedFileRaw; break;
	case Functions::ReadFile: return &newFunctions::newReadFile; break;
	case Functions::ReadFileEx: return &newFunctions::newReadFileEx; break;
	case Functions::RemoveUsersFromEncryptedFile: return &newFunctions::newRemoveUsersFromEncryptedFile; break;
	case Functions::ReOpenFile: return &newFunctions::newReOpenFile; break;
	case Functions::ReplaceFileA: return &newFunctions::newReplaceFileA; break;
	case Functions::SearchPathA: return &newFunctions::newSearchPathA; break;
	case Functions::SetEndOfFile: return &newFunctions::newSetEndOfFile; break;
	case Functions::SetFileApisToANSI: return &newFunctions::newSetFileApisToANSI; break;
	case Functions::SetFileApisToOEM: return &newFunctions::newSetFileApisToOEM; break;
	case Functions::SetFileAttributesA: return &newFunctions::newSetFileAttributesA; break;
	case Functions::SetFileAttributesTransactedA: return &newFunctions::newSetFileAttributesTransactedA; break;
	case Functions::SetFileBandwidthReservation: return &newFunctions::newSetFileBandwidthReservation; break;
	case Functions::SetFileCompletionNotificationModes: return &newFunctions::newSetFileCompletionNotificationModes; break;
	case Functions::SetFileInformationByHandle: return &newFunctions::newSetFileInformationByHandle; break;
	case Functions::SetFileIoOverlappedRange: return &newFunctions::newSetFileIoOverlappedRange; break;
	case Functions::SetFilePointer: return &newFunctions::newSetFilePointer; break;
	case Functions::SetFilePointerEx: return &newFunctions::newSetFilePointerEx; break;
	case Functions::SetFileShortNameA: return &newFunctions::newSetFileShortNameA; break;
	case Functions::SetFileValidData: return &newFunctions::newSetFileValidData; break;
	case Functions::SetSearchPathMode: return &newFunctions::newSetSearchPathMode; break;
	case Functions::SetUserFileEncryptionKey: return &newFunctions::newSetUserFileEncryptionKey; break;
	case Functions::UnlockFile: return &newFunctions::newUnlockFile; break;
	case Functions::UnlockFileEx: return &newFunctions::newUnlockFileEx; break;
	case Functions::Wow64DisableWow64FsRedirection: return &newFunctions::newWow64DisableWow64FsRedirection; break;
	case Functions::Wow64EnableWow64FsRedirection: return &newFunctions::newWow64EnableWow64FsRedirection; break;
	case Functions::Wow64RevertWow64FsRedirection: return &newFunctions::newWow64RevertWow64FsRedirection; break;
	case Functions::WriteEncryptedFileRaw: return &newFunctions::newWriteEncryptedFileRaw; break;
	case Functions::WriteFile: return &newFunctions::newWriteFile; break;
	case Functions::WriteFileEx: return &newFunctions::newWriteFileEx; break;
	case Functions::accept: return &newFunctions::newaccept; break;
	case Functions::bind: return &newFunctions::newbind;break;
	case Functions::closesocket: return &newFunctions::newclosesocket;break;
	case Functions::connect: return &newFunctions::newconnect;break;
	case Functions::gai_strerrorA: return &newFunctions::newgai_strerrorA;break;
	case Functions::gethostname: return &newFunctions::newgethostname;break;
	case Functions::getpeername: return &newFunctions::newgetpeername;break;
	case Functions::getprotobyname: return &newFunctions::newgetprotobyname;break;
	case Functions::getprotobynumber: return &newFunctions::newgetprotobynumber;break;
	case Functions::getservbyname: return &newFunctions::newgetservbyname;break;
	case Functions::getservbyport: return &newFunctions::newgetservbyport;break;
	case Functions::getsockname: return &newFunctions::newgetsockname;break;
	case Functions::getsockopt: return &newFunctions::newgetsockopt;break;
	case Functions::htons: return &newFunctions::newhtons;break;
	case Functions::inet_addr: return &newFunctions::newinet_addr;break;
	case Functions::inet_ntoa: return &newFunctions::newinet_ntoa;break;
	case Functions::InetNtopW: return &newFunctions::newInetNtopW;break;
	case Functions::InetPtonW: return &newFunctions::newInetPtonW;break;
	case Functions::ioctlsocket: return &newFunctions::newioctlsocket;break;
	case Functions::listen: return &newFunctions::newlisten;break;
	case Functions::ntohl: return &newFunctions::newntohl;break;
	case Functions::ntohs: return &newFunctions::newntohs;break;
	case Functions::recv: return &newFunctions::newrecv;break;
	case Functions::recvfrom: return &newFunctions::newrecvfrom;break;
	case Functions::select: return &newFunctions::newselect;break;
	case Functions::send: return &newFunctions::newsend;break;
	case Functions::sendto: return &newFunctions::newsendto;break;
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
	case Functions::WSADuplicateSocketA: return &newFunctions::newWSADuplicateSocketA;break;
	case Functions::WSAEnumNameSpaceProvidersA: return &newFunctions::newWSAEnumNameSpaceProvidersA;break;
	case Functions::WSAEnumNameSpaceProvidersExA: return &newFunctions::newWSAEnumNameSpaceProvidersExA;break;
	case Functions::WSAEnumNetworkEvents: return &newFunctions::newWSAEnumNetworkEvents;break;
	case Functions::WSAEnumProtocolsA: return &newFunctions::newWSAEnumProtocolsA;break;
	case Functions::WSAEventSelect: return &newFunctions::newWSAEventSelect;break;
	case Functions::__WSAFDIsSet: return &newFunctions::new__WSAFDIsSet;break;
	case Functions::WSAGetLastError: return &newFunctions::newWSAGetLastError;break;
	case Functions::WSAGetOverlappedResult: return &newFunctions::newWSAGetOverlappedResult;break;
	case Functions::WSAGetQOSByName: return &newFunctions::newWSAGetQOSByName;break;
	case Functions::WSAGetServiceClassInfoA: return &newFunctions::newWSAGetServiceClassInfoA;break;
	case Functions::WSAGetServiceClassNameByClassIdA: return &newFunctions::newWSAGetServiceClassNameByClassIdA;break;
	case Functions::WSAHtonl: return &newFunctions::newWSAHtonl;break;
	case Functions::WSAHtons: return &newFunctions::newWSAHtons;break;
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
	case Functions::WSARecvFrom: return &newFunctions::newWSARecvFrom;break;
	case Functions::WSARemoveServiceClass: return &newFunctions::newWSARemoveServiceClass;break;
	case Functions::WSAResetEvent: return &newFunctions::newWSAResetEvent;break;
	case Functions::WSASend: return &newFunctions::newWSASend;break;
	case Functions::WSASendDisconnect: return &newFunctions::newWSASendDisconnect;break;
	case Functions::WSASendMsg: return &newFunctions::newWSASendMsg;break;
	case Functions::WSASendTo: return &newFunctions::newWSASendTo;break;
	case Functions::WSASetEvent: return &newFunctions::newWSASetEvent;break;
	case Functions::WSASetLastError: return &newFunctions::newWSASetLastError;break;
	case Functions::WSASetServiceA: return &newFunctions::newWSASetServiceA;break;
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
	case Functions::WriteProfileStringA: return &newFunctions::newWriteProfileStringA;break;

	}
	return nullptr;
}

std::string* ResizeAndFixFunctionName(char* func) {
	int count{ 0 };
	char forbidden{ *"@" };
	for (int i{ 0 }; i < 40; ++i) {
		char ch = *(func + i);
		if (ch == forbidden) {
			break;
		}
		++count;
	}
	char* buf = new char[count + 1];
	//strncpy_s(buf,count, func, count);
	memcpy(buf, func, count);
	char add{ '\0' };
	memcpy(buf + count, &add, 1);
	std::string* st = new std::string(buf);
	return st;
}

SOCKET* SetFunctionsToHookSocket() {
	WSADATA wsaData;
	std::cout << "setting sock up!\n";
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cout << "WSAStartup function failed with error: " << iResult << '\n';
		return nullptr;
	}

	SOCKET* sock = new SOCKET{ socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) };
	if (*sock == INVALID_SOCKET) {
		wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
		std::cout << "socket function failed with error: " << WSAGetLastError() << '\n';
		return nullptr;
	}
	sockaddr_in saServer;
	saServer.sin_family = AF_INET;
	saServer.sin_addr.S_un.S_addr = inet_addr(_my_addr_);
	//InetPton(AF_INET, (PCWSTR)_my_addr_, &saServer.sin_addr.S_un.S_addr);
	saServer.sin_port = htons(50512);
	iResult = connect(*sock, (SOCKADDR*)&saServer, sizeof(saServer));
	if (iResult == SOCKET_ERROR) {
		std::cout << "error connecting to server\n";
		return nullptr;
	}
	return sock;
}

std::vector<std::string>* getFunctionsToHook() {
	SOCKET* sock = SetFunctionsToHookSocket();
	std::cout << "finished setting sock up\n";
	if (sock == nullptr || *sock == INVALID_SOCKET || *sock == NULL) {
		std::cout << "error connecting to python server\n";
		TerminateProcess(GetCurrentProcess(), 1);
	}
	std::vector<std::string>* vec = new std::vector<std::string>;
	int iResult;
	char* buffer;
	std::cout << "starting to get functions\n";
	do {
		buffer = new char[40];
		iResult = recv(*sock, buffer, 40, 0);
		std::cout << "got function\n";
		if (iResult == SOCKET_ERROR) {
			std::cout << "Error receving function from injectDll server\nterminating\n";
			TerminateProcess(GetCurrentProcess(), 1);
		}
		char add = '\0';
		strcpy_s(buffer + 39, 1, &add);
		std::string* st = ResizeAndFixFunctionName(buffer);
		if (strcmp(st->data(), "stop") == 0) {
			break;
		}
		WhatToDoFs = *"p";
		WhatToDoReg = *"p";
		WhatToDoSock = *"p";
		if (strcmp(st->c_str(),"bfs")==0) {
			WhatToDoFs = *"b";
		}
		if (strcmp(st->c_str(), "wfs") == 0) {
			WhatToDoFs = *"w";
		}
		if (strcmp(st->c_str(), "bsock") == 0) {
			WhatToDoSock = *"b";
		}
		if (strcmp(st->c_str(), "wsock") == 0) {
			WhatToDoSock = *"w";
		}
		if (strcmp(st->c_str(), "breg") == 0) {
			WhatToDoReg = *"b";
		}
		if (strcmp(st->c_str(), "wregs") == 0) {
			WhatToDoReg = *"w";
		}
		vec->push_back(*st);

	} while (true);

	return vec;

}

char WhatToDoInFunction(const char* func_name){
	std::cout << "checking for function " << func_name << '\n';
	for(auto func : *functions){
		if(strcmp(&func.c_str()[1],func_name)==0){
			std::cout << "returning " << func.at(0) << '\n';
			return func.at(0);
		}
	}
	/*std::cout << "called with func " << func_name << '\n';
	if (std::find(fs_functions.begin(), fs_functions.end(), func_name) != fs_functions.end()) {
		
	}*/
	for (auto item : fs_functions) {
		if (item == func_name) {
			return WhatToDoFs;
		}
	}
	/*if (std::find(reg_functions.begin(), reg_functions.end(), new std::string(func_name)) != reg_functions.end()) {
		return WhatToDoReg;
	}*/
	for (auto item : reg_functions) {
		if (item == func_name) {
			return WhatToDoReg;
		}
	}
	/*if (std::find(sock_functions.begin(), sock_functions.end(), new std::string(func_name)) != sock_functions.end()) {
		return WhatToDoSock;
	}*/
	for (auto item : sock_functions) {
		if (item == func_name) {
			return WhatToDoSock;
		}
	}


	return *"p";
}



void deployInitialHook(){
	for(int i{0};i<(int)Hook::Functions::max_functions_number;++i){
		Hook{(Hook::Functions)i}.deploy_hook();
	}
}

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved) // Reserved
{
	char fs[][97] = { "AddUsersToEncryptedFile", "AreFileApisANSI", "CheckNameLegalDOS8Dot3A", "CloseEncryptedFileRaw", "CopyFile", "CopyFile2", "CopyFileExA", "CopyFileTransactedA", "CreateFileA", "CreateFile2", "CreateFileTransactedA", "CreateHardLinkA", "CreateHardLinkTransactedA", "CreateSymbolicLinkA", "CreateSymbolicLinkTransactedA", "DecryptFileA", "DeleteFileA", "DeleteFileTransactedA", "DuplicateEncryptionInfoFile", "EncryptFileA", "EncryptionDisable", "FileEncryptionStatusA", "FindClose", "FindFirstFileA", "FindFirstFileExA", "FindFirstFileNameTransactedW", "FindFirstFileNameW", "FindFirstFileTransactedA", "FindFirstStreamTransactedW", "FindFirstStreamW", "FindNextFileA", "FindNextFileNameW", "FindNextStreamW", "FlushFileBuffers", "FreeEncryptionCertificateHashList", "GetBinaryTypeA", "GetCompressedFileSizeA", "GetCompressedFileSizeTransactedA", "GetFileAttributesA", "GetFileAttributesExA", "GetFileAttributesTransactedA", "GetFileBandwidthReservation", "GetFileInformationByHandle", "GetFileInformationByHandleEx", "GetFileSize", "GetFileSizeEx", "GetFileType", "GetFinalPathNameByHandleA", "GetFullPathNameA", "GetFullPathNameTransactedA", "GetLongPathNameA", "GetLongPathNameTransactedA", "GetQueuedCompletionStatus", "GetShortPathNameW", "GetTempFileNameA", "GetTempPathA", "LockFile", "LockFileEx", "MoveFile", "MoveFileExA", "MoveFileTransactedA", "MoveFileWithProgressA", "OpenEncryptedFileRawA", "OpenFile", "OpenFileById", "QueryRecoveryAgentsOnEncryptedFile", "QueryUsersOnEncryptedFile", "ReadEncryptedFileRaw", "ReadFile", "ReadFileEx", "RemoveUsersFromEncryptedFile", "ReOpenFile", "ReplaceFileA", "SearchPathA", "SetEndOfFile", "SetFileApisToANSI", "SetFileApisToOEM", "SetFileAttributesA", "SetFileAttributesTransactedA", "SetFileBandwidthReservation", "SetFileCompletionNotificationModes", "SetFileInformationByHandle", "SetFileIoOverlappedRange", "SetFilePointer", "SetFilePointerEx", "SetFileShortNameA", "SetFileValidData", "SetSearchPathMode", "SetUserFileEncryptionKey", "UnlockFile", "UnlockFileEx", "Wow64DisableWow64FsRedirection", "Wow64EnableWow64FsRedirection", "Wow64RevertWow64FsRedirection", "WriteEncryptedFileRaw", "WriteFile", "WriteFileEx" };
	for (int i = { 0 }; i < sizeof(fs) / sizeof(fs[0]); ++i) {
		fs_functions.push_back(std::string(fs[i]));
	}
	char sock[][87] = { "accept", "bind", "closesocket", "connect", "gai_strerrorA", "gethostname", "getpeername", "getprotobyname", "getprotobynumber", "getservbyname", "getservbyport", "getsockname", "getsockopt", "htons", "inet_addr", "inet_ntoa", "InetNtopW", "InetPtonW", "ioctlsocket", "listen", "ntohl", "ntohs", "recv", "recvfrom", "select", "send", "sendto", "setsockopt", "shutdown", "socket", "WSAAccept", "WSAAddressToStringA", "WSAAsyncGetHostByAddr", "WSAAsyncGetHostByName", "WSAAsyncGetProtoByName", "WSAAsyncGetProtoByNumber", "WSAAsyncGetServByName", "WSAAsyncGetServByPort", "WSAAsyncSelect", "WSACancelAsyncRequest", "WSACleanup", "WSACloseEvent", "WSAConnect", "WSAConnectByList", "WSAConnectByNameA", "WSACreateEvent", "WSADuplicateSocketA", "WSAEnumNameSpaceProvidersA", "WSAEnumNameSpaceProvidersExA", "WSAEnumNetworkEvents", "WSAEnumProtocolsA", "WSAEventSelect", "__WSAFDIsSet", "WSAGetLastError", "WSAGetOverlappedResult", "WSAGetQOSByName", "WSAGetServiceClassInfoA", "WSAGetServiceClassNameByClassIdA", "WSAHtonl", "WSAHtons", "WSAInstallServiceClassA", "WSAIoctl", "WSAJoinLeaf", "WSALookupServiceBeginA", "WSALookupServiceEnd", "WSALookupServiceNextA", "WSANSPIoctl", "WSANtohl", "WSANtohs", "WSAPoll", "WSAProviderConfigChange", "WSARecv", "WSARecvDisconnect", "WSARecvFrom", "WSARemoveServiceClass", "WSAResetEvent", "WSASend", "WSASendDisconnect", "WSASendMsg", "WSASendTo", "WSASetEvent", "WSASetLastError", "WSASetServiceA", "WSASocketA", "WSAStartup", "WSAStringToAddressA", "WSAWaitForMultipleEvents" };
	for (int i{ 0 }; i < sizeof(sock) / sizeof(sock[0]); ++i) {
		sock_functions.push_back(std::string(sock[i]));
	}
	char reg[][55] = { "GetSystemRegistryQuota", "RegCloseKey", "RegConnectRegistryA", "RegCopyTreeA", "RegCreateKeyExA", "RegCreateKeyTransactedA", "RegDeleteKeyA", "RegDeleteKeyExA", "RegDeleteKeyTransactedA", "RegDeleteKeyValueA", "RegDeleteTreeA", "RegDeleteValueA", "RegDisablePredefinedCache", "RegDisablePredefinedCacheEx", "RegDisableReflectionKey", "RegEnableReflectionKey", "RegEnumKeyExA", "RegEnumValueA", "RegFlushKey", "RegGetKeySecurity", "RegGetValueA", "RegLoadKeyA", "RegLoadMUIStringA", "RegNotifyChangeKeyValue", "RegOpenCurrentUser", "RegOpenKeyExA", "RegOpenKeyTransactedA", "RegOpenUserClassesRoot", "RegOverridePredefKey", "RegQueryInfoKeyA", "RegQueryMultipleValuesA", "RegQueryReflectionKey", "RegQueryValueExA", "RegRenameKey", "RegReplaceKeyA", "RegRestoreKeyA", "RegSaveKeyA", "RegSaveKeyExA", "RegSetKeyValueA", "RegSetKeySecurity", "RegSetValueExA", "RegUnLoadKeyA", "GetPrivateProfileInt", "GetPrivateProfileSection", "GetPrivateProfileSectionNames", "GetPrivateProfileString", "GetPrivateProfileStruct", "GetProfileIntA", "GetProfileSectionA", "GetProfileStringA", "WritePrivateProfileSectionA", "WritePrivateProfileStringA", "WritePrivateProfileStructA", "WriteProfileSectionA", "WriteProfileStringA" };
	for (int i{ 0 }; i < sizeof(reg) / sizeof(reg[0]); ++i) {
		reg_functions.push_back(std::string(reg[i]));
	}
	std::cout << "got into DLL!!\n";
	void* f;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		//set_up_hook();
		Hook::set_up_vars();
		//mylog(msg, 49);
		functions = getFunctionsToHook();
		for (auto item : *functions) {
			std::cout << "got " << item << '\n';
		}
		std::cout << "my test is: " << WhatToDoInFunction("connect");
		deployInitialHook();
		Hook{ Hook::Functions::connect }.deploy_hook();
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return TRUE;
}