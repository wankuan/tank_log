cmake_minimum_required(VERSION 3.10)
project(demo_log)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-Wall -fdata-sections -ffunction-sections -g")
include_directories(
    ${PROJECT_SOURCE_DIR}
)
SET(SRCS
    test_log.c
    tank_log.c
    tank_log_api.c
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/target)

add_executable(${PROJECT_NAME}.out ${SRCS})