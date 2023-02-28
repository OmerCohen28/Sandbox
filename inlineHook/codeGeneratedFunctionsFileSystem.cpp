#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)
#include "codeGeneratedFunctionsFileSystem.h"
#include "inlineHook.h"
#include <functional>
#include <string>
#include <vector>
#include <array>
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
        LPCWSTR                      lpFileName,
        PENCRYPTION_CERTIFICATE_LIST pEncryptionCertificates
    ) {
        //unhook AddUsersToEncryptedFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::AddUsersToEncryptedFile],
            original_bytes[(int)Hook::Functions::AddUsersToEncryptedFile], 6, NULL);

        DWORD result = AddUsersToEncryptedFile(lpFileName, pEncryptionCertificates
        );
        Hook reset_hook{ Hook::Functions::AddUsersToEncryptedFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newAreFileApisANSI() {
        //unhook AreFileApisANSItion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::AreFileApisANSI],
            original_bytes[(int)Hook::Functions::AreFileApisANSI], 6, NULL);

        BOOL result = AreFileApisANSI();
        Hook reset_hook{ Hook::Functions::AreFileApisANSI };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newCheckNameLegalDOS8Dot3A(
        LPCSTR lpName,
        LPSTR  lpOemName,
        DWORD  OemNameSize,
        PBOOL  pbNameContainsSpaces,
        PBOOL  pbNameLegal
    ) {
        //unhook CheckNameLegalDOS8Dot3Ation
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CheckNameLegalDOS8Dot3A],
            original_bytes[(int)Hook::Functions::CheckNameLegalDOS8Dot3A], 6, NULL);

        BOOL result = CheckNameLegalDOS8Dot3A(lpName, lpOemName, OemNameSize, pbNameContainsSpaces, pbNameLegal
        );
        Hook reset_hook{ Hook::Functions::CheckNameLegalDOS8Dot3A };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    void __stdcall newCloseEncryptedFileRaw(
        PVOID pvContext
    ) {
        //unhook CloseEncryptedFileRawtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CloseEncryptedFileRaw],
            original_bytes[(int)Hook::Functions::CloseEncryptedFileRaw], 6, NULL);

        CloseEncryptedFileRaw(pvContext
        );
        Hook reset_hook{ Hook::Functions::CloseEncryptedFileRaw };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

    }
    BOOL __stdcall newCopyFile(
        LPCTSTR lpExistingFileName,
        LPCTSTR lpNewFileName,
        BOOL    bFailIfExists
    ) {
        //unhook CopyFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CopyFile],
            original_bytes[(int)Hook::Functions::CopyFile], 6, NULL);

        BOOL result = CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists
        );
        Hook reset_hook{ Hook::Functions::CopyFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HRESULT __stdcall newCopyFile2(
        PCWSTR                        pwszExistingFileName,
        PCWSTR                        pwszNewFileName,
        COPYFILE2_EXTENDED_PARAMETERS* pExtendedParameters
    ) {
        //unhook CopyFile2tion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CopyFile2],
            original_bytes[(int)Hook::Functions::CopyFile2], 6, NULL);

        HRESULT result = CopyFile2(pwszExistingFileName, pwszNewFileName, pExtendedParameters
        );
        Hook reset_hook{ Hook::Functions::CopyFile2 };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newCopyFileExA(
        LPCSTR             lpExistingFileName,
        LPCSTR             lpNewFileName,
        LPPROGRESS_ROUTINE lpProgressRoutine,
        LPVOID             lpData,
        LPBOOL             pbCancel,
        DWORD              dwCopyFlags
    ) {
        //unhook CopyFileExAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CopyFileExA],
            original_bytes[(int)Hook::Functions::CopyFileExA], 6, NULL);

        BOOL result = ::CopyFileExA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags
        );
        Hook reset_hook{ Hook::Functions::CopyFileExA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newCopyFileTransactedA(
        LPCSTR             lpExistingFileName,
        LPCSTR             lpNewFileName,
        LPPROGRESS_ROUTINE lpProgressRoutine,
        LPVOID             lpData,
        LPBOOL             pbCancel,
        DWORD              dwCopyFlags,
        HANDLE             hTransaction
    ) {
        //unhook CopyFileTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CopyFileTransactedA],
            original_bytes[(int)Hook::Functions::CopyFileTransactedA], 6, NULL);

        BOOL result = CopyFileTransactedA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags, hTransaction
        );
        Hook reset_hook{ Hook::Functions::CopyFileTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newCreateFileA(
        LPCSTR                lpFileName,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwCreationDisposition,
        DWORD                 dwFlagsAndAttributes,
        HANDLE                hTemplateFile
    ) {
        //unhook CreateFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateFileA],
            original_bytes[(int)Hook::Functions::CreateFileA], 6, NULL);
        std::cout << "here\n";
        HANDLE result = ::CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile
        );
        Hook reset_hook{ Hook::Functions::CreateFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newCreateFile2(
        LPCWSTR                           lpFileName,
        DWORD                             dwDesiredAccess,
        DWORD                             dwShareMode,
        DWORD                             dwCreationDisposition,
        LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams
    ) {
        //unhook CreateFile2tion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateFile2],
            original_bytes[(int)Hook::Functions::CreateFile2], 6, NULL);

        HANDLE result = CreateFile2(lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, pCreateExParams
        );
        Hook reset_hook{ Hook::Functions::CreateFile2 };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newCreateFileTransactedA(
        LPCSTR                lpFileName,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwCreationDisposition,
        DWORD                 dwFlagsAndAttributes,
        HANDLE                hTemplateFile,
        HANDLE                hTransaction,
        PUSHORT               pusMiniVersion,
        PVOID                 lpExtendedParameter
    ) {
        //unhook CreateFileTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateFileTransactedA],
            original_bytes[(int)Hook::Functions::CreateFileTransactedA], 6, NULL);

        HANDLE result = CreateFileTransactedA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile, hTransaction, pusMiniVersion, lpExtendedParameter
        );
        Hook reset_hook{ Hook::Functions::CreateFileTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newCreateHardLinkA(
        LPCSTR                lpFileName,
        LPCSTR                lpExistingFileName,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes
    ) {
        //unhook CreateHardLinkAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateHardLinkA],
            original_bytes[(int)Hook::Functions::CreateHardLinkA], 6, NULL);

        BOOL result = CreateHardLinkA(lpFileName, lpExistingFileName, lpSecurityAttributes
        );
        Hook reset_hook{ Hook::Functions::CreateHardLinkA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newCreateHardLinkTransactedA(
        LPCSTR                lpFileName,
        LPCSTR                lpExistingFileName,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        HANDLE                hTransaction
    ) {
        //unhook CreateHardLinkTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateHardLinkTransactedA],
            original_bytes[(int)Hook::Functions::CreateHardLinkTransactedA], 6, NULL);

        BOOL result = CreateHardLinkTransactedA(lpFileName, lpExistingFileName, lpSecurityAttributes, hTransaction
        );
        Hook reset_hook{ Hook::Functions::CreateHardLinkTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOLEAN __stdcall newCreateSymbolicLinkA(
        LPCSTR lpSymlinkFileName,
        LPCSTR lpTargetFileName,
        DWORD  dwFlags
    ) {
        //unhook CreateSymbolicLinkAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateSymbolicLinkA],
            original_bytes[(int)Hook::Functions::CreateSymbolicLinkA], 6, NULL);

        BOOLEAN result = CreateSymbolicLinkA(lpSymlinkFileName, lpTargetFileName, dwFlags
        );
        Hook reset_hook{ Hook::Functions::CreateSymbolicLinkA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOLEAN __stdcall newCreateSymbolicLinkTransactedA(
        LPCSTR lpSymlinkFileName,
        LPCSTR lpTargetFileName,
        DWORD  dwFlags,
        HANDLE hTransaction
    ) {
        //unhook CreateSymbolicLinkTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::CreateSymbolicLinkTransactedA],
            original_bytes[(int)Hook::Functions::CreateSymbolicLinkTransactedA], 6, NULL);

        BOOLEAN result = CreateSymbolicLinkTransactedA(lpSymlinkFileName, lpTargetFileName, dwFlags, hTransaction
        );
        Hook reset_hook{ Hook::Functions::CreateSymbolicLinkTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newDecryptFileA(
        LPCSTR lpFileName,
        DWORD  dwReserved
    ) {
        //unhook DecryptFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::DecryptFileA],
            original_bytes[(int)Hook::Functions::DecryptFileA], 6, NULL);

        BOOL result = DecryptFileA(lpFileName, dwReserved
        );
        Hook reset_hook{ Hook::Functions::DecryptFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newDeleteFileA(
        LPCSTR lpFileName
    ) {
        //unhook DeleteFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileA],
            original_bytes[(int)Hook::Functions::DeleteFileA], 6, NULL);

        BOOL result = DeleteFileA(lpFileName
        );
        Hook reset_hook{ Hook::Functions::DeleteFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newDeleteFileTransactedA(
        LPCSTR lpFileName,
        HANDLE hTransaction
    ) {
        //unhook DeleteFileTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::DeleteFileTransactedA],
            original_bytes[(int)Hook::Functions::DeleteFileTransactedA], 6, NULL);

        BOOL result = DeleteFileTransactedA(lpFileName, hTransaction
        );
        Hook reset_hook{ Hook::Functions::DeleteFileTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newDuplicateEncryptionInfoFile(
        LPCWSTR                     SrcFileName,
        LPCWSTR                     DstFileName,
        DWORD                       dwCreationDistribution,
        DWORD                       dwAttributes,
        const LPSECURITY_ATTRIBUTES lpSecurityAttributes
    ) {
        //unhook DuplicateEncryptionInfoFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::DuplicateEncryptionInfoFile],
            original_bytes[(int)Hook::Functions::DuplicateEncryptionInfoFile], 6, NULL);

        DWORD result = DuplicateEncryptionInfoFile(SrcFileName, DstFileName, dwCreationDistribution, dwAttributes, lpSecurityAttributes
        );
        Hook reset_hook{ Hook::Functions::DuplicateEncryptionInfoFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newEncryptFileA(
        LPCSTR lpFileName
    ) {
        //unhook EncryptFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::EncryptFileA],
            original_bytes[(int)Hook::Functions::EncryptFileA], 6, NULL);

        BOOL result = EncryptFileA(lpFileName
        );
        Hook reset_hook{ Hook::Functions::EncryptFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newEncryptionDisable(
        LPCWSTR DirPath,
        BOOL    Disable
    ) {
        //unhook EncryptionDisabletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::EncryptionDisable],
            original_bytes[(int)Hook::Functions::EncryptionDisable], 6, NULL);

        BOOL result = EncryptionDisable(DirPath, Disable
        );
        Hook reset_hook{ Hook::Functions::EncryptionDisable };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL newFileEncryptionStatusA(
        LPCSTR  lpFileName,
        LPDWORD lpStatus
    ) {
        //unhook FileEncryptionStatusAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FileEncryptionStatusA],
            original_bytes[(int)Hook::Functions::FileEncryptionStatusA], 6, NULL);

        BOOL result = FileEncryptionStatusA(lpFileName, lpStatus
        );
        Hook reset_hook{ Hook::Functions::FileEncryptionStatusA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL newFindClose(
        HANDLE hFindFile
    ) {
        //unhook FindClosetion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindClose],
            original_bytes[(int)Hook::Functions::FindClose], 6, NULL);

        BOOL result = FindClose(hFindFile
        );
        Hook reset_hook{ Hook::Functions::FindClose };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstFileA(
        LPCSTR             lpFileName,
        LPWIN32_FIND_DATAA lpFindFileData
    ) {
        //unhook FindFirstFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileA],
            original_bytes[(int)Hook::Functions::FindFirstFileA], 6, NULL);

        HANDLE result = FindFirstFileA(lpFileName, lpFindFileData
        );
        Hook reset_hook{ Hook::Functions::FindFirstFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstFileExA(
        LPCSTR             lpFileName,
        FINDEX_INFO_LEVELS fInfoLevelId,
        LPVOID             lpFindFileData,
        FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
        DWORD              dwAdditionalFlags
    ) {
        //unhook FindFirstFileExAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileExA],
            original_bytes[(int)Hook::Functions::FindFirstFileExA], 6, NULL);

        HANDLE result = FindFirstFileExA(lpFileName, fInfoLevelId, lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags
        );
        Hook reset_hook{ Hook::Functions::FindFirstFileExA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstFileNameTransactedW(
        LPCWSTR lpFileName,
        DWORD   dwFlags,
        LPDWORD StringLength,
        PWSTR   LinkName,
        HANDLE  hTransaction
    ) {
        //unhook FindFirstFileNameTransactedWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileNameTransactedW],
            original_bytes[(int)Hook::Functions::FindFirstFileNameTransactedW], 6, NULL);

        HANDLE result = FindFirstFileNameTransactedW(lpFileName, dwFlags, StringLength, LinkName, hTransaction
        );
        Hook reset_hook{ Hook::Functions::FindFirstFileNameTransactedW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstFileNameW(
        LPCWSTR lpFileName,
        DWORD   dwFlags,
        LPDWORD StringLength,
        PWSTR   LinkName
    ) {
        //unhook FindFirstFileNameWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileNameW],
            original_bytes[(int)Hook::Functions::FindFirstFileNameW], 6, NULL);

        HANDLE result = FindFirstFileNameW(lpFileName, dwFlags, StringLength, LinkName
        );
        Hook reset_hook{ Hook::Functions::FindFirstFileNameW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstFileTransactedA(
        LPCSTR             lpFileName,
        FINDEX_INFO_LEVELS fInfoLevelId,
        LPVOID             lpFindFileData,
        FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
        DWORD              dwAdditionalFlags,
        HANDLE             hTransaction
    ) {
        //unhook FindFirstFileTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstFileTransactedA],
            original_bytes[(int)Hook::Functions::FindFirstFileTransactedA], 6, NULL);

        HANDLE result = FindFirstFileTransactedA(lpFileName, fInfoLevelId, lpFindFileData, fSearchOp, lpSearchFilter, dwAdditionalFlags, hTransaction
        );
        Hook reset_hook{ Hook::Functions::FindFirstFileTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstStreamTransactedW(
        LPCWSTR            lpFileName,
        STREAM_INFO_LEVELS InfoLevel,
        LPVOID             lpFindStreamData,
        DWORD              dwFlags,
        HANDLE             hTransaction
    ) {
        //unhook FindFirstStreamTransactedWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstStreamTransactedW],
            original_bytes[(int)Hook::Functions::FindFirstStreamTransactedW], 6, NULL);

        HANDLE result = FindFirstStreamTransactedW(lpFileName, InfoLevel, lpFindStreamData, dwFlags, hTransaction
        );
        Hook reset_hook{ Hook::Functions::FindFirstStreamTransactedW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newFindFirstStreamW(
        LPCWSTR            lpFileName,
        STREAM_INFO_LEVELS InfoLevel,
        LPVOID             lpFindStreamData,
        DWORD              dwFlags
    ) {
        //unhook FindFirstStreamWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindFirstStreamW],
            original_bytes[(int)Hook::Functions::FindFirstStreamW], 6, NULL);

        HANDLE result = FindFirstStreamW(lpFileName, InfoLevel, lpFindStreamData, dwFlags
        );
        Hook reset_hook{ Hook::Functions::FindFirstStreamW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newFindNextFileA(
        HANDLE             hFindFile,
        LPWIN32_FIND_DATAA lpFindFileData
    ) {
        //unhook FindNextFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindNextFileA],
            original_bytes[(int)Hook::Functions::FindNextFileA], 6, NULL);

        BOOL result = FindNextFileA(hFindFile, lpFindFileData
        );
        Hook reset_hook{ Hook::Functions::FindNextFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newFindNextFileNameW(
        HANDLE  hFindStream,
        LPDWORD StringLength,
        PWSTR   LinkName
    ) {
        //unhook FindNextFileNameWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindNextFileNameW],
            original_bytes[(int)Hook::Functions::FindNextFileNameW], 6, NULL);

        BOOL result = FindNextFileNameW(hFindStream, StringLength, LinkName
        );
        Hook reset_hook{ Hook::Functions::FindNextFileNameW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newFindNextStreamW(
        HANDLE hFindStream,
        LPVOID lpFindStreamData
    ) {
        //unhook FindNextStreamWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FindNextStreamW],
            original_bytes[(int)Hook::Functions::FindNextStreamW], 6, NULL);

        BOOL result = FindNextStreamW(hFindStream, lpFindStreamData
        );
        Hook reset_hook{ Hook::Functions::FindNextStreamW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newFlushFileBuffers(
        HANDLE hFile
    ) {
        //unhook FlushFileBufferstion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FlushFileBuffers],
            original_bytes[(int)Hook::Functions::FlushFileBuffers], 6, NULL);

        BOOL result = FlushFileBuffers(hFile
        );
        Hook reset_hook{ Hook::Functions::FlushFileBuffers };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    void __stdcall newFreeEncryptionCertificateHashList(
        PENCRYPTION_CERTIFICATE_HASH_LIST pUsers
    ) {
        //unhook FreeEncryptionCertificateHashListtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::FreeEncryptionCertificateHashList],
            original_bytes[(int)Hook::Functions::FreeEncryptionCertificateHashList], 6, NULL);

        FreeEncryptionCertificateHashList(pUsers
        );
        Hook reset_hook{ Hook::Functions::FreeEncryptionCertificateHashList };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

    }
    BOOL __stdcall newGetBinaryTypeA(
        LPCSTR  lpApplicationName,
        LPDWORD lpBinaryType
    ) {
        //unhook GetBinaryTypeAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetBinaryTypeA],
            original_bytes[(int)Hook::Functions::GetBinaryTypeA], 6, NULL);

        BOOL result = GetBinaryTypeA(lpApplicationName, lpBinaryType
        );
        Hook reset_hook{ Hook::Functions::GetBinaryTypeA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetCompressedFileSizeA(
        LPCSTR  lpFileName,
        LPDWORD lpFileSizeHigh
    ) {
        //unhook GetCompressedFileSizeAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetCompressedFileSizeA],
            original_bytes[(int)Hook::Functions::GetCompressedFileSizeA], 6, NULL);

        DWORD result = GetCompressedFileSizeA(lpFileName, lpFileSizeHigh
        );
        Hook reset_hook{ Hook::Functions::GetCompressedFileSizeA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetCompressedFileSizeTransactedA(
        LPCSTR  lpFileName,
        LPDWORD lpFileSizeHigh,
        HANDLE  hTransaction
    ) {
        //unhook GetCompressedFileSizeTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetCompressedFileSizeTransactedA],
            original_bytes[(int)Hook::Functions::GetCompressedFileSizeTransactedA], 6, NULL);

        DWORD result = GetCompressedFileSizeTransactedA(lpFileName, lpFileSizeHigh, hTransaction
        );
        Hook reset_hook{ Hook::Functions::GetCompressedFileSizeTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetFileAttributesA(
        LPCSTR lpFileName
    ) {
        //unhook GetFileAttributesAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesA],
            original_bytes[(int)Hook::Functions::GetFileAttributesA], 6, NULL);

        DWORD result = GetFileAttributesA(lpFileName
        );
        Hook reset_hook{ Hook::Functions::GetFileAttributesA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetFileAttributesExA(
        LPCSTR                 lpFileName,
        GET_FILEEX_INFO_LEVELS fInfoLevelId,
        LPVOID                 lpFileInformation
    ) {
        //unhook GetFileAttributesExAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesExA],
            original_bytes[(int)Hook::Functions::GetFileAttributesExA], 6, NULL);

        BOOL result = GetFileAttributesExA(lpFileName, fInfoLevelId, lpFileInformation
        );
        Hook reset_hook{ Hook::Functions::GetFileAttributesExA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetFileAttributesTransactedA(
        LPCSTR                 lpFileName,
        GET_FILEEX_INFO_LEVELS fInfoLevelId,
        LPVOID                 lpFileInformation,
        HANDLE                 hTransaction
    ) {
        //unhook GetFileAttributesTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileAttributesTransactedA],
            original_bytes[(int)Hook::Functions::GetFileAttributesTransactedA], 6, NULL);

        BOOL result = GetFileAttributesTransactedA(lpFileName, fInfoLevelId, lpFileInformation, hTransaction
        );
        Hook reset_hook{ Hook::Functions::GetFileAttributesTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetFileBandwidthReservation(
        HANDLE  hFile,
        LPDWORD lpPeriodMilliseconds,
        LPDWORD lpBytesPerPeriod,
        LPBOOL  pDiscardable,
        LPDWORD lpTransferSize,
        LPDWORD lpNumOutstandingRequests
    ) {
        //unhook GetFileBandwidthReservationtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileBandwidthReservation],
            original_bytes[(int)Hook::Functions::GetFileBandwidthReservation], 6, NULL);

        BOOL result = GetFileBandwidthReservation(hFile, lpPeriodMilliseconds, lpBytesPerPeriod, pDiscardable, lpTransferSize, lpNumOutstandingRequests
        );
        Hook reset_hook{ Hook::Functions::GetFileBandwidthReservation };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetFileInformationByHandle(
        HANDLE                       hFile,
        LPBY_HANDLE_FILE_INFORMATION lpFileInformation
    ) {
        //unhook GetFileInformationByHandletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileInformationByHandle],
            original_bytes[(int)Hook::Functions::GetFileInformationByHandle], 6, NULL);

        BOOL result = GetFileInformationByHandle(hFile, lpFileInformation
        );
        Hook reset_hook{ Hook::Functions::GetFileInformationByHandle };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetFileInformationByHandleEx(
        HANDLE                    hFile,
        FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
        LPVOID                    lpFileInformation,
        DWORD                     dwBufferSize
    ) {
        //unhook GetFileInformationByHandleExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileInformationByHandleEx],
            original_bytes[(int)Hook::Functions::GetFileInformationByHandleEx], 6, NULL);

        BOOL result = GetFileInformationByHandleEx(hFile, FileInformationClass, lpFileInformation, dwBufferSize
        );
        Hook reset_hook{ Hook::Functions::GetFileInformationByHandleEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetFileSize(
        HANDLE  hFile,
        LPDWORD lpFileSizeHigh
    ) {
        //unhook GetFileSizetion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileSize],
            original_bytes[(int)Hook::Functions::GetFileSize], 6, NULL);

        DWORD result = GetFileSize(hFile, lpFileSizeHigh
        );
        Hook reset_hook{ Hook::Functions::GetFileSize };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetFileSizeEx(
        HANDLE         hFile,
        PLARGE_INTEGER lpFileSize
    ) {
        //unhook GetFileSizeExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileSizeEx],
            original_bytes[(int)Hook::Functions::GetFileSizeEx], 6, NULL);

        BOOL result = GetFileSizeEx(hFile, lpFileSize
        );
        Hook reset_hook{ Hook::Functions::GetFileSizeEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetFileType(
        HANDLE hFile
    ) {
        //unhook GetFileTypetion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFileType],
            original_bytes[(int)Hook::Functions::GetFileType], 6, NULL);

        DWORD result = GetFileType(hFile
        );
        Hook reset_hook{ Hook::Functions::GetFileType };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetFinalPathNameByHandleA(
        HANDLE hFile,
        LPSTR  lpszFilePath,
        DWORD  cchFilePath,
        DWORD  dwFlags
    ) {
        //unhook GetFinalPathNameByHandleAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFinalPathNameByHandleA],
            original_bytes[(int)Hook::Functions::GetFinalPathNameByHandleA], 6, NULL);

        DWORD result = GetFinalPathNameByHandleA(hFile, lpszFilePath, cchFilePath, dwFlags
        );
        Hook reset_hook{ Hook::Functions::GetFinalPathNameByHandleA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetFullPathNameA(
        LPCSTR lpFileName,
        DWORD  nBufferLength,
        LPSTR  lpBuffer,
        LPSTR* lpFilePart
    ) {
        //unhook GetFullPathNameAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFullPathNameA],
            original_bytes[(int)Hook::Functions::GetFullPathNameA], 6, NULL);

        DWORD result = GetFullPathNameA(lpFileName, nBufferLength, lpBuffer, lpFilePart
        );
        Hook reset_hook{ Hook::Functions::GetFullPathNameA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetFullPathNameTransactedA(
        LPCSTR lpFileName,
        DWORD  nBufferLength,
        LPSTR  lpBuffer,
        LPSTR* lpFilePart,
        HANDLE hTransaction
    ) {
        //unhook GetFullPathNameTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetFullPathNameTransactedA],
            original_bytes[(int)Hook::Functions::GetFullPathNameTransactedA], 6, NULL);

        DWORD result = GetFullPathNameTransactedA(lpFileName, nBufferLength, lpBuffer, lpFilePart, hTransaction
        );
        Hook reset_hook{ Hook::Functions::GetFullPathNameTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetLongPathNameA(
        LPCSTR lpszShortPath,
        LPSTR  lpszLongPath,
        DWORD  cchBuffer
    ) {
        //unhook GetLongPathNameAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetLongPathNameA],
            original_bytes[(int)Hook::Functions::GetLongPathNameA], 6, NULL);

        DWORD result = GetLongPathNameA(lpszShortPath, lpszLongPath, cchBuffer
        );
        Hook reset_hook{ Hook::Functions::GetLongPathNameA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetLongPathNameTransactedA(
        LPCSTR lpszShortPath,
        LPSTR  lpszLongPath,
        DWORD  cchBuffer,
        HANDLE hTransaction
    ) {
        //unhook GetLongPathNameTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetLongPathNameTransactedA],
            original_bytes[(int)Hook::Functions::GetLongPathNameTransactedA], 6, NULL);

        DWORD result = GetLongPathNameTransactedA(lpszShortPath, lpszLongPath, cchBuffer, hTransaction
        );
        Hook reset_hook{ Hook::Functions::GetLongPathNameTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newGetQueuedCompletionStatus(
        HANDLE       CompletionPort,
        LPDWORD      lpNumberOfBytesTransferred,
        PULONG_PTR   lpCompletionKey,
        LPOVERLAPPED* lpOverlapped,
        DWORD        dwMilliseconds
    ) {
        //unhook GetQueuedCompletionStatustion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetQueuedCompletionStatus],
            original_bytes[(int)Hook::Functions::GetQueuedCompletionStatus], 6, NULL);

        BOOL result = GetQueuedCompletionStatus(CompletionPort, lpNumberOfBytesTransferred, lpCompletionKey, lpOverlapped, dwMilliseconds
        );
        Hook reset_hook{ Hook::Functions::GetQueuedCompletionStatus };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetShortPathNameW(
        LPCWSTR lpszLongPath,
        LPWSTR  lpszShortPath,
        DWORD   cchBuffer
    ) {
        //unhook GetShortPathNameWtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetShortPathNameW],
            original_bytes[(int)Hook::Functions::GetShortPathNameW], 6, NULL);

        DWORD result = GetShortPathNameW(lpszLongPath, lpszShortPath, cchBuffer
        );
        Hook reset_hook{ Hook::Functions::GetShortPathNameW };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    UINT __stdcall newGetTempFileNameA(
        LPCSTR lpPathName,
        LPCSTR lpPrefixString,
        UINT   uUnique,
        LPSTR  lpTempFileName
    ) {
        //unhook GetTempFileNameAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetTempFileNameA],
            original_bytes[(int)Hook::Functions::GetTempFileNameA], 6, NULL);

        UINT result = GetTempFileNameA(lpPathName, lpPrefixString, uUnique, lpTempFileName
        );
        Hook reset_hook{ Hook::Functions::GetTempFileNameA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newGetTempPathA(
        DWORD nBufferLength,
        LPSTR lpBuffer
    ) {
        //unhook GetTempPathAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::GetTempPathA],
            original_bytes[(int)Hook::Functions::GetTempPathA], 6, NULL);

        DWORD result = GetTempPathA(nBufferLength, lpBuffer
        );
        Hook reset_hook{ Hook::Functions::GetTempPathA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL newLockFile(
        HANDLE hFile,
        DWORD  dwFileOffsetLow,
        DWORD  dwFileOffsetHigh,
        DWORD  nNumberOfBytesToLockLow,
        DWORD  nNumberOfBytesToLockHigh
    ) {
        //unhook LockFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::LockFile],
            original_bytes[(int)Hook::Functions::LockFile], 6, NULL);

        BOOL result = LockFile(hFile, dwFileOffsetLow, dwFileOffsetHigh, nNumberOfBytesToLockLow, nNumberOfBytesToLockHigh
        );
        Hook reset_hook{ Hook::Functions::LockFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newLockFileEx(
        HANDLE       hFile,
        DWORD        dwFlags,
        DWORD        dwReserved,
        DWORD        nNumberOfBytesToLockLow,
        DWORD        nNumberOfBytesToLockHigh,
        LPOVERLAPPED lpOverlapped
    ) {
        //unhook LockFileExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::LockFileEx],
            original_bytes[(int)Hook::Functions::LockFileEx], 6, NULL);

        BOOL result = LockFileEx(hFile, dwFlags, dwReserved, nNumberOfBytesToLockLow, nNumberOfBytesToLockHigh, lpOverlapped
        );
        Hook reset_hook{ Hook::Functions::LockFileEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newMoveFile(
        LPCTSTR lpExistingFileName,
        LPCTSTR lpNewFileName
    ) {
        //unhook MoveFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::MoveFile],
            original_bytes[(int)Hook::Functions::MoveFile], 6, NULL);

        BOOL result = MoveFile(lpExistingFileName, lpNewFileName
        );
        Hook reset_hook{ Hook::Functions::MoveFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newMoveFileExA(
        LPCSTR lpExistingFileName,
        LPCSTR lpNewFileName,
        DWORD  dwFlags
    ) {
        //unhook MoveFileExAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::MoveFileExA],
            original_bytes[(int)Hook::Functions::MoveFileExA], 6, NULL);

        BOOL result = MoveFileExA(lpExistingFileName, lpNewFileName, dwFlags
        );
        Hook reset_hook{ Hook::Functions::MoveFileExA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newMoveFileTransactedA(
        LPCSTR             lpExistingFileName,
        LPCSTR             lpNewFileName,
        LPPROGRESS_ROUTINE lpProgressRoutine,
        LPVOID             lpData,
        DWORD              dwFlags,
        HANDLE             hTransaction
    ) {
        //unhook MoveFileTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::MoveFileTransactedA],
            original_bytes[(int)Hook::Functions::MoveFileTransactedA], 6, NULL);

        BOOL result = MoveFileTransactedA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags, hTransaction
        );
        Hook reset_hook{ Hook::Functions::MoveFileTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newMoveFileWithProgressA(
        LPCSTR             lpExistingFileName,
        LPCSTR             lpNewFileName,
        LPPROGRESS_ROUTINE lpProgressRoutine,
        LPVOID             lpData,
        DWORD              dwFlags
    ) {
        //unhook MoveFileWithProgressAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::MoveFileWithProgressA],
            original_bytes[(int)Hook::Functions::MoveFileWithProgressA], 6, NULL);

        BOOL result = MoveFileWithProgressA(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, dwFlags
        );
        Hook reset_hook{ Hook::Functions::MoveFileWithProgressA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newOpenEncryptedFileRawA(
        LPCSTR lpFileName,
        ULONG  ulFlags,
        PVOID* pvContext
    ) {
        //unhook OpenEncryptedFileRawAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::OpenEncryptedFileRawA],
            original_bytes[(int)Hook::Functions::OpenEncryptedFileRawA], 6, NULL);

        DWORD result = OpenEncryptedFileRawA(lpFileName, ulFlags, pvContext
        );
        Hook reset_hook{ Hook::Functions::OpenEncryptedFileRawA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HFILE __stdcall newOpenFile(
        LPCSTR     lpFileName,
        LPOFSTRUCT lpReOpenBuff,
        UINT       uStyle
    ) {
        //unhook OpenFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::OpenFile],
            original_bytes[(int)Hook::Functions::OpenFile], 6, NULL);

        HFILE result = OpenFile(lpFileName, lpReOpenBuff, uStyle
        );
        Hook reset_hook{ Hook::Functions::OpenFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newOpenFileById(
        HANDLE                hVolumeHint,
        LPFILE_ID_DESCRIPTOR  lpFileId,
        DWORD                 dwDesiredAccess,
        DWORD                 dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD                 dwFlagsAndAttributes
    ) {
        //unhook OpenFileByIdtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::OpenFileById],
            original_bytes[(int)Hook::Functions::OpenFileById], 6, NULL);

        HANDLE result = OpenFileById(hVolumeHint, lpFileId, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwFlagsAndAttributes
        );
        Hook reset_hook{ Hook::Functions::OpenFileById };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newQueryRecoveryAgentsOnEncryptedFile(
        LPCWSTR                           lpFileName,
        PENCRYPTION_CERTIFICATE_HASH_LIST* pRecoveryAgents
    ) {
        //unhook QueryRecoveryAgentsOnEncryptedFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::QueryRecoveryAgentsOnEncryptedFile],
            original_bytes[(int)Hook::Functions::QueryRecoveryAgentsOnEncryptedFile], 6, NULL);

        DWORD result = QueryRecoveryAgentsOnEncryptedFile(lpFileName, pRecoveryAgents
        );
        Hook reset_hook{ Hook::Functions::QueryRecoveryAgentsOnEncryptedFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newQueryUsersOnEncryptedFile(
        LPCWSTR                           lpFileName,
        PENCRYPTION_CERTIFICATE_HASH_LIST* pUsers
    ) {
        //unhook QueryUsersOnEncryptedFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::QueryUsersOnEncryptedFile],
            original_bytes[(int)Hook::Functions::QueryUsersOnEncryptedFile], 6, NULL);

        DWORD result = QueryUsersOnEncryptedFile(lpFileName, pUsers
        );
        Hook reset_hook{ Hook::Functions::QueryUsersOnEncryptedFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newReadEncryptedFileRaw(
        PFE_EXPORT_FUNC pfExportCallback,
        PVOID           pvCallbackContext,
        PVOID           pvContext
    ) {
        //unhook ReadEncryptedFileRawtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::ReadEncryptedFileRaw],
            original_bytes[(int)Hook::Functions::ReadEncryptedFileRaw], 6, NULL);

        DWORD result = ReadEncryptedFileRaw(pfExportCallback, pvCallbackContext, pvContext
        );
        Hook reset_hook{ Hook::Functions::ReadEncryptedFileRaw };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newReadFile(
        HANDLE       hFile,
        LPVOID       lpBuffer,
        DWORD        nNumberOfBytesToRead,
        LPDWORD      lpNumberOfBytesRead,
        LPOVERLAPPED lpOverlapped
    ) {
        //unhook ReadFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::ReadFile],
            original_bytes[(int)Hook::Functions::ReadFile], 6, NULL);

        BOOL result = ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped
        );
        Hook reset_hook{ Hook::Functions::ReadFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newReadFileEx(
        HANDLE                          hFile,
        LPVOID                          lpBuffer,
        DWORD                           nNumberOfBytesToRead,
        LPOVERLAPPED                    lpOverlapped,
        LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ) {
        //unhook ReadFileExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::ReadFileEx],
            original_bytes[(int)Hook::Functions::ReadFileEx], 6, NULL);

        BOOL result = ReadFileEx(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine
        );
        Hook reset_hook{ Hook::Functions::ReadFileEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newRemoveUsersFromEncryptedFile(
        LPCWSTR                           lpFileName,
        PENCRYPTION_CERTIFICATE_HASH_LIST pHashes
    ) {
        //unhook RemoveUsersFromEncryptedFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::RemoveUsersFromEncryptedFile],
            original_bytes[(int)Hook::Functions::RemoveUsersFromEncryptedFile], 6, NULL);

        DWORD result = RemoveUsersFromEncryptedFile(lpFileName, pHashes
        );
        Hook reset_hook{ Hook::Functions::RemoveUsersFromEncryptedFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    HANDLE __stdcall newReOpenFile(
        HANDLE hOriginalFile,
        DWORD  dwDesiredAccess,
        DWORD  dwShareMode,
        DWORD  dwFlagsAndAttributes
    ) {
        //unhook ReOpenFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::ReOpenFile],
            original_bytes[(int)Hook::Functions::ReOpenFile], 6, NULL);

        HANDLE result = ReOpenFile(hOriginalFile, dwDesiredAccess, dwShareMode, dwFlagsAndAttributes
        );
        Hook reset_hook{ Hook::Functions::ReOpenFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newReplaceFileA(
        LPCSTR lpReplacedFileName,
        LPCSTR lpReplacementFileName,
        LPCSTR lpBackupFileName,
        DWORD  dwReplaceFlags,
        LPVOID lpExclude,
        LPVOID lpReserved
    ) {
        //unhook ReplaceFileAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::ReplaceFileA],
            original_bytes[(int)Hook::Functions::ReplaceFileA], 6, NULL);

        BOOL result = ReplaceFileA(lpReplacedFileName, lpReplacementFileName, lpBackupFileName, dwReplaceFlags, lpExclude, lpReserved
        );
        Hook reset_hook{ Hook::Functions::ReplaceFileA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newSearchPathA(
        LPCSTR lpPath,
        LPCSTR lpFileName,
        LPCSTR lpExtension,
        DWORD  nBufferLength,
        LPSTR  lpBuffer,
        LPSTR* lpFilePart
    ) {
        //unhook SearchPathAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SearchPathA],
            original_bytes[(int)Hook::Functions::SearchPathA], 6, NULL);

        DWORD result = SearchPathA(lpPath, lpFileName, lpExtension, nBufferLength, lpBuffer, lpFilePart
        );
        Hook reset_hook{ Hook::Functions::SearchPathA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetEndOfFile(
        HANDLE hFile
    ) {
        //unhook SetEndOfFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetEndOfFile],
            original_bytes[(int)Hook::Functions::SetEndOfFile], 6, NULL);

        BOOL result = SetEndOfFile(hFile
        );
        Hook reset_hook{ Hook::Functions::SetEndOfFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    void __stdcall newSetFileApisToANSI() {
        //unhook SetFileApisToANSItion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileApisToANSI],
            original_bytes[(int)Hook::Functions::SetFileApisToANSI], 6, NULL);

        SetFileApisToANSI();
        Hook reset_hook{ Hook::Functions::SetFileApisToANSI };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

    }
    void __stdcall newSetFileApisToOEM() {
        //unhook SetFileApisToOEMtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileApisToOEM],
            original_bytes[(int)Hook::Functions::SetFileApisToOEM], 6, NULL);

        SetFileApisToOEM();
        Hook reset_hook{ Hook::Functions::SetFileApisToOEM };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

    }
    BOOL __stdcall newSetFileAttributesA(
        LPCSTR lpFileName,
        DWORD  dwFileAttributes
    ) {
        //unhook SetFileAttributesAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileAttributesA],
            original_bytes[(int)Hook::Functions::SetFileAttributesA], 6, NULL);

        BOOL result = SetFileAttributesA(lpFileName, dwFileAttributes
        );
        Hook reset_hook{ Hook::Functions::SetFileAttributesA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileAttributesTransactedA(
        LPCSTR lpFileName,
        DWORD  dwFileAttributes,
        HANDLE hTransaction
    ) {
        //unhook SetFileAttributesTransactedAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileAttributesTransactedA],
            original_bytes[(int)Hook::Functions::SetFileAttributesTransactedA], 6, NULL);

        BOOL result = SetFileAttributesTransactedA(lpFileName, dwFileAttributes, hTransaction
        );
        Hook reset_hook{ Hook::Functions::SetFileAttributesTransactedA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileBandwidthReservation(
        HANDLE  hFile,
        DWORD   nPeriodMilliseconds,
        DWORD   nBytesPerPeriod,
        BOOL    bDiscardable,
        LPDWORD lpTransferSize,
        LPDWORD lpNumOutstandingRequests
    ) {
        //unhook SetFileBandwidthReservationtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileBandwidthReservation],
            original_bytes[(int)Hook::Functions::SetFileBandwidthReservation], 6, NULL);

        BOOL result = SetFileBandwidthReservation(hFile, nPeriodMilliseconds, nBytesPerPeriod, bDiscardable, lpTransferSize, lpNumOutstandingRequests
        );
        Hook reset_hook{ Hook::Functions::SetFileBandwidthReservation };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileCompletionNotificationModes(
        HANDLE FileHandle,
        UCHAR  Flags
    ) {
        //unhook SetFileCompletionNotificationModestion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileCompletionNotificationModes],
            original_bytes[(int)Hook::Functions::SetFileCompletionNotificationModes], 6, NULL);

        BOOL result = SetFileCompletionNotificationModes(FileHandle, Flags
        );
        Hook reset_hook{ Hook::Functions::SetFileCompletionNotificationModes };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileInformationByHandle(
        HANDLE                    hFile,
        FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
        LPVOID                    lpFileInformation,
        DWORD                     dwBufferSize
    ) {
        //unhook SetFileInformationByHandletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileInformationByHandle],
            original_bytes[(int)Hook::Functions::SetFileInformationByHandle], 6, NULL);

        BOOL result = SetFileInformationByHandle(hFile, FileInformationClass, lpFileInformation, dwBufferSize
        );
        Hook reset_hook{ Hook::Functions::SetFileInformationByHandle };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileIoOverlappedRange(
        HANDLE FileHandle,
        PUCHAR OverlappedRangeStart,
        ULONG  Length
    ) {
        //unhook SetFileIoOverlappedRangetion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileIoOverlappedRange],
            original_bytes[(int)Hook::Functions::SetFileIoOverlappedRange], 6, NULL);

        BOOL result = SetFileIoOverlappedRange(FileHandle, OverlappedRangeStart, Length
        );
        Hook reset_hook{ Hook::Functions::SetFileIoOverlappedRange };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newSetFilePointer(
        HANDLE hFile,
        LONG   lDistanceToMove,
        PLONG  lpDistanceToMoveHigh,
        DWORD  dwMoveMethod
    ) {
        //unhook SetFilePointertion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFilePointer],
            original_bytes[(int)Hook::Functions::SetFilePointer], 6, NULL);

        DWORD result = SetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod
        );
        Hook reset_hook{ Hook::Functions::SetFilePointer };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFilePointerEx(
        HANDLE         hFile,
        LARGE_INTEGER  liDistanceToMove,
        PLARGE_INTEGER lpNewFilePointer,
        DWORD          dwMoveMethod
    ) {
        //unhook SetFilePointerExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFilePointerEx],
            original_bytes[(int)Hook::Functions::SetFilePointerEx], 6, NULL);

        BOOL result = SetFilePointerEx(hFile, liDistanceToMove, lpNewFilePointer, dwMoveMethod
        );
        Hook reset_hook{ Hook::Functions::SetFilePointerEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileShortNameA(
        HANDLE hFile,
        LPCSTR lpShortName
    ) {
        //unhook SetFileShortNameAtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileShortNameA],
            original_bytes[(int)Hook::Functions::SetFileShortNameA], 6, NULL);

        BOOL result = SetFileShortNameA(hFile, lpShortName
        );
        Hook reset_hook{ Hook::Functions::SetFileShortNameA };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetFileValidData(
        HANDLE   hFile,
        LONGLONG ValidDataLength
    ) {
        //unhook SetFileValidDatation
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetFileValidData],
            original_bytes[(int)Hook::Functions::SetFileValidData], 6, NULL);

        BOOL result = SetFileValidData(hFile, ValidDataLength
        );
        Hook reset_hook{ Hook::Functions::SetFileValidData };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newSetSearchPathMode(
        DWORD Flags
    ) {
        //unhook SetSearchPathModetion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetSearchPathMode],
            original_bytes[(int)Hook::Functions::SetSearchPathMode], 6, NULL);

        BOOL result = SetSearchPathMode(Flags
        );
        Hook reset_hook{ Hook::Functions::SetSearchPathMode };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newSetUserFileEncryptionKey(
        PENCRYPTION_CERTIFICATE pEncryptionCertificate
    ) {
        //unhook SetUserFileEncryptionKeytion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::SetUserFileEncryptionKey],
            original_bytes[(int)Hook::Functions::SetUserFileEncryptionKey], 6, NULL);

        DWORD result = SetUserFileEncryptionKey(pEncryptionCertificate
        );
        Hook reset_hook{ Hook::Functions::SetUserFileEncryptionKey };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newUnlockFile(
        HANDLE hFile,
        DWORD  dwFileOffsetLow,
        DWORD  dwFileOffsetHigh,
        DWORD  nNumberOfBytesToUnlockLow,
        DWORD  nNumberOfBytesToUnlockHigh
    ) {
        //unhook UnlockFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::UnlockFile],
            original_bytes[(int)Hook::Functions::UnlockFile], 6, NULL);

        BOOL result = UnlockFile(hFile, dwFileOffsetLow, dwFileOffsetHigh, nNumberOfBytesToUnlockLow, nNumberOfBytesToUnlockHigh
        );
        Hook reset_hook{ Hook::Functions::UnlockFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newUnlockFileEx(
        HANDLE       hFile,
        DWORD        dwReserved,
        DWORD        nNumberOfBytesToUnlockLow,
        DWORD        nNumberOfBytesToUnlockHigh,
        LPOVERLAPPED lpOverlapped
    ) {
        //unhook UnlockFileExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::UnlockFileEx],
            original_bytes[(int)Hook::Functions::UnlockFileEx], 6, NULL);

        BOOL result = UnlockFileEx(hFile, dwReserved, nNumberOfBytesToUnlockLow, nNumberOfBytesToUnlockHigh, lpOverlapped
        );
        Hook reset_hook{ Hook::Functions::UnlockFileEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newWow64DisableWow64FsRedirection(
        PVOID* OldValue
    ) {
        //unhook Wow64DisableWow64FsRedirectiontion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::Wow64DisableWow64FsRedirection],
            original_bytes[(int)Hook::Functions::Wow64DisableWow64FsRedirection], 6, NULL);

        BOOL result = Wow64DisableWow64FsRedirection(OldValue
        );
        Hook reset_hook{ Hook::Functions::Wow64DisableWow64FsRedirection };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOLEAN __stdcall newWow64EnableWow64FsRedirection(
        BOOLEAN Wow64FsEnableRedirection
    ) {
        //unhook Wow64EnableWow64FsRedirectiontion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::Wow64EnableWow64FsRedirection],
            original_bytes[(int)Hook::Functions::Wow64EnableWow64FsRedirection], 6, NULL);

        BOOLEAN result = Wow64EnableWow64FsRedirection(Wow64FsEnableRedirection
        );
        Hook reset_hook{ Hook::Functions::Wow64EnableWow64FsRedirection };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newWow64RevertWow64FsRedirection(
        PVOID OlValue
    ) {
        //unhook Wow64RevertWow64FsRedirectiontion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::Wow64RevertWow64FsRedirection],
            original_bytes[(int)Hook::Functions::Wow64RevertWow64FsRedirection], 6, NULL);

        BOOL result = Wow64RevertWow64FsRedirection(OlValue
        );
        Hook reset_hook{ Hook::Functions::Wow64RevertWow64FsRedirection };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    DWORD __stdcall newWriteEncryptedFileRaw(
        PFE_IMPORT_FUNC pfImportCallback,
        PVOID           pvCallbackContext,
        PVOID           pvContext
    ) {
        //unhook WriteEncryptedFileRawtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::WriteEncryptedFileRaw],
            original_bytes[(int)Hook::Functions::WriteEncryptedFileRaw], 6, NULL);

        DWORD result = WriteEncryptedFileRaw(pfImportCallback, pvCallbackContext, pvContext
        );
        Hook reset_hook{ Hook::Functions::WriteEncryptedFileRaw };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newWriteFile(
        HANDLE       hFile,
        LPCVOID      lpBuffer,
        DWORD        nNumberOfBytesToWrite,
        LPDWORD      lpNumberOfBytesWritten,
        LPOVERLAPPED lpOverlapped
    ) {
        //unhook WriteFiletion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::WriteFile],
            original_bytes[(int)Hook::Functions::WriteFile], 6, NULL);

        BOOL result = WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped
        );
        Hook reset_hook{ Hook::Functions::WriteFile };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
    BOOL __stdcall newWriteFileEx(
        HANDLE                          hFile,
        LPCVOID                         lpBuffer,
        DWORD                           nNumberOfBytesToWrite,
        LPOVERLAPPED                    lpOverlapped,
        LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    ) {
        //unhook WriteFileExtion
        WriteProcessMemory(GetCurrentProcess(),
            (LPVOID)hooked_addr[(int)Hook::Functions::WriteFileEx],
            original_bytes[(int)Hook::Functions::WriteFileEx], 6, NULL);

        BOOL result = WriteFileEx(hFile, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, lpCompletionRoutine
        );
        Hook reset_hook{ Hook::Functions::WriteFileEx };
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

    }
}