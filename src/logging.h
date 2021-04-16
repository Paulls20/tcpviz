#pragma once

#include <map>
#include <spdlog/spdlog.h>
#include <string_view>

namespace tcpviz {
    enum LogLevel {
        INFO = 0,
        ERROR,
        WARN,
        CRITICAL,
    };


    template<LogLevel level, typename... Args>
    void log(std::string_view formatString, Args... args) {
        switch (level) {
            case INFO:
                spdlog::info(formatString, args...);
                break;
            case ERROR:
                spdlog::error(formatString, args...);
                break;
            case WARN:
                spdlog::warn(formatString, args...);
                break;
            case CRITICAL:
                spdlog::critical(formatString, args...);
                break;
        }
    }
}// namespace tcpviz