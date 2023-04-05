#pragma once
#include <mutex>
#include <string>

#include "Mutex.h"

namespace amdaemon::util {
	class LaunchChecker {

		Mutex _mutex;
		std::unique_lock<Mutex> _controller;

	public:

		explicit LaunchChecker(const std::wstring& name);

        bool isFirstLaunch();

    };
}
