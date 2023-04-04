#pragma once
#include <memory>
#include <atomic>

namespace amdaemon::util {
	class Mutex {

        class Impl {
            void* _handle;
            std::atomic<int> _lockCount;

        public:
            explicit Impl(const wchar_t* name);
            bool valid();
            bool try_lock();

            template<typename F>
            bool doLock(F locker);

            bool lock();

            bool unlock();
        };

        std::unique_ptr<Impl> _impl;
	public:

		explicit Mutex(const wchar_t* name);
		Mutex(const Mutex&&) noexcept;

        bool try_lock();

        bool lock();

        bool unlock();
    };

}

