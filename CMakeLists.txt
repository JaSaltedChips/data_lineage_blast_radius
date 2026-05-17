cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME BLAST_RADIUS)
project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lineage)
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(test)
endif()
add_subdirectory(src)