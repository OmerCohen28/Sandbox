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
DWORD __stdcall newAddUsersToEncryptedFile(
       LPCWSTR                      lpFileName,
       PENCRYPTION_CERTIFICATE_LIST pEncryptionCertificates
);
BOOL __stdcall newAreFileApisANSI();
BOOL __stdcall newCheckNameLegalDOS8Dot3A(
                  LPCSTR lpName,
                  LPSTR  lpOemName,
                  DWORD  OemNameSize,
                  PBOOL  pbNameContainsSpaces,
                  PBOOL  pbNameLegal
);
void __stdcall newCloseEncryptedFileRaw(
       PVOID pvContext
);
BOOL __stdcall newCopyFile(
       LPCTSTR lpExistingFileName,
       LPCTSTR lpNewFileName,
       BOOL    bFailIfExists
);
HRESULT __stdcall newCopyFile2(
                 PCWSTR                        pwszExistingFileName,
                 PCWSTR                        pwszNewFileName,
                 COPYFILE2_EXTENDED_PARAMETERS *pExtendedParameters
);
BOOL newCopyFileExA(
                 LPCSTR             lpExistingFileName,
                 LPCSTR             lpNewFileName,
                 LPPROGRESS_ROUTINE lpProgressRoutine,
                 LPVOID             lpData,
                 LPBOOL             pbCancel,
                 DWORD              dwCopyFlags
);
BOOL __stdcall newCopyFileTransactedA(
                 LPCSTR             lpExistingFileName,
                 LPCSTR             lpNewFileName,
                 LPPROGRESS_ROUTINE lpProgressRoutine,
                 LPVOID             lpData,
                 LPBOOL             pbCancel,
                 DWORD              dwCopyFlags,
                 HANDLE             hTransaction
);
HANDLE newCreateFileA(
                 LPCSTR                lpFileName,
                 DWORD                 dwDesiredAccess,
                 DWORD                 dwShareMode,
                 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                 DWORD                 dwCreationDisposition,
                 DWORD                 dwFlagsAndAttributes,
                 HANDLE                hTemplateFile
);
HANDLE __stdcall newCreateFile2(
                 LPCWSTR                           lpFileName,
                 DWORD                             dwDesiredAccess,
                 DWORD                             dwShareMode,
                 DWORD                             dwCreationDisposition,
                 LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams
);
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
);
BOOL __stdcall newCreateHardLinkA(
       LPCSTR                lpFileName,
       LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
BOOL __stdcall newCreateHardLinkTransactedA(
       LPCSTR                lpFileName,
       LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
       HANDLE                hTransaction
);
BOOLEAN __stdcall newCreateSymbolicLinkA(
       LPCSTR lpSymlinkFileName,
       LPCSTR lpTargetFileName,
       DWORD  dwFlags
);
BOOLEAN __stdcall newCreateSymbolicLinkTransactedA(
       LPCSTR lpSymlinkFileName,
       LPCSTR lpTargetFileName,
       DWORD  dwFlags,
       HANDLE hTransaction
);
BOOL __stdcall newDecryptFileA(
       LPCSTR lpFileName,
       DWORD  dwReserved
);
BOOL __stdcall newDeleteFileA(
       LPCSTR lpFileName
);
BOOL __stdcall newDeleteFileTransactedA(
       LPCSTR lpFileName,
       HANDLE hTransaction
);
DWORD __stdcall newDuplicateEncryptionInfoFile(
                 LPCWSTR                     SrcFileName,
                 LPCWSTR                     DstFileName,
                 DWORD                       dwCreationDistribution,
                 DWORD                       dwAttributes,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
BOOL __stdcall newEncryptFileA(
       LPCSTR lpFileName
);
BOOL __stdcall newEncryptionDisable(
       LPCWSTR DirPath,
       BOOL    Disable
);
BOOL newFileEncryptionStatusA(
        LPCSTR  lpFileName,
        LPDWORD lpStatus
);
BOOL newFindClose(
            HANDLE hFindFile
);
HANDLE __stdcall newFindFirstFileA(
        LPCSTR             lpFileName,
        LPWIN32_FIND_DATAA lpFindFileData
);
HANDLE __stdcall newFindFirstFileExA(
        LPCSTR             lpFileName,
        FINDEX_INFO_LEVELS fInfoLevelId,
        LPVOID             lpFindFileData,
        FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
        DWORD              dwAdditionalFlags
);
HANDLE __stdcall newFindFirstFileNameTransactedW(
                 LPCWSTR lpFileName,
                 DWORD   dwFlags,
                 LPDWORD StringLength,
                 PWSTR   LinkName,
                 HANDLE  hTransaction
);
HANDLE __stdcall newFindFirstFileNameW(
            LPCWSTR lpFileName,
            DWORD   dwFlags,
            LPDWORD StringLength,
            PWSTR   LinkName
);
HANDLE __stdcall newFindFirstFileTransactedA(
        LPCSTR             lpFileName,
        FINDEX_INFO_LEVELS fInfoLevelId,
        LPVOID             lpFindFileData,
        FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
        DWORD              dwAdditionalFlags,
        HANDLE             hTransaction
);
HANDLE __stdcall newFindFirstStreamTransactedW(
        LPCWSTR            lpFileName,
        STREAM_INFO_LEVELS InfoLevel,
        LPVOID             lpFindStreamData,
        DWORD              dwFlags,
        HANDLE             hTransaction
);
HANDLE __stdcall newFindFirstStreamW(
        LPCWSTR            lpFileName,
        STREAM_INFO_LEVELS InfoLevel,
        LPVOID             lpFindStreamData,
        DWORD              dwFlags
);
BOOL __stdcall newFindNextFileA(
        HANDLE             hFindFile,
        LPWIN32_FIND_DATAA lpFindFileData
);
BOOL __stdcall newFindNextFileNameW(
            HANDLE  hFindStream,
            LPDWORD StringLength,
            PWSTR   LinkName
);
BOOL __stdcall newFindNextStreamW(
        HANDLE hFindStream,
        LPVOID lpFindStreamData
);
BOOL __stdcall newFlushFileBuffers(
       HANDLE hFile
);
void __stdcall newFreeEncryptionCertificateHashList(
       PENCRYPTION_CERTIFICATE_HASH_LIST pUsers
);
BOOL __stdcall newGetBinaryTypeA(
        LPCSTR  lpApplicationName,
        LPDWORD lpBinaryType
);
DWORD __stdcall newGetCompressedFileSizeA(
                  LPCSTR  lpFileName,
                  LPDWORD lpFileSizeHigh
);
DWORD __stdcall newGetCompressedFileSizeTransactedA(
                  LPCSTR  lpFileName,
                  LPDWORD lpFileSizeHigh,
                  HANDLE  hTransaction
);
DWORD __stdcall newGetFileAttributesA(
       LPCSTR lpFileName
);
BOOL __stdcall newGetFileAttributesExA(
        LPCSTR                 lpFileName,
        GET_FILEEX_INFO_LEVELS fInfoLevelId,
        LPVOID                 lpFileInformation
);
BOOL __stdcall newGetFileAttributesTransactedA(
        LPCSTR                 lpFileName,
        GET_FILEEX_INFO_LEVELS fInfoLevelId,
        LPVOID                 lpFileInformation,
        HANDLE                 hTransaction
);
BOOL __stdcall newGetFileBandwidthReservation(
        HANDLE  hFile,
        LPDWORD lpPeriodMilliseconds,
        LPDWORD lpBytesPerPeriod,
        LPBOOL  pDiscardable,
        LPDWORD lpTransferSize,
        LPDWORD lpNumOutstandingRequests
);
BOOL __stdcall newGetFileInformationByHandle(
        HANDLE                       hFile,
        LPBY_HANDLE_FILE_INFORMATION lpFileInformation
);
BOOL __stdcall newGetFileInformationByHandleEx(
        HANDLE                    hFile,
        FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
        LPVOID                    lpFileInformation,
        DWORD                     dwBufferSize
);
DWORD __stdcall newGetFileSize(
                  HANDLE  hFile,
                  LPDWORD lpFileSizeHigh
);
BOOL __stdcall newGetFileSizeEx(
        HANDLE         hFile,
        PLARGE_INTEGER lpFileSize
);
DWORD __stdcall newGetFileType(
       HANDLE hFile
);
DWORD __stdcall newGetFinalPathNameByHandleA(
        HANDLE hFile,
        LPSTR  lpszFilePath,
        DWORD  cchFilePath,
        DWORD  dwFlags
);
DWORD __stdcall newGetFullPathNameA(
        LPCSTR lpFileName,
        DWORD  nBufferLength,
        LPSTR  lpBuffer,
        LPSTR  *lpFilePart
);
DWORD __stdcall newGetFullPathNameTransactedA(
        LPCSTR lpFileName,
        DWORD  nBufferLength,
        LPSTR  lpBuffer,
        LPSTR  *lpFilePart,
        HANDLE hTransaction
);
DWORD __stdcall newGetLongPathNameA(
        LPCSTR lpszShortPath,
        LPSTR  lpszLongPath,
        DWORD  cchBuffer
);
DWORD __stdcall newGetLongPathNameTransactedA(
        LPCSTR lpszShortPath,
        LPSTR  lpszLongPath,
        DWORD  cchBuffer,
        HANDLE hTransaction
);
BOOL __stdcall newGetQueuedCompletionStatus(
        HANDLE       CompletionPort,
        LPDWORD      lpNumberOfBytesTransferred,
        PULONG_PTR   lpCompletionKey,
        LPOVERLAPPED *lpOverlapped,
        DWORD        dwMilliseconds
);
DWORD __stdcall newGetShortPathNameW(
        LPCWSTR lpszLongPath,
        LPWSTR  lpszShortPath,
        DWORD   cchBuffer
);
UINT __stdcall newGetTempFileNameA(
        LPCSTR lpPathName,
        LPCSTR lpPrefixString,
        UINT   uUnique,
        LPSTR  lpTempFileName
);
DWORD __stdcall newGetTempPathA(
        DWORD nBufferLength,
        LPSTR lpBuffer
);
BOOL newLockFile(
       HANDLE hFile,
       DWORD  dwFileOffsetLow,
       DWORD  dwFileOffsetHigh,
       DWORD  nNumberOfBytesToLockLow,
       DWORD  nNumberOfBytesToLockHigh
);
BOOL __stdcall newLockFileEx(
            HANDLE       hFile,
            DWORD        dwFlags,
            DWORD        dwReserved,
            DWORD        nNumberOfBytesToLockLow,
            DWORD        nNumberOfBytesToLockHigh,
            LPOVERLAPPED lpOverlapped
);
BOOL __stdcall newMoveFile(
       LPCTSTR lpExistingFileName,
       LPCTSTR lpNewFileName
);
BOOL __stdcall newMoveFileExA(
                 LPCSTR lpExistingFileName,
                 LPCSTR lpNewFileName,
                 DWORD  dwFlags
);
BOOL __stdcall newMoveFileTransactedA(
                 LPCSTR             lpExistingFileName,
                 LPCSTR             lpNewFileName,
                 LPPROGRESS_ROUTINE lpProgressRoutine,
                 LPVOID             lpData,
                 DWORD              dwFlags,
                 HANDLE             hTransaction
);
BOOL __stdcall newMoveFileWithProgressA(
                 LPCSTR             lpExistingFileName,
                 LPCSTR             lpNewFileName,
                 LPPROGRESS_ROUTINE lpProgressRoutine,
                 LPVOID             lpData,
                 DWORD              dwFlags
);
DWORD __stdcall newOpenEncryptedFileRawA(
        LPCSTR lpFileName,
        ULONG  ulFlags,
        PVOID  *pvContext
);
HFILE __stdcall newOpenFile(
        LPCSTR     lpFileName,
        LPOFSTRUCT lpReOpenBuff,
        UINT       uStyle
);
HANDLE __stdcall newOpenFileById(
                 HANDLE                hVolumeHint,
                 LPFILE_ID_DESCRIPTOR  lpFileId,
                 DWORD                 dwDesiredAccess,
                 DWORD                 dwShareMode,
                 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                 DWORD                 dwFlagsAndAttributes
);
DWORD __stdcall newQueryRecoveryAgentsOnEncryptedFile(
        LPCWSTR                           lpFileName,
        PENCRYPTION_CERTIFICATE_HASH_LIST *pRecoveryAgents
);
DWORD __stdcall newQueryUsersOnEncryptedFile(
        LPCWSTR                           lpFileName,
        PENCRYPTION_CERTIFICATE_HASH_LIST *pUsers
);
DWORD __stdcall newReadEncryptedFileRaw(
                 PFE_EXPORT_FUNC pfExportCallback,
                 PVOID           pvCallbackContext,
                 PVOID           pvContext
);
BOOL __stdcall newReadFile(
                      HANDLE       hFile,
                      LPVOID       lpBuffer,
                      DWORD        nNumberOfBytesToRead,
                      LPDWORD      lpNumberOfBytesRead,
                      LPOVERLAPPED lpOverlapped
);
BOOL __stdcall newReadFileEx(
                  HANDLE                          hFile,
                  LPVOID                          lpBuffer,
                  DWORD                           nNumberOfBytesToRead,
                  LPOVERLAPPED                    lpOverlapped,
                  LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
DWORD __stdcall newRemoveUsersFromEncryptedFile(
       LPCWSTR                           lpFileName,
       PENCRYPTION_CERTIFICATE_HASH_LIST pHashes
);
HANDLE __stdcall newReOpenFile(
       HANDLE hOriginalFile,
       DWORD  dwDesiredAccess,
       DWORD  dwShareMode,
       DWORD  dwFlagsAndAttributes
);
BOOL __stdcall newReplaceFileA(
                 LPCSTR lpReplacedFileName,
                 LPCSTR lpReplacementFileName,
                 LPCSTR lpBackupFileName,
                 DWORD  dwReplaceFlags,
                 LPVOID lpExclude,
                 LPVOID lpReserved
);
DWORD __stdcall newSearchPathA(
                  LPCSTR lpPath,
                  LPCSTR lpFileName,
                  LPCSTR lpExtension,
                  DWORD  nBufferLength,
                  LPSTR  lpBuffer,
                  LPSTR  *lpFilePart
);
BOOL __stdcall newSetEndOfFile(
       HANDLE hFile
);
void __stdcall newSetFileApisToANSI();
void __stdcall newSetFileApisToOEM();
BOOL __stdcall newSetFileAttributesA(
       LPCSTR lpFileName,
       DWORD  dwFileAttributes
);
BOOL __stdcall newSetFileAttributesTransactedA(
       LPCSTR lpFileName,
       DWORD  dwFileAttributes,
       HANDLE hTransaction
);
BOOL __stdcall newSetFileBandwidthReservation(
        HANDLE  hFile,
        DWORD   nPeriodMilliseconds,
        DWORD   nBytesPerPeriod,
        BOOL    bDiscardable,
        LPDWORD lpTransferSize,
        LPDWORD lpNumOutstandingRequests
);
BOOL __stdcall newSetFileCompletionNotificationModes(
       HANDLE FileHandle,
       UCHAR  Flags
);
BOOL __stdcall newSetFileInformationByHandle(
       HANDLE                    hFile,
       FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
       LPVOID                    lpFileInformation,
       DWORD                     dwBufferSize
);
BOOL __stdcall newSetFileIoOverlappedRange(
       HANDLE FileHandle,
       PUCHAR OverlappedRangeStart,
       ULONG  Length
);
DWORD __stdcall newSetFilePointer(
                      HANDLE hFile,
                      LONG   lDistanceToMove,
                      PLONG  lpDistanceToMoveHigh,
                      DWORD  dwMoveMethod
);
BOOL __stdcall newSetFilePointerEx(
                  HANDLE         hFile,
                  LARGE_INTEGER  liDistanceToMove,
                  PLARGE_INTEGER lpNewFilePointer,
                  DWORD          dwMoveMethod
);
BOOL __stdcall newSetFileShortNameA(
       HANDLE hFile,
       LPCSTR lpShortName
);
BOOL __stdcall newSetFileValidData(
       HANDLE   hFile,
       LONGLONG ValidDataLength
);
BOOL __stdcall newSetSearchPathMode(
       DWORD Flags
);
DWORD __stdcall newSetUserFileEncryptionKey(
       PENCRYPTION_CERTIFICATE pEncryptionCertificate
);
BOOL __stdcall newUnlockFile(
       HANDLE hFile,
       DWORD  dwFileOffsetLow,
       DWORD  dwFileOffsetHigh,
       DWORD  nNumberOfBytesToUnlockLow,
       DWORD  nNumberOfBytesToUnlockHigh
);
BOOL __stdcall newUnlockFileEx(
            HANDLE       hFile,
            DWORD        dwReserved,
            DWORD        nNumberOfBytesToUnlockLow,
            DWORD        nNumberOfBytesToUnlockHigh,
            LPOVERLAPPED lpOverlapped
);
BOOL __stdcall newWow64DisableWow64FsRedirection(
        PVOID *OldValue
);
BOOLEAN __stdcall newWow64EnableWow64FsRedirection(
  BOOLEAN Wow64FsEnableRedirection
);
BOOL __stdcall newWow64RevertWow64FsRedirection(
  PVOID OlValue
);
DWORD __stdcall newWriteEncryptedFileRaw(
                 PFE_IMPORT_FUNC pfImportCallback,
                 PVOID           pvCallbackContext,
                 PVOID           pvContext
);
BOOL __stdcall newWriteFile(
                      HANDLE       hFile,
                      LPCVOID      lpBuffer,
                      DWORD        nNumberOfBytesToWrite,
                      LPDWORD      lpNumberOfBytesWritten,
                      LPOVERLAPPED lpOverlapped
);
BOOL __stdcall newWriteFileEx(
                 HANDLE                          hFile,
                 LPCVOID                         lpBuffer,
                 DWORD                           nNumberOfBytesToWrite,
                 LPOVERLAPPED                    lpOverlapped,
                 LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
}