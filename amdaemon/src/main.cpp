
#include <string>
#include <windows.h>

#include "util/LaunchChecker.h"
#include "process/ArgumentsParser.h"

using namespace amdaemon;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow) {
	auto checker = amdaemon::util::LaunchChecker(std::wstring(L"AM Daemon"));
    if (checker.isFirstLaunch()) {
        auto args = amdaemon::process::ArgumentsParser();
        if (args.parse(__argc, __wargv) != 0) {
            fwprintf_s(stderr, L"Usage: amdaemon.exe [-c <config file path ...>] [-l <log file path>]\n");
            return 20;
        } else {
            // amdaemon::App::App();
            return 0;
        }
    } else {
        return 10;
    }
}