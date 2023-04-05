#include "ArgumentsParser.h"

#include <unordered_map>
#include <algorithm>

namespace {

    using namespace amdaemon::process;

    struct OptionKeyInfo {
        std::wstring name;
        bool withParam;
        bool multiply;
    };

    OptionKeyInfo infos[5] = {
        {L"-c", true, true},
        {L"-l", true, false},
        {L"-m", true, false},
        {L"-f", false, false},
        {L"-w", true, false},
    };


    int addArgumentsToMap(const OptionKeyInfo &keyInfo, const std::vector<std::wstring> &params, std::unordered_map<std::wstring, std::vector<std::wstring>> &dest) {
        if (keyInfo.withParam == params.empty()) {
            return ArgumentsParser::Result::InvalidFormat;
        }
        auto v1 = &dest[keyInfo.name];
        v1->insert(v1->end(), params.begin(), params.end());
        if (keyInfo.multiply || v1->size() < 2) {
            return ArgumentsParser::Result::Ok;
        }
        return ArgumentsParser::Result::InvalidFormat;
    }

    const OptionKeyInfo (&getOptionKeyInfos())[5] {
        return (const OptionKeyInfo (&)[5])infos;
    }

    const OptionKeyInfo *findOptionKeyInfo(const std::wstring &key) {
        auto last = std::end(getOptionKeyInfos());
        auto res = std::find_if(std::begin(getOptionKeyInfos()), last, [&key](const OptionKeyInfo &info) {
            return info.name == key;
        });
        if (res == last) {
            return nullptr;
        }
        return res;
    }


    int makeArgumentMap(int argc, const wchar_t *const *argv, std::unordered_map<std::wstring, std::vector<std::wstring>> &dest) {
        OptionKeyInfo *keyInfo = nullptr;
        auto params = std::vector<std::wstring>();
        std::wstring key;
        for (auto j = 1; j < argc; ++j) {
            if (!argv[j]) {
                return ArgumentsParser::Result::InvalidParam;
            }
            if (*argv[j] == L'-') {
                if (keyInfo) {
                    auto v1 = addArgumentsToMap(*keyInfo, params, dest);
                    if (v1) {
                        return v1;
                    }
                }
                key = argv[j];
                std::transform(key.begin(), key.end(), key.begin(), towlower);
                keyInfo = (OptionKeyInfo *)findOptionKeyInfo(key);
                if (!keyInfo) {
                    return ArgumentsParser::Result::InvalidFormat;
                }
            } else {
                if (!keyInfo) {
                    return ArgumentsParser::Result::InvalidFormat;
                }
                params.emplace_back(argv[j]);
            }
        }
        if (keyInfo) {
            auto v1 = addArgumentsToMap(*keyInfo, params, dest);
            if (v1 != ArgumentsParser::Result::Ok) {
                return v1;
            }
        } else {
            return ArgumentsParser::Result::Ok;
        }
        return ArgumentsParser::Result::Ok;
    }
}

namespace amdaemon::process {

    ArgumentsParser::ArgumentsParser() = default;


    int ArgumentsParser::parse(int argc, const wchar_t *const *argv) {
        auto dest = std::unordered_map<std::wstring, std::vector<std::wstring>>();
        auto res = makeArgumentMap(argc, argv, dest);
        if (res) {
            return res;
        }
        auto v1 = dest.find(L"-w");
        if (v1 == dest.end()) {
            _bEnableConsoleStatus = false;
        } else {
            auto str = v1->second[0];
            std::transform(str.begin(), str.end(), str.begin(), towlower);
            if (str == L"show") {
                _bShowConsole = true;
            } else if (str == L"hide") {
                _bShowConsole = false;
            } else {
                return ArgumentsParser::Result::InvalidFormat;
            }
        }
        _configFilePathes.clear();
        _logFilePath.clear();
        _mergedConfigFilePath.clear();
        _frameRateHigh = false;
        v1 = dest.find(L"-c");
        if (v1 != dest.end()) {
            _configFilePathes = v1->second;
        }
        v1 = dest.find(L"-l");
        if (v1 != dest.end()) {
            _logFilePath = v1->second[0];
        }
        v1 = dest.find(L"-m");
        if (v1 != dest.end()) {
            _mergedConfigFilePath = v1->second[0];
        }
        v1 = dest.find(L"-f");
        _frameRateHigh = v1 != dest.end();
        return 0;
    }
}