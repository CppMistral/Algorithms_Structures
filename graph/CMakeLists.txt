cmake_minimum_required(VERSION 3.16)

project(graph LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(graph
    src/main.cpp
    src/graph.cpp
    tests/graph_generator.cpp
)

target_include_directories(graph PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

target_compile_options(graph PRIVATE
    -Wall
    -Wextra
    -pedantic
)
