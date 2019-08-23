cmake_minimum_required(VERSION 3.10)
project(Homework_1)

if(UNITTESTS)
    include(cmake/gtest.cmake)
endif()
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(problem1)
add_subdirectory(problem2)
add_subdirectory(problem3)
