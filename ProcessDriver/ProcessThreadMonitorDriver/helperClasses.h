#pragma once
#include <ntddk.h>
#include "fastmutex.h"
#include <wdmsec.h>
#include <ntstrsafe.h>




enum class ItemType : short {
	None,
	ProcessCreate,
	ProcessExit,
	ThreadCreate,
	ThreadExit
};

struct ItemHeader {
	ItemType Type;
	USHORT Size;
	LARGE_INTEGER Time;
};


struct ProcessExitInfo : ItemHeader {
	ULONG ProcessId;
};

template<typename T>
struct FullItem {
	LIST_ENTRY Entry;
	T Data;
};


struct Globals {
	LIST_ENTRY ItemsHead;
	int ItemCount;
	FastMutex Mutex;
	DWORD idToBlock;
};

struct ProcessCreateInfo : ItemHeader {
	ULONG ProcessId;
	ULONG ParentProcessId;
	USHORT CommandLineLength;
	USHORT CommandLineOffset;
};

struct ThreadCreateExitInfo : ItemHeader {
	ULONG ThreadId;
	ULONG ProcessId;
};