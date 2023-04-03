#pragma once
#include <memory>

namespace amdaemon::util {
	class Mutex
	{
		class Impl {
			void* _handle;
			std::atomic<int> _lockCount;

		public:
			Impl(const wchar_t* name);
			bool valid();
		};

		std::unique_ptr<Impl> _impl;

	public:
		Mutex(const wchar_t* name);
		Mutex(const Mutex&);
	};

}

