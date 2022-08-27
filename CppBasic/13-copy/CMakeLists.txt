cmake_minimum_required(VERSION 3.22)
project(13_copy)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_copy main.cpp test_array_copy.cpp test_class_copy.cpp)
