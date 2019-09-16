 cmake_minimum_required(VERSION 2.8.12)
 project(CPP_babel_2019)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 set(CLIENT_SRC
         client/src/main.cpp
)

 add_executable(client ${CLIENT_SRC})
 target_link_libraries(client ${CONAN_LIBS})