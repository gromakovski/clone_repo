cmake_minimum_required(VERSION 3.5)

project(timus)

add_executable(1820 1820.cpp)
add_executable(2066 2066.cpp)
add_executable(1197 1197.cpp)
add_executable(1880 1880.cpp)
add_executable(1639 1639.cpp)

set_target_properties(1820 2066 1197 1880 1639  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
