#include "application.h"
#include "device.h"
#include "logging.h"
#include <argparse/argparse.hpp>
#include <thread>

using namespace tcpviz;

Application::Application(int argc, char **argv) {
    parseArguments(argc, argv);
}

void Application::parseArguments(int argc, char **argv) {
    argparse::ArgumentParser app("tcp visualizer");

    app.add_argument("--interface", "-i")
            .help("network interface e.g. eth0")
            .default_value(std::string(""));

    app.add_argument("--gui", "-g")
            .help("show GUI")
            .default_value(false)
            .implicit_value(true);


    try {
        app.parse_args(argc, argv);

    } catch (const std::runtime_error &err) {
        log<ERROR>(err.what());
        exit(1);
    }

    if (app["--gui"] == true) {
        enableGUI_ = true;
    }

    networkInterface_ = app.get<std::string>("--interface");
}

void Application::init()
{
    sniffer_ = std::make_unique<Sniffer>(networkInterface_, packetQueue_);
}

int Application::run() {

    if (enableGUI_) {
        log<INFO>("GUI enabled");
        for (const auto &dev : Device::getDeviceNames())
            log<INFO>("{}", dev);
    } else {
        Device device(networkInterface_);
        auto deviceName = device.getName();
        if (deviceName.empty()) {
            return 1;
        }

        device.open();
    }

    std::jthread snifferThread(std::bind_front(&Sniffer::run, *sniffer_));
    while (true) { // TODO: Remove test code.
        using namespace std::chrono_literals;
        int packet = -1;
        if (packetQueue_.try_pop(packet)) {
            log<INFO>("Packet recevied {}", packet);
        }
        std::this_thread::sleep_for(1s);
    }

    return 0;
}
