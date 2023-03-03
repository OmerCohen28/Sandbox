#pragma once
#include <ntddk.h>

void OnProcessNotify(PEPROCESS Process, HANDLE ProcessId,PPS_CREATE_NOTIFY_INFO CreateInfo);
NTSTATUS SysMonRead(PDEVICE_OBJECT, PIRP Irp);
NTSTATUS SysMonWrite(PDEVICE_OBJECT, PIRP Irp);
void SysMonUnload(PDRIVER_OBJECT DriverObject);
void OnThreadNotify(HANDLE ProcessId, HANDLE ThreadId, BOOLEAN Create);