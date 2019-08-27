cmake_minimum_required(VERSION 2.8)
project(Hmk1_Problem2)

add_executable(${PROJECT_NAME} Hmk1_Problem2.cpp)

# Custom command to copy the targets to the build directory
#   For easy of running
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}
        )
