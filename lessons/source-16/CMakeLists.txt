cmake_minimum_required(VERSION 3.5)

project(16.STL_1)

add_executable(vector vector.cpp)
set_target_properties(vector PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(array array.cpp)
set_target_properties(array PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(deque deque.cpp)
set_target_properties(deque PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(stack stack.cpp)
set_target_properties(stack PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(queue queue.cpp)
set_target_properties(queue PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(forward_list forward_list.cpp)
set_target_properties(forward_list PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(list list.cpp)
set_target_properties(list PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(set set.cpp)
set_target_properties(set PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(map map.cpp)
set_target_properties(map PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(multiset multiset.cpp)
set_target_properties(multiset PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(unordered_set unordered_set.cpp)
set_target_properties(unordered_set PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )