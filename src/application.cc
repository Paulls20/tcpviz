#include "application.h"
#include "device.h"
#include "logging.h"
#include <argparse/argparse.hpp>

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

int Application::run() {

    if (enableGUI_) {
        log<INFO>("GUI enabled");
        for (const auto& dev : Device::getDeviceNames())
            log<INFO>("{}", dev);
    }
    else
    {
        Device device(networkInterface_);
        auto deviceName = device.getName();
        if (deviceName.empty()) {
            return 1;
        }

        device.open();
    }
    return 0;
}

