cmake_minimum_required(VERSION 3.10)
project(problem3)

set(FIB_HELPER fib_helper)
set(KNIGHTS knights)
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        main.cpp
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
        knights.cpp
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
