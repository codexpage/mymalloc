cmake_minimum_required(VERSION 3.9)
project(hw3)

set(CMAKE_CXX_STANDARD 99)

add_executable(hw3
        calloc.c
        free.c
        malloc.c
        malloc.h
        memalign.c
        posix_memalign.c
        realloc.c
        reallocarray.c
        simple-test.c
        t-test1.c
        t-test2.c
        test.c
        thread-test.c
        util.c)

add_custom_target(mytest COMMAND make test4
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(test2
        calloc.c
        free.c
        malloc.c
        malloc.h
        realloc.c
        reallocarray.c
        t-test1.c
        util.c)

target_link_libraries(test2 pthread)