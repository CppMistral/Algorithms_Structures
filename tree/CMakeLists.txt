cmake_minimum_required(VERSION 3.16)

project(tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tree
    src/main.cpp
    src/binary_tree.cpp
)

target_compile_options(tree PRIVATE
    -Wall
    -Wextra
    -pedantic
)
