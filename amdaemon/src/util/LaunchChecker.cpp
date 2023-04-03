#include "LaunchChecker.h"

#include <mutex>
#include <string>

namespace amdaemon::util {

	LaunchChecker::LaunchChecker(const std::wstring *name) {
		const auto n = name->c_str();
		this->_mutex = Mutex(n);
		this->_controller = std::unique_lock(this->_mutex, std::try_to_lock);
	}

}
