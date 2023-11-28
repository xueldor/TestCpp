cmake_minimum_required(VERSION 3.16)
project(test_threadpool)

set(CMAKE_CXX_STANDARD 14)
add_executable(test_threadpool test_threadpool.cpp)
target_link_libraries(test_threadpool pthread)
