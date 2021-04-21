#include "application.h"

int main(int argc, char *argv[]) {
    tcpviz::Application app(argc, argv);
    app.init();
    return app.run();
}