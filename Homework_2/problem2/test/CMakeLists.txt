cmake_minimum_required(VERSION 2.8)
project(Hmk2_Problem2_Tests)

add_executable(${PROJECT_NAME}
        test_main.cpp
        test_grid_product_between_indices.cpp
        test_grid_largest_product_along_line.cpp)

target_link_libraries(${PROJECT_NAME}
        gtest_main
        grid
        )
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})

# Custom command to copy the targets to the build directory
#   For easy of running
configure_file(
        data_Problem2.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data_Problem2.txt
        COPYONLY)

