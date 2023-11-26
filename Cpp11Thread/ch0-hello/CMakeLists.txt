cmake_minimum_required(VERSION 3.16)
project(ch0-hello)

set(CMAKE_CXX_STANDARD 14)
add_executable(ch0-hello main.cpp)
target_link_libraries(ch0-hello pthread)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#target_link_libraries(ch0-hello PUBLIC Threads::Threads)

#set_target_properties(ch0-hello PROPERTIES
#        COMPILE_FLAGS "-pthread"
#        LINK_FLAGS "-pthread")