cmake_minimum_required(VERSION 3.12)

project(cpp-notes VERSION 0.1)

################################################################################
# Threads
# set(CMAKE_THREAD_PREFER_PTHREAD ON)
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)

################################################################################
file(GLOB_RECURSE app_sources CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

################################################################################
# Executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(executable ${CMAKE_PROJECT_NAME})

add_executable(${executable} ${app_sources})

# target_link_libraries(${executable} PRIVATE
#     atomic
#     # Threads::Threads
# )

################################################################################
# Compiler Options and Features
target_compile_options(${executable} PRIVATE
    $<$<CONFIG:Debug>:-Og -g3>
    $<$<CONFIG:Release>:-O3 -g0>
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wsuggest-override
    -Werror
    -fdiagnostics-color=always
)

target_compile_features(${executable} PRIVATE
    c_std_11
    cxx_std_23
)

################################################################################
# Misc Options
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
