cmake_minimum_required(VERSION 3.5)
project(20_thread)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)
find_package(Threads)

add_executable(motivation motivation.cpp)
target_link_libraries(motivation
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(thread thread.cpp)
target_link_libraries(thread
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(promise promise.cpp)
target_link_libraries(promise
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(async async.cpp)
target_link_libraries(async
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(condition condition.cpp)
target_link_libraries(condition
  ${CMAKE_THREAD_LIBS_INIT}
  )


add_executable(interprocess2 interprocess2.cpp)
target_include_directories(interprocess2 PUBLIC "${Boost_INCLUDE_DIRS}")

target_link_libraries(interprocess2 ${Boost_LIBRARIES})
target_link_libraries(interprocess2 ${CMAKE_THREAD_LIBS_INIT})

if(UNIX)
    target_link_libraries(interprocess2 rt)
endif()