
#include <string>
#include <windows.h>

#include "util/LaunchChecker.h"
#include "process/ArgumentsParser.h"

using namespace amdaemon;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow) {
	auto checker = amdaemon::util::LaunchChecker(std::wstring(L"AM Daemon"));
    if (checker.isFirstLaunch()) {
        auto args = amdaemon::process::ArgumentsParser();

    }
}