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
  [in] LPCWSTR                      lpFileName,
  [in] PENCRYPTION_CERTIFICATE_LIST pEncryptionCertificates
);
BOOL __stdcall newAreFileApisANSI();
BOOL __stdcall newCheckNameLegalDOS8Dot3A(
  [in]            LPCSTR lpName,
  [out, optional] LPSTR  lpOemName,
  [in]            DWORD  OemNameSize,
  [out, optional] PBOOL  pbNameContainsSpaces,
  [out]           PBOOL  pbNameLegal
);
void __stdcall newCloseEncryptedFileRaw(
  [in] PVOID pvContext
);
BOOL __stdcall newCopyFile(
  [in] LPCTSTR lpExistingFileName,
  [in] LPCTSTR lpNewFileName,
  [in] BOOL    bFailIfExists
);
HRESULT __stdcall newCopyFile2(
  [in]           PCWSTR                        pwszExistingFileName,
  [in]           PCWSTR                        pwszNewFileName,
  [in, optional] COPYFILE2_EXTENDED_PARAMETERS *pExtendedParameters
);

BOOL __stdcall newCopyFileExA(
  [in]           LPCSTR             lpExistingFileName,
  [in]           LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in, optional] LPBOOL             pbCancel,
  [in]           DWORD              dwCopyFlags
);
BOOL __stdcall newCopyFileTransactedA(
  [in]           LPCSTR             lpExistingFileName,
  [in]           LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in, optional] LPBOOL             pbCancel,
  [in]           DWORD              dwCopyFlags,
  [in]           HANDLE             hTransaction
);

