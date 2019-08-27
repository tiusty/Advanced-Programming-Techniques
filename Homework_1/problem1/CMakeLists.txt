cmake_minimum_required(VERSION 2.8)
project(Hmk1_Problem3)

add_executable(${PROJECT_NAME} main.cpp)

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${PROJECT_SOURCE_DIR}
        )
