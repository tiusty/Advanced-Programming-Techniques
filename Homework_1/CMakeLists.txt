cmake_minimum_required(VERSION 2.8)
project(Homework_1)

# CMake 3.1 or older needs this method of setting compiler standards
add_compile_options(-std=c++14)

# If unittests are defined then clone down gtest repo for gtest sources files
if(UNITTESTS)
    include(cmake/gtest.cmake)
endif()

# Add the directories for the different problems
add_subdirectory(problem1)
add_subdirectory(problem2)
add_subdirectory(problem3)
