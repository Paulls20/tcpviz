#pragma once

#include <optional>
#include <string>
#include <vector>

namespace pcpp {
    class PcapLiveDevice;
}

namespace tcpviz {
    class Device {
    public:
        Device() = default;
        explicit Device(std::string deviceName);
        [[nodiscard]] std::string getName() const;
        [[nodiscard]] static std::vector<std::string> getDeviceNames() ;
        void open();

    private:
        void init(std::string deviceName);
        pcpp::PcapLiveDevice * liveDevice_ = nullptr;
    };
}// namespace tcpviz
