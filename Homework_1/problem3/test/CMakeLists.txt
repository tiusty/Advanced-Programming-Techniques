cmake_minimum_required(VERSION 2.8)
project(Hmk1_Problem3_Tests)

add_executable(${PROJECT_NAME}
        test_main.cpp
        test_fib_helper.cpp
        test_integration.cpp)

target_link_libraries(${PROJECT_NAME}
        gtest_main
        fib_helper
        knights
        )
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})
