cmake_minimum_required(VERSION 3.1.0)
project(CPP_babel_2019)

set(CMAKE_AUTOMOC ON)
add_definitions("-std=c++11")

set(CMAKE_VERBOSE_MAKEFILE TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(client/includes)

set(CLIENT_SRC
    client/src/main.cpp
        client/src/mainwidget.cpp client/src/Network/UdpNetwork.cpp client/src/Network/SipManager.cpp client/src/Network/TcpNetwork.cpp)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
add_executable(client ${CLIENT_SRC})
target_link_libraries(client ${CONAN_LIBS} Qt5::Core Qt5::OpenGL Qt5::Widgets Qt5::Network)

