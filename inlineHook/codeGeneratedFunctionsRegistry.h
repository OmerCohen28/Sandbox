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
BOOL __stdcall newGetSystemRegistryQuota(
  [out, optional] PDWORD pdwQuotaAllowed,
  [out, optional] PDWORD pdwQuotaUsed
);
LSTATUS __stdcall newRegCloseKey(
  [in] HKEY hKey
);
LSTATUS __stdcall newRegConnectRegistryA(
  [in, optional] LPCSTR lpMachineName,
  [in]           HKEY   hKey,
  [out]          PHKEY  phkResult
);
LSTATUS __stdcall newRegCopyTreeA(
  [in]           HKEY   hKeySrc,
  [in, optional] LPCSTR lpSubKey,
  [in]           HKEY   hKeyDest
);
LSTATUS __stdcall newRegCreateKeyExA(
  [in]            HKEY                        hKey,
  [in]            LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
  [in, optional]  LPSTR                       lpClass,
  [in]            DWORD                       dwOptions,
  [in]            REGSAM                      samDesired,
  [in, optional]  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [out]           PHKEY                       phkResult,
  [out, optional] LPDWORD                     lpdwDisposition
);
LSTATUS __stdcall newRegCreateKeyTransactedA(
  [in]            HKEY                        hKey,
  [in]            LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
  [in, optional]  LPSTR                       lpClass,
  [in]            DWORD                       dwOptions,
  [in]            REGSAM                      samDesired,
  [in, optional]  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [out]           PHKEY                       phkResult,
  [out, optional] LPDWORD                     lpdwDisposition,
  [in]            HANDLE                      hTransaction,
                  PVOID                       pExtendedParemeter
);
LSTATUS __stdcall newRegDeleteKeyA(
  [in] HKEY   hKey,
  [in] LPCSTR lpSubKey
);
LSTATUS __stdcall newRegDeleteKeyExA(
  [in] HKEY   hKey,
  [in] LPCSTR lpSubKey,
  [in] REGSAM samDesired,
       DWORD  Reserved
);
LSTATUS __stdcall newRegDeleteKeyTransactedA(
  [in] HKEY   hKey,
  [in] LPCSTR lpSubKey,
  [in] REGSAM samDesired,
       DWORD  Reserved,
  [in] HANDLE hTransaction,
       PVOID  pExtendedParameter
);
LSTATUS __stdcall newRegDeleteKeyValueA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey,
  [in, optional] LPCSTR lpValueName
);
LSTATUS __stdcall newRegDeleteTreeA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey
);
LSTATUS __stdcall newRegDeleteValueA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpValueName
);
LSTATUS __stdcall newRegDisablePredefinedCache();
LSTATUS __stdcall newRegDisablePredefinedCacheEx();
LONG __stdcall newRegDisableReflectionKey(
  [in] HKEY hBase
);
LONG __stdcall newRegEnableReflectionKey(
  [in] HKEY hBase
);
LSTATUS __stdcall newRegEnumKeyExA(
  [in]                HKEY      hKey,
  [in]                DWORD     dwIndex,
  [out]               LPSTR     lpName,
  [in, out]           LPDWORD   lpcchName,
                      LPDWORD   lpReserved,
  [in, out]           LPSTR     lpClass,
  [in, out, optional] LPDWORD   lpcchClass,
  [out, optional]     PFILETIME lpftLastWriteTime
);
LSTATUS __stdcall newRegEnumValueA(
  [in]                HKEY    hKey,
  [in]                DWORD   dwIndex,
  [out]               LPSTR   lpValueName,
  [in, out]           LPDWORD lpcchValueName,
                      LPDWORD lpReserved,
  [out, optional]     LPDWORD lpType,
  [out, optional]     LPBYTE  lpData,
  [in, out, optional] LPDWORD lpcbData
);
LSTATUS __stdcall newRegFlushKey(
  [in] HKEY hKey
);
LSTATUS __stdcall newRegGetKeySecurity(
  [in]            HKEY                 hKey,
  [in]            SECURITY_INFORMATION SecurityInformation,
  [out, optional] PSECURITY_DESCRIPTOR pSecurityDescriptor,
  [in, out]       LPDWORD              lpcbSecurityDescriptor
);
LSTATUS __stdcall newRegGetValueA(
  [in]                HKEY    hkey,
  [in, optional]      LPCSTR  lpSubKey,
  [in, optional]      LPCSTR  lpValue,
  [in, optional]      DWORD   dwFlags,
  [out, optional]     LPDWORD pdwType,
  [out, optional]     PVOID   pvData,
  [in, out, optional] LPDWORD pcbData
);
LSTATUS __stdcall newRegLoadKeyA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey,
  [in]           LPCSTR lpFile
);
LSTATUS __stdcall newRegLoadMUIStringA(
  [in]            HKEY    hKey,
  [in, optional]  LPCSTR  pszValue,
  [out, optional] LPSTR   pszOutBuf,
  [in]            DWORD   cbOutBuf,
  [out, optional] LPDWORD pcbData,
  [in]            DWORD   Flags,
  [in, optional]  LPCSTR  pszDirectory
);
LSTATUS __stdcall newRegNotifyChangeKeyValue(
  [in]           HKEY   hKey,
  [in]           BOOL   bWatchSubtree,
  [in]           DWORD  dwNotifyFilter,
  [in, optional] HANDLE hEvent,
  [in]           BOOL   fAsynchronous
);
LSTATUS __stdcall newRegOpenCurrentUser(
  [in]  REGSAM samDesired,
  [out] PHKEY  phkResult
);
LSTATUS __stdcall newRegOpenKeyExA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey,
  [in]           DWORD  ulOptions,
  [in]           REGSAM samDesired,
  [out]          PHKEY  phkResult
);
LSTATUS __stdcall newRegOpenKeyTransactedA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey,
  [in]           DWORD  ulOptions,
  [in]           REGSAM samDesired,
  [out]          PHKEY  phkResult,
  [in]           HANDLE hTransaction,
                 PVOID  pExtendedParemeter
);
LSTATUS __stdcall newRegOpenUserClassesRoot(
  [in]  HANDLE hToken,
        DWORD  dwOptions,
  [in]  REGSAM samDesired,
  [out] PHKEY  phkResult
);
LSTATUS __stdcall newRegOverridePredefKey(
  [in]           HKEY hKey,
  [in, optional] HKEY hNewHKey
);
LSTATUS __stdcall newRegQueryInfoKeyA(
  [in]                HKEY      hKey,
  [out, optional]     LPSTR     lpClass,
  [in, out, optional] LPDWORD   lpcchClass,
                      LPDWORD   lpReserved,
  [out, optional]     LPDWORD   lpcSubKeys,
  [out, optional]     LPDWORD   lpcbMaxSubKeyLen,
  [out, optional]     LPDWORD   lpcbMaxClassLen,
  [out, optional]     LPDWORD   lpcValues,
  [out, optional]     LPDWORD   lpcbMaxValueNameLen,
  [out, optional]     LPDWORD   lpcbMaxValueLen,
  [out, optional]     LPDWORD   lpcbSecurityDescriptor,
  [out, optional]     PFILETIME lpftLastWriteTime
);
LSTATUS __stdcall newRegQueryMultipleValuesA(
  [in]                HKEY     hKey,
  [out]               PVALENTA val_list,
  [in]                DWORD    num_vals,
  [out, optional]     LPSTR    lpValueBuf,
  [in, out, optional] LPDWORD  ldwTotsize
);
LONG __stdcall newRegQueryReflectionKey(
  [in]  HKEY hBase,
  [out] BOOL *bIsReflectionDisabled
);
LSTATUS __stdcall newRegQueryValueExA(
  [in]                HKEY    hKey,
  [in, optional]      LPCSTR  lpValueName,
                      LPDWORD lpReserved,
  [out, optional]     LPDWORD lpType,
  [out, optional]     LPBYTE  lpData,
  [in, out, optional] LPDWORD lpcbData
);
LSTATUS __stdcall newRegRenameKey(
  HKEY    hKey,
  LPCWSTR lpSubKeyName,
  LPCWSTR lpNewKeyName
);
LSTATUS __stdcall newRegReplaceKeyA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey,
  [in]           LPCSTR lpNewFile,
  [in]           LPCSTR lpOldFile
);
LSTATUS __stdcall newRegRestoreKeyA(
  [in] HKEY   hKey,
  [in] LPCSTR lpFile,
  [in] DWORD  dwFlags
);
LSTATUS __stdcall newRegSaveKeyA(
  [in]           HKEY                        hKey,
  [in]           LPCSTR                      lpFile,
  [in, optional] const LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
LSTATUS __stdcall newRegSaveKeyExA(
  [in]           HKEY                        hKey,
  [in]           LPCSTR                      lpFile,
  [in, optional] const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  [in]           DWORD                       Flags
);
LSTATUS __stdcall newRegSetKeyValueA(
  [in]           HKEY    hKey,
  [in, optional] LPCSTR  lpSubKey,
  [in, optional] LPCSTR  lpValueName,
  [in]           DWORD   dwType,
  [in, optional] LPCVOID lpData,
  [in]           DWORD   cbData
);
LSTATUS __stdcall newRegSetKeySecurity(
  [in] HKEY                 hKey,
  [in] SECURITY_INFORMATION SecurityInformation,
  [in] PSECURITY_DESCRIPTOR pSecurityDescriptor
);
LSTATUS __stdcall newRegSetValueExA(
  [in]           HKEY       hKey,
  [in, optional] LPCSTR     lpValueName,
                 DWORD      Reserved,
  [in]           DWORD      dwType,
  [in]           const BYTE *lpData,
  [in]           DWORD      cbData
);
LSTATUS __stdcall newRegUnLoadKeyA(
  [in]           HKEY   hKey,
  [in, optional] LPCSTR lpSubKey
);
UINT __stdcall newGetPrivateProfileInt(
  [in] LPCTSTR lpAppName,
  [in] LPCTSTR lpKeyName,
  [in] INT     nDefault,
  [in] LPCTSTR lpFileName
);
DWORD __stdcall newGetPrivateProfileSection(
  [in]  LPCTSTR lpAppName,
  [out] LPTSTR  lpReturnedString,
  [in]  DWORD   nSize,
  [in]  LPCTSTR lpFileName
);
DWORD __stdcall newGetPrivateProfileSectionNames(
  [out] LPTSTR  lpszReturnBuffer,
  [in]  DWORD   nSize,
  [in]  LPCTSTR lpFileName
);
DWORD __stdcall newGetPrivateProfileString(
  [in]  LPCTSTR lpAppName,
  [in]  LPCTSTR lpKeyName,
  [in]  LPCTSTR lpDefault,
  [out] LPTSTR  lpReturnedString,
  [in]  DWORD   nSize,
  [in]  LPCTSTR lpFileName
);
BOOL __stdcall newGetPrivateProfileStruct(
  [in]  LPCTSTR lpszSection,
  [in]  LPCTSTR lpszKey,
  [out] LPVOID  lpStruct,
  [in]  UINT    uSizeStruct,
  [in]  LPCTSTR szFile
);
UINT __stdcall newGetProfileIntA(
  [in] LPCSTR lpAppName,
  [in] LPCSTR lpKeyName,
  [in] INT    nDefault
);
DWORD __stdcall newGetProfileSectionA(
  [in]  LPCSTR lpAppName,
  [out] LPSTR  lpReturnedString,
  [in]  DWORD  nSize
);
DWORD __stdcall newGetProfileStringA(
  [in]  LPCSTR lpAppName,
  [in]  LPCSTR lpKeyName,
  [in]  LPCSTR lpDefault,
  [out] LPSTR  lpReturnedString,
  [in]  DWORD  nSize
);
BOOL __stdcall newWritePrivateProfileSectionA(
  [in] LPCSTR lpAppName,
  [in] LPCSTR lpString,
  [in] LPCSTR lpFileName
);
BOOL __stdcall newWritePrivateProfileStringA(
  [in] LPCSTR lpAppName,
  [in] LPCSTR lpKeyName,
  [in] LPCSTR lpString,
  [in] LPCSTR lpFileName
);
BOOL __stdcall newWritePrivateProfileStructA(
  [in] LPCSTR lpszSection,
  [in] LPCSTR lpszKey,
  [in] LPVOID lpStruct,
  [in] UINT   uSizeStruct,
  [in] LPCSTR szFile
);
BOOL __stdcall newWriteProfileSectionA(
  [in] LPCSTR lpAppName,
  [in] LPCSTR lpString
);
BOOL __stdcall newWriteProfileStringA(
  [in] LPCSTR lpAppName,
  [in] LPCSTR lpKeyName,
  [in] LPCSTR lpString
);
}