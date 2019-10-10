cmake_minimum_required(VERSION 2.8)
project(Homework_4_Client)

add_executable(${PROJECT_NAME}
        main.cpp
        clientUDP.cpp
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
