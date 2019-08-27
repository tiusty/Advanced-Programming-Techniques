cmake_minimum_required(VERSION 2.8)
project(Hmk1_Problem1)

add_executable(${PROJECT_NAME} Hmk1_Problem1.cpp)

install(CODE "
    EXECUTE_PROCESS(COMMAND ln -s ${PROJECT_NAME}
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
       )
    ")
