cmake_minimum_required(VERSION 2.8)
project(Hmk1_Problem3)

set(FIB_HELPER fib_helper)
set(KNIGHTS knights)

add_executable(${PROJECT_NAME}
        Hmk1_Problem3.cpp
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        ${FIB_HELPER}
        ${KNIGHTS}
        )

add_library(${KNIGHTS}
        table.cpp
        knight.cpp
        )

target_include_directories(${KNIGHTS}
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )

add_library(${FIB_HELPER}
        fib_helper.cpp
        )
target_include_directories(${FIB_HELPER}
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
