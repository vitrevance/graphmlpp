cmake_minimum_required(VERSION 3.27)

project(
    graphmlpp
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

add_subdirectory(${PROJECT_NAME})

set(TESTS_OPTION "${PROJECT_NAME}_BUILD_TESTS")
option(${TESTS_OPTION} "build tests" OFF)

if (${TESTS_OPTION})
    add_subdirectory(test)
endif()
