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
                  PDWORD pdwQuotaAllowed,
                  PDWORD pdwQuotaUsed
);
LSTATUS __stdcall newRegCloseKey(
       HKEY hKey
);
LSTATUS __stdcall newRegConnectRegistryA(
                 LPCSTR lpMachineName,
                 HKEY   hKey,
                 PHKEY  phkResult
);
LSTATUS __stdcall newRegCopyTreeA(
                 HKEY   hKeySrc,
                 LPCSTR lpSubKey,
                 HKEY   hKeyDest
);
LSTATUS __stdcall newRegCreateKeyExA(
                  HKEY                        hKey,
                  LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
                  LPSTR                       lpClass,
                  DWORD                       dwOptions,
                  REGSAM                      samDesired,
                  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                  PHKEY                       phkResult,
                  LPDWORD                     lpdwDisposition
);
LSTATUS __stdcall newRegCreateKeyTransactedA(
                  HKEY                        hKey,
                  LPCSTR                      lpSubKey,
                  DWORD                       Reserved,
                  LPSTR                       lpClass,
                  DWORD                       dwOptions,
                  REGSAM                      samDesired,
                  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                  PHKEY                       phkResult,
                  LPDWORD                     lpdwDisposition,
                  HANDLE                      hTransaction,
                  PVOID                       pExtendedParemeter
);
LSTATUS __stdcall newRegDeleteKeyA(
       HKEY   hKey,
       LPCSTR lpSubKey
);
LSTATUS __stdcall newRegDeleteKeyExA(
       HKEY   hKey,
       LPCSTR lpSubKey,
       REGSAM samDesired,
       DWORD  Reserved
);
LSTATUS __stdcall newRegDeleteKeyTransactedA(
       HKEY   hKey,
       LPCSTR lpSubKey,
       REGSAM samDesired,
       DWORD  Reserved,
       HANDLE hTransaction,
       PVOID  pExtendedParameter
);
LSTATUS __stdcall newRegDeleteKeyValueA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpValueName
);
LSTATUS __stdcall newRegDeleteTreeA(
                 HKEY   hKey,
                 LPCSTR lpSubKey
);
LSTATUS __stdcall newRegDeleteValueA(
                 HKEY   hKey,
                 LPCSTR lpValueName
);
LSTATUS __stdcall newRegDisablePredefinedCache();
LSTATUS __stdcall newRegDisablePredefinedCacheEx();
LONG __stdcall newRegDisableReflectionKey(
       HKEY hBase
);
LONG __stdcall newRegEnableReflectionKey(
       HKEY hBase
);
LSTATUS __stdcall newRegEnumKeyExA(
                      HKEY      hKey,
                      DWORD     dwIndex,
                      LPSTR     lpName,
                      LPDWORD   lpcchName,
                      LPDWORD   lpReserved,
                      LPSTR     lpClass,
                      LPDWORD   lpcchClass,
                      PFILETIME lpftLastWriteTime
);
LSTATUS __stdcall newRegEnumValueA(
                      HKEY    hKey,
                      DWORD   dwIndex,
                      LPSTR   lpValueName,
                      LPDWORD lpcchValueName,
                      LPDWORD lpReserved,
                      LPDWORD lpType,
                      LPBYTE  lpData,
                      LPDWORD lpcbData
);
LSTATUS __stdcall newRegFlushKey(
       HKEY hKey
);
LSTATUS __stdcall newRegGetKeySecurity(
                  HKEY                 hKey,
                  SECURITY_INFORMATION SecurityInformation,
                  PSECURITY_DESCRIPTOR pSecurityDescriptor,
                  LPDWORD              lpcbSecurityDescriptor
);
LSTATUS __stdcall newRegGetValueA(
                      HKEY    hkey,
                      LPCSTR  lpSubKey,
                      LPCSTR  lpValue,
                      DWORD   dwFlags,
                      LPDWORD pdwType,
                      PVOID   pvData,
                      LPDWORD pcbData
);
LSTATUS __stdcall newRegLoadKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpFile
);
LSTATUS __stdcall newRegLoadMUIStringA(
                  HKEY    hKey,
                  LPCSTR  pszValue,
                  LPSTR   pszOutBuf,
                  DWORD   cbOutBuf,
                  LPDWORD pcbData,
                  DWORD   Flags,
                  LPCSTR  pszDirectory
);
LSTATUS __stdcall newRegNotifyChangeKeyValue(
                 HKEY   hKey,
                 BOOL   bWatchSubtree,
                 DWORD  dwNotifyFilter,
                 HANDLE hEvent,
                 BOOL   fAsynchronous
);
LSTATUS __stdcall newRegOpenCurrentUser(
        REGSAM samDesired,
        PHKEY  phkResult
);
LSTATUS __stdcall newRegOpenKeyExA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 DWORD  ulOptions,
                 REGSAM samDesired,
                 PHKEY  phkResult
);
LSTATUS __stdcall newRegOpenKeyTransactedA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 DWORD  ulOptions,
                 REGSAM samDesired,
                 PHKEY  phkResult,
                 HANDLE hTransaction,
                 PVOID  pExtendedParemeter
);
LSTATUS __stdcall newRegOpenUserClassesRoot(
        HANDLE hToken,
        DWORD  dwOptions,
        REGSAM samDesired,
        PHKEY  phkResult
);
LSTATUS __stdcall newRegOverridePredefKey(
                 HKEY hKey,
                 HKEY hNewHKey
);
LSTATUS __stdcall newRegQueryInfoKeyA(
                      HKEY      hKey,
                      LPSTR     lpClass,
                      LPDWORD   lpcchClass,
                      LPDWORD   lpReserved,
                      LPDWORD   lpcSubKeys,
                      LPDWORD   lpcbMaxSubKeyLen,
                      LPDWORD   lpcbMaxClassLen,
                      LPDWORD   lpcValues,
                      LPDWORD   lpcbMaxValueNameLen,
                      LPDWORD   lpcbMaxValueLen,
                      LPDWORD   lpcbSecurityDescriptor,
                      PFILETIME lpftLastWriteTime
);
LSTATUS __stdcall newRegQueryMultipleValuesA(
                      HKEY     hKey,
                      PVALENTA val_list,
                      DWORD    num_vals,
                      LPSTR    lpValueBuf,
                      LPDWORD  ldwTotsize
);
LONG __stdcall newRegQueryReflectionKey(
        HKEY hBase,
        BOOL *bIsReflectionDisabled
);
LSTATUS __stdcall newRegQueryValueExA(
                      HKEY    hKey,
                      LPCSTR  lpValueName,
                      LPDWORD lpReserved,
                      LPDWORD lpType,
                      LPBYTE  lpData,
                      LPDWORD lpcbData
);
LSTATUS __stdcall newRegRenameKey(
  HKEY    hKey,
  LPCWSTR lpSubKeyName,
  LPCWSTR lpNewKeyName
);
LSTATUS __stdcall newRegReplaceKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpNewFile,
                 LPCSTR lpOldFile
);
LSTATUS __stdcall newRegRestoreKeyA(
       HKEY   hKey,
       LPCSTR lpFile,
       DWORD  dwFlags
);
LSTATUS __stdcall newRegSaveKeyA(
                 HKEY                        hKey,
                 LPCSTR                      lpFile,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
LSTATUS __stdcall newRegSaveKeyExA(
                 HKEY                        hKey,
                 LPCSTR                      lpFile,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                 DWORD                       Flags
);
LSTATUS __stdcall newRegSetKeyValueA(
                 HKEY    hKey,
                 LPCSTR  lpSubKey,
                 LPCSTR  lpValueName,
                 DWORD   dwType,
                 LPCVOID lpData,
                 DWORD   cbData
);
LSTATUS __stdcall newRegSetKeySecurity(
       HKEY                 hKey,
       SECURITY_INFORMATION SecurityInformation,
       PSECURITY_DESCRIPTOR pSecurityDescriptor
);
LSTATUS __stdcall newRegSetValueExA(
                 HKEY       hKey,
                 LPCSTR     lpValueName,
                 DWORD      Reserved,
                 DWORD      dwType,
                 const BYTE *lpData,
                 DWORD      cbData
);
LSTATUS __stdcall newRegUnLoadKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey
);
UINT __stdcall newGetPrivateProfileInt(
       LPCTSTR lpAppName,
       LPCTSTR lpKeyName,
       INT     nDefault,
       LPCTSTR lpFileName
);
DWORD __stdcall newGetPrivateProfileSection(
        LPCTSTR lpAppName,
        LPTSTR  lpReturnedString,
        DWORD   nSize,
        LPCTSTR lpFileName
);
DWORD __stdcall newGetPrivateProfileSectionNames(
        LPTSTR  lpszReturnBuffer,
        DWORD   nSize,
        LPCTSTR lpFileName
);
DWORD __stdcall newGetPrivateProfileString(
        LPCTSTR lpAppName,
        LPCTSTR lpKeyName,
        LPCTSTR lpDefault,
        LPTSTR  lpReturnedString,
        DWORD   nSize,
        LPCTSTR lpFileName
);
BOOL __stdcall newGetPrivateProfileStruct(
        LPCTSTR lpszSection,
        LPCTSTR lpszKey,
        LPVOID  lpStruct,
        UINT    uSizeStruct,
        LPCTSTR szFile
);
UINT __stdcall newGetProfileIntA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       INT    nDefault
);
DWORD __stdcall newGetProfileSectionA(
        LPCSTR lpAppName,
        LPSTR  lpReturnedString,
        DWORD  nSize
);
DWORD __stdcall newGetProfileStringA(
        LPCSTR lpAppName,
        LPCSTR lpKeyName,
        LPCSTR lpDefault,
        LPSTR  lpReturnedString,
        DWORD  nSize
);
BOOL __stdcall newWritePrivateProfileSectionA(
       LPCSTR lpAppName,
       LPCSTR lpString,
       LPCSTR lpFileName
);
BOOL __stdcall newWritePrivateProfileStringA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       LPCSTR lpString,
       LPCSTR lpFileName
);
BOOL __stdcall newWritePrivateProfileStructA(
       LPCSTR lpszSection,
       LPCSTR lpszKey,
       LPVOID lpStruct,
       UINT   uSizeStruct,
       LPCSTR szFile
);
BOOL __stdcall newWriteProfileSectionA(
       LPCSTR lpAppName,
       LPCSTR lpString
);
BOOL __stdcall newWriteProfileStringA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       LPCSTR lpString
);
}