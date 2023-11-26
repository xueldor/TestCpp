cmake_minimum_required(VERSION 3.14)
project(c99c11new C)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD 11)

# Ubuntu18.04上面test_thread.c跑不起来，定义一个条件编译
set(TEST_THREAD false) #change to true or false
if(TEST_THREAD)
    message("include pthread")
    add_definitions(-DTEST_THREAD)
endif()

set(CMAKE_C_FLAGS -pthread)

add_executable(c99c11new main.c test_wchar_t.c test_vla.c test_init.c test_alignof.c )
if(TEST_THREAD)
    message("target_sources test_thread.c")
    target_sources(c99c11new  PRIVATE test_thread.c)
endif()