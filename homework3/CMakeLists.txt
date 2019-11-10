cmake_minimum_required(VERSION 3.5)

set(ENV{GTEST_COLOR} 1)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message(STATUS "TRAVIS_BUILD_NUMBER environment variable defined")
    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(allocator VERSION 0.0.1)
endif()


set(SOURCES main.cpp map_allocator.h simple_list.h)

add_executable(${PROJECT_NAME} ${SOURCES})



set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)        
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT explorer.85@mail.ru)

include (CPack)

#############################################
if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
else()
# Unit tests
find_package(GTest)

# enable CTest testing
enable_testing()

# Add a testing executable
add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests gtest gtest_main pthread)
gtest_add_tests(TARGET unit_tests)


endif()



