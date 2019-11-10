cmake_minimum_required(VERSION 3.5)

project(timus)

add_executable(1409 1409.cpp)
add_executable(1877 1877.cpp)
add_executable(2001 2001.cpp)
add_executable(1264 1264.cpp)
add_executable(1787 1787.cpp)

set_target_properties(1409 1877 2001 1264 1787  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
