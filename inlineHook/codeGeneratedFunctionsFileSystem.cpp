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
#include "newFunctions.h"
#include <cstring>
#include <sstream>
#include <time.h>

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;

extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

extern HANDLE LOGfile;
extern bool IsMyCall;

namespace newFunctions {

DWORD __stdcall newAddUsersToEncryptedFile(
  [in] LPCWSTR                      lpFileName,
  [in] PENCRYPTION_CERTIFICATE_LIST pEncryptionCertificates
){
    	//unhook AddUsersToEncryptedFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::AddUsersToEncryptedFile],
		original_bytes[(int)Hook::Functions::AddUsersToEncryptedFile], 6, NULL);

    DWORD result = AddUsersToEncryptedFile(lpFileName,pEncryptionCertificates
);
    Hook reset_hook { Hook::Functions::AddUsersToEncryptedFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newAreFileApisANSI(){
    	//unhook AreFileApisANSItion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::AreFileApisANSI],
		original_bytes[(int)Hook::Functions::AreFileApisANSI], 6, NULL);

    BOOL result = AreFileApisANSI();
    Hook reset_hook { Hook::Functions::AreFileApisANSI};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newCheckNameLegalDOS8Dot3A(
  [in]            LPCSTR lpName,
  [out, optional] LPSTR  lpOemName,
  [in]            DWORD  OemNameSize,
  [out, optional] PBOOL  pbNameContainsSpaces,
  [out]           PBOOL  pbNameLegal
){
    	//unhook CheckNameLegalDOS8Dot3Ation
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CheckNameLegalDOS8Dot3A],
		original_bytes[(int)Hook::Functions::CheckNameLegalDOS8Dot3A], 6, NULL);

    BOOL result = CheckNameLegalDOS8Dot3A(lpName,lpOemName,OemNameSize,pbNameContainsSpaces,pbNameLegal
);
    Hook reset_hook { Hook::Functions::CheckNameLegalDOS8Dot3A};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
void __stdcall newCloseEncryptedFileRaw(
  [in] PVOID pvContext
){
    	//unhook CloseEncryptedFileRawtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CloseEncryptedFileRaw],
		original_bytes[(int)Hook::Functions::CloseEncryptedFileRaw], 6, NULL);

    CloseEncryptedFileRaw(pvContext
);
    Hook reset_hook { Hook::Functions::CloseEncryptedFileRaw};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newCopyFile(
  [in] LPCTSTR lpExistingFileName,
  [in] LPCTSTR lpNewFileName,
  [in] BOOL    bFailIfExists
){
    	//unhook CopyFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CopyFile],
		original_bytes[(int)Hook::Functions::CopyFile], 6, NULL);

    BOOL result = CopyFile(lpExistingFileName,lpNewFileName,bFailIfExists
);
    Hook reset_hook { Hook::Functions::CopyFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HRESULT __stdcall newCopyFile2(
  [in]           PCWSTR                        pwszExistingFileName,
  [in]           PCWSTR                        pwszNewFileName,
  [in, optional] COPYFILE2_EXTENDED_PARAMETERS *pExtendedParameters
){
    	//unhook CopyFile2tion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CopyFile2],
		original_bytes[(int)Hook::Functions::CopyFile2], 6, NULL);

    HRESULT result = CopyFile2(pwszExistingFileName,pwszNewFileName,pExtendedParameters
);
    Hook reset_hook { Hook::Functions::CopyFile2};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}

BOOL __stdcall newCopyFileExA(
  [in]           LPCSTR             lpExistingFileName,
  [in]           LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in, optional] LPBOOL             pbCancel,
  [in]           DWORD              dwCopyFlags
){
    	//unhook CopyFileExAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CopyFileExA],
		original_bytes[(int)Hook::Functions::CopyFileExA], 6, NULL);

    BOOL result = CopyFileExA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,pbCancel,dwCopyFlags
);
    Hook reset_hook { Hook::Functions::CopyFileExA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newCopyFileTransactedA(
  [in]           LPCSTR             lpExistingFileName,
  [in]           LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in, optional] LPBOOL             pbCancel,
  [in]           DWORD              dwCopyFlags,
  [in]           HANDLE             hTransaction
){
    	//unhook CopyFileTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CopyFileTransactedA],
		original_bytes[(int)Hook::Functions::CopyFileTransactedA], 6, NULL);

    BOOL result = CopyFileTransactedA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,pbCancel,dwCopyFlags,hTransaction
);
    Hook reset_hook { Hook::Functions::CopyFileTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}

HANDLE __stdcall newCreateFileA(
  [in]           LPCSTR                lpFileName,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwCreationDisposition,
  [in]           DWORD                 dwFlagsAndAttributes,
  [in, optional] HANDLE                hTemplateFile
){
    	//unhook CreateFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateFileA],
		original_bytes[(int)Hook::Functions::CreateFileA], 6, NULL);

    HANDLE result = CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile
);
    Hook reset_hook { Hook::Functions::CreateFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newCreateFile2(
  [in]           LPCWSTR                           lpFileName,
  [in]           DWORD                             dwDesiredAccess,
  [in]           DWORD                             dwShareMode,
  [in]           DWORD                             dwCreationDisposition,
  [in, optional] LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams
){
    	//unhook CreateFile2tion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateFile2],
		original_bytes[(int)Hook::Functions::CreateFile2], 6, NULL);

    HANDLE result = CreateFile2(lpFileName,dwDesiredAccess,dwShareMode,dwCreationDisposition,pCreateExParams
);
    Hook reset_hook { Hook::Functions::CreateFile2};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newCreateFileTransactedA(
  [in]           LPCSTR                lpFileName,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwCreationDisposition,
  [in]           DWORD                 dwFlagsAndAttributes,
  [in, optional] HANDLE                hTemplateFile,
  [in]           HANDLE                hTransaction,
  [in, optional] PUSHORT               pusMiniVersion,
                 PVOID                 lpExtendedParameter
){
    	//unhook CreateFileTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateFileTransactedA],
		original_bytes[(int)Hook::Functions::CreateFileTransactedA], 6, NULL);

    HANDLE result = CreateFileTransactedA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile,hTransaction,pusMiniVersion,lpExtendedParameter
);
    Hook reset_hook { Hook::Functions::CreateFileTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newCreateHardLinkA(
  [in] LPCSTR                lpFileName,
  [in] LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes
){
    	//unhook CreateHardLinkAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateHardLinkA],
		original_bytes[(int)Hook::Functions::CreateHardLinkA], 6, NULL);

    BOOL result = CreateHardLinkA(lpFileName,lpExistingFileName,lpSecurityAttributes
);
    Hook reset_hook { Hook::Functions::CreateHardLinkA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newCreateHardLinkTransactedA(
  [in] LPCSTR                lpFileName,
  [in] LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in] HANDLE                hTransaction
){
    	//unhook CreateHardLinkTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateHardLinkTransactedA],
		original_bytes[(int)Hook::Functions::CreateHardLinkTransactedA], 6, NULL);

    BOOL result = CreateHardLinkTransactedA(lpFileName,lpExistingFileName,lpSecurityAttributes,hTransaction
);
    Hook reset_hook { Hook::Functions::CreateHardLinkTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOLEAN __stdcall newCreateSymbolicLinkA(
  [in] LPCSTR lpSymlinkFileName,
  [in] LPCSTR lpTargetFileName,
  [in] DWORD  dwFlags
){
    	//unhook CreateSymbolicLinkAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateSymbolicLinkA],
		original_bytes[(int)Hook::Functions::CreateSymbolicLinkA], 6, NULL);

    BOOLEAN result = CreateSymbolicLinkA(lpSymlinkFileName,lpTargetFileName,dwFlags
);
    Hook reset_hook { Hook::Functions::CreateSymbolicLinkA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOLEAN __stdcall newCreateSymbolicLinkTransactedA(
  [in] LPCSTR lpSymlinkFileName,
  [in] LPCSTR lpTargetFileName,
  [in] DWORD  dwFlags,
  [in] HANDLE hTransaction
){
    	//unhook CreateSymbolicLinkTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::CreateSymbolicLinkTransactedA],
		original_bytes[(int)Hook::Functions::CreateSymbolicLinkTransactedA], 6, NULL);

    BOOLEAN result = CreateSymbolicLinkTransactedA(lpSymlinkFileName,lpTargetFileName,dwFlags,hTransaction
);
    Hook reset_hook { Hook::Functions::CreateSymbolicLinkTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newDecryptFileA(
  [in] LPCSTR lpFileName,
       DWORD  dwReserved
){
    	//unhook DecryptFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::DecryptFileA],
		original_bytes[(int)Hook::Functions::DecryptFileA], 6, NULL);

    BOOL result = DecryptFileA(lpFileName,dwReserved
);
    Hook reset_hook { Hook::Functions::DecryptFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newDeleteFileA(
  [in] LPCSTR lpFileName
){
    	//unhook DeleteFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileA],
		original_bytes[(int)Hook::Functions::DeleteFileA], 6, NULL);

    BOOL result = DeleteFileA(lpFileName
);
    Hook reset_hook { Hook::Functions::DeleteFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newDeleteFileTransactedA(
  [in] LPCSTR lpFileName,
  [in] HANDLE hTransaction
){
    	//unhook DeleteFileTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileTransactedA],
		original_bytes[(int)Hook::Functions::DeleteFileTransactedA], 6, NULL);

    BOOL result = DeleteFileTransactedA(lpFileName,hTransaction
);
    Hook reset_hook { Hook::Functions::DeleteFileTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newDuplicateEncryptionInfoFile(
  [in]           LPCWSTR                     SrcFileName,
  [in]           LPCWSTR                     DstFileName,
  [in]           DWORD                       dwCreationDistribution,
  [in]           DWORD                       dwAttributes,
  [in, optional] const LPSECURITY_ATTRIBUTES lpSecurityAttributes
){
    	//unhook DuplicateEncryptionInfoFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::DuplicateEncryptionInfoFile],
		original_bytes[(int)Hook::Functions::DuplicateEncryptionInfoFile], 6, NULL);

    DWORD result = DuplicateEncryptionInfoFile(SrcFileName,DstFileName,dwCreationDistribution,dwAttributes,lpSecurityAttributes
);
    Hook reset_hook { Hook::Functions::DuplicateEncryptionInfoFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newEncryptFileA(
  [in] LPCSTR lpFileName
){
    	//unhook EncryptFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::EncryptFileA],
		original_bytes[(int)Hook::Functions::EncryptFileA], 6, NULL);

    BOOL result = EncryptFileA(lpFileName
);
    Hook reset_hook { Hook::Functions::EncryptFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newEncryptionDisable(
  [in] LPCWSTR DirPath,
  [in] BOOL    Disable
){
    	//unhook EncryptionDisabletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::EncryptionDisable],
		original_bytes[(int)Hook::Functions::EncryptionDisable], 6, NULL);

    BOOL result = EncryptionDisable(DirPath,Disable
);
    Hook reset_hook { Hook::Functions::EncryptionDisable};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}

BOOL __stdcall newFileEncryptionStatusA(
  [in]  LPCSTR  lpFileName,
  [out] LPDWORD lpStatus
){
    	//unhook FileEncryptionStatusAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FileEncryptionStatusA],
		original_bytes[(int)Hook::Functions::FileEncryptionStatusA], 6, NULL);

    BOOL result = FileEncryptionStatusA(lpFileName,lpStatus
);
    Hook reset_hook { Hook::Functions::FileEncryptionStatusA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}

BOOL __stdcall newFindClose(
  [in, out] HANDLE hFindFile
){
    	//unhook FindClosetion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindClose],
		original_bytes[(int)Hook::Functions::FindClose], 6, NULL);

    BOOL result = FindClose(hFindFile
);
    Hook reset_hook { Hook::Functions::FindClose};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstFileA(
  [in]  LPCSTR             lpFileName,
  [out] LPWIN32_FIND_DATAA lpFindFileData
){
    	//unhook FindFirstFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileA],
		original_bytes[(int)Hook::Functions::FindFirstFileA], 6, NULL);

    HANDLE result = FindFirstFileA(lpFileName,lpFindFileData
);
    Hook reset_hook { Hook::Functions::FindFirstFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstFileExA(
  [in]  LPCSTR             lpFileName,
  [in]  FINDEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID             lpFindFileData,
  [in]  FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
  [in]  DWORD              dwAdditionalFlags
){
    	//unhook FindFirstFileExAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileExA],
		original_bytes[(int)Hook::Functions::FindFirstFileExA], 6, NULL);

    HANDLE result = FindFirstFileExA(lpFileName,fInfoLevelId,lpFindFileData,fSearchOp,lpSearchFilter,dwAdditionalFlags
);
    Hook reset_hook { Hook::Functions::FindFirstFileExA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstFileNameTransactedW(
  [in]           LPCWSTR lpFileName,
  [in]           DWORD   dwFlags,
  [in, out]      LPDWORD StringLength,
  [in, out]      PWSTR   LinkName,
  [in, optional] HANDLE  hTransaction
){
    	//unhook FindFirstFileNameTransactedWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileNameTransactedW],
		original_bytes[(int)Hook::Functions::FindFirstFileNameTransactedW], 6, NULL);

    HANDLE result = FindFirstFileNameTransactedW(lpFileName,dwFlags,StringLength,LinkName,hTransaction
);
    Hook reset_hook { Hook::Functions::FindFirstFileNameTransactedW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstFileNameW(
  [in]      LPCWSTR lpFileName,
  [in]      DWORD   dwFlags,
  [in, out] LPDWORD StringLength,
  [in, out] PWSTR   LinkName
){
    	//unhook FindFirstFileNameWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileNameW],
		original_bytes[(int)Hook::Functions::FindFirstFileNameW], 6, NULL);

    HANDLE result = FindFirstFileNameW(lpFileName,dwFlags,StringLength,LinkName
);
    Hook reset_hook { Hook::Functions::FindFirstFileNameW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstFileTransactedA(
  [in]  LPCSTR             lpFileName,
  [in]  FINDEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID             lpFindFileData,
  [in]  FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
  [in]  DWORD              dwAdditionalFlags,
  [in]  HANDLE             hTransaction
){
    	//unhook FindFirstFileTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileTransactedA],
		original_bytes[(int)Hook::Functions::FindFirstFileTransactedA], 6, NULL);

    HANDLE result = FindFirstFileTransactedA(lpFileName,fInfoLevelId,lpFindFileData,fSearchOp,lpSearchFilter,dwAdditionalFlags,hTransaction
);
    Hook reset_hook { Hook::Functions::FindFirstFileTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstStreamTransactedW(
  [in]  LPCWSTR            lpFileName,
  [in]  STREAM_INFO_LEVELS InfoLevel,
  [out] LPVOID             lpFindStreamData,
        DWORD              dwFlags,
  [in]  HANDLE             hTransaction
){
    	//unhook FindFirstStreamTransactedWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstStreamTransactedW],
		original_bytes[(int)Hook::Functions::FindFirstStreamTransactedW], 6, NULL);

    HANDLE result = FindFirstStreamTransactedW(lpFileName,InfoLevel,lpFindStreamData,dwFlags,hTransaction
);
    Hook reset_hook { Hook::Functions::FindFirstStreamTransactedW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newFindFirstStreamW(
  [in]  LPCWSTR            lpFileName,
  [in]  STREAM_INFO_LEVELS InfoLevel,
  [out] LPVOID             lpFindStreamData,
        DWORD              dwFlags
){
    	//unhook FindFirstStreamWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindFirstStreamW],
		original_bytes[(int)Hook::Functions::FindFirstStreamW], 6, NULL);

    HANDLE result = FindFirstStreamW(lpFileName,InfoLevel,lpFindStreamData,dwFlags
);
    Hook reset_hook { Hook::Functions::FindFirstStreamW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newFindNextFileA(
  [in]  HANDLE             hFindFile,
  [out] LPWIN32_FIND_DATAA lpFindFileData
){
    	//unhook FindNextFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindNextFileA],
		original_bytes[(int)Hook::Functions::FindNextFileA], 6, NULL);

    BOOL result = FindNextFileA(hFindFile,lpFindFileData
);
    Hook reset_hook { Hook::Functions::FindNextFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newFindNextFileNameW(
  [in]      HANDLE  hFindStream,
  [in, out] LPDWORD StringLength,
  [in, out] PWSTR   LinkName
){
    	//unhook FindNextFileNameWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindNextFileNameW],
		original_bytes[(int)Hook::Functions::FindNextFileNameW], 6, NULL);

    BOOL result = FindNextFileNameW(hFindStream,StringLength,LinkName
);
    Hook reset_hook { Hook::Functions::FindNextFileNameW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newFindNextStreamW(
  [in]  HANDLE hFindStream,
  [out] LPVOID lpFindStreamData
){
    	//unhook FindNextStreamWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FindNextStreamW],
		original_bytes[(int)Hook::Functions::FindNextStreamW], 6, NULL);

    BOOL result = FindNextStreamW(hFindStream,lpFindStreamData
);
    Hook reset_hook { Hook::Functions::FindNextStreamW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newFlushFileBuffers(
  [in] HANDLE hFile
){
    	//unhook FlushFileBufferstion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FlushFileBuffers],
		original_bytes[(int)Hook::Functions::FlushFileBuffers], 6, NULL);

    BOOL result = FlushFileBuffers(hFile
);
    Hook reset_hook { Hook::Functions::FlushFileBuffers};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
void __stdcall newFreeEncryptionCertificateHashList(
  [in] PENCRYPTION_CERTIFICATE_HASH_LIST pUsers
){
    	//unhook FreeEncryptionCertificateHashListtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::FreeEncryptionCertificateHashList],
		original_bytes[(int)Hook::Functions::FreeEncryptionCertificateHashList], 6, NULL);

    FreeEncryptionCertificateHashList(pUsers
);
    Hook reset_hook { Hook::Functions::FreeEncryptionCertificateHashList};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetBinaryTypeA(
  [in]  LPCSTR  lpApplicationName,
  [out] LPDWORD lpBinaryType
){
    	//unhook GetBinaryTypeAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetBinaryTypeA],
		original_bytes[(int)Hook::Functions::GetBinaryTypeA], 6, NULL);

    BOOL result = GetBinaryTypeA(lpApplicationName,lpBinaryType
);
    Hook reset_hook { Hook::Functions::GetBinaryTypeA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetCompressedFileSizeA(
  [in]            LPCSTR  lpFileName,
  [out, optional] LPDWORD lpFileSizeHigh
){
    	//unhook GetCompressedFileSizeAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetCompressedFileSizeA],
		original_bytes[(int)Hook::Functions::GetCompressedFileSizeA], 6, NULL);

    DWORD result = GetCompressedFileSizeA(lpFileName,lpFileSizeHigh
);
    Hook reset_hook { Hook::Functions::GetCompressedFileSizeA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetCompressedFileSizeTransactedA(
  [in]            LPCSTR  lpFileName,
  [out, optional] LPDWORD lpFileSizeHigh,
  [in]            HANDLE  hTransaction
){
    	//unhook GetCompressedFileSizeTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetCompressedFileSizeTransactedA],
		original_bytes[(int)Hook::Functions::GetCompressedFileSizeTransactedA], 6, NULL);

    DWORD result = GetCompressedFileSizeTransactedA(lpFileName,lpFileSizeHigh,hTransaction
);
    Hook reset_hook { Hook::Functions::GetCompressedFileSizeTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
INT __stdcall newGetExpandedNameA(
  [in]  LPSTR lpszSource,
  [out] LPSTR lpszBuffer
){
    	//unhook GetExpandedNameAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetExpandedNameA],
		original_bytes[(int)Hook::Functions::GetExpandedNameA], 6, NULL);

    INT result = GetExpandedNameA(lpszSource,lpszBuffer
);
    Hook reset_hook { Hook::Functions::GetExpandedNameA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetFileAttributesA(
  [in] LPCSTR lpFileName
){
    	//unhook GetFileAttributesAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesA],
		original_bytes[(int)Hook::Functions::GetFileAttributesA], 6, NULL);

    DWORD result = GetFileAttributesA(lpFileName
);
    Hook reset_hook { Hook::Functions::GetFileAttributesA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetFileAttributesExA(
  [in]  LPCSTR                 lpFileName,
  [in]  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID                 lpFileInformation
){
    	//unhook GetFileAttributesExAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesExA],
		original_bytes[(int)Hook::Functions::GetFileAttributesExA], 6, NULL);

    BOOL result = GetFileAttributesExA(lpFileName,fInfoLevelId,lpFileInformation
);
    Hook reset_hook { Hook::Functions::GetFileAttributesExA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetFileAttributesTransactedA(
  [in]  LPCSTR                 lpFileName,
  [in]  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID                 lpFileInformation,
  [in]  HANDLE                 hTransaction
){
    	//unhook GetFileAttributesTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesTransactedA],
		original_bytes[(int)Hook::Functions::GetFileAttributesTransactedA], 6, NULL);

    BOOL result = GetFileAttributesTransactedA(lpFileName,fInfoLevelId,lpFileInformation,hTransaction
);
    Hook reset_hook { Hook::Functions::GetFileAttributesTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetFileBandwidthReservation(
  [in]  HANDLE  hFile,
  [out] LPDWORD lpPeriodMilliseconds,
  [out] LPDWORD lpBytesPerPeriod,
  [out] LPBOOL  pDiscardable,
  [out] LPDWORD lpTransferSize,
  [out] LPDWORD lpNumOutstandingRequests
){
    	//unhook GetFileBandwidthReservationtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileBandwidthReservation],
		original_bytes[(int)Hook::Functions::GetFileBandwidthReservation], 6, NULL);

    BOOL result = GetFileBandwidthReservation(hFile,lpPeriodMilliseconds,lpBytesPerPeriod,pDiscardable,lpTransferSize,lpNumOutstandingRequests
);
    Hook reset_hook { Hook::Functions::GetFileBandwidthReservation};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetFileInformationByHandle(
  [in]  HANDLE                       hFile,
  [out] LPBY_HANDLE_FILE_INFORMATION lpFileInformation
){
    	//unhook GetFileInformationByHandletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileInformationByHandle],
		original_bytes[(int)Hook::Functions::GetFileInformationByHandle], 6, NULL);

    BOOL result = GetFileInformationByHandle(hFile,lpFileInformation
);
    Hook reset_hook { Hook::Functions::GetFileInformationByHandle};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetFileInformationByHandleEx(
  [in]  HANDLE                    hFile,
  [in]  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  [out] LPVOID                    lpFileInformation,
  [in]  DWORD                     dwBufferSize
){
    	//unhook GetFileInformationByHandleExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileInformationByHandleEx],
		original_bytes[(int)Hook::Functions::GetFileInformationByHandleEx], 6, NULL);

    BOOL result = GetFileInformationByHandleEx(hFile,FileInformationClass,lpFileInformation,dwBufferSize
);
    Hook reset_hook { Hook::Functions::GetFileInformationByHandleEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetFileSize(
  [in]            HANDLE  hFile,
  [out, optional] LPDWORD lpFileSizeHigh
){
    	//unhook GetFileSizetion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileSize],
		original_bytes[(int)Hook::Functions::GetFileSize], 6, NULL);

    DWORD result = GetFileSize(hFile,lpFileSizeHigh
);
    Hook reset_hook { Hook::Functions::GetFileSize};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetFileSizeEx(
  [in]  HANDLE         hFile,
  [out] PLARGE_INTEGER lpFileSize
){
    	//unhook GetFileSizeExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileSizeEx],
		original_bytes[(int)Hook::Functions::GetFileSizeEx], 6, NULL);

    BOOL result = GetFileSizeEx(hFile,lpFileSize
);
    Hook reset_hook { Hook::Functions::GetFileSizeEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetFileType(
  [in] HANDLE hFile
){
    	//unhook GetFileTypetion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFileType],
		original_bytes[(int)Hook::Functions::GetFileType], 6, NULL);

    DWORD result = GetFileType(hFile
);
    Hook reset_hook { Hook::Functions::GetFileType};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetFinalPathNameByHandleA(
  [in]  HANDLE hFile,
  [out] LPSTR  lpszFilePath,
  [in]  DWORD  cchFilePath,
  [in]  DWORD  dwFlags
){
    	//unhook GetFinalPathNameByHandleAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFinalPathNameByHandleA],
		original_bytes[(int)Hook::Functions::GetFinalPathNameByHandleA], 6, NULL);

    DWORD result = GetFinalPathNameByHandleA(hFile,lpszFilePath,cchFilePath,dwFlags
);
    Hook reset_hook { Hook::Functions::GetFinalPathNameByHandleA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetFullPathNameA(
  [in]  LPCSTR lpFileName,
  [in]  DWORD  nBufferLength,
  [out] LPSTR  lpBuffer,
  [out] LPSTR  *lpFilePart
){
    	//unhook GetFullPathNameAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFullPathNameA],
		original_bytes[(int)Hook::Functions::GetFullPathNameA], 6, NULL);

    DWORD result = GetFullPathNameA(lpFileName,nBufferLength,lpBuffer,lpFilePart
);
    Hook reset_hook { Hook::Functions::GetFullPathNameA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetFullPathNameTransactedA(
  [in]  LPCSTR lpFileName,
  [in]  DWORD  nBufferLength,
  [out] LPSTR  lpBuffer,
  [out] LPSTR  *lpFilePart,
  [in]  HANDLE hTransaction
){
    	//unhook GetFullPathNameTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetFullPathNameTransactedA],
		original_bytes[(int)Hook::Functions::GetFullPathNameTransactedA], 6, NULL);

    DWORD result = GetFullPathNameTransactedA(lpFileName,nBufferLength,lpBuffer,lpFilePart,hTransaction
);
    Hook reset_hook { Hook::Functions::GetFullPathNameTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetLongPathNameA(
  [in]  LPCSTR lpszShortPath,
  [out] LPSTR  lpszLongPath,
  [in]  DWORD  cchBuffer
){
    	//unhook GetLongPathNameAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetLongPathNameA],
		original_bytes[(int)Hook::Functions::GetLongPathNameA], 6, NULL);

    DWORD result = GetLongPathNameA(lpszShortPath,lpszLongPath,cchBuffer
);
    Hook reset_hook { Hook::Functions::GetLongPathNameA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetLongPathNameTransactedA(
  [in]  LPCSTR lpszShortPath,
  [out] LPSTR  lpszLongPath,
  [in]  DWORD  cchBuffer,
  [in]  HANDLE hTransaction
){
    	//unhook GetLongPathNameTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetLongPathNameTransactedA],
		original_bytes[(int)Hook::Functions::GetLongPathNameTransactedA], 6, NULL);

    DWORD result = GetLongPathNameTransactedA(lpszShortPath,lpszLongPath,cchBuffer,hTransaction
);
    Hook reset_hook { Hook::Functions::GetLongPathNameTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newGetQueuedCompletionStatus(
  [in]  HANDLE       CompletionPort,
        LPDWORD      lpNumberOfBytesTransferred,
  [out] PULONG_PTR   lpCompletionKey,
  [out] LPOVERLAPPED *lpOverlapped,
  [in]  DWORD        dwMilliseconds
){
    	//unhook GetQueuedCompletionStatustion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetQueuedCompletionStatus],
		original_bytes[(int)Hook::Functions::GetQueuedCompletionStatus], 6, NULL);

    BOOL result = GetQueuedCompletionStatus(CompletionPort,lpNumberOfBytesTransferred,lpCompletionKey,lpOverlapped,dwMilliseconds
);
    Hook reset_hook { Hook::Functions::GetQueuedCompletionStatus};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetShortPathNameW(
  [in]  LPCWSTR lpszLongPath,
  [out] LPWSTR  lpszShortPath,
  [in]  DWORD   cchBuffer
){
    	//unhook GetShortPathNameWtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetShortPathNameW],
		original_bytes[(int)Hook::Functions::GetShortPathNameW], 6, NULL);

    DWORD result = GetShortPathNameW(lpszLongPath,lpszShortPath,cchBuffer
);
    Hook reset_hook { Hook::Functions::GetShortPathNameW};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
UINT __stdcall newGetTempFileNameA(
  [in]  LPCSTR lpPathName,
  [in]  LPCSTR lpPrefixString,
  [in]  UINT   uUnique,
  [out] LPSTR  lpTempFileName
){
    	//unhook GetTempFileNameAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetTempFileNameA],
		original_bytes[(int)Hook::Functions::GetTempFileNameA], 6, NULL);

    UINT result = GetTempFileNameA(lpPathName,lpPrefixString,uUnique,lpTempFileName
);
    Hook reset_hook { Hook::Functions::GetTempFileNameA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newGetTempPathA(
  [in]  DWORD nBufferLength,
  [out] LPSTR lpBuffer
){
    	//unhook GetTempPathAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::GetTempPathA],
		original_bytes[(int)Hook::Functions::GetTempPathA], 6, NULL);

    DWORD result = GetTempPathA(nBufferLength,lpBuffer
);
    Hook reset_hook { Hook::Functions::GetTempPathA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}

BOOL __stdcall newLockFile(
  [in] HANDLE hFile,
  [in] DWORD  dwFileOffsetLow,
  [in] DWORD  dwFileOffsetHigh,
  [in] DWORD  nNumberOfBytesToLockLow,
  [in] DWORD  nNumberOfBytesToLockHigh
){
    	//unhook LockFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LockFile],
		original_bytes[(int)Hook::Functions::LockFile], 6, NULL);

    BOOL result = LockFile(hFile,dwFileOffsetLow,dwFileOffsetHigh,nNumberOfBytesToLockLow,nNumberOfBytesToLockHigh
);
    Hook reset_hook { Hook::Functions::LockFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newLockFileEx(
  [in]      HANDLE       hFile,
  [in]      DWORD        dwFlags,
            DWORD        dwReserved,
  [in]      DWORD        nNumberOfBytesToLockLow,
  [in]      DWORD        nNumberOfBytesToLockHigh,
  [in, out] LPOVERLAPPED lpOverlapped
){
    	//unhook LockFileExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LockFileEx],
		original_bytes[(int)Hook::Functions::LockFileEx], 6, NULL);

    BOOL result = LockFileEx(hFile,dwFlags,dwReserved,nNumberOfBytesToLockLow,nNumberOfBytesToLockHigh,lpOverlapped
);
    Hook reset_hook { Hook::Functions::LockFileEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
void __stdcall newLZClose(
  [in] INT hFile
){
    	//unhook LZClosetion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LZClose],
		original_bytes[(int)Hook::Functions::LZClose], 6, NULL);

    LZClose(hFile
);
    Hook reset_hook { Hook::Functions::LZClose};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
LONG __stdcall newLZCopy(
  [in] INT hfSource,
  [in] INT hfDest
){
    	//unhook LZCopytion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LZCopy],
		original_bytes[(int)Hook::Functions::LZCopy], 6, NULL);

    LONG result = LZCopy(hfSource,hfDest
);
    Hook reset_hook { Hook::Functions::LZCopy};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
INT __stdcall newLZInit(
  [in] INT hfSource
){
    	//unhook LZInittion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LZInit],
		original_bytes[(int)Hook::Functions::LZInit], 6, NULL);

    INT result = LZInit(hfSource
);
    Hook reset_hook { Hook::Functions::LZInit};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
INT __stdcall newLZOpenFileA(
  [in]  LPSTR      lpFileName,
  [out] LPOFSTRUCT lpReOpenBuf,
  [in]  WORD       wStyle
){
    	//unhook LZOpenFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LZOpenFileA],
		original_bytes[(int)Hook::Functions::LZOpenFileA], 6, NULL);

    INT result = LZOpenFileA(lpFileName,lpReOpenBuf,wStyle
);
    Hook reset_hook { Hook::Functions::LZOpenFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
INT __stdcall newLZRead(
  [in]  INT  hFile,
  [out] CHAR *lpBuffer,
  [in]  INT  cbRead
){
    	//unhook LZReadtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LZRead],
		original_bytes[(int)Hook::Functions::LZRead], 6, NULL);

    INT result = LZRead(hFile,lpBuffer,cbRead
);
    Hook reset_hook { Hook::Functions::LZRead};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
LONG __stdcall newLZSeek(
  [in] INT  hFile,
  [in] LONG lOffset,
  [in] INT  iOrigin
){
    	//unhook LZSeektion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::LZSeek],
		original_bytes[(int)Hook::Functions::LZSeek], 6, NULL);

    LONG result = LZSeek(hFile,lOffset,iOrigin
);
    Hook reset_hook { Hook::Functions::LZSeek};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newMoveFile(
  [in] LPCTSTR lpExistingFileName,
  [in] LPCTSTR lpNewFileName
){
    	//unhook MoveFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::MoveFile],
		original_bytes[(int)Hook::Functions::MoveFile], 6, NULL);

    BOOL result = MoveFile(lpExistingFileName,lpNewFileName
);
    Hook reset_hook { Hook::Functions::MoveFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newMoveFileExA(
  [in]           LPCSTR lpExistingFileName,
  [in, optional] LPCSTR lpNewFileName,
  [in]           DWORD  dwFlags
){
    	//unhook MoveFileExAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::MoveFileExA],
		original_bytes[(int)Hook::Functions::MoveFileExA], 6, NULL);

    BOOL result = MoveFileExA(lpExistingFileName,lpNewFileName,dwFlags
);
    Hook reset_hook { Hook::Functions::MoveFileExA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newMoveFileTransactedA(
  [in]           LPCSTR             lpExistingFileName,
  [in, optional] LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in]           DWORD              dwFlags,
  [in]           HANDLE             hTransaction
){
    	//unhook MoveFileTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::MoveFileTransactedA],
		original_bytes[(int)Hook::Functions::MoveFileTransactedA], 6, NULL);

    BOOL result = MoveFileTransactedA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,dwFlags,hTransaction
);
    Hook reset_hook { Hook::Functions::MoveFileTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newMoveFileWithProgressA(
  [in]           LPCSTR             lpExistingFileName,
  [in, optional] LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in]           DWORD              dwFlags
){
    	//unhook MoveFileWithProgressAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::MoveFileWithProgressA],
		original_bytes[(int)Hook::Functions::MoveFileWithProgressA], 6, NULL);

    BOOL result = MoveFileWithProgressA(lpExistingFileName,lpNewFileName,lpProgressRoutine,lpData,dwFlags
);
    Hook reset_hook { Hook::Functions::MoveFileWithProgressA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newOpenEncryptedFileRawA(
  [in]  LPCSTR lpFileName,
  [in]  ULONG  ulFlags,
  [out] PVOID  *pvContext
){
    	//unhook OpenEncryptedFileRawAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::OpenEncryptedFileRawA],
		original_bytes[(int)Hook::Functions::OpenEncryptedFileRawA], 6, NULL);

    DWORD result = OpenEncryptedFileRawA(lpFileName,ulFlags,pvContext
);
    Hook reset_hook { Hook::Functions::OpenEncryptedFileRawA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HFILE __stdcall newOpenFile(
  [in]  LPCSTR     lpFileName,
  [out] LPOFSTRUCT lpReOpenBuff,
  [in]  UINT       uStyle
){
    	//unhook OpenFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::OpenFile],
		original_bytes[(int)Hook::Functions::OpenFile], 6, NULL);

    HFILE result = OpenFile(lpFileName,lpReOpenBuff,uStyle
);
    Hook reset_hook { Hook::Functions::OpenFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newOpenFileById(
  [in]           HANDLE                hVolumeHint,
  [in]           LPFILE_ID_DESCRIPTOR  lpFileId,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwFlagsAndAttributes
){
    	//unhook OpenFileByIdtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::OpenFileById],
		original_bytes[(int)Hook::Functions::OpenFileById], 6, NULL);

    HANDLE result = OpenFileById(hVolumeHint,lpFileId,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwFlagsAndAttributes
);
    Hook reset_hook { Hook::Functions::OpenFileById};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newQueryRecoveryAgentsOnEncryptedFile(
  [in]  LPCWSTR                           lpFileName,
  [out] PENCRYPTION_CERTIFICATE_HASH_LIST *pRecoveryAgents
){
    	//unhook QueryRecoveryAgentsOnEncryptedFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::QueryRecoveryAgentsOnEncryptedFile],
		original_bytes[(int)Hook::Functions::QueryRecoveryAgentsOnEncryptedFile], 6, NULL);

    DWORD result = QueryRecoveryAgentsOnEncryptedFile(lpFileName,pRecoveryAgents
);
    Hook reset_hook { Hook::Functions::QueryRecoveryAgentsOnEncryptedFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newQueryUsersOnEncryptedFile(
  [in]  LPCWSTR                           lpFileName,
  [out] PENCRYPTION_CERTIFICATE_HASH_LIST *pUsers
){
    	//unhook QueryUsersOnEncryptedFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::QueryUsersOnEncryptedFile],
		original_bytes[(int)Hook::Functions::QueryUsersOnEncryptedFile], 6, NULL);

    DWORD result = QueryUsersOnEncryptedFile(lpFileName,pUsers
);
    Hook reset_hook { Hook::Functions::QueryUsersOnEncryptedFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newReadEncryptedFileRaw(
  [in]           PFE_EXPORT_FUNC pfExportCallback,
  [in, optional] PVOID           pvCallbackContext,
  [in]           PVOID           pvContext
){
    	//unhook ReadEncryptedFileRawtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::ReadEncryptedFileRaw],
		original_bytes[(int)Hook::Functions::ReadEncryptedFileRaw], 6, NULL);

    DWORD result = ReadEncryptedFileRaw(pfExportCallback,pvCallbackContext,pvContext
);
    Hook reset_hook { Hook::Functions::ReadEncryptedFileRaw};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newReadFile(
  [in]                HANDLE       hFile,
  [out]               LPVOID       lpBuffer,
  [in]                DWORD        nNumberOfBytesToRead,
  [out, optional]     LPDWORD      lpNumberOfBytesRead,
  [in, out, optional] LPOVERLAPPED lpOverlapped
){
    	//unhook ReadFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::ReadFile],
		original_bytes[(int)Hook::Functions::ReadFile], 6, NULL);

    BOOL result = ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped
);
    Hook reset_hook { Hook::Functions::ReadFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newReadFileEx(
  [in]            HANDLE                          hFile,
  [out, optional] LPVOID                          lpBuffer,
  [in]            DWORD                           nNumberOfBytesToRead,
  [in, out]       LPOVERLAPPED                    lpOverlapped,
  [in]            LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
    	//unhook ReadFileExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::ReadFileEx],
		original_bytes[(int)Hook::Functions::ReadFileEx], 6, NULL);

    BOOL result = ReadFileEx(hFile,lpBuffer,nNumberOfBytesToRead,lpOverlapped,lpCompletionRoutine
);
    Hook reset_hook { Hook::Functions::ReadFileEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}

DWORD __stdcall newRemoveUsersFromEncryptedFile(
  [in] LPCWSTR                           lpFileName,
  [in] PENCRYPTION_CERTIFICATE_HASH_LIST pHashes
){
    	//unhook RemoveUsersFromEncryptedFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::RemoveUsersFromEncryptedFile],
		original_bytes[(int)Hook::Functions::RemoveUsersFromEncryptedFile], 6, NULL);

    DWORD result = RemoveUsersFromEncryptedFile(lpFileName,pHashes
);
    Hook reset_hook { Hook::Functions::RemoveUsersFromEncryptedFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
HANDLE __stdcall newReOpenFile(
  [in] HANDLE hOriginalFile,
  [in] DWORD  dwDesiredAccess,
  [in] DWORD  dwShareMode,
  [in] DWORD  dwFlagsAndAttributes
){
    	//unhook ReOpenFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::ReOpenFile],
		original_bytes[(int)Hook::Functions::ReOpenFile], 6, NULL);

    HANDLE result = ReOpenFile(hOriginalFile,dwDesiredAccess,dwShareMode,dwFlagsAndAttributes
);
    Hook reset_hook { Hook::Functions::ReOpenFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newReplaceFileA(
  [in]           LPCSTR lpReplacedFileName,
  [in]           LPCSTR lpReplacementFileName,
  [in, optional] LPCSTR lpBackupFileName,
  [in]           DWORD  dwReplaceFlags,
                 LPVOID lpExclude,
                 LPVOID lpReserved
){
    	//unhook ReplaceFileAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::ReplaceFileA],
		original_bytes[(int)Hook::Functions::ReplaceFileA], 6, NULL);

    BOOL result = ReplaceFileA(lpReplacedFileName,lpReplacementFileName,lpBackupFileName,dwReplaceFlags,lpExclude,lpReserved
);
    Hook reset_hook { Hook::Functions::ReplaceFileA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newSearchPathA(
  [in, optional]  LPCSTR lpPath,
  [in]            LPCSTR lpFileName,
  [in, optional]  LPCSTR lpExtension,
  [in]            DWORD  nBufferLength,
  [out]           LPSTR  lpBuffer,
  [out, optional] LPSTR  *lpFilePart
){
    	//unhook SearchPathAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SearchPathA],
		original_bytes[(int)Hook::Functions::SearchPathA], 6, NULL);

    DWORD result = SearchPathA(lpPath,lpFileName,lpExtension,nBufferLength,lpBuffer,lpFilePart
);
    Hook reset_hook { Hook::Functions::SearchPathA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetEndOfFile(
  [in] HANDLE hFile
){
    	//unhook SetEndOfFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetEndOfFile],
		original_bytes[(int)Hook::Functions::SetEndOfFile], 6, NULL);

    BOOL result = SetEndOfFile(hFile
);
    Hook reset_hook { Hook::Functions::SetEndOfFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
void __stdcall newSetFileApisToANSI(){
    	//unhook SetFileApisToANSItion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileApisToANSI],
		original_bytes[(int)Hook::Functions::SetFileApisToANSI], 6, NULL);

    SetFileApisToANSI();
    Hook reset_hook { Hook::Functions::SetFileApisToANSI};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
void __stdcall newSetFileApisToOEM(){
    	//unhook SetFileApisToOEMtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileApisToOEM],
		original_bytes[(int)Hook::Functions::SetFileApisToOEM], 6, NULL);

    SetFileApisToOEM();
    Hook reset_hook { Hook::Functions::SetFileApisToOEM};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileAttributesA(
  [in] LPCSTR lpFileName,
  [in] DWORD  dwFileAttributes
){
    	//unhook SetFileAttributesAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileAttributesA],
		original_bytes[(int)Hook::Functions::SetFileAttributesA], 6, NULL);

    BOOL result = SetFileAttributesA(lpFileName,dwFileAttributes
);
    Hook reset_hook { Hook::Functions::SetFileAttributesA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileAttributesTransactedA(
  [in] LPCSTR lpFileName,
  [in] DWORD  dwFileAttributes,
  [in] HANDLE hTransaction
){
    	//unhook SetFileAttributesTransactedAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileAttributesTransactedA],
		original_bytes[(int)Hook::Functions::SetFileAttributesTransactedA], 6, NULL);

    BOOL result = SetFileAttributesTransactedA(lpFileName,dwFileAttributes,hTransaction
);
    Hook reset_hook { Hook::Functions::SetFileAttributesTransactedA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileBandwidthReservation(
  [in]  HANDLE  hFile,
  [in]  DWORD   nPeriodMilliseconds,
  [in]  DWORD   nBytesPerPeriod,
  [in]  BOOL    bDiscardable,
  [out] LPDWORD lpTransferSize,
  [out] LPDWORD lpNumOutstandingRequests
){
    	//unhook SetFileBandwidthReservationtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileBandwidthReservation],
		original_bytes[(int)Hook::Functions::SetFileBandwidthReservation], 6, NULL);

    BOOL result = SetFileBandwidthReservation(hFile,nPeriodMilliseconds,nBytesPerPeriod,bDiscardable,lpTransferSize,lpNumOutstandingRequests
);
    Hook reset_hook { Hook::Functions::SetFileBandwidthReservation};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileCompletionNotificationModes(
  [in] HANDLE FileHandle,
  [in] UCHAR  Flags
){
    	//unhook SetFileCompletionNotificationModestion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileCompletionNotificationModes],
		original_bytes[(int)Hook::Functions::SetFileCompletionNotificationModes], 6, NULL);

    BOOL result = SetFileCompletionNotificationModes(FileHandle,Flags
);
    Hook reset_hook { Hook::Functions::SetFileCompletionNotificationModes};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileInformationByHandle(
  [in] HANDLE                    hFile,
  [in] FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  [in] LPVOID                    lpFileInformation,
  [in] DWORD                     dwBufferSize
){
    	//unhook SetFileInformationByHandletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileInformationByHandle],
		original_bytes[(int)Hook::Functions::SetFileInformationByHandle], 6, NULL);

    BOOL result = SetFileInformationByHandle(hFile,FileInformationClass,lpFileInformation,dwBufferSize
);
    Hook reset_hook { Hook::Functions::SetFileInformationByHandle};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileIoOverlappedRange(
  [in] HANDLE FileHandle,
  [in] PUCHAR OverlappedRangeStart,
  [in] ULONG  Length
){
    	//unhook SetFileIoOverlappedRangetion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileIoOverlappedRange],
		original_bytes[(int)Hook::Functions::SetFileIoOverlappedRange], 6, NULL);

    BOOL result = SetFileIoOverlappedRange(FileHandle,OverlappedRangeStart,Length
);
    Hook reset_hook { Hook::Functions::SetFileIoOverlappedRange};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newSetFilePointer(
  [in]                HANDLE hFile,
  [in]                LONG   lDistanceToMove,
  [in, out, optional] PLONG  lpDistanceToMoveHigh,
  [in]                DWORD  dwMoveMethod
){
    	//unhook SetFilePointertion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFilePointer],
		original_bytes[(int)Hook::Functions::SetFilePointer], 6, NULL);

    DWORD result = SetFilePointer(hFile,lDistanceToMove,lpDistanceToMoveHigh,dwMoveMethod
);
    Hook reset_hook { Hook::Functions::SetFilePointer};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFilePointerEx(
  [in]            HANDLE         hFile,
  [in]            LARGE_INTEGER  liDistanceToMove,
  [out, optional] PLARGE_INTEGER lpNewFilePointer,
  [in]            DWORD          dwMoveMethod
){
    	//unhook SetFilePointerExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFilePointerEx],
		original_bytes[(int)Hook::Functions::SetFilePointerEx], 6, NULL);

    BOOL result = SetFilePointerEx(hFile,liDistanceToMove,lpNewFilePointer,dwMoveMethod
);
    Hook reset_hook { Hook::Functions::SetFilePointerEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileShortNameA(
  [in] HANDLE hFile,
  [in] LPCSTR lpShortName
){
    	//unhook SetFileShortNameAtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileShortNameA],
		original_bytes[(int)Hook::Functions::SetFileShortNameA], 6, NULL);

    BOOL result = SetFileShortNameA(hFile,lpShortName
);
    Hook reset_hook { Hook::Functions::SetFileShortNameA};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetFileValidData(
  [in] HANDLE   hFile,
  [in] LONGLONG ValidDataLength
){
    	//unhook SetFileValidDatation
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetFileValidData],
		original_bytes[(int)Hook::Functions::SetFileValidData], 6, NULL);

    BOOL result = SetFileValidData(hFile,ValidDataLength
);
    Hook reset_hook { Hook::Functions::SetFileValidData};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newSetSearchPathMode(
  [in] DWORD Flags
){
    	//unhook SetSearchPathModetion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetSearchPathMode],
		original_bytes[(int)Hook::Functions::SetSearchPathMode], 6, NULL);

    BOOL result = SetSearchPathMode(Flags
);
    Hook reset_hook { Hook::Functions::SetSearchPathMode};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newSetUserFileEncryptionKey(
  [in] PENCRYPTION_CERTIFICATE pEncryptionCertificate
){
    	//unhook SetUserFileEncryptionKeytion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::SetUserFileEncryptionKey],
		original_bytes[(int)Hook::Functions::SetUserFileEncryptionKey], 6, NULL);

    DWORD result = SetUserFileEncryptionKey(pEncryptionCertificate
);
    Hook reset_hook { Hook::Functions::SetUserFileEncryptionKey};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newUnlockFile(
  [in] HANDLE hFile,
  [in] DWORD  dwFileOffsetLow,
  [in] DWORD  dwFileOffsetHigh,
  [in] DWORD  nNumberOfBytesToUnlockLow,
  [in] DWORD  nNumberOfBytesToUnlockHigh
){
    	//unhook UnlockFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::UnlockFile],
		original_bytes[(int)Hook::Functions::UnlockFile], 6, NULL);

    BOOL result = UnlockFile(hFile,dwFileOffsetLow,dwFileOffsetHigh,nNumberOfBytesToUnlockLow,nNumberOfBytesToUnlockHigh
);
    Hook reset_hook { Hook::Functions::UnlockFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newUnlockFileEx(
  [in]      HANDLE       hFile,
            DWORD        dwReserved,
  [in]      DWORD        nNumberOfBytesToUnlockLow,
  [in]      DWORD        nNumberOfBytesToUnlockHigh,
  [in, out] LPOVERLAPPED lpOverlapped
){
    	//unhook UnlockFileExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::UnlockFileEx],
		original_bytes[(int)Hook::Functions::UnlockFileEx], 6, NULL);

    BOOL result = UnlockFileEx(hFile,dwReserved,nNumberOfBytesToUnlockLow,nNumberOfBytesToUnlockHigh,lpOverlapped
);
    Hook reset_hook { Hook::Functions::UnlockFileEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}



BOOL __stdcall newWow64DisableWow64FsRedirection(
  [out] PVOID *OldValue
){
    	//unhook Wow64DisableWow64FsRedirectiontion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::Wow64DisableWow64FsRedirection],
		original_bytes[(int)Hook::Functions::Wow64DisableWow64FsRedirection], 6, NULL);

    BOOL result = Wow64DisableWow64FsRedirection(OldValue
);
    Hook reset_hook { Hook::Functions::Wow64DisableWow64FsRedirection};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOLEAN __stdcall newWow64EnableWow64FsRedirection(
  BOOLEAN Wow64FsEnableRedirection
){
    	//unhook Wow64EnableWow64FsRedirectiontion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::Wow64EnableWow64FsRedirection],
		original_bytes[(int)Hook::Functions::Wow64EnableWow64FsRedirection], 6, NULL);

    BOOLEAN result = Wow64EnableWow64FsRedirection(Wow64FsEnableRedirection
);
    Hook reset_hook { Hook::Functions::Wow64EnableWow64FsRedirection};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newWow64RevertWow64FsRedirection(
  PVOID OlValue
){
    	//unhook Wow64RevertWow64FsRedirectiontion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::Wow64RevertWow64FsRedirection],
		original_bytes[(int)Hook::Functions::Wow64RevertWow64FsRedirection], 6, NULL);

    BOOL result = Wow64RevertWow64FsRedirection(OlValue
);
    Hook reset_hook { Hook::Functions::Wow64RevertWow64FsRedirection};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
DWORD __stdcall newWriteEncryptedFileRaw(
  [in]           PFE_IMPORT_FUNC pfImportCallback,
  [in, optional] PVOID           pvCallbackContext,
  [in]           PVOID           pvContext
){
    	//unhook WriteEncryptedFileRawtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::WriteEncryptedFileRaw],
		original_bytes[(int)Hook::Functions::WriteEncryptedFileRaw], 6, NULL);

    DWORD result = WriteEncryptedFileRaw(pfImportCallback,pvCallbackContext,pvContext
);
    Hook reset_hook { Hook::Functions::WriteEncryptedFileRaw};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newWriteFile(
  [in]                HANDLE       hFile,
  [in]                LPCVOID      lpBuffer,
  [in]                DWORD        nNumberOfBytesToWrite,
  [out, optional]     LPDWORD      lpNumberOfBytesWritten,
  [in, out, optional] LPOVERLAPPED lpOverlapped
){
    	//unhook WriteFiletion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::WriteFile],
		original_bytes[(int)Hook::Functions::WriteFile], 6, NULL);

    BOOL result = WriteFile(hFile,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped
);
    Hook reset_hook { Hook::Functions::WriteFile};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
BOOL __stdcall newWriteFileEx(
  [in]           HANDLE                          hFile,
  [in, optional] LPCVOID                         lpBuffer,
  [in]           DWORD                           nNumberOfBytesToWrite,
  [in, out]      LPOVERLAPPED                    lpOverlapped,
  [in]           LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
){
    	//unhook WriteFileExtion
	WriteProcessMemory(GetCurrentProcess(),
		(LPVOID)hooked_addr[(int)Hook::Functions::WriteFileEx],
		original_bytes[(int)Hook::Functions::WriteFileEx], 6, NULL);

    BOOL result = WriteFileEx(hFile,lpBuffer,nNumberOfBytesToWrite,lpOverlapped,lpCompletionRoutine
);
    Hook reset_hook { Hook::Functions::WriteFileEx};
    reset_hook.deploy_hook();

    //char* msg = new msg{whatever}
    //log1(msg,msg.len)

}
}