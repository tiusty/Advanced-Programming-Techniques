cmake_minimum_required(VERSION 2.8)
project(Hmk2_Problem3_Tests)

add_compile_options(-std=c++14)

add_executable(${PROJECT_NAME}
        test_main.cpp
        test_triangle_get_node.cpp
        test_triangle_determine_valid_index.cpp
        test_triangle_determine_largest_parent.cpp
        )

target_link_libraries(${PROJECT_NAME}
        gtest_main
        tri
        node
        )
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME})

# Custom command to copy the targets to the build directory
#   For easy of running
configure_file(
        data_triangle.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data_triangle.txt
        COPYONLY)

