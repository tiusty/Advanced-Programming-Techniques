cmake_minimum_required(VERSION 2.8)
project(Hmk3_Problem1)

add_compile_options(-std=c++14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(LATTICE_LIB lattice)

add_executable(${PROJECT_NAME}
        main.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${LATTICE_LIB}
        )

add_library(${LATTICE_LIB}
        lattice.cpp
        )

target_include_directories(${LATTICE_LIB}
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )

# Custom command to copy the targets to the build directory
#   For easy of running
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}
        )
