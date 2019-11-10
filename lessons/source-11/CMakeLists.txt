cmake_minimum_required(VERSION 3.5)

project(11.grasp)

add_executable(map map.cpp)
set_target_properties(map PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(indirection indirection.cpp)
set_target_properties(indirection PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(relations relations.cpp)
set_target_properties(relations PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(low_coupling low_coupling.cpp)
set_target_properties(low_coupling PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(high_cohesion high_cohesion.cpp)
set_target_properties(high_cohesion PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)