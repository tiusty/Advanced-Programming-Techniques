cmake_minimum_required(VERSION 2.8)
project(Hmk2_Problem2_Tests)

add_executable(${PROJECT_NAME}
        test_main.cpp
        test_grid_class.cpp
        )

target_link_libraries(${PROJECT_NAME}
        gtest_main
        grid
        )
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})
