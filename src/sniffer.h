#pragma once

#include <stop_token>
#include <string>
#include <tbb/concurrent_queue.h>

namespace tcpviz {
    class Sniffer {
    public:
        Sniffer(std::string device, tbb::concurrent_bounded_queue<int> &packetQueue);
        void run(std::stop_token stop_token);

    private:
        tbb::concurrent_bounded_queue<int> &packetQueue_;
    };
}// namespace tcpviz