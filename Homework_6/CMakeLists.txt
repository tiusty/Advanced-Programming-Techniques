cmake_minimum_required(VERSION 2.8)
project(Homework_6)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# CMake 3.1 or older needs this method of setting compiler standards
add_compile_options(-std=c++11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(${PROJECT_NAME}
        main.cpp)

target_link_libraries (${PROJECT_NAME}
        PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES})

add_executable(helloWorld
        exampleCode/mainHelloWorld.cpp)

target_link_libraries (helloWorld
        PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES})

add_executable(snowMen
        exampleCode/mainSnowMen.cpp)

target_link_libraries (snowMen
        PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES})

add_executable(solarSystem
        exampleCode/mainSolarSystem.cpp)

target_link_libraries (solarSystem
        PUBLIC
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES})
