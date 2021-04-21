#pragma once

#include "sniffer.h"
#include <tbb/concurrent_queue.h>

#include <string>
#include <vector>

namespace tcpviz {
    class Application {
    public:
        Application(int argc, char **argv);
        void init();
        [[nodiscard]] int run();

    private:
        void parseArguments(int argc, char **argv);
        bool enableGUI_{false};
        std::string networkInterface_;
        tbb::concurrent_bounded_queue<int> packetQueue_;
        std::unique_ptr<Sniffer> sniffer_ = nullptr;
    };
}// namespace tcpviz