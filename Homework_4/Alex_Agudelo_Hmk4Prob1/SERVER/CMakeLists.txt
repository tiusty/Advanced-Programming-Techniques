cmake_minimum_required(VERSION 2.8)
project(Homework_4_Server)

add_executable(${PROJECT_NAME}
        serverUDP.cpp
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )
