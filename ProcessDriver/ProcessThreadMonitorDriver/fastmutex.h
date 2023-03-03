#pragma once
#include <ntddk.h>

NTSTATUS myFunc3();

class FastMutex {
public:
	void Init();
	void Lock();
	void Unlock();
private:
	FAST_MUTEX _mutex;
};


template<typename TLock>
struct AutoLock {
	AutoLock(TLock& lock) : _lock(lock) {
		__try {
			lock.Init();
			lock.Lock();
		}
		__except(EXCEPTION_EXECUTE_HANDLER){
			myFunc3();
		}
	}
	~AutoLock() {
		__try {
			_lock.Unlock();
		}
		__except(EXCEPTION_EXECUTE_HANDLER){
			myFunc3();
		}
	}
private:
	TLock& _lock;
};