HANDLE __stdcall newCreateFileA(
  [in]           LPCSTR                lpFileName,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwCreationDisposition,
  [in]           DWORD                 dwFlagsAndAttributes,
  [in, optional] HANDLE                hTemplateFile
);
HANDLE __stdcall newCreateFile2(
  [in]           LPCWSTR                           lpFileName,
  [in]           DWORD                             dwDesiredAccess,
  [in]           DWORD                             dwShareMode,
  [in]           DWORD                             dwCreationDisposition,
  [in, optional] LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams
);
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
);
BOOL __stdcall newCreateHardLinkA(
  [in] LPCSTR                lpFileName,
  [in] LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
BOOL __stdcall newCreateHardLinkTransactedA(
  [in] LPCSTR                lpFileName,
  [in] LPCSTR                lpExistingFileName,
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in] HANDLE                hTransaction
);
BOOLEAN __stdcall newCreateSymbolicLinkA(
  [in] LPCSTR lpSymlinkFileName,
  [in] LPCSTR lpTargetFileName,
  [in] DWORD  dwFlags
);
BOOLEAN __stdcall newCreateSymbolicLinkTransactedA(
  [in] LPCSTR lpSymlinkFileName,
  [in] LPCSTR lpTargetFileName,
  [in] DWORD  dwFlags,
  [in] HANDLE hTransaction
);
BOOL __stdcall newDecryptFileA(
  [in] LPCSTR lpFileName,
       DWORD  dwReserved
);
BOOL __stdcall newDeleteFileA(
  [in] LPCSTR lpFileName
);
BOOL __stdcall newDeleteFileTransactedA(
  [in] LPCSTR lpFileName,
  [in] HANDLE hTransaction
);
DWORD __stdcall newDuplicateEncryptionInfoFile(
  [in]           LPCWSTR                     SrcFileName,
  [in]           LPCWSTR                     DstFileName,
  [in]           DWORD                       dwCreationDistribution,
  [in]           DWORD                       dwAttributes,
  [in, optional] const LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
BOOL __stdcall newEncryptFileA(
  [in] LPCSTR lpFileName
);
BOOL __stdcall newEncryptionDisable(
  [in] LPCWSTR DirPath,
  [in] BOOL    Disable
);

BOOL __stdcall newFileEncryptionStatusA(
  [in]  LPCSTR  lpFileName,
  [out] LPDWORD lpStatus
);

BOOL __stdcall newFindClose(
  [in, out] HANDLE hFindFile
);
HANDLE __stdcall newFindFirstFileA(
  [in]  LPCSTR             lpFileName,
  [out] LPWIN32_FIND_DATAA lpFindFileData
);
HANDLE __stdcall newFindFirstFileExA(
  [in]  LPCSTR             lpFileName,
  [in]  FINDEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID             lpFindFileData,
  [in]  FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
  [in]  DWORD              dwAdditionalFlags
);
HANDLE __stdcall newFindFirstFileNameTransactedW(
  [in]           LPCWSTR lpFileName,
  [in]           DWORD   dwFlags,
  [in, out]      LPDWORD StringLength,
  [in, out]      PWSTR   LinkName,
  [in, optional] HANDLE  hTransaction
);
HANDLE __stdcall newFindFirstFileNameW(
  [in]      LPCWSTR lpFileName,
  [in]      DWORD   dwFlags,
  [in, out] LPDWORD StringLength,
  [in, out] PWSTR   LinkName
);
HANDLE __stdcall newFindFirstFileTransactedA(
  [in]  LPCSTR             lpFileName,
  [in]  FINDEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID             lpFindFileData,
  [in]  FINDEX_SEARCH_OPS  fSearchOp,
        LPVOID             lpSearchFilter,
  [in]  DWORD              dwAdditionalFlags,
  [in]  HANDLE             hTransaction
);
HANDLE __stdcall newFindFirstStreamTransactedW(
  [in]  LPCWSTR            lpFileName,
  [in]  STREAM_INFO_LEVELS InfoLevel,
  [out] LPVOID             lpFindStreamData,
        DWORD              dwFlags,
  [in]  HANDLE             hTransaction
);
HANDLE __stdcall newFindFirstStreamW(
  [in]  LPCWSTR            lpFileName,
  [in]  STREAM_INFO_LEVELS InfoLevel,
  [out] LPVOID             lpFindStreamData,
        DWORD              dwFlags
);
BOOL __stdcall newFindNextFileA(
  [in]  HANDLE             hFindFile,
  [out] LPWIN32_FIND_DATAA lpFindFileData
);
BOOL __stdcall newFindNextFileNameW(
  [in]      HANDLE  hFindStream,
  [in, out] LPDWORD StringLength,
  [in, out] PWSTR   LinkName
);
BOOL __stdcall newFindNextStreamW(
  [in]  HANDLE hFindStream,
  [out] LPVOID lpFindStreamData
);
BOOL __stdcall newFlushFileBuffers(
  [in] HANDLE hFile
);
void __stdcall newFreeEncryptionCertificateHashList(
  [in] PENCRYPTION_CERTIFICATE_HASH_LIST pUsers
);
BOOL __stdcall newGetBinaryTypeA(
  [in]  LPCSTR  lpApplicationName,
  [out] LPDWORD lpBinaryType
);
DWORD __stdcall newGetCompressedFileSizeA(
  [in]            LPCSTR  lpFileName,
  [out, optional] LPDWORD lpFileSizeHigh
);
DWORD __stdcall newGetCompressedFileSizeTransactedA(
  [in]            LPCSTR  lpFileName,
  [out, optional] LPDWORD lpFileSizeHigh,
  [in]            HANDLE  hTransaction
);
INT __stdcall newGetExpandedNameA(
  [in]  LPSTR lpszSource,
  [out] LPSTR lpszBuffer
);
DWORD __stdcall newGetFileAttributesA(
  [in] LPCSTR lpFileName
);
BOOL __stdcall newGetFileAttributesExA(
  [in]  LPCSTR                 lpFileName,
  [in]  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID                 lpFileInformation
);
BOOL __stdcall newGetFileAttributesTransactedA(
  [in]  LPCSTR                 lpFileName,
  [in]  GET_FILEEX_INFO_LEVELS fInfoLevelId,
  [out] LPVOID                 lpFileInformation,
  [in]  HANDLE                 hTransaction
);
BOOL __stdcall newGetFileBandwidthReservation(
  [in]  HANDLE  hFile,
  [out] LPDWORD lpPeriodMilliseconds,
  [out] LPDWORD lpBytesPerPeriod,
  [out] LPBOOL  pDiscardable,
  [out] LPDWORD lpTransferSize,
  [out] LPDWORD lpNumOutstandingRequests
);
BOOL __stdcall newGetFileInformationByHandle(
  [in]  HANDLE                       hFile,
  [out] LPBY_HANDLE_FILE_INFORMATION lpFileInformation
);
BOOL __stdcall newGetFileInformationByHandleEx(
  [in]  HANDLE                    hFile,
  [in]  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  [out] LPVOID                    lpFileInformation,
  [in]  DWORD                     dwBufferSize
);
DWORD __stdcall newGetFileSize(
  [in]            HANDLE  hFile,
  [out, optional] LPDWORD lpFileSizeHigh
);
BOOL __stdcall newGetFileSizeEx(
  [in]  HANDLE         hFile,
  [out] PLARGE_INTEGER lpFileSize
);
DWORD __stdcall newGetFileType(
  [in] HANDLE hFile
);
DWORD __stdcall newGetFinalPathNameByHandleA(
  [in]  HANDLE hFile,
  [out] LPSTR  lpszFilePath,
  [in]  DWORD  cchFilePath,
  [in]  DWORD  dwFlags
);
DWORD __stdcall newGetFullPathNameA(
  [in]  LPCSTR lpFileName,
  [in]  DWORD  nBufferLength,
  [out] LPSTR  lpBuffer,
  [out] LPSTR  *lpFilePart
);
DWORD __stdcall newGetFullPathNameTransactedA(
  [in]  LPCSTR lpFileName,
  [in]  DWORD  nBufferLength,
  [out] LPSTR  lpBuffer,
  [out] LPSTR  *lpFilePart,
  [in]  HANDLE hTransaction
);
DWORD __stdcall newGetLongPathNameA(
  [in]  LPCSTR lpszShortPath,
  [out] LPSTR  lpszLongPath,
  [in]  DWORD  cchBuffer
);
DWORD __stdcall newGetLongPathNameTransactedA(
  [in]  LPCSTR lpszShortPath,
  [out] LPSTR  lpszLongPath,
  [in]  DWORD  cchBuffer,
  [in]  HANDLE hTransaction
);
BOOL __stdcall newGetQueuedCompletionStatus(
  [in]  HANDLE       CompletionPort,
        LPDWORD      lpNumberOfBytesTransferred,
  [out] PULONG_PTR   lpCompletionKey,
  [out] LPOVERLAPPED *lpOverlapped,
  [in]  DWORD        dwMilliseconds
);
DWORD __stdcall newGetShortPathNameW(
  [in]  LPCWSTR lpszLongPath,
  [out] LPWSTR  lpszShortPath,
  [in]  DWORD   cchBuffer
);
UINT __stdcall newGetTempFileNameA(
  [in]  LPCSTR lpPathName,
  [in]  LPCSTR lpPrefixString,
  [in]  UINT   uUnique,
  [out] LPSTR  lpTempFileName
);
DWORD __stdcall newGetTempPathA(
  [in]  DWORD nBufferLength,
  [out] LPSTR lpBuffer
);

BOOL __stdcall newLockFile(
  [in] HANDLE hFile,
  [in] DWORD  dwFileOffsetLow,
  [in] DWORD  dwFileOffsetHigh,
  [in] DWORD  nNumberOfBytesToLockLow,
  [in] DWORD  nNumberOfBytesToLockHigh
);
BOOL __stdcall newLockFileEx(
  [in]      HANDLE       hFile,
  [in]      DWORD        dwFlags,
            DWORD        dwReserved,
  [in]      DWORD        nNumberOfBytesToLockLow,
  [in]      DWORD        nNumberOfBytesToLockHigh,
  [in, out] LPOVERLAPPED lpOverlapped
);
void __stdcall newLZClose(
  [in] INT hFile
);
LONG __stdcall newLZCopy(
  [in] INT hfSource,
  [in] INT hfDest
);
INT __stdcall newLZInit(
  [in] INT hfSource
);
INT __stdcall newLZOpenFileA(
  [in]  LPSTR      lpFileName,
  [out] LPOFSTRUCT lpReOpenBuf,
  [in]  WORD       wStyle
);
INT __stdcall newLZRead(
  [in]  INT  hFile,
  [out] CHAR *lpBuffer,
  [in]  INT  cbRead
);
LONG __stdcall newLZSeek(
  [in] INT  hFile,
  [in] LONG lOffset,
  [in] INT  iOrigin
);
BOOL __stdcall newMoveFile(
  [in] LPCTSTR lpExistingFileName,
  [in] LPCTSTR lpNewFileName
);
BOOL __stdcall newMoveFileExA(
  [in]           LPCSTR lpExistingFileName,
  [in, optional] LPCSTR lpNewFileName,
  [in]           DWORD  dwFlags
);
BOOL __stdcall newMoveFileTransactedA(
  [in]           LPCSTR             lpExistingFileName,
  [in, optional] LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in]           DWORD              dwFlags,
  [in]           HANDLE             hTransaction
);
BOOL __stdcall newMoveFileWithProgressA(
  [in]           LPCSTR             lpExistingFileName,
  [in, optional] LPCSTR             lpNewFileName,
  [in, optional] LPPROGRESS_ROUTINE lpProgressRoutine,
  [in, optional] LPVOID             lpData,
  [in]           DWORD              dwFlags
);
DWORD __stdcall newOpenEncryptedFileRawA(
  [in]  LPCSTR lpFileName,
  [in]  ULONG  ulFlags,
  [out] PVOID  *pvContext
);
HFILE __stdcall newOpenFile(
  [in]  LPCSTR     lpFileName,
  [out] LPOFSTRUCT lpReOpenBuff,
  [in]  UINT       uStyle
);
HANDLE __stdcall newOpenFileById(
  [in]           HANDLE                hVolumeHint,
  [in]           LPFILE_ID_DESCRIPTOR  lpFileId,
  [in]           DWORD                 dwDesiredAccess,
  [in]           DWORD                 dwShareMode,
  [in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                 dwFlagsAndAttributes
);
DWORD __stdcall newQueryRecoveryAgentsOnEncryptedFile(
  [in]  LPCWSTR                           lpFileName,
  [out] PENCRYPTION_CERTIFICATE_HASH_LIST *pRecoveryAgents
);
DWORD __stdcall newQueryUsersOnEncryptedFile(
  [in]  LPCWSTR                           lpFileName,
  [out] PENCRYPTION_CERTIFICATE_HASH_LIST *pUsers
);
DWORD __stdcall newReadEncryptedFileRaw(
  [in]           PFE_EXPORT_FUNC pfExportCallback,
  [in, optional] PVOID           pvCallbackContext,
  [in]           PVOID           pvContext
);
BOOL __stdcall newReadFile(
  [in]                HANDLE       hFile,
  [out]               LPVOID       lpBuffer,
  [in]                DWORD        nNumberOfBytesToRead,
  [out, optional]     LPDWORD      lpNumberOfBytesRead,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
BOOL __stdcall newReadFileEx(
  [in]            HANDLE                          hFile,
  [out, optional] LPVOID                          lpBuffer,
  [in]            DWORD                           nNumberOfBytesToRead,
  [in, out]       LPOVERLAPPED                    lpOverlapped,
  [in]            LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);

DWORD __stdcall newRemoveUsersFromEncryptedFile(
  [in] LPCWSTR                           lpFileName,
  [in] PENCRYPTION_CERTIFICATE_HASH_LIST pHashes
);
HANDLE __stdcall newReOpenFile(
  [in] HANDLE hOriginalFile,
  [in] DWORD  dwDesiredAccess,
  [in] DWORD  dwShareMode,
  [in] DWORD  dwFlagsAndAttributes
);
BOOL __stdcall newReplaceFileA(
  [in]           LPCSTR lpReplacedFileName,
  [in]           LPCSTR lpReplacementFileName,
  [in, optional] LPCSTR lpBackupFileName,
  [in]           DWORD  dwReplaceFlags,
                 LPVOID lpExclude,
                 LPVOID lpReserved
);
DWORD __stdcall newSearchPathA(
  [in, optional]  LPCSTR lpPath,
  [in]            LPCSTR lpFileName,
  [in, optional]  LPCSTR lpExtension,
  [in]            DWORD  nBufferLength,
  [out]           LPSTR  lpBuffer,
  [out, optional] LPSTR  *lpFilePart
);
BOOL __stdcall newSetEndOfFile(
  [in] HANDLE hFile
);
void __stdcall newSetFileApisToANSI();
void __stdcall newSetFileApisToOEM();
BOOL __stdcall newSetFileAttributesA(
  [in] LPCSTR lpFileName,
  [in] DWORD  dwFileAttributes
);
BOOL __stdcall newSetFileAttributesTransactedA(
  [in] LPCSTR lpFileName,
  [in] DWORD  dwFileAttributes,
  [in] HANDLE hTransaction
);
BOOL __stdcall newSetFileBandwidthReservation(
  [in]  HANDLE  hFile,
  [in]  DWORD   nPeriodMilliseconds,
  [in]  DWORD   nBytesPerPeriod,
  [in]  BOOL    bDiscardable,
  [out] LPDWORD lpTransferSize,
  [out] LPDWORD lpNumOutstandingRequests
);
BOOL __stdcall newSetFileCompletionNotificationModes(
  [in] HANDLE FileHandle,
  [in] UCHAR  Flags
);
BOOL __stdcall newSetFileInformationByHandle(
  [in] HANDLE                    hFile,
  [in] FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
  [in] LPVOID                    lpFileInformation,
  [in] DWORD                     dwBufferSize
);
BOOL __stdcall newSetFileIoOverlappedRange(
  [in] HANDLE FileHandle,
  [in] PUCHAR OverlappedRangeStart,
  [in] ULONG  Length
);
DWORD __stdcall newSetFilePointer(
  [in]                HANDLE hFile,
  [in]                LONG   lDistanceToMove,
  [in, out, optional] PLONG  lpDistanceToMoveHigh,
  [in]                DWORD  dwMoveMethod
);
BOOL __stdcall newSetFilePointerEx(
  [in]            HANDLE         hFile,
  [in]            LARGE_INTEGER  liDistanceToMove,
  [out, optional] PLARGE_INTEGER lpNewFilePointer,
  [in]            DWORD          dwMoveMethod
);
BOOL __stdcall newSetFileShortNameA(
  [in] HANDLE hFile,
  [in] LPCSTR lpShortName
);
BOOL __stdcall newSetFileValidData(
  [in] HANDLE   hFile,
  [in] LONGLONG ValidDataLength
);
BOOL __stdcall newSetSearchPathMode(
  [in] DWORD Flags
);
DWORD __stdcall newSetUserFileEncryptionKey(
  [in] PENCRYPTION_CERTIFICATE pEncryptionCertificate
);
BOOL __stdcall newUnlockFile(
  [in] HANDLE hFile,
  [in] DWORD  dwFileOffsetLow,
  [in] DWORD  dwFileOffsetHigh,
  [in] DWORD  nNumberOfBytesToUnlockLow,
  [in] DWORD  nNumberOfBytesToUnlockHigh
);
BOOL __stdcall newUnlockFileEx(
  [in]      HANDLE       hFile,
            DWORD        dwReserved,
  [in]      DWORD        nNumberOfBytesToUnlockLow,
  [in]      DWORD        nNumberOfBytesToUnlockHigh,
  [in, out] LPOVERLAPPED lpOverlapped
);

BOOL __stdcall newWofenumfilesproc(
  [in]           PCWSTR FilePath,
  [in]           PVOID ExternalFileInfo,
  [in, optional] PVOID UserData
);

HRESULT __stdcall newWofGetDriverVersion(
  [in]  HANDLE FileOrVolumeHandle,
  [in]  ULONG  Provider,
  [out] PULONG WofVersion
);
HRESULT __stdcall newWofIsExternalFile(
  [in]                LPCWSTR FilePath,
  [out, optional]     PBOOL   IsExternalFile,
  [out, optional]     PULONG  Provider,
  [out, optional]     PVOID   ExternalFileInfo,
  [in, out, optional] PULONG  BufferLength
);
HRESULT __stdcall newWofSetFileDataLocation(
  [in] HANDLE FileHandle,
  [in] ULONG  Provider,
  [in] PVOID  ExternalFileInfo,
  [in] ULONG  Length
);
BOOL __stdcall newWofShouldCompressBinaries(
  [in]  LPCWSTR Volume,
  [out] PULONG  Algorithm
);
HRESULT __stdcall newWofWimAddEntry(
  [in]  PCWSTR         VolumeName,
  [in]  PCWSTR         WimPath,
  [in]  DWORD          WimType,
  [in]  DWORD          WimIndex,
  [out] PLARGE_INTEGER DataSourceId
);

HRESULT __stdcall newWofWimRemoveEntry(
  [in] PCWSTR        VolumeName,
  [in] LARGE_INTEGER DataSourceId
);
HRESULT __stdcall newWofWimSuspendEntry(
  [in] PCWSTR        VolumeName,
  [in] LARGE_INTEGER DataSourceId
);
HRESULT __stdcall newWofWimUpdateEntry(
  [in] PCWSTR        VolumeName,
  [in] LARGE_INTEGER DataSourceId,
  [in] PCWSTR        NewWimPath
);
BOOL __stdcall newWow64DisableWow64FsRedirection(
  [out] PVOID *OldValue
);
BOOLEAN __stdcall newWow64EnableWow64FsRedirection(
  BOOLEAN Wow64FsEnableRedirection
);
BOOL __stdcall newWow64RevertWow64FsRedirection(
  PVOID OlValue
);
DWORD __stdcall newWriteEncryptedFileRaw(
  [in]           PFE_IMPORT_FUNC pfImportCallback,
  [in, optional] PVOID           pvCallbackContext,
  [in]           PVOID           pvContext
);
BOOL __stdcall newWriteFile(
  [in]                HANDLE       hFile,
  [in]                LPCVOID      lpBuffer,
  [in]                DWORD        nNumberOfBytesToWrite,
  [out, optional]     LPDWORD      lpNumberOfBytesWritten,
  [in, out, optional] LPOVERLAPPED lpOverlapped
);
BOOL __stdcall newWriteFileEx(
  [in]           HANDLE                          hFile,
  [in, optional] LPCVOID                         lpBuffer,
  [in]           DWORD                           nNumberOfBytesToWrite,
  [in, out]      LPOVERLAPPED                    lpOverlapped,
  [in]           LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
);
}