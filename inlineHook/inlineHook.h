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
char WhatToDoInFunction(char);
void log(std::string);

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
		if(myFncAdrr == nullptr){
			return;
		}
		memcpy_s(patch, 1, "\x68", 1);
		memcpy_s(patch + 1, 4, &myFncAdrr, 4);
		memcpy_s(patch + 5, 1, "\xC3", 1);

		WriteProcessMemory(GetCurrentProcess(), (LPVOID)hooked_addr[(int)func_to_hook], patch, 6, NULL);
	}


	Hook(Functions func) : func_to_hook{ func } {}

private:

	static std::string get_new_func_name(Functions func) {
		switch (func) {
		case Functions::AddUsersToEncryptedFile: return "AddUsersToEncryptedFile"; break;
		case Functions::AreFileApisANSI: return "AreFileApisANSI"; break;
		case Functions::CheckNameLegalDOS8Dot3A: return "CheckNameLegalDOS8Dot3A"; break;
		case Functions::CloseEncryptedFileRaw: return "CloseEncryptedFileRaw"; break;
		case Functions::CopyFile: return "CopyFile"; break;
		case Functions::CopyFile2: return "CopyFile2"; break;
		case Functions::CopyFileExA: return "CopyFileExA"; break;
		case Functions::CopyFileTransactedA: return "CopyFileTransactedA"; break;
		case Functions::CreateFileA: return "CreateFileA"; break;
		case Functions::CreateFile2: return "CreateFile2"; break;
		case Functions::CreateFileTransactedA: return "CreateFileTransactedA"; break;
		case Functions::CreateHardLinkA: return "CreateHardLinkA"; break;
		case Functions::CreateHardLinkTransactedA: return "CreateHardLinkTransactedA"; break;
		case Functions::CreateSymbolicLinkA: return "CreateSymbolicLinkA"; break;
		case Functions::CreateSymbolicLinkTransactedA: return "CreateSymbolicLinkTransactedA"; break;
		case Functions::DecryptFileA: return "DecryptFileA"; break;
		case Functions::DeleteFileA: return "DeleteFileA"; break;
		case Functions::DeleteFileTransactedA: return "DeleteFileTransactedA"; break;
		case Functions::DuplicateEncryptionInfoFile: return "DuplicateEncryptionInfoFile"; break;
		case Functions::EncryptFileA: return "EncryptFileA"; break;
		case Functions::EncryptionDisable: return "EncryptionDisable"; break;
		case Functions::FileEncryptionStatusA: return "FileEncryptionStatusA"; break;
		case Functions::FindClose: return "FindClose"; break;
		case Functions::FindFirstFileA: return "FindFirstFileA"; break;
		case Functions::FindFirstFileExA: return "FindFirstFileExA"; break;
		case Functions::FindFirstFileNameTransactedW: return "FindFirstFileNameTransactedW"; break;
		case Functions::FindFirstFileNameW: return "FindFirstFileNameW"; break;
		case Functions::FindFirstFileTransactedA: return "FindFirstFileTransactedA"; break;
		case Functions::FindFirstStreamTransactedW: return "FindFirstStreamTransactedW"; break;
		case Functions::FindFirstStreamW: return "FindFirstStreamW"; break;
		case Functions::FindNextFileA: return "FindNextFileA"; break;
		case Functions::FindNextFileNameW: return "FindNextFileNameW"; break;
		case Functions::FindNextStreamW: return "FindNextStreamW"; break;
		case Functions::FlushFileBuffers: return "FlushFileBuffers"; break;
		case Functions::FreeEncryptionCertificateHashList: return "FreeEncryptionCertificateHashList"; break;
		case Functions::GetBinaryTypeA: return "GetBinaryTypeA"; break;
		case Functions::GetCompressedFileSizeA: return "GetCompressedFileSizeA"; break;
		case Functions::GetCompressedFileSizeTransactedA: return "GetCompressedFileSizeTransactedA"; break;
		case Functions::GetExpandedNameA: return "GetExpandedNameA"; break;
		case Functions::GetFileAttributesA: return "GetFileAttributesA"; break;
		case Functions::GetFileAttributesExA: return "GetFileAttributesExA"; break;
		case Functions::GetFileAttributesTransactedA: return "GetFileAttributesTransactedA"; break;
		case Functions::GetFileBandwidthReservation: return "GetFileBandwidthReservation"; break;
		case Functions::GetFileInformationByHandle: return "GetFileInformationByHandle"; break;
		case Functions::GetFileInformationByHandleEx: return "GetFileInformationByHandleEx"; break;
		case Functions::GetFileSize: return "GetFileSize"; break;
		case Functions::GetFileSizeEx: return "GetFileSizeEx"; break;
		case Functions::GetFileType: return "GetFileType"; break;
		case Functions::GetFinalPathNameByHandleA: return "GetFinalPathNameByHandleA"; break;
		case Functions::GetFullPathNameA: return "GetFullPathNameA"; break;
		case Functions::GetFullPathNameTransactedA: return "GetFullPathNameTransactedA"; break;
		case Functions::GetLongPathNameA: return "GetLongPathNameA"; break;
		case Functions::GetLongPathNameTransactedA: return "GetLongPathNameTransactedA"; break;
		case Functions::GetQueuedCompletionStatus: return "GetQueuedCompletionStatus"; break;
		case Functions::GetShortPathNameW: return "GetShortPathNameW"; break;
		case Functions::GetTempFileNameA: return "GetTempFileNameA"; break;
		case Functions::GetTempPathA: return "GetTempPathA"; break;
		case Functions::LockFile: return "LockFile"; break;
		case Functions::LockFileEx: return "LockFileEx"; break;
		case Functions::LZClose: return "LZClose"; break;
		case Functions::LZCopy: return "LZCopy"; break;
		case Functions::LZInit: return "LZInit"; break;
		case Functions::LZOpenFileA: return "LZOpenFileA"; break;
		case Functions::LZRead: return "LZRead"; break;
		case Functions::LZSeek: return "LZSeek"; break;
		case Functions::MoveFile: return "MoveFile"; break;
		case Functions::MoveFileExA: return "MoveFileExA"; break;
		case Functions::MoveFileTransactedA: return "MoveFileTransactedA"; break;
		case Functions::MoveFileWithProgressA: return "MoveFileWithProgressA"; break;
		case Functions::OpenEncryptedFileRawA: return "OpenEncryptedFileRawA"; break;
		case Functions::OpenFile: return "OpenFile"; break;
		case Functions::OpenFileById: return "OpenFileById"; break;
		case Functions::QueryRecoveryAgentsOnEncryptedFile: return "QueryRecoveryAgentsOnEncryptedFile"; break;
		case Functions::QueryUsersOnEncryptedFile: return "QueryUsersOnEncryptedFile"; break;
		case Functions::ReadEncryptedFileRaw: return "ReadEncryptedFileRaw"; break;
		case Functions::ReadFile: return "ReadFile"; break;
		case Functions::ReadFileEx: return "ReadFileEx"; break;
		case Functions::RemoveUsersFromEncryptedFile: return "RemoveUsersFromEncryptedFile"; break;
		case Functions::ReOpenFile: return "ReOpenFile"; break;
		case Functions::ReplaceFileA: return "ReplaceFileA"; break;
		case Functions::SearchPathA: return "SearchPathA"; break;
		case Functions::SetEndOfFile: return "SetEndOfFile"; break;
		case Functions::SetFileApisToANSI: return "SetFileApisToANSI"; break;
		case Functions::SetFileApisToOEM: return "SetFileApisToOEM"; break;
		case Functions::SetFileAttributesA: return "SetFileAttributesA"; break;
		case Functions::SetFileAttributesTransactedA: return "SetFileAttributesTransactedA"; break;
		case Functions::SetFileBandwidthReservation: return "SetFileBandwidthReservation"; break;
		case Functions::SetFileCompletionNotificationModes: return "SetFileCompletionNotificationModes"; break;
		case Functions::SetFileInformationByHandle: return "SetFileInformationByHandle"; break;
		case Functions::SetFileIoOverlappedRange: return "SetFileIoOverlappedRange"; break;
		case Functions::SetFilePointer: return "SetFilePointer"; break;
		case Functions::SetFilePointerEx: return "SetFilePointerEx"; break;
		case Functions::SetFileShortNameA: return "SetFileShortNameA"; break;
		case Functions::SetFileValidData: return "SetFileValidData"; break;
		case Functions::SetSearchPathMode: return "SetSearchPathMode"; break;
		case Functions::SetUserFileEncryptionKey: return "SetUserFileEncryptionKey"; break;
		case Functions::UnlockFile: return "UnlockFile"; break;
		case Functions::UnlockFileEx: return "UnlockFileEx"; break;
		case Functions::Wofenumfilesproc: return "Wofenumfilesproc"; break;
		case Functions::WofGetDriverVersion: return "WofGetDriverVersion"; break;
		case Functions::WofIsExternalFile: return "WofIsExternalFile"; break;
		case Functions::WofSetFileDataLocation: return "WofSetFileDataLocation"; break;
		case Functions::WofShouldCompressBinaries: return "WofShouldCompressBinaries"; break;
		case Functions::WofWimAddEntry: return "WofWimAddEntry"; break;
		case Functions::WofWimRemoveEntry: return "WofWimRemoveEntry"; break;
		case Functions::WofWimSuspendEntry: return "WofWimSuspendEntry"; break;
		case Functions::WofWimUpdateEntry: return "WofWimUpdateEntry"; break;
		case Functions::Wow64DisableWow64FsRedirection: return "Wow64DisableWow64FsRedirection"; break;
		case Functions::Wow64EnableWow64FsRedirection: return "Wow64EnableWow64FsRedirection"; break;
		case Functions::Wow64RevertWow64FsRedirection: return "Wow64RevertWow64FsRedirection"; break;
		case Functions::WriteEncryptedFileRaw: return "WriteEncryptedFileRaw"; break;
		case Functions::WriteFile: return "WriteFile"; break;
		case Functions::WriteFileEx: return "WriteFileEx"; break;
		case Functions::accept: return "accept"; break;
		case Functions::AcceptEx: return "AcceptEx"; break;
		case Functions::bind: return "bind"; break;
		case Functions::closesocket: return "closesocket"; break;
		case Functions::connect: return "connect"; break;
		case Functions::LpfnConnectex: return "LpfnConnectex"; break;
		case Functions::DisconnectEx: return "DisconnectEx"; break;
		case Functions::EnumProtocolsA: return "EnumProtocolsA"; break;
		case Functions::freeaddrinfo: return "freeaddrinfo"; break;
		case Functions::FreeAddrInfoEx: return "FreeAddrInfoEx"; break;
		case Functions::FreeAddrInfoW: return "FreeAddrInfoW"; break;
		case Functions::gai_strerrorA: return "gai_strerrorA"; break;
		case Functions::GetAcceptExSockaddrs: return "GetAcceptExSockaddrs"; break;
		case Functions::GetAddressByNameA: return "GetAddressByNameA"; break;
		case Functions::getaddrinfo: return "getaddrinfo"; break;
		case Functions::GetAddrInfoExA: return "GetAddrInfoExA"; break;
		case Functions::GetAddrInfoExCancel: return "GetAddrInfoExCancel"; break;
		case Functions::GetAddrInfoExOverlappedResult: return "GetAddrInfoExOverlappedResult"; break;
		case Functions::GetAddrInfoW: return "GetAddrInfoW"; break;
		case Functions::gethostname: return "gethostname"; break;
		case Functions::GetHostNameW: return "GetHostNameW"; break;
		case Functions::getipv4sourcefilter: return "getipv4sourcefilter"; break;
		case Functions::GetNameByTypeA: return "GetNameByTypeA"; break;
		case Functions::getnameinfo: return "getnameinfo"; break;
		case Functions::GetNameInfoW: return "GetNameInfoW"; break;
		case Functions::getpeername: return "getpeername"; break;
		case Functions::getprotobyname: return "getprotobyname"; break;
		case Functions::getprotobynumber: return "getprotobynumber"; break;
		case Functions::getservbyname: return "getservbyname"; break;
		case Functions::getservbyport: return "getservbyport"; break;
		case Functions::GetServiceA: return "GetServiceA"; break;
		case Functions::getsockname: return "getsockname"; break;
		case Functions::getsockopt: return "getsockopt"; break;
		case Functions::getsourcefilter: return "getsourcefilter"; break;
		case Functions::GetTypeByNameA: return "GetTypeByNameA"; break;
		case Functions::htons: return "htons"; break;
		case Functions::inet_addr: return "inet_addr"; break;
		case Functions::inet_ntoa: return "inet_ntoa"; break;
		case Functions::InetNtopW: return "InetNtopW"; break;
		case Functions::InetPtonW: return "InetPtonW"; break;
		case Functions::ioctlsocket: return "ioctlsocket"; break;
		case Functions::listen: return "listen"; break;
		case Functions::ntohd: return "ntohd"; break;
		case Functions::ntohf: return "ntohf"; break;
		case Functions::ntohl: return "ntohl"; break;
		case Functions::ntohs: return "ntohs"; break;
		case Functions::recv: return "recv"; break;
		case Functions::recvfrom: return "recvfrom"; break;
		case Functions::select: return "select"; break;
		case Functions::send: return "send"; break;
		case Functions::sendto: return "sendto"; break;
		case Functions::SetAddrInfoExA: return "SetAddrInfoExA"; break;
		case Functions::setipv4sourcefilter: return "setipv4sourcefilter"; break;
		case Functions::SetServiceA: return "SetServiceA"; break;
		case Functions::SetSocketMediaStreamingMode: return "SetSocketMediaStreamingMode"; break;
		case Functions::setsockopt: return "setsockopt"; break;
		case Functions::setsourcefilter: return "setsourcefilter"; break;
		case Functions::shutdown: return "shutdown"; break;
		case Functions::socket: return "socket"; break;
		case Functions::TransmitFile: return "TransmitFile"; break;
		case Functions::LpfnTransmitpackets: return "LpfnTransmitpackets"; break;
		case Functions::WSAAccept: return "WSAAccept"; break;
		case Functions::WSAAddressToStringA: return "WSAAddressToStringA"; break;
		case Functions::WSAAsyncGetHostByAddr: return "WSAAsyncGetHostByAddr"; break;
		case Functions::WSAAsyncGetHostByName: return "WSAAsyncGetHostByName"; break;
		case Functions::WSAAsyncGetProtoByName: return "WSAAsyncGetProtoByName"; break;
		case Functions::WSAAsyncGetProtoByNumber: return "WSAAsyncGetProtoByNumber"; break;
		case Functions::WSAAsyncGetServByName: return "WSAAsyncGetServByName"; break;
		case Functions::WSAAsyncGetServByPort: return "WSAAsyncGetServByPort"; break;
		case Functions::WSAAsyncSelect: return "WSAAsyncSelect"; break;
		case Functions::WSACancelAsyncRequest: return "WSACancelAsyncRequest"; break;
		case Functions::WSACleanup: return "WSACleanup"; break;
		case Functions::WSACloseEvent: return "WSACloseEvent"; break;
		case Functions::WSAConnect: return "WSAConnect"; break;
		case Functions::WSAConnectByList: return "WSAConnectByList"; break;
		case Functions::WSAConnectByNameA: return "WSAConnectByNameA"; break;
		case Functions::WSACreateEvent: return "WSACreateEvent"; break;
		case Functions::WSADeleteSocketPeerTargetName: return "WSADeleteSocketPeerTargetName"; break;
		case Functions::WSADuplicateSocketA: return "WSADuplicateSocketA"; break;
		case Functions::WSAEnumNameSpaceProvidersA: return "WSAEnumNameSpaceProvidersA"; break;
		case Functions::WSAEnumNameSpaceProvidersExA: return "WSAEnumNameSpaceProvidersExA"; break;
		case Functions::WSAEnumNetworkEvents: return "WSAEnumNetworkEvents"; break;
		case Functions::WSAEnumProtocolsA: return "WSAEnumProtocolsA"; break;
		case Functions::WSAEventSelect: return "WSAEventSelect"; break;
		case Functions::__WSAFDIsSet: return "__WSAFDIsSet"; break;
		case Functions::WSAGetFailConnectOnIcmpError: return "WSAGetFailConnectOnIcmpError"; break;
		case Functions::WSAGetIcmpErrorInfo: return "WSAGetIcmpErrorInfo"; break;
		case Functions::WSAGetIPUserMtu: return "WSAGetIPUserMtu"; break;
		case Functions::WSAGetLastError: return "WSAGetLastError"; break;
		case Functions::WSAGetOverlappedResult: return "WSAGetOverlappedResult"; break;
		case Functions::WSAGetQOSByName: return "WSAGetQOSByName"; break;
		case Functions::WSAGetServiceClassInfoA: return "WSAGetServiceClassInfoA"; break;
		case Functions::WSAGetServiceClassNameByClassIdA: return "WSAGetServiceClassNameByClassIdA"; break;
		case Functions::WSAGetUdpRecvMaxCoalescedSize: return "WSAGetUdpRecvMaxCoalescedSize"; break;
		case Functions::WSAGetUdpSendMessageSize: return "WSAGetUdpSendMessageSize"; break;
		case Functions::WSAHtonl: return "WSAHtonl"; break;
		case Functions::WSAHtons: return "WSAHtons"; break;
		case Functions::WSAImpersonateSocketPeer: return "WSAImpersonateSocketPeer"; break;
		case Functions::WSAInstallServiceClassA: return "WSAInstallServiceClassA"; break;
		case Functions::WSAIoctl: return "WSAIoctl"; break;
		case Functions::WSAJoinLeaf: return "WSAJoinLeaf"; break;
		case Functions::WSALookupServiceBeginA: return "WSALookupServiceBeginA"; break;
		case Functions::WSALookupServiceEnd: return "WSALookupServiceEnd"; break;
		case Functions::WSALookupServiceNextA: return "WSALookupServiceNextA"; break;
		case Functions::WSANSPIoctl: return "WSANSPIoctl"; break;
		case Functions::WSANtohl: return "WSANtohl"; break;
		case Functions::WSANtohs: return "WSANtohs"; break;
		case Functions::WSAPoll: return "WSAPoll"; break;
		case Functions::WSAProviderConfigChange: return "WSAProviderConfigChange"; break;
		case Functions::WSARecv: return "WSARecv"; break;
		case Functions::WSARecvDisconnect: return "WSARecvDisconnect"; break;
		case Functions::WSARecvEx: return "WSARecvEx"; break;
		case Functions::WSARecvFrom: return "WSARecvFrom"; break;
		case Functions::WSARemoveServiceClass: return "WSARemoveServiceClass"; break;
		case Functions::WSAResetEvent: return "WSAResetEvent"; break;
		case Functions::WSARevertImpersonation: return "WSARevertImpersonation"; break;
		case Functions::WSASend: return "WSASend"; break;
		case Functions::WSASendDisconnect: return "WSASendDisconnect"; break;
		case Functions::WSASendMsg: return "WSASendMsg"; break;
		case Functions::WSASendTo: return "WSASendTo"; break;
		case Functions::WSASetEvent: return "WSASetEvent"; break;
		case Functions::WSASetFailConnectOnIcmpError: return "WSASetFailConnectOnIcmpError"; break;
		case Functions::WSASetIPUserMtu: return "WSASetIPUserMtu"; break;
		case Functions::WSASetLastError: return "WSASetLastError"; break;
		case Functions::WSASetServiceA: return "WSASetServiceA"; break;
		case Functions::WSASetUdpRecvMaxCoalescedSize: return "WSASetUdpRecvMaxCoalescedSize"; break;
		case Functions::WSASetUdpSendMessageSize: return "WSASetUdpSendMessageSize"; break;
		case Functions::WSASocketA: return "WSASocketA"; break;
		case Functions::WSAStartup: return "WSAStartup"; break;
		case Functions::WSAStringToAddressA: return "WSAStringToAddressA"; break;
		case Functions::WSAWaitForMultipleEvents: return "WSAWaitForMultipleEvents"; break;
		case Functions::GetSystemRegistryQuota: return "GetSystemRegistryQuota"; break;
		case Functions::RegCloseKey: return "RegCloseKey"; break;
		case Functions::RegConnectRegistryA: return "RegConnectRegistryA"; break;
		case Functions::RegCopyTreeA: return "RegCopyTreeA"; break;
		case Functions::RegCreateKeyExA: return "RegCreateKeyExA"; break;
		case Functions::RegCreateKeyTransactedA: return "RegCreateKeyTransactedA"; break;
		case Functions::RegDeleteKeyA: return "RegDeleteKeyA"; break;
		case Functions::RegDeleteKeyExA: return "RegDeleteKeyExA"; break;
		case Functions::RegDeleteKeyTransactedA: return "RegDeleteKeyTransactedA"; break;
		case Functions::RegDeleteKeyValueA: return "RegDeleteKeyValueA"; break;
		case Functions::RegDeleteTreeA: return "RegDeleteTreeA"; break;
		case Functions::RegDeleteValueA: return "RegDeleteValueA"; break;
		case Functions::RegDisablePredefinedCache: return "RegDisablePredefinedCache"; break;
		case Functions::RegDisablePredefinedCacheEx: return "RegDisablePredefinedCacheEx"; break;
		case Functions::RegDisableReflectionKey: return "RegDisableReflectionKey"; break;
		case Functions::RegEnableReflectionKey: return "RegEnableReflectionKey"; break;
		case Functions::RegEnumKeyExA: return "RegEnumKeyExA"; break;
		case Functions::RegEnumValueA: return "RegEnumValueA"; break;
		case Functions::RegFlushKey: return "RegFlushKey"; break;
		case Functions::RegGetKeySecurity: return "RegGetKeySecurity"; break;
		case Functions::RegGetValueA: return "RegGetValueA"; break;
		case Functions::RegLoadKeyA: return "RegLoadKeyA"; break;
		case Functions::RegLoadMUIStringA: return "RegLoadMUIStringA"; break;
		case Functions::RegNotifyChangeKeyValue: return "RegNotifyChangeKeyValue"; break;
		case Functions::RegOpenCurrentUser: return "RegOpenCurrentUser"; break;
		case Functions::RegOpenKeyExA: return "RegOpenKeyExA"; break;
		case Functions::RegOpenKeyTransactedA: return "RegOpenKeyTransactedA"; break;
		case Functions::RegOpenUserClassesRoot: return "RegOpenUserClassesRoot"; break;
		case Functions::RegOverridePredefKey: return "RegOverridePredefKey"; break;
		case Functions::RegQueryInfoKeyA: return "RegQueryInfoKeyA"; break;
		case Functions::RegQueryMultipleValuesA: return "RegQueryMultipleValuesA"; break;
		case Functions::RegQueryReflectionKey: return "RegQueryReflectionKey"; break;
		case Functions::RegQueryValueExA: return "RegQueryValueExA"; break;
		case Functions::RegRenameKey: return "RegRenameKey"; break;
		case Functions::RegReplaceKeyA: return "RegReplaceKeyA"; break;
		case Functions::RegRestoreKeyA: return "RegRestoreKeyA"; break;
		case Functions::RegSaveKeyA: return "RegSaveKeyA"; break;
		case Functions::RegSaveKeyExA: return "RegSaveKeyExA"; break;
		case Functions::RegSetKeyValueA: return "RegSetKeyValueA"; break;
		case Functions::RegSetKeySecurity: return "RegSetKeySecurity"; break;
		case Functions::RegSetValueExA: return "RegSetValueExA"; break;
		case Functions::RegUnLoadKeyA: return "RegUnLoadKeyA"; break;
		case Functions::GetPrivateProfileInt: return "GetPrivateProfileInt"; break;
		case Functions::GetPrivateProfileSection: return "GetPrivateProfileSection"; break;
		case Functions::GetPrivateProfileSectionNames: return "GetPrivateProfileSectionNames"; break;
		case Functions::GetPrivateProfileString: return "GetPrivateProfileString"; break;
		case Functions::GetPrivateProfileStruct: return "GetPrivateProfileStruct"; break;
		case Functions::GetProfileIntA: return "GetProfileIntA"; break;
		case Functions::GetProfileSectionA: return "GetProfileSectionA"; break;
		case Functions::GetProfileStringA: return "GetProfileStringA"; break;
		case Functions::WritePrivateProfileSectionA: return "WritePrivateProfileSectionA"; break;
		case Functions::WritePrivateProfileStringA: return "WritePrivateProfileStringA"; break;
		case Functions::WritePrivateProfileStructA: return "WritePrivateProfileStructA"; break;
		case Functions::WriteProfileSectionA: return "WriteProfileSectionA"; break;
		case Functions::WriteProfileStringA: return "WriteProfileStringA"; break;
		}
	}

	void* get_new_fnc_pointer();

};
