cmake_minimum_required(VERSION 3.5)
project(23_Atomic)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

add_executable(atomicity atomicity.cpp)
set_target_properties(atomicity PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_executable(increment increment.cpp)
set_target_properties(increment PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(increment
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(atomic_flag atomic_flag.cpp)
set_target_properties(atomic_flag PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(atomic_flag
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(operations operations.cpp)
set_target_properties(operations PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(operations
        ${CMAKE_THREAD_LIBS_INIT}
)
if (NOT WIN32)
        target_link_libraries(operations
                atomic
        )
else()
        add_definitions(-D_ENABLE_ATOMIC_ALIGNMENT_FIX)
endif()

add_executable(perfomance perfomance.cpp)
set_target_properties(perfomance PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(perfomance
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(memory_order_seq memory_order_seq.cpp)
set_target_properties(memory_order_seq PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(memory_order_seq
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(memory_order_relaxed memory_order_relaxed.cpp)
set_target_properties(memory_order_relaxed PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(memory_order_relaxed
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(memory_order_acq_rel memory_order_acq_rel.cpp)
set_target_properties(memory_order_acq_rel PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(memory_order_acq_rel
        ${CMAKE_THREAD_LIBS_INIT}
)