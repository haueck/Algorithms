cmake_minimum_required(VERSION 3.0)

project(Problem)

add_definitions(-Wall -std=c++11 -g -O0)
add_library(sorting quicksort.cpp insertsort.cpp bubblesort.cpp mergesort.cpp bucketsort.cpp radixsort.cpp heapsort.cpp)
add_executable(tests tests.cpp)
target_link_libraries(tests sorting gtest pthread gtest_main)
