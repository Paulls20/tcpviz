project(tcpviz)

cmake_minimum_required(VERSION 3.13)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

conan_basic_setup(TARGETS)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cc
        src/application.h
        src/application.cc
        src/logging.h
        src/sniffer.h
        src/sniffer.cc
        src/device.h
        src/device.cc)

target_link_libraries(${PROJECT_NAME}
        CONAN_PKG::pcapplusplus
        CONAN_PKG::spdlog
        CONAN_PKG::tbb)
