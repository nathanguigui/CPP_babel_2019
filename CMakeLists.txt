 cmake_minimum_required(VERSION 2.8.12)
 project(CPP_babel_2019)

 add_definitions("-std=c++11")

 include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
 conan_basic_setup()

 add_executable(md5 mdr5.cpp)
 target_link_libraries(md5 ${CONAN_LIBS})