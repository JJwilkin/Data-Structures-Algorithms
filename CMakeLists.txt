cmake_minimum_required(VERSION 3.15)
project(Assignment3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment3
        main.cpp
        lab3_binary_search_tree.cpp
        lab3_binary_search_tree.hpp
        lab3_priority_queue.cpp
        lab3_priority_queue.hpp
        lab3_tests.hpp)