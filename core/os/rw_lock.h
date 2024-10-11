#ifndef RW_LOCK_H
#define RW_LOCK_H

#include "core/error_list.h"

#if !defined(NO_THREADS)
#include "core/typedefs.h"

#include <shared_mutex>

class RWLock {
	mutable std::shared_timed_mutex mutex;

public:
	// Lock the RWLock, block if locked by someone else.
	_ALWAYS_INLINE_ void read_lock() const {
		mutex.lock_shared();
	}

	// Unlock the RWLock, let other threads continue.
	_ALWAYS_INLINE_ void read_unlock() const {
		mutex.unlock_shared();
	}

	// Attempt to lock the RWLock for reading. True on success, false means it can't lock.
	_ALWAYS_INLINE_ Error read_try_lock() const {
		return mutex.try_lock_shared() ? OK : ERR_BUSY;
	}

	// Lock the RWLock, block if locked by someone else.
	_ALWAYS_INLINE_ void write_lock() {
		mutex.lock();
	}

	// Unlock the RWLock, let other threads continue.
	_ALWAYS_INLINE_ void write_unlock() {
		mutex.unlock();
	}

	// Attempt to lock the RWLock for writing. True on success, false means it can't lock.
	_ALWAYS_INLINE_ Error write_try_lock() {
		return mutex.try_lock() ? OK : ERR_BUSY;
	}
};

#else

class RWLock {
public:
	void read_lock() const {}
	void read_unlock() const {}
	Error read_try_lock() const { return OK; }

	void write_lock() {}
	void write_unlock() {}
	Error write_try_lock() { return OK; }
};

#endif

class RWLockRead {
	const RWLock &lock;

public:
	_ALWAYS_INLINE_ RWLockRead(const RWLock &p_lock) :
			lock(p_lock) {
		lock.read_lock();
	}
	_ALWAYS_INLINE_ ~RWLockRead() {
		lock.read_unlock();
	}
};

class RWLockWrite {
	RWLock &lock;

public:
	_ALWAYS_INLINE_ RWLockWrite(RWLock &p_lock) :
			lock(p_lock) {
		lock.write_lock();
	}
	_ALWAYS_INLINE_ ~RWLockWrite() {
		lock.write_unlock();
	}
};

#endif // RW_LOCK_H
