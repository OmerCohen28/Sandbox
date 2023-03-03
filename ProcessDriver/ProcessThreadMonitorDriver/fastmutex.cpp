#include "FastMutex.h"
void FastMutex::Init() {
	ExInitializeFastMutex(&_mutex);
}
void FastMutex::Lock() {
	ExAcquireFastMutex(&_mutex);
}
void FastMutex::Unlock() {
	ExReleaseFastMutex(&_mutex);
}

NTSTATUS myFunc3() {
	UNICODE_STRING fileName = RTL_CONSTANT_STRING(L"\\DosDevices\\C:\\temp\\error.txt");
	OBJECT_ATTRIBUTES objectAttributes;
	HANDLE fileHandle;
	IO_STATUS_BLOCK ioStatusBlock;
	NTSTATUS status;
	char writeBuffer[] = "Error with mutex";

	InitializeObjectAttributes(&objectAttributes, &fileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	status = ZwCreateFile(&fileHandle, GENERIC_WRITE, &objectAttributes, &ioStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

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