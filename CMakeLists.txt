cmake_minimum_required(VERSION 3.25)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(test-unit)

add_executable(Project1
        src/AVL_TREE.cpp
        src/AVL_TREE.h
        src/main.cpp
        test-unit/catch.hpp
        test-unit/test.cpp)
