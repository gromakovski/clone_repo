cmake_minimum_required(VERSION 3.9)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    message(STATUS "TRAVIS_BUILD_NUMBER environment variable defined")
    project(bulk_server VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(bulk_server VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 14)

add_library(async SHARED async.cpp async.h command_queue.h
    bulk_builder/bulk_builder.h
    bulk_builder/bulk_builder.cpp
    bulk_builder/observer.h
    bulk_builder/observable.h
    bulk_builder/console_log_writer.h
    bulk_builder/file_writer.h
    bulk_builder/thread_object.h
    bulk_builder/ThreadPool.h)


find_package(Threads REQUIRED)


target_link_libraries (async ${CMAKE_THREAD_LIBS_INIT})



find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(bulk_server main.cpp server.h server.cpp  session.h session.cpp
    builder_selector.h builder_selector.cpp)


target_link_libraries(bulk_server
        async
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})



install(TARGETS async LIBRARY DESTINATION lib)
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT explorer.85@mail.ru)

include (CPack)

#############################################
#if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
#else()
## Unit tests
#find_package(GTest)

## enable CTest testing
#enable_testing()

## Add a testing executable
#add_executable(unit_tests unit_tests.cpp async.h)
#target_link_libraries(unit_tests gtest gtest_main pthread async)
#gtest_add_tests(TARGET unit_tests)


#endif()
