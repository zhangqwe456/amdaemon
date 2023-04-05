#ifndef AMDAEMON_ARGUMENTSPARSER_H
#define AMDAEMON_ARGUMENTSPARSER_H

#include <vector>
#include <string>


namespace amdaemon::process {

    class ArgumentsParser {
        std::vector<std::wstring> _configFilePathes{};
        std::wstring _logFilePath{};
        std::wstring _mergedConfigFilePath{};
        bool _frameRateHigh{};
        bool _bEnableConsoleStatus{};
        bool _bShowConsole{};

    public:
        enum Result : __int32
        {
            Ok = 0x0,
            InvalidParam = 0x1,
            InvalidFormat = 0x2,
            NoRequired = 0x3,
        };

        ArgumentsParser();

        int parse(int argc, const wchar_t *const argv[]);
    };

}


#endif //AMDAEMON_ARGUMENTSPARSER_H
