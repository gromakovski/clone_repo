cmake_minimum_required(VERSION 3.5)

project(08.allocator)

add_executable(allocator allocator.cpp)
set_target_properties(allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(polymorphism polymorphism.cpp)
set_target_properties(polymorphism PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(byte byte.cpp)
set_target_properties(byte PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(string_view string_view.cpp)
set_target_properties(string_view PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(emplace_back emplace_back.cpp)
set_target_properties(emplace_back PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
