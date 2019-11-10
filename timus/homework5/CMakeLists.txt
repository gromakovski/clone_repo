cmake_minimum_required(VERSION 3.5)

project(timus)

add_executable(1086 1086.cpp)
add_executable(1582 1582.cpp)

set_target_properties(1086 1582   PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
