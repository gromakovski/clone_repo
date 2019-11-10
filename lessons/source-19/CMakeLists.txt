cmake_minimum_required(VERSION 3.5)
project(19_boost_2)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(fusion fusion.cpp)
add_executable(factory factory.cpp)
add_executable(signals2 signals2.cpp)
add_executable(lightweight lightweight.cpp)
add_executable(interprocess interprocess.cpp)
add_executable(serialization serialization.cpp)

target_link_libraries(lightweight ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(interprocess ${CMAKE_THREAD_LIBS_INIT})

if(UNIX)
    target_link_libraries(interprocess rt)
endif()

if(MSVC)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()