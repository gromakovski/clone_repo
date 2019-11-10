cmake_minimum_required(VERSION 3.5)

project(timus)

add_executable(1496 1496.cpp)
add_executable(1545 1545.cpp)
add_executable(1196 1196.cpp)
add_executable(1837 1837.cpp)

set_target_properties(1496 1545 1196 1837 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
