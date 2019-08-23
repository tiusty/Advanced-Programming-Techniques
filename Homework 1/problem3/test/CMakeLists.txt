cmake_minimum_required(VERSION 3.10)
project(Homework_1_Tests)

add_executable(${PROJECT_NAME}
        test_main.cpp
        )
target_link_libraries(${PROJECT_NAME} gtest_main)
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})
