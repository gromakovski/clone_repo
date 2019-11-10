cmake_minimum_required(VERSION 3.5)
project(18_boost_1)

find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(bimap bimap.cpp)
add_executable(circular_buffer circular_buffer.cpp)
add_executable(format format.cpp)
add_executable(fusion fusion.cpp)
add_executable(multi_index multi_index.cpp)
add_executable(program_options program_options.cpp)
add_executable(test test.cpp)
add_executable(tokenizer tokenizer.cpp)

target_link_libraries(program_options
        ${Boost_LIBRARIES}
        )

target_link_libraries(test
        ${Boost_LIBRARIES}
        )

set_target_properties(test PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        )

add_executable(iterators iterators.cpp)
set_target_properties(iterators PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)