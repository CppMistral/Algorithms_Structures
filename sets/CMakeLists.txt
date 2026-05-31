cmake_minimum_required(VERSION 3.16)

project(sets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SETS_STRUCTURES_SOURCES
    src/structures/array_set.cpp
    src/structures/list_set.cpp
    src/structures/bit_array_set.cpp
    src/structures/machine_word_set.cpp
)

set(SETS_CLASSES_SOURCES
    src/classes/array_set.cpp
    src/classes/list_set.cpp
    src/classes/bit_array_set.cpp
    src/classes/machine_word_set.cpp
)

set(SETS_COMMON_SOURCES
    tests/generator.cpp
)

add_executable(sets_structs
    src/main.cpp
    ${SETS_STRUCTURES_SOURCES}
    ${SETS_COMMON_SOURCES}
)

add_executable(sets_classes
    src/main.cpp
    ${SETS_CLASSES_SOURCES}
    ${SETS_COMMON_SOURCES}
)

foreach(target sets_structs sets_classes)
target_include_directories(${target} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks
)
endforeach()

target_compile_definitions(sets_structs PRIVATE
    WITH_STRUCTURES
)
