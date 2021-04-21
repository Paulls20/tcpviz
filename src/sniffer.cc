#include "sniffer.h"
#include "logging.h"
#include <PcapLiveDeviceList.h>
#include <chrono>
#include <thread>

using namespace tcpviz;

Sniffer::Sniffer(std::string device, tbb::concurrent_bounded_queue<int> &packetQueue)
    : packetQueue_(packetQueue) {
}

void Sniffer::run(std::stop_token stop_token) {
    using namespace std::chrono_literals;
    static int index = 0;
    while (!stop_token.stop_requested()) {
        packetQueue_.push(++index);
        std::this_thread::sleep_for(1s);
    }
}