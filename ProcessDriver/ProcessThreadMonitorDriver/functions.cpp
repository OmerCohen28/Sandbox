#include <ntddk.h>
#include <ntstrsafe.h>
//#include < Ntifs.h>
#include <wdmsec.h>
#include "fastmutex.h"
#include "helperClasses.h"
#include "functions.h"
#define DRIVER_PREFIX "Zero: "
#define DRIVER_TAG 'dcba'

#if defined(_WIN64)
typedef ULONG_PTR PROCESS_ID;
#else
typedef ULONG PROCESS_ID;
#endif

extern Globals g_Globals;

NTSTATUS MyFunc3(DWORD* info) {
	UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\DosDevices\\C:\\temp\\output.txt");
	OBJECT_ATTRIBUTES objectAttributes;
	HANDLE fileHandle;
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS status;

	InitializeObjectAttributes(&objectAttributes, &fileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	status = ZwCreateFile(&fileHandle, GENERIC_WRITE, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	int g = 0;
	g += 1;
	if (!NT_SUCCESS(status))
	{
		// Handle error
		return status;
	}

	status = ZwWriteFile(fileHandle, NULL, NULL, NULL, &ioStatusBlock, info, sizeof(DWORD), NULL, NULL);

	if (!NT_SUCCESS(status))
	{
		// Handle error
		ZwClose(fileHandle);
		return status;
	}

	ZwClose(fileHandle);
	return STATUS_SUCCESS;
}

DWORD ConvertLittleEndianToBigEndian(DWORD littleEndianValue) {
	DWORD bigEndianValue = ((littleEndianValue & 0x000000FF) << 24) |
		((littleEndianValue & 0x0000FF00) << 8) |
		((littleEndianValue & 0x00FF0000) >> 8) |
		((littleEndianValue & 0xFF000000) >> 24);
	return bigEndianValue;
}

DWORD asciiToInteger(const char* str)
{
	DWORD value = 0;
	while (*str != '\0') {
		value = (value * 10) + (*str - '0');
		++str;
	}
	return value;
}

NTSTATUS GetProcessIDToBlock(DWORD* id) {
	NTSTATUS status;

	//UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\DosDevices\\C:\\temp\\id.txt");

	UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\DosDevices\\C:\\temp\\id.txt");


	HANDLE fileHandle;
	OBJECT_ATTRIBUTES objectAttributes;
	IO_STATUS_BLOCK ioStatusBlock;
	InitializeObjectAttributes(&objectAttributes, &fileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);
	status = ZwCreateFile(&fileHandle, GENERIC_READ | SYNCHRONIZE, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OPEN_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

	if (!NT_SUCCESS(status))
	{
		// Handle error
		ZwClose(fileHandle);
		return status;
	}

	auto info = (char*)ExAllocatePool2(POOL_FLAG_NON_PAGED,
		sizeof(DWORD), DRIVER_TAG);

	if (info == NULL) {
		ZwClose(fileHandle);
		return STATUS_SUCCESS;
	}

	status = ZwReadFile(
		fileHandle,
		NULL,
		NULL,
		NULL,
		&ioStatusBlock,
		info,
		sizeof(DWORD),
		NULL,
		NULL
	);

	if (info == NULL) {
		ZwClose(fileHandle);
		return STATUS_SUCCESS;
	}

	if (!NT_SUCCESS(status))
	{
		// Handle error
		ZwClose(fileHandle);
		return status;
	}

	DWORD idInDWORD = asciiToInteger(info);
	
	if (idInDWORD == (DWORD)6120) {
		*id = idInDWORD;
		ZwClose(fileHandle);
		return STATUS_SUCCESS;
	}

	if (idInDWORD == 6120) {
		*id = idInDWORD;
		ZwClose(fileHandle);
		return STATUS_SUCCESS;
	}

	DWORD info2 = ConvertLittleEndianToBigEndian(idInDWORD);

	if (info2 == (DWORD)6120) {
		return STATUS_SUCCESS;
	}

	char procID[10];
	sprintf(procID, "%d", *info);
	ZwClose(fileHandle);
	ExFreePool(info);
	return STATUS_SUCCESS;
}


extern "C" NTSTATUS myFunc2() {
	static int count = -1;
	++count;

	UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\DosDevices\\C:\\temp\\output2.txt");
	HANDLE fileHandle;
	OBJECT_ATTRIBUTES objectAttributes;
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS status;

	WCHAR buffer[25];
	RtlStringCchPrintfW(buffer, sizeof(buffer), L"ThreaddExitedd %d", count);

	//*buff = *tmp + *count_str;

	InitializeObjectAttributes(&objectAttributes, &fileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	status = ZwCreateFile(&fileHandle, GENERIC_WRITE | FILE_WRITE_DATA, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

	if (!NT_SUCCESS(status))
	{
		// Handle error
		ZwClose(fileHandle);
		return status;
	}

	status = ZwWriteFile(fileHandle, NULL, NULL, NULL, &ioStatusBlock, buffer,19*sizeof(WCHAR), NULL, NULL);

	if (!NT_SUCCESS(status))
	{
		// Handle error
		ZwClose(fileHandle);
		return status;
	}

	ZwClose(fileHandle);
	return STATUS_SUCCESS;
}

void PushItem(LIST_ENTRY* entry) {
	AutoLock<FastMutex> lock(g_Globals.Mutex);
	if (g_Globals.ItemCount > 800) {
		// too many items, remove oldest one
		auto head = RemoveHeadList(&g_Globals.ItemsHead);
		g_Globals.ItemCount--;
		auto item = CONTAINING_RECORD(head, FullItem<ItemHeader>, Entry);
		//ExFreePool2(item, DRIVER_TAG,NULL,0);
		ExFreePool(item);
	}
	InsertTailList(&g_Globals.ItemsHead, entry);
	g_Globals.ItemCount++;
}

void f(DWORD n1, DWORD n2) {
	UNREFERENCED_PARAMETER(n1);
	UNREFERENCED_PARAMETER(n2);

}


void OnProcessNotify(PEPROCESS Process, HANDLE ProcessId,
	PPS_CREATE_NOTIFY_INFO CreateInfo) {
	//HANDLE ProcessHandle = CreateInfo->CreatingThreadId.UniqueProcess;
	//PEPROCESS Process = NULL;
	//NTSTATUS status = PsLookupProcessByProcessId(ProcessHandle, &Process);
	//if (NT_SUCCESS(status)) {
	//	// Get the process ID from the handle using PsGetProcessId.
	//	DWORD HandleProcessId = (DWORD)PsGetProcessId(Process);

	//	// Compare the two process IDs.
	//	if (HandleProcessId == (DWORD)6112) {
	//		// The two process IDs match.
	//	}
	//	else {
	//		// The two process IDs do not match.
	//	}

	//	// Release the reference to the process object.
	//	ObDereferenceObject(Process);
	//}
	//else {
	//	// PsLookupProcessByProcessId failed. Handle the error.
	//}
	/*if (CreateInfo->CreatingThreadId.UniqueProcess == nullptr || CreateInfo->CreatingThreadId.UniqueProcess == NULL) {
		return;
	}*/
	if (CreateInfo == nullptr) {
		return;
	}
	if (CreateInfo->CreatingThreadId.UniqueProcess == nullptr) {
		return;
	}
	DWORD pId = HandleToULong(CreateInfo->CreatingThreadId.UniqueProcess);

	if (pId == (DWORD)2444) {
		CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
		return;
	}

	if (pId == g_Globals.idToBlock) {
		CreateInfo->CreationStatus = STATUS_ACCESS_DENIED;
		return;
	}
	
	UNREFERENCED_PARAMETER(Process);
	if (CreateInfo) {
		USHORT allocSize = sizeof(FullItem<ProcessCreateInfo>);
		USHORT commandLineSize = 0;
		if (CreateInfo->CommandLine) {
			commandLineSize = CreateInfo->CommandLine->Length;
			allocSize += commandLineSize;
		}
		auto info = (FullItem<ProcessCreateInfo>*)ExAllocatePool2(POOL_FLAG_NON_PAGED,
			allocSize, DRIVER_TAG);
		if (info == nullptr) {
			KdPrint((DRIVER_PREFIX "failed allocation\n"));
			return;
		}


		auto& item = info->Data;
		KeQuerySystemTimePrecise(&item.Time);
		item.Type = ItemType::ProcessCreate;
		item.Size = sizeof(ProcessCreateInfo) + commandLineSize;
		item.ProcessId = HandleToULong(ProcessId);
		item.ParentProcessId = HandleToULong(CreateInfo->ParentProcessId);


		if (commandLineSize > 0) {
			::memcpy((UCHAR*)&item + sizeof(item), CreateInfo->CommandLine->Buffer,
				commandLineSize);
			item.CommandLineLength = commandLineSize / sizeof(WCHAR); // length in WCHARs
			item.CommandLineOffset = sizeof(item);
		}
		else {
			item.CommandLineLength = 0;
		}
		PushItem(&info->Entry);
	}
	else {
		auto info = (FullItem<ProcessExitInfo>*)ExAllocatePool2(POOL_FLAG_NON_PAGED,
			sizeof(FullItem<ProcessExitInfo>), DRIVER_TAG);
		if (info == nullptr) {
			KdPrint((DRIVER_PREFIX "failed allocation\n"));
			return;
		}
		auto& item = info->Data;
		KeQuerySystemTimePrecise(&item.Time);
		item.Type = ItemType::ProcessExit;
		item.ProcessId = HandleToULong(ProcessId);
		item.Size = sizeof(ProcessExitInfo);
		PushItem(&info->Entry);


	}
}


NTSTATUS SysMonRead(PDEVICE_OBJECT, PIRP Irp) {
	auto stack = IoGetCurrentIrpStackLocation(Irp);
	auto len = stack->Parameters.Read.Length;
	auto status = STATUS_SUCCESS;
	auto count = 0;
	NT_ASSERT(Irp->MdlAddress); // we're using Direct I/O
	auto buffer = (UCHAR*)MmGetSystemAddressForMdlSafe(Irp->MdlAddress,
		NormalPagePriority);
	if (!buffer) {
		status = STATUS_INSUFFICIENT_RESOURCES;
	}
	else {
		AutoLock lock(g_Globals.Mutex);
		while (true) {
			if (IsListEmpty(&g_Globals.ItemsHead)) // can also check g_Globals.ItemCount
				break;
			auto entry = RemoveHeadList(&g_Globals.ItemsHead);
			auto info = CONTAINING_RECORD(entry, FullItem<ItemHeader>, Entry);
			auto size = info->Data.Size;
			if (len < size) {
				// user's buffer is full, insert item back
				InsertHeadList(&g_Globals.ItemsHead, entry);
				break;
			}
			g_Globals.ItemCount--;
			::memcpy(buffer, &info->Data, size);
			len -= size;
			buffer += size;
			count += size;
			// free data after copy
			ExFreePool(info);
		}
	}
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = count;
	IoCompleteRequest(Irp, 0);
	return status;
}



void OnThreadNotify(HANDLE ProcessId, HANDLE ThreadId, BOOLEAN Create) {
	//myFunc2();
	DWORD pId = HandleToULong(ProcessId);

	if (pId == (DWORD)2444) {
		Create = FALSE;
		return;
	}

	if (pId == g_Globals.idToBlock) {
		Create = FALSE;
		return;
	}
	auto size = sizeof(FullItem<ThreadCreateExitInfo>);
	auto info = (FullItem<ThreadCreateExitInfo>*)ExAllocatePool2(POOL_FLAG_NON_PAGED,
		size, DRIVER_TAG);
	if (info == nullptr) {
		KdPrint((DRIVER_PREFIX "Failed to allocate memory\n"));
		return;
	}
	auto& item = info->Data;
	KeQuerySystemTimePrecise(&item.Time);
	item.Size = sizeof(item);
	item.Type = Create ? ItemType::ThreadCreate : ItemType::ThreadExit;
	item.ProcessId = HandleToULong(ProcessId);
	item.ThreadId = HandleToULong(ThreadId);
	PushItem(&info->Entry);
}
