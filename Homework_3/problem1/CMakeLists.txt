cmake_minimum_required(VERSION 2.8)
project(Hmk3_Problem1)

add_compile_options(-std=c++14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(${PROJECT_NAME}
        )

target_link_libraries(${PROJECT_NAME}
        ${MATRIX_LIB}
        )

# Custom command to copy the targets to the build directory
#   For easy of running
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}
        )

add_custom_command(TARGET ${MATRIX_LIB} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${MATRIX_LIB}> ${CMAKE_BINARY_DIR}
        )
