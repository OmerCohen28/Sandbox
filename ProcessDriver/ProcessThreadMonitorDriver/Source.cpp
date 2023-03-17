#include <ntddk.h>
#include "helperClasses.h"
#define DRIVER_PREFIX "Moni: "
#define DRIVER_TAG 'dcba'
#include <wdmsec.h>
#include <ntstrsafe.h>
#include "functions.h"


#define FILE_DEVICE_MYDRIVER 0x00008001
#define MYDRIVER_WRITE_FILE CTL_CODE(FILE_DEVICE_MYDRIVER, 0x800, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

Globals g_Globals;


NTSTATUS MyFunc() {
	UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\DosDevices\\C:\\temp\\output.txt");
	OBJECT_ATTRIBUTES objectAttributes;
	HANDLE fileHandle;
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS status;
	char writeBuffer[] = "Hello from the driver";

	InitializeObjectAttributes(&objectAttributes, &fileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	status = ZwCreateFile(&fileHandle, GENERIC_WRITE, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	int g = 0;
	g += 1;
	if (!NT_SUCCESS(status))
	{
		// Handle error
		return status;
	}

	status = ZwWriteFile(fileHandle, NULL, NULL, NULL, &ioStatusBlock, writeBuffer, sizeof(writeBuffer), NULL, NULL);

	if (!NT_SUCCESS(status))
	{
		// Handle error
		ZwClose(fileHandle);
		return status;
	}

	ZwClose(fileHandle);
	return STATUS_SUCCESS;
}


NTSTATUS SysMonCreateClose(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp) { 
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

void SysMonUnload(PDRIVER_OBJECT DriverObject) {
	// unregister process notifications
	PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, TRUE);
	PsRemoveCreateThreadNotifyRoutine(OnThreadNotify);
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\sysmon");
	IoDeleteSymbolicLink(&symLink);
	IoDeleteDevice(DriverObject->DeviceObject);
	// free remaining items
	while (!IsListEmpty(&g_Globals.ItemsHead)) {
		auto entry = RemoveHeadList(&g_Globals.ItemsHead);
		//ExFreePool2(CONTAINING_RECORD(entry, FullItem<ItemHeader>, Entry),DRIVER_TAG,NULL,0);
		ExFreePool(CONTAINING_RECORD(entry, FullItem<ItemHeader>, Entry));
	}
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);
	g_Globals.idToBlock = 0000;
	auto status = STATUS_SUCCESS;
	InitializeListHead(&g_Globals.ItemsHead);
	g_Globals.Mutex.Init();
	PDEVICE_OBJECT DeviceObject = nullptr;
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\sysmon");
	bool symLinkCreated = false;
	do {
		UNICODE_STRING devName = RTL_CONSTANT_STRING(L"\\Device\\sysmon");
		status = IoCreateDevice(DriverObject, 0, &devName,
			FILE_DEVICE_UNKNOWN, 0, TRUE, &DeviceObject);
		if (!NT_SUCCESS(status)) {
			KdPrint((DRIVER_PREFIX "failed to create device (0x%08X)\n",
				status));
			break;
		}
		DeviceObject->Flags |= DO_DIRECT_IO;
		status = IoCreateSymbolicLink(&symLink, &devName);
		if (!NT_SUCCESS(status)) {
			KdPrint((DRIVER_PREFIX "failed to create sym link (0x%08X)\n",
				status));
			break;
		}
		symLinkCreated = true;
		// register for process notifications
		status = PsSetCreateProcessNotifyRoutineEx(OnProcessNotify, FALSE);
		if (!NT_SUCCESS(status)) {
			KdPrint((DRIVER_PREFIX "failed to register process callback (0x%08X)\n",
				status));
			break;
		}

		status = PsSetCreateThreadNotifyRoutine(OnThreadNotify);
		if (!NT_SUCCESS(status)) {
			KdPrint((DRIVER_PREFIX "failed to set thread callbacks (status=%08X)\n", status)\
			);
			break;
		} 


	} while (false);
	if (!NT_SUCCESS(status)) {
		if (symLinkCreated)
			IoDeleteSymbolicLink(&symLink);
		if (DeviceObject)
			IoDeleteDevice(DeviceObject);
	}
	DriverObject->MajorFunction[IRP_MJ_CREATE] =
		DriverObject->MajorFunction[IRP_MJ_CLOSE] = SysMonCreateClose;
	DriverObject->MajorFunction[IRP_MJ_READ] = SysMonRead;
	MyFunc();
	GetProcessIDToBlock(&g_Globals.idToBlock);
	DriverObject->DriverUnload = SysMonUnload;
	KdPrint(("Finished driver entry\n"));
	return status;
}

