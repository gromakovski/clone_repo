cmake_minimum_required(VERSION 3.5)

project(13.gof_2)

add_executable(adapter adapter.cpp)
add_executable(bridge bridge.cpp)
add_executable(composite composite.cpp)
add_executable(decorator decorator.cpp)
add_executable(facade facade.cpp)
add_executable(flyweight flyweight.cpp)
add_executable(proxy proxy.cpp)
add_executable(chars chars.cpp)

set_target_properties(adapter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(bridge PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(composite PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(decorator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(facade PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(flyweight proxy PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(proxy PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(chars PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )