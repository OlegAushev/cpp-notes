cmake_minimum_required(VERSION 3.5)
project(cpp-notes VERSION 0.1.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) 
set(executable ${CMAKE_PROJECT_NAME})

add_executable(${executable}
    ${PROJECT_SOURCE_DIR}/src/algorithms/sorting.cpp
)

target_compile_definitions(${executable} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_compile_options(${executable} PRIVATE
    #$<$<CONFIG:Debug>:-Og -g3 -ggdb>
    #$<$<CONFIG:Release>:-Og -g0>
    -Wall
    -Wextra
    -Wpedantic
    -fdiagnostics-color=always
)

target_compile_features(${executable} PRIVATE
    c_std_11
    cxx_std_23
)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
