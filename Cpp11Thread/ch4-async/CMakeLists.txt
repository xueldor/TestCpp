cmake_minimum_required(VERSION 3.16)
project(test_async)

set(CMAKE_CXX_STANDARD 14)
add_executable(test_async test_async.cpp)
target_link_libraries(test_async pthread)
