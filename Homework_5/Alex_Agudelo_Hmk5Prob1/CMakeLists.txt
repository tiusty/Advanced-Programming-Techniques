cmake_minimum_required(VERSION 2.8)
project(Homework_5)

# CMake 3.1 or older needs this method of setting compiler standards
add_compile_options(-std=c++14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# If unittests are defined then clone down gtest repo for gtest sources files
if(UNITTESTS)
    include(cmake/gtest.cmake)
endif()

# Add the directories for the different problems
add_executable(exec
        main.cpp)

target_link_libraries(exec
        PUBLIC
            ship
            world)

add_library(ship
        ship.cpp
        )
target_include_directories(ship
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )

add_library(world
        world.cpp)

target_include_directories(world
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR})

if(UNITTESTS)
    add_subdirectory(test)
endif()