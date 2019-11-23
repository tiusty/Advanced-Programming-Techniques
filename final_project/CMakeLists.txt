cmake_minimum_required(VERSION 2.8)
project(FinalProject)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package( Threads )

# CMake 3.1 or older needs this method of setting compiler standards
add_compile_options(-std=c++11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(${PROJECT_NAME}
        mainNotMpi.cpp
        uav.cpp
        footballField.cpp)

target_link_libraries (${PROJECT_NAME}
        PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        )


target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
