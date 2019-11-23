cmake_minimum_required(VERSION 2.8)
project(FinalProject)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# CMake 3.1 or older needs this method of setting compiler standards
add_compile_options(-std=c++11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(${PROJECT_NAME}
        main.cpp)