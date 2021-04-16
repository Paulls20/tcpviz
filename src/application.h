#pragma once

#include "sniffer.h"

#include <string>
#include <vector>

namespace tcpviz {
    class Application {
    public:
        Application(int argc, char** argv);
        [[nodiscard]] int run() ;
    private:
        void parseArguments(int argc, char **argv);
        bool enableGUI_{false};
        std::string networkInterface_;
    };
}