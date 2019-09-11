cmake_minimum_required(VERSION 2.8)
project(Hmk2_Problem3)

set(TRI_LIB tri)

add_executable(${PROJECT_NAME}
        main.cpp
        )

target_link_libraries(${PROJECT_NAME}
        ${TRI_LIB}
        )

add_library(${TRI_LIB}
        triangle.cpp)

target_include_directories(${TRI_LIB}
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )

# If unittests are defined then add the unittests
if(UNITTESTS)
#    add_subdirectory(test)
endif()

# Custom command to copy the targets to the build directory
#   For easy of running
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}
        )
