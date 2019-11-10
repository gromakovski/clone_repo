cmake_minimum_required(VERSION 3.5)

project(30.ORM)

find_package(odb REQUIRED)

add_executable(odb_example main.cpp person.cpp other_person.cpp person-odb.cxx other_person-odb.cxx)

set_target_properties(odb_example PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

if (MSVC)
        target_link_libraries(odb_example
                ${CMAKE_THREAD_LIBS_INIT}
                sqlite3
                "C:/my/vcpkg/vcpkg/installed/x64-windows/lib/libodb.lib"
                "C:/my/vcpkg/vcpkg/installed/x64-windows/lib/libodb-sqlite.lib"
        )
else (MSVC)
        target_link_libraries(odb_example
                ${CMAKE_THREAD_LIBS_INIT}
                sqlite3
                ${ODB_LIBRARY}
                odb-sqlite
                dl
        )
endif (MSVC)

