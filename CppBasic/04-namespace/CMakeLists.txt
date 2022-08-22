cmake_minimum_required(VERSION 3.22)
project(04_namespace)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_namespace main.cpp testnamespace.cpp testScope2.cpp testScope.cpp testUsing.cpp)
