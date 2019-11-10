cmake_minimum_required(VERSION 3.5)

project(10.design)

add_executable(variant variant.cpp)
set_target_properties(variant PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(dry dry.cpp)
set_target_properties(dry PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(tda tda.cpp)
set_target_properties(tda PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(union union.cpp)
set_target_properties(union PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)