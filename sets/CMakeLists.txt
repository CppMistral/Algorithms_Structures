cmake_minimum_required(VERSION 3.16)

project(sets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WITH_STRUCTURES ON)
option(ENABLE_CLANG_TIDY OFF)


if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    
        set(CMAKE_CXX_CLANG_TIDY 
            ${CLANG_TIDY_EXE} 
            -header-filter=.* 
        )
    else()
        message(WARNING "clang-tidy was requested but not found")
    endif()
endif()

if(WITH_STRUCTURES)
set(SETS_IMPLEMENTATION_SOURCES
    src/structures/array_set.cpp
    src/structures/list_set.cpp
    src/structures/bit_array_set.cpp
    src/structures/machine_word_set.cpp
)
else()
set(SETS_IMPLEMENTATION_SOURCES
    src/classes/array_set.cpp
    src/classes/list_set.cpp
    src/classes/bit_array_set.cpp
    src/classes/machine_word_set.cpp
)
endif()

set(SETS_SOURCES
    ${SETS_IMPLEMENTATION_SOURCES}
    tests/generator.cpp
)

add_executable(sets
    src/main.cpp
    ${SETS_SOURCES}
)

target_include_directories(sets PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks
)

if(WITH_STRUCTURES)
    target_compile_definitions(sets PRIVATE WITH_STRUCTURES)
endif()

target_compile_options(sets PRIVATE
    -Wall
    -Wextra
    -pedantic
)