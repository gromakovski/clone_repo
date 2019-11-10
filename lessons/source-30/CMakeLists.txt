cmake_minimum_required(VERSION 3.5)

project(30.ORM)

add_subdirectory("${CMAKE_SOURCE_DIR}/sqlite" "${CMAKE_BINARY_DIR}/sqlite")


find_package(Threads)
add_executable(motivation1 motivation1.cpp utils.cpp)
set_target_properties(motivation1 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
if (MSVC)
    target_link_libraries(motivation1
            ${CMAKE_THREAD_LIBS_INIT}
            sqlite3
    )
else (MSVC)
    target_link_libraries(motivation1
            ${CMAKE_THREAD_LIBS_INIT}
            sqlite3
            dl
    )
endif (MSVC)


add_executable(motivation2 motivation2.cpp utils.cpp)
set_target_properties(motivation2 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
if (MSVC)
    target_link_libraries(motivation2
            ${CMAKE_THREAD_LIBS_INIT}
            sqlite3
    )
else (MSVC)
    target_link_libraries(motivation2
            ${CMAKE_THREAD_LIBS_INIT}
            sqlite3
            dl
    )
endif (MSVC)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_subdirectory(odb_example)