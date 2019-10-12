cmake_minimum_required(VERSION 3.1.0)
project(CPP_babel_2019)

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)
INCLUDE_DIRECTORIES(${CONAN_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_thread -lclient/dependencies/libs/portaudio_x86 -lclient/dependencies/libs/celt -lclient/dependencies/libs/opus -lclient/dependencies/libs/silk_common -lclient/dependencies/libs/silk_fixed -lclient/dependencies/libs/silk_float")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_thread -Lclient/dependencies -lopus -lportaudio")
endif()

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(CLIENT_SOURCES
    client/src/main.cpp
    client/src/mainwindow.cpp
    client/src/optionWindow.cpp
    client/src/UISettings.cpp
    client/src/contactWindow.cpp
    client/src/callWindow.cpp
    client/src/Network/SessionManager.cpp
    client/src/Network/TcpNetwork.cpp
    client/src/Network/UdpNetwork.cpp
    client/src/contact.cpp
    client/src/Network/AsyncSession.cpp 
    client/src/CallManagement/CallManager.cpp
    client/src/Audio/AudioException.cpp
    client/src/Audio/OutputDevice.cpp
    client/src/Audio/RecordingDevice.cpp
    client/src/Audio/SoundManager.cpp
    client/src/callThread.cpp)

set(CLIENT_HEADERS
    client/includes/mainWindow.hpp
    client/includes/optionWindow.hpp
    client/includes/UISettings.hpp
    client/includes/contactWindow.hpp
    client/includes/callWindow.hpp
    client/includes/Network/SessionManager.hpp
    client/includes/Network/TcpNetwork.hpp
    client/includes/Network/UdpNetwork.hpp
    client/includes/contact.hpp
    client/includes/Network/SERVER_IP.hpp
    client/includes/Network/AsyncSession.hpp
    client/includes/CallManagement/CallManager.hpp
    client/includes/Audio/AudioException.hpp
    client/includes/Audio/AudioSettings.hpp
    client/includes/Audio/IAudioDevice.hpp
    client/includes/Audio/OutputDevice.hpp
    client/includes/Audio/RecordingDevice.hpp
    client/includes/Audio/SoundManager.hpp
    client/includes/callThread.hpp
    client/includes/portaudio.h)

set(CLIENT_LIBRARIES
    Qt5::Core
    Qt5::Widgets
    Qt5::Network)

include_directories(babel_client client/includes)

add_executable(babel_client ${CLIENT_SOURCES} ${CLIENT_HEADERS})

target_link_libraries(babel_client Qt5::Core Qt5::Widgets Qt5::Network)

#include_directories(server/includes)

set(SERVER_SRC
        server/src/main.cpp
        server/src/Server.cpp
        server/src/SipManager.cpp
        server/src/tcp_connection.cpp
        server/src/connection_manager.cpp
        )

set(SERVER_HEADERS
        server/includes/Server.hpp
        server/includes/SipManager.hpp
        )

#set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})
find_package(SQLite3 REQUIRED)
add_executable(server ${SERVER_SRC} ${SERVER_HEADERS})
target_link_libraries(server sqlite3)

#cmake_minimum_required(VERSION 3.1.0)
#project(CPP_babel_2019)
#
#set(CMAKE_AUTOMOC ON)
#add_definitions("-std=c++11")
#
#set(CMAKE_VERBOSE_MAKEFILE TRUE)
#
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()
#
#
#include_directories(client/includes)
#
#set(CLIENT_SRC
#    client/src/main.cpp
#        client/src/mainwidget.cpp)
#
#find_package(Qt5Core CONFIG REQUIRED)
#find_package(Qt5OpenGL REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#add_executable(client ${CLIENT_SRC})
#target_link_libraries(client ${CONAN_LIBS} Qt5::Core Qt5::OpenGL Qt5::Widgets)
#
#include_directories(server/includes)
#
#set(SERVER_SRC
#        server/src/main.cpp
#        )
#
#set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})
#find_package(SQLite3 REQUIRED)
#add_executable(server ${SERVER_SRC})
#target_link_libraries(server ${CONAN_LIBS} sqlite3)
#

#include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)
#file(COPY ${CMAKE_BINARY_DIR}/qt.conf DESTINATION ${CMAKE_SOURCE_DIR})
#subdirs(.)
#
#set(CMAKE_AUTOUIC ON)
#set(AUTOGEN_BUILD_DIR ${CMAKE_SOURCE_DIR/client/includes})
#set(babel_client_SRCS main.cpp mainWindow.cpp loginWindow.cpp)
#
#find_package(Qt5Widgets CONFIG REQUIRED)
#find_package(Qt5OpenGL REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Network REQUIRED)
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
#add_executable(babel_client ${babel_client_SRCS})
#
#target_include_directories(babel_client PUBLIC ${babel_SOURCE_DIR} PUBLIC ${babel_SOURCE_DIR}/client/includes)
#target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Core Qt5::OpenGL Qt5::Widgets Qt5::Network)




#include_directories(${babel_source_dir}/client/includes)
#include_directories(client/includes)
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#
#
#set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++11")
#target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Core Qt5::OpenGL Qt5::Widgets Qt5::Network)


#set(CMAKE_AUTOMOC ON)
#add_definitions("-std=c++11")
#
#set(CMAKE_VERBOSE_MAKEFILE TRUE)
#
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()
#
#
#include_directories(client/includes)
#
#set(CLIENT_SRC
#    client/src/main.cpp
#        client/src/mainwindow.cpp
#        client/src/loginWindow.cpp)
#
#find_package(Qt5Core CONFIG REQUIRED)
#find_package(Qt5OpenGL REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5Network REQUIRED)
#add_executable(client ${CLIENT_SRC})
#target_link_libraries(CPP_babel_2019 ${CONAN_LIBS} Qt5::Core Qt5::OpenGL Qt5::Widgets Qt5::Network)



