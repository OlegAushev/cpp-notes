cmake_minimum_required(VERSION 3.0.0)
project(patterns VERSION 0.1.0)


### -- Misc options
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -DDEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) 

add_subdirectory(patterns)
add_subdirectory(basics)

### -- Compile options and features
#target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
#target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
