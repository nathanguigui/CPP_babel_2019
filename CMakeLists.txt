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
        client/src/mainwidget.cpp client/src/Network/UdpNetwork.cpp client/src/Network/SipManager.cpp)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
add_executable(client ${CLIENT_SRC})
target_link_libraries(client ${CONAN_LIBS} Qt5::Core Qt5::OpenGL Qt5::Widgets Qt5::Network)

include_directories(server/includes)

set(SERVER_SRC
        server/src/main.cpp
        server/src/Server.cpp
        server/src/SipManager.cpp
        server/src/tcp_connection.cpp
        server/src/connection_manager.cpp
        )

set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})
find_package(SQLite3 REQUIRED)
add_executable(server ${SERVER_SRC})
target_link_libraries(server ${CONAN_LIBS} sqlite3)

