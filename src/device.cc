#include "device.h"
#include "logging.h"
#include <PcapLiveDeviceList.h>
#include <ranges>

using namespace tcpviz;

Device::Device(std::string deviceName) {
    init(deviceName);
}

void Device::init(std::string deviceName)
{
    liveDevice_ = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(deviceName);
    if (liveDevice_ == nullptr) {
        log<ERROR>("No network interface found");
    }
}

std::string Device::getName() const {
    if (liveDevice_ == nullptr) {
        return "";
    }

    return liveDevice_->getName();
}

std::vector<std::string> Device::getDeviceNames() {
    std::vector<std::string> deviceNames;
    auto deviceList = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    std::ranges::transform(deviceList, std::back_inserter(deviceNames),
                           [](pcpp::PcapLiveDevice *liveDevice) -> std::string { return liveDevice->getName(); });
    return deviceNames;
}

void Device::open() {
    if (liveDevice_ == nullptr)
    {
        log<ERROR>("Interface not initialized.");
        return;
    }

    if (!liveDevice_->open())
    {
        log<ERROR>("Cannot open interface");
        return;
    }

    log<INFO>("Device {} opened", getName());


}
