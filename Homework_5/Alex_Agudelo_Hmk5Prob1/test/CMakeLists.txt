cmake_minimum_required(VERSION 2.8)
project(Hmk5_Problem1_Tests)

add_executable(${PROJECT_NAME}
        test_main.cpp
        )

target_link_libraries(${PROJECT_NAME}
        gtest_main
        ship
        )
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})
