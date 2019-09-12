cmake_minimum_required(VERSION 2.8)
project(Hmk2_Problem3)

add_compile_options(-std=c++14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(TRI_LIB tri)
set(NODE_LIB node)

add_executable(${PROJECT_NAME}
        main.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${TRI_LIB}
        ${NODE_LIB}
        )

add_library(${TRI_LIB}
        triangle.cpp)

target_include_directories(${TRI_LIB}
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )

add_library(${NODE_LIB}
        node.cpp)

target_include_directories(${NODE_LIB}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

# If unittests are defined then add the unittests
if(UNITTESTS)
    add_subdirectory(test)
endif()

# Custom command to copy the targets to the build directory
#   For easy of running
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}
        )
