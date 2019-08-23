cmake_minimum_required(VERSION 3.10)
project(problem3)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        main.cpp
        knight.cpp
        fib_helper.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

if(UNITTESTS)
    add_subdirectory(test)
endif()
