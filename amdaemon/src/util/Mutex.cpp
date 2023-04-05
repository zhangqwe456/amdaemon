#include "Mutex.h"

#include <windows.h>
#include <mutex>

namespace {

    namespace mutexDetail {
        bool lockMutexImpl(void *handle, unsigned int timeoutMilliseconds) {
            DWORD result = WaitForSingleObject(handle, timeoutMilliseconds);
            return result == WAIT_OBJECT_0 || result == WAIT_ABANDONED;
        }
    }

	void* getInvalidMutexHandleValue() {
		return nullptr;
	}

	HANDLE openMutex(const wchar_t *name) {
		return OpenMutexW(MUTEX_ALL_ACCESS, FALSE, name);
	}

	HANDLE createMutex(const wchar_t *name) {
		return CreateMutexW(nullptr, FALSE, name);
	}

    bool tryLockMutex(void *handle) {
        return mutexDetail::lockMutexImpl(handle, 0);
    }

    bool lockMutex(void *handle) {
        return mutexDetail::lockMutexImpl(handle, INFINITE);
    }

    bool unlockMutex(void *handle) {
        return ReleaseMutex(handle);
    }

}

namespace amdaemon::util {
	Mutex::Impl::Impl(const wchar_t *name) {
		_handle = getInvalidMutexHandleValue();
		_lockCount = 0;
		if (name) {
			_handle = openMutex(name);
		}
		if (!valid()) {
			_handle = createMutex(name);
		}
	}

	bool Mutex::Impl::valid() {
		return _handle != getInvalidMutexHandleValue();
	}

    bool Mutex::Impl::try_lock() {
        return doLock([](void *handle) {
            return tryLockMutex(handle);
        });
    }

    bool Mutex::Impl::lock() {
        return doLock([](void *handle) {
            return lockMutex(handle);
        });
    }

    bool Mutex::Impl::unlock() {
        if (!valid() || _lockCount == 0 || !unlockMutex(_handle)) {
            return false;
        }
        _lockCount--;
        return true;
    }

    template<typename F>
    bool Mutex::Impl::doLock(F locker) {
        if (!valid()) {
            return false;
        }
        if (!locker(_handle)) {
            return false;
        }
        _lockCount++;
        return true;
    }

    Mutex::Mutex(const wchar_t *name) {
		_impl = std::make_unique<Impl>(name);
	}

	Mutex::Mutex(Mutex &&src) noexcept {
        _impl = std::move(src._impl);
	}

    bool Mutex::try_lock() {
        return _impl && _impl->try_lock();
    }

    bool Mutex::lock() {
        return _impl && _impl->lock();
    }

    bool Mutex::unlock() {
        return _impl && _impl->unlock();
    }

    Mutex::operator int() {
        return 0;
    }
}
