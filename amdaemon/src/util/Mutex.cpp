#include "Mutex.h"

#include <windows.h>

namespace {
	void* getInvalidMutexHandleValue() {
		return nullptr;
	}

	HANDLE openMutex(const wchar_t *name) {
		return OpenMutexW(MUTEX_ALL_ACCESS, FALSE, name);
	}

	HANDLE createMutex(const wchar_t *name) {
		return CreateMutexW(nullptr, FALSE, name);
	}
}

namespace amdaemon::util {
	Mutex::Impl::Impl(const wchar_t *name) {
		this->_handle = getInvalidMutexHandleValue();
		this->_lockCount = 0;
		if (name) {
			this->_handle = openMutex(name);
		}
		if (!valid()) {
			this->_handle = createMutex(name);
		}
	}

	bool Mutex::Impl::valid() {
		return this->_handle != getInvalidMutexHandleValue();
	}

	Mutex::Mutex(const wchar_t *name) {
		this->_impl = std::make_unique<Impl>(Impl(name));
	}

	Mutex::Mutex(const Mutex &src) {
		this->_impl = std::move(src._impl);
	}
}
