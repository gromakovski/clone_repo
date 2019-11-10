cmake_minimum_required(VERSION 3.5)

project(timus)

add_executable(1001 1001.cpp)
add_executable(1000 1000.cpp)
add_executable(1785 1785.cpp)
add_executable(1293 1293.cpp)
add_executable(2012 2012.cpp)

set_target_properties(1001 1000 1785 1293 2012 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
