#include "LaunchChecker.h"

#include <mutex>
#include <string>

namespace amdaemon::util {

    LaunchChecker::LaunchChecker(const std::wstring &name) :
        _mutex(name.c_str()),
        _controller(std::unique_lock(this->_mutex, std::try_to_lock)) {}

    bool LaunchChecker::isFirstLaunch() {
        return _controller.owns_lock();
    }
}
