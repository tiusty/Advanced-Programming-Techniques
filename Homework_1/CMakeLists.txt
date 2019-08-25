cmake_minimum_required(VERSION 3.10)
project(Homework_1)

# If unittests are defined then clone down gtest repo for gtest sources files
if(UNITTESTS)
    include(cmake/gtest.cmake)
endif()

# Want to use c++ 14
set(CMAKE_CXX_STANDARD 14)

# Add the directories for the different problems
add_subdirectory(problem1)
add_subdirectory(problem2)
add_subdirectory(problem3)
