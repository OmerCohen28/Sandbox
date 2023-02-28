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

extern std::vector<CHAR*> original_bytes;
extern std::vector<FARPROC> hooked_addr;
extern time_t begin, end;

extern HINSTANCE hLibFiles;
extern HINSTANCE hLibSock;
extern HINSTANCE hLibReg;

extern HANDLE LOGfile;
extern bool IsMyCall;

namespace newFunctions {

BOOL __stdcall newGetSystemRegistryQuota(
                  PDWORD pdwQuotaAllowed,
                  PDWORD pdwQuotaUsed
){
        	//unhook GetSystemRegistryQuotation
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetSystemRegistryQuota],
    		original_bytes[(int)Hook::Functions::GetSystemRegistryQuota], 6, NULL);

        BOOL result = GetSystemRegistryQuota(pdwQuotaAllowed,pdwQuotaUsed
);
        Hook reset_hook { Hook::Functions::GetSystemRegistryQuota};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegCloseKey(
       HKEY hKey
){
        	//unhook RegCloseKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegCloseKey],
    		original_bytes[(int)Hook::Functions::RegCloseKey], 6, NULL);

        LSTATUS result = RegCloseKey(hKey
);
        Hook reset_hook { Hook::Functions::RegCloseKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegConnectRegistryA(
                 LPCSTR lpMachineName,
                 HKEY   hKey,
                 PHKEY  phkResult
){
        	//unhook RegConnectRegistryAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegConnectRegistryA],
    		original_bytes[(int)Hook::Functions::RegConnectRegistryA], 6, NULL);

        LSTATUS result = RegConnectRegistryA(lpMachineName,hKey,phkResult
);
        Hook reset_hook { Hook::Functions::RegConnectRegistryA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegCopyTreeA(
                 HKEY   hKeySrc,
                 LPCSTR lpSubKey,
                 HKEY   hKeyDest
){
        	//unhook RegCopyTreeAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegCopyTreeA],
    		original_bytes[(int)Hook::Functions::RegCopyTreeA], 6, NULL);

        LSTATUS result = RegCopyTreeA(hKeySrc,lpSubKey,hKeyDest
);
        Hook reset_hook { Hook::Functions::RegCopyTreeA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
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
){
        	//unhook RegCreateKeyExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegCreateKeyExA],
    		original_bytes[(int)Hook::Functions::RegCreateKeyExA], 6, NULL);

        LSTATUS result = RegCreateKeyExA(hKey,lpSubKey,Reserved,lpClass,dwOptions,samDesired,lpSecurityAttributes,phkResult,lpdwDisposition
);
        Hook reset_hook { Hook::Functions::RegCreateKeyExA};
        reset_hook.deploy_hook();

        std::cout << "hooked RegCreateKeyExA\n";
        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
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
){
        	//unhook RegCreateKeyTransactedAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegCreateKeyTransactedA],
    		original_bytes[(int)Hook::Functions::RegCreateKeyTransactedA], 6, NULL);

        LSTATUS result = RegCreateKeyTransactedA(hKey,lpSubKey,Reserved,lpClass,dwOptions,samDesired,lpSecurityAttributes,phkResult,lpdwDisposition,hTransaction,pExtendedParemeter
);
        Hook reset_hook { Hook::Functions::RegCreateKeyTransactedA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDeleteKeyA(
       HKEY   hKey,
       LPCSTR lpSubKey
){
        	//unhook RegDeleteKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyA],
    		original_bytes[(int)Hook::Functions::RegDeleteKeyA], 6, NULL);

        LSTATUS result = RegDeleteKeyA(hKey,lpSubKey
);
        Hook reset_hook { Hook::Functions::RegDeleteKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDeleteKeyExA(
       HKEY   hKey,
       LPCSTR lpSubKey,
       REGSAM samDesired,
       DWORD  Reserved
){
        	//unhook RegDeleteKeyExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyExA],
    		original_bytes[(int)Hook::Functions::RegDeleteKeyExA], 6, NULL);

        LSTATUS result = RegDeleteKeyExA(hKey,lpSubKey,samDesired,Reserved
);
        Hook reset_hook { Hook::Functions::RegDeleteKeyExA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDeleteKeyTransactedA(
       HKEY   hKey,
       LPCSTR lpSubKey,
       REGSAM samDesired,
       DWORD  Reserved,
       HANDLE hTransaction,
       PVOID  pExtendedParameter
){
        	//unhook RegDeleteKeyTransactedAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyTransactedA],
    		original_bytes[(int)Hook::Functions::RegDeleteKeyTransactedA], 6, NULL);

        LSTATUS result = RegDeleteKeyTransactedA(hKey,lpSubKey,samDesired,Reserved,hTransaction,pExtendedParameter
);
        Hook reset_hook { Hook::Functions::RegDeleteKeyTransactedA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDeleteKeyValueA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpValueName
){
        	//unhook RegDeleteKeyValueAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteKeyValueA],
    		original_bytes[(int)Hook::Functions::RegDeleteKeyValueA], 6, NULL);

        LSTATUS result = RegDeleteKeyValueA(hKey,lpSubKey,lpValueName
);
        Hook reset_hook { Hook::Functions::RegDeleteKeyValueA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDeleteTreeA(
                 HKEY   hKey,
                 LPCSTR lpSubKey
){
        	//unhook RegDeleteTreeAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteTreeA],
    		original_bytes[(int)Hook::Functions::RegDeleteTreeA], 6, NULL);

        LSTATUS result = RegDeleteTreeA(hKey,lpSubKey
);
        Hook reset_hook { Hook::Functions::RegDeleteTreeA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDeleteValueA(
                 HKEY   hKey,
                 LPCSTR lpValueName
){
        	//unhook RegDeleteValueAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDeleteValueA],
    		original_bytes[(int)Hook::Functions::RegDeleteValueA], 6, NULL);

        LSTATUS result = RegDeleteValueA(hKey,lpValueName
);
        Hook reset_hook { Hook::Functions::RegDeleteValueA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDisablePredefinedCache(){
        	//unhook RegDisablePredefinedCachetion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDisablePredefinedCache],
    		original_bytes[(int)Hook::Functions::RegDisablePredefinedCache], 6, NULL);

        LSTATUS result = RegDisablePredefinedCache();
        Hook reset_hook { Hook::Functions::RegDisablePredefinedCache};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegDisablePredefinedCacheEx(){
        	//unhook RegDisablePredefinedCacheExtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDisablePredefinedCacheEx],
    		original_bytes[(int)Hook::Functions::RegDisablePredefinedCacheEx], 6, NULL);

        LSTATUS result = RegDisablePredefinedCacheEx();
        Hook reset_hook { Hook::Functions::RegDisablePredefinedCacheEx};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LONG __stdcall newRegDisableReflectionKey(
       HKEY hBase
){
        	//unhook RegDisableReflectionKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegDisableReflectionKey],
    		original_bytes[(int)Hook::Functions::RegDisableReflectionKey], 6, NULL);

        LONG result = RegDisableReflectionKey(hBase
);
        Hook reset_hook { Hook::Functions::RegDisableReflectionKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LONG __stdcall newRegEnableReflectionKey(
       HKEY hBase
){
        	//unhook RegEnableReflectionKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegEnableReflectionKey],
    		original_bytes[(int)Hook::Functions::RegEnableReflectionKey], 6, NULL);

        LONG result = RegEnableReflectionKey(hBase
);
        Hook reset_hook { Hook::Functions::RegEnableReflectionKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegEnumKeyExA(
                      HKEY      hKey,
                      DWORD     dwIndex,
                      LPSTR     lpName,
                      LPDWORD   lpcchName,
                      LPDWORD   lpReserved,
                      LPSTR     lpClass,
                      LPDWORD   lpcchClass,
                      PFILETIME lpftLastWriteTime
){
        	//unhook RegEnumKeyExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegEnumKeyExA],
    		original_bytes[(int)Hook::Functions::RegEnumKeyExA], 6, NULL);

        LSTATUS result = RegEnumKeyExA(hKey,dwIndex,lpName,lpcchName,lpReserved,lpClass,lpcchClass,lpftLastWriteTime
);
        Hook reset_hook { Hook::Functions::RegEnumKeyExA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegEnumValueA(
                      HKEY    hKey,
                      DWORD   dwIndex,
                      LPSTR   lpValueName,
                      LPDWORD lpcchValueName,
                      LPDWORD lpReserved,
                      LPDWORD lpType,
                      LPBYTE  lpData,
                      LPDWORD lpcbData
){
        	//unhook RegEnumValueAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegEnumValueA],
    		original_bytes[(int)Hook::Functions::RegEnumValueA], 6, NULL);

        LSTATUS result = RegEnumValueA(hKey,dwIndex,lpValueName,lpcchValueName,lpReserved,lpType,lpData,lpcbData
);
        Hook reset_hook { Hook::Functions::RegEnumValueA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegFlushKey(
       HKEY hKey
){
        	//unhook RegFlushKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegFlushKey],
    		original_bytes[(int)Hook::Functions::RegFlushKey], 6, NULL);

        LSTATUS result = RegFlushKey(hKey
);
        Hook reset_hook { Hook::Functions::RegFlushKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegGetKeySecurity(
                  HKEY                 hKey,
                  SECURITY_INFORMATION SecurityInformation,
                  PSECURITY_DESCRIPTOR pSecurityDescriptor,
                  LPDWORD              lpcbSecurityDescriptor
){
        	//unhook RegGetKeySecuritytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegGetKeySecurity],
    		original_bytes[(int)Hook::Functions::RegGetKeySecurity], 6, NULL);

        LSTATUS result = RegGetKeySecurity(hKey,SecurityInformation,pSecurityDescriptor,lpcbSecurityDescriptor
);
        Hook reset_hook { Hook::Functions::RegGetKeySecurity};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegGetValueA(
                      HKEY    hkey,
                      LPCSTR  lpSubKey,
                      LPCSTR  lpValue,
                      DWORD   dwFlags,
                      LPDWORD pdwType,
                      PVOID   pvData,
                      LPDWORD pcbData
){
        	//unhook RegGetValueAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegGetValueA],
    		original_bytes[(int)Hook::Functions::RegGetValueA], 6, NULL);

        LSTATUS result = RegGetValueA(hkey,lpSubKey,lpValue,dwFlags,pdwType,pvData,pcbData
);
        Hook reset_hook { Hook::Functions::RegGetValueA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegLoadKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpFile
){
        	//unhook RegLoadKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegLoadKeyA],
    		original_bytes[(int)Hook::Functions::RegLoadKeyA], 6, NULL);

        LSTATUS result = RegLoadKeyA(hKey,lpSubKey,lpFile
);
        Hook reset_hook { Hook::Functions::RegLoadKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegLoadMUIStringA(
                  HKEY    hKey,
                  LPCSTR  pszValue,
                  LPSTR   pszOutBuf,
                  DWORD   cbOutBuf,
                  LPDWORD pcbData,
                  DWORD   Flags,
                  LPCSTR  pszDirectory
){
        	//unhook RegLoadMUIStringAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegLoadMUIStringA],
    		original_bytes[(int)Hook::Functions::RegLoadMUIStringA], 6, NULL);

        LSTATUS result = RegLoadMUIStringA(hKey,pszValue,pszOutBuf,cbOutBuf,pcbData,Flags,pszDirectory
);
        Hook reset_hook { Hook::Functions::RegLoadMUIStringA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegNotifyChangeKeyValue(
                 HKEY   hKey,
                 BOOL   bWatchSubtree,
                 DWORD  dwNotifyFilter,
                 HANDLE hEvent,
                 BOOL   fAsynchronous
){
        	//unhook RegNotifyChangeKeyValuetion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegNotifyChangeKeyValue],
    		original_bytes[(int)Hook::Functions::RegNotifyChangeKeyValue], 6, NULL);

        LSTATUS result = RegNotifyChangeKeyValue(hKey,bWatchSubtree,dwNotifyFilter,hEvent,fAsynchronous
);
        Hook reset_hook { Hook::Functions::RegNotifyChangeKeyValue};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegOpenCurrentUser(
        REGSAM samDesired,
        PHKEY  phkResult
){
        	//unhook RegOpenCurrentUsertion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenCurrentUser],
    		original_bytes[(int)Hook::Functions::RegOpenCurrentUser], 6, NULL);

        LSTATUS result = RegOpenCurrentUser(samDesired,phkResult
);
        Hook reset_hook { Hook::Functions::RegOpenCurrentUser};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegOpenKeyExA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 DWORD  ulOptions,
                 REGSAM samDesired,
                 PHKEY  phkResult
){
        	//unhook RegOpenKeyExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenKeyExA],
    		original_bytes[(int)Hook::Functions::RegOpenKeyExA], 6, NULL);

        LSTATUS result = RegOpenKeyExA(hKey,lpSubKey,ulOptions,samDesired,phkResult
);
        Hook reset_hook { Hook::Functions::RegOpenKeyExA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegOpenKeyTransactedA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 DWORD  ulOptions,
                 REGSAM samDesired,
                 PHKEY  phkResult,
                 HANDLE hTransaction,
                 PVOID  pExtendedParemeter
){
        	//unhook RegOpenKeyTransactedAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenKeyTransactedA],
    		original_bytes[(int)Hook::Functions::RegOpenKeyTransactedA], 6, NULL);

        LSTATUS result = RegOpenKeyTransactedA(hKey,lpSubKey,ulOptions,samDesired,phkResult,hTransaction,pExtendedParemeter
);
        Hook reset_hook { Hook::Functions::RegOpenKeyTransactedA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegOpenUserClassesRoot(
        HANDLE hToken,
        DWORD  dwOptions,
        REGSAM samDesired,
        PHKEY  phkResult
){
        	//unhook RegOpenUserClassesRoottion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegOpenUserClassesRoot],
    		original_bytes[(int)Hook::Functions::RegOpenUserClassesRoot], 6, NULL);

        LSTATUS result = RegOpenUserClassesRoot(hToken,dwOptions,samDesired,phkResult
);
        Hook reset_hook { Hook::Functions::RegOpenUserClassesRoot};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegOverridePredefKey(
                 HKEY hKey,
                 HKEY hNewHKey
){
        	//unhook RegOverridePredefKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegOverridePredefKey],
    		original_bytes[(int)Hook::Functions::RegOverridePredefKey], 6, NULL);

        LSTATUS result = RegOverridePredefKey(hKey,hNewHKey
);
        Hook reset_hook { Hook::Functions::RegOverridePredefKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
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
){
        	//unhook RegQueryInfoKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryInfoKeyA],
    		original_bytes[(int)Hook::Functions::RegQueryInfoKeyA], 6, NULL);

        LSTATUS result = RegQueryInfoKeyA(hKey,lpClass,lpcchClass,lpReserved,lpcSubKeys,lpcbMaxSubKeyLen,lpcbMaxClassLen,lpcValues,lpcbMaxValueNameLen,lpcbMaxValueLen,lpcbSecurityDescriptor,lpftLastWriteTime
);
        Hook reset_hook { Hook::Functions::RegQueryInfoKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegQueryMultipleValuesA(
                      HKEY     hKey,
                      PVALENTA val_list,
                      DWORD    num_vals,
                      LPSTR    lpValueBuf,
                      LPDWORD  ldwTotsize
){
        	//unhook RegQueryMultipleValuesAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryMultipleValuesA],
    		original_bytes[(int)Hook::Functions::RegQueryMultipleValuesA], 6, NULL);

        LSTATUS result = RegQueryMultipleValuesA(hKey,val_list,num_vals,lpValueBuf,ldwTotsize
);
        Hook reset_hook { Hook::Functions::RegQueryMultipleValuesA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LONG __stdcall newRegQueryReflectionKey(
        HKEY hBase,
        BOOL *bIsReflectionDisabled
){
        	//unhook RegQueryReflectionKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryReflectionKey],
    		original_bytes[(int)Hook::Functions::RegQueryReflectionKey], 6, NULL);

        LONG result = RegQueryReflectionKey(hBase,bIsReflectionDisabled
);
        Hook reset_hook { Hook::Functions::RegQueryReflectionKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegQueryValueExA(
                      HKEY    hKey,
                      LPCSTR  lpValueName,
                      LPDWORD lpReserved,
                      LPDWORD lpType,
                      LPBYTE  lpData,
                      LPDWORD lpcbData
){
        	//unhook RegQueryValueExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegQueryValueExA],
    		original_bytes[(int)Hook::Functions::RegQueryValueExA], 6, NULL);

        LSTATUS result = RegQueryValueExA(hKey,lpValueName,lpReserved,lpType,lpData,lpcbData
);
        Hook reset_hook { Hook::Functions::RegQueryValueExA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegRenameKey(
  HKEY    hKey,
  LPCWSTR lpSubKeyName,
  LPCWSTR lpNewKeyName
){
        	//unhook RegRenameKeytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegRenameKey],
    		original_bytes[(int)Hook::Functions::RegRenameKey], 6, NULL);

        LSTATUS result = RegRenameKey(hKey,lpSubKeyName,lpNewKeyName
);
        Hook reset_hook { Hook::Functions::RegRenameKey};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegReplaceKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey,
                 LPCSTR lpNewFile,
                 LPCSTR lpOldFile
){
        	//unhook RegReplaceKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegReplaceKeyA],
    		original_bytes[(int)Hook::Functions::RegReplaceKeyA], 6, NULL);

        LSTATUS result = RegReplaceKeyA(hKey,lpSubKey,lpNewFile,lpOldFile
);
        Hook reset_hook { Hook::Functions::RegReplaceKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegRestoreKeyA(
       HKEY   hKey,
       LPCSTR lpFile,
       DWORD  dwFlags
){
        	//unhook RegRestoreKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegRestoreKeyA],
    		original_bytes[(int)Hook::Functions::RegRestoreKeyA], 6, NULL);

        LSTATUS result = RegRestoreKeyA(hKey,lpFile,dwFlags
);
        Hook reset_hook { Hook::Functions::RegRestoreKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegSaveKeyA(
                 HKEY                        hKey,
                 LPCSTR                      lpFile,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes
){
        	//unhook RegSaveKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegSaveKeyA],
    		original_bytes[(int)Hook::Functions::RegSaveKeyA], 6, NULL);

        LSTATUS result = RegSaveKeyA(hKey,lpFile,lpSecurityAttributes
);
        Hook reset_hook { Hook::Functions::RegSaveKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegSaveKeyExA(
                 HKEY                        hKey,
                 LPCSTR                      lpFile,
                 const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                 DWORD                       Flags
){
        	//unhook RegSaveKeyExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegSaveKeyExA],
    		original_bytes[(int)Hook::Functions::RegSaveKeyExA], 6, NULL);

        LSTATUS result = RegSaveKeyExA(hKey,lpFile,lpSecurityAttributes,Flags
);
        Hook reset_hook { Hook::Functions::RegSaveKeyExA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegSetKeyValueA(
                 HKEY    hKey,
                 LPCSTR  lpSubKey,
                 LPCSTR  lpValueName,
                 DWORD   dwType,
                 LPCVOID lpData,
                 DWORD   cbData
){
        	//unhook RegSetKeyValueAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegSetKeyValueA],
    		original_bytes[(int)Hook::Functions::RegSetKeyValueA], 6, NULL);

        LSTATUS result = RegSetKeyValueA(hKey,lpSubKey,lpValueName,dwType,lpData,cbData
);
        Hook reset_hook { Hook::Functions::RegSetKeyValueA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegSetKeySecurity(
       HKEY                 hKey,
       SECURITY_INFORMATION SecurityInformation,
       PSECURITY_DESCRIPTOR pSecurityDescriptor
){
        	//unhook RegSetKeySecuritytion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegSetKeySecurity],
    		original_bytes[(int)Hook::Functions::RegSetKeySecurity], 6, NULL);

        LSTATUS result = RegSetKeySecurity(hKey,SecurityInformation,pSecurityDescriptor
);
        Hook reset_hook { Hook::Functions::RegSetKeySecurity};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegSetValueExA(
                 HKEY       hKey,
                 LPCSTR     lpValueName,
                 DWORD      Reserved,
                 DWORD      dwType,
                 const BYTE *lpData,
                 DWORD      cbData
){
        	//unhook RegSetValueExAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegSetValueExA],
    		original_bytes[(int)Hook::Functions::RegSetValueExA], 6, NULL);

        LSTATUS result = RegSetValueExA(hKey,lpValueName,Reserved,dwType,lpData,cbData
);
        Hook reset_hook { Hook::Functions::RegSetValueExA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
LSTATUS __stdcall newRegUnLoadKeyA(
                 HKEY   hKey,
                 LPCSTR lpSubKey
){
        	//unhook RegUnLoadKeyAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::RegUnLoadKeyA],
    		original_bytes[(int)Hook::Functions::RegUnLoadKeyA], 6, NULL);

        LSTATUS result = RegUnLoadKeyA(hKey,lpSubKey
);
        Hook reset_hook { Hook::Functions::RegUnLoadKeyA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
UINT __stdcall newGetPrivateProfileInt(
       LPCTSTR lpAppName,
       LPCTSTR lpKeyName,
       INT     nDefault,
       LPCTSTR lpFileName
){
        	//unhook GetPrivateProfileInttion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileInt],
    		original_bytes[(int)Hook::Functions::GetPrivateProfileInt], 6, NULL);

        UINT result = GetPrivateProfileInt(lpAppName,lpKeyName,nDefault,lpFileName
);
        Hook reset_hook { Hook::Functions::GetPrivateProfileInt};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
DWORD __stdcall newGetPrivateProfileSection(
        LPCTSTR lpAppName,
        LPTSTR  lpReturnedString,
        DWORD   nSize,
        LPCTSTR lpFileName
){
        	//unhook GetPrivateProfileSectiontion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileSection],
    		original_bytes[(int)Hook::Functions::GetPrivateProfileSection], 6, NULL);

        DWORD result = GetPrivateProfileSection(lpAppName,lpReturnedString,nSize,lpFileName
);
        Hook reset_hook { Hook::Functions::GetPrivateProfileSection};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
DWORD __stdcall newGetPrivateProfileSectionNames(
        LPTSTR  lpszReturnBuffer,
        DWORD   nSize,
        LPCTSTR lpFileName
){
        	//unhook GetPrivateProfileSectionNamestion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileSectionNames],
    		original_bytes[(int)Hook::Functions::GetPrivateProfileSectionNames], 6, NULL);

        DWORD result = GetPrivateProfileSectionNames(lpszReturnBuffer,nSize,lpFileName
);
        Hook reset_hook { Hook::Functions::GetPrivateProfileSectionNames};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
DWORD __stdcall newGetPrivateProfileString(
        LPCTSTR lpAppName,
        LPCTSTR lpKeyName,
        LPCTSTR lpDefault,
        LPTSTR  lpReturnedString,
        DWORD   nSize,
        LPCTSTR lpFileName
){
        	//unhook GetPrivateProfileStringtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileString],
    		original_bytes[(int)Hook::Functions::GetPrivateProfileString], 6, NULL);

        DWORD result = GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,lpFileName
);
        Hook reset_hook { Hook::Functions::GetPrivateProfileString};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
BOOL __stdcall newGetPrivateProfileStruct(
        LPCTSTR lpszSection,
        LPCTSTR lpszKey,
        LPVOID  lpStruct,
        UINT    uSizeStruct,
        LPCTSTR szFile
){
        	//unhook GetPrivateProfileStructtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetPrivateProfileStruct],
    		original_bytes[(int)Hook::Functions::GetPrivateProfileStruct], 6, NULL);

        BOOL result = GetPrivateProfileStruct(lpszSection,lpszKey,lpStruct,uSizeStruct,szFile
);
        Hook reset_hook { Hook::Functions::GetPrivateProfileStruct};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
UINT __stdcall newGetProfileIntA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       INT    nDefault
){
        	//unhook GetProfileIntAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetProfileIntA],
    		original_bytes[(int)Hook::Functions::GetProfileIntA], 6, NULL);

        UINT result = GetProfileIntA(lpAppName,lpKeyName,nDefault
);
        Hook reset_hook { Hook::Functions::GetProfileIntA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
DWORD __stdcall newGetProfileSectionA(
        LPCSTR lpAppName,
        LPSTR  lpReturnedString,
        DWORD  nSize
){
        	//unhook GetProfileSectionAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetProfileSectionA],
    		original_bytes[(int)Hook::Functions::GetProfileSectionA], 6, NULL);

        DWORD result = GetProfileSectionA(lpAppName,lpReturnedString,nSize
);
        Hook reset_hook { Hook::Functions::GetProfileSectionA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
DWORD __stdcall newGetProfileStringA(
        LPCSTR lpAppName,
        LPCSTR lpKeyName,
        LPCSTR lpDefault,
        LPSTR  lpReturnedString,
        DWORD  nSize
){
        	//unhook GetProfileStringAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::GetProfileStringA],
    		original_bytes[(int)Hook::Functions::GetProfileStringA], 6, NULL);

        DWORD result = GetProfileStringA(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize
);
        Hook reset_hook { Hook::Functions::GetProfileStringA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
BOOL __stdcall newWritePrivateProfileSectionA(
       LPCSTR lpAppName,
       LPCSTR lpString,
       LPCSTR lpFileName
){
        	//unhook WritePrivateProfileSectionAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::WritePrivateProfileSectionA],
    		original_bytes[(int)Hook::Functions::WritePrivateProfileSectionA], 6, NULL);

        BOOL result = WritePrivateProfileSectionA(lpAppName,lpString,lpFileName
);
        Hook reset_hook { Hook::Functions::WritePrivateProfileSectionA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
BOOL __stdcall newWritePrivateProfileStringA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       LPCSTR lpString,
       LPCSTR lpFileName
){
        	//unhook WritePrivateProfileStringAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::WritePrivateProfileStringA],
    		original_bytes[(int)Hook::Functions::WritePrivateProfileStringA], 6, NULL);

        BOOL result = WritePrivateProfileStringA(lpAppName,lpKeyName,lpString,lpFileName
);
        Hook reset_hook { Hook::Functions::WritePrivateProfileStringA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
BOOL __stdcall newWritePrivateProfileStructA(
       LPCSTR lpszSection,
       LPCSTR lpszKey,
       LPVOID lpStruct,
       UINT   uSizeStruct,
       LPCSTR szFile
){
        	//unhook WritePrivateProfileStructAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::WritePrivateProfileStructA],
    		original_bytes[(int)Hook::Functions::WritePrivateProfileStructA], 6, NULL);

        BOOL result = WritePrivateProfileStructA(lpszSection,lpszKey,lpStruct,uSizeStruct,szFile
);
        Hook reset_hook { Hook::Functions::WritePrivateProfileStructA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
BOOL __stdcall newWriteProfileSectionA(
       LPCSTR lpAppName,
       LPCSTR lpString
){
        	//unhook WriteProfileSectionAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::WriteProfileSectionA],
    		original_bytes[(int)Hook::Functions::WriteProfileSectionA], 6, NULL);

        BOOL result = WriteProfileSectionA(lpAppName,lpString
);
        Hook reset_hook { Hook::Functions::WriteProfileSectionA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
BOOL __stdcall newWriteProfileStringA(
       LPCSTR lpAppName,
       LPCSTR lpKeyName,
       LPCSTR lpString
){
        	//unhook WriteProfileStringAtion
    	WriteProcessMemory(GetCurrentProcess(),
    		(LPVOID)hooked_addr[(int)Hook::Functions::WriteProfileStringA],
    		original_bytes[(int)Hook::Functions::WriteProfileStringA], 6, NULL);

        BOOL result = WriteProfileStringA(lpAppName,lpKeyName,lpString
);
        Hook reset_hook { Hook::Functions::WriteProfileStringA};
        reset_hook.deploy_hook();

        //char* msg = new msg{whatever}
        //log1(msg,msg.len)

        return result;

}
}