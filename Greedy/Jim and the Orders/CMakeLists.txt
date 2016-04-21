cmake_minimum_required(VERSION 2.8)

project(Problem)

if (EXISTS /opt/gcc-4.9.1/bin/g++)
    set(CMAKE_CXX_COMPILER /opt/gcc-4.9.1/bin/g++)
    add_definitions(-Wl,-rpath,/opt/gcc-4.9.1/lib)
endif()

add_definitions(-Wall -std=c++11 -g -O0)
add_executable(solution solution.cpp)
