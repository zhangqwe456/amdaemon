
#include <string>
#include <windows.h>

#include "util/LaunchChecker.h"

using namespace amdaemon;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	auto checker = amdaemon::util::LaunchChecker(std::wstring(L"AM Daemon"));
}