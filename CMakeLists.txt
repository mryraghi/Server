cmake_minimum_required(VERSION 3.3)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(Boost 1.5 COMPONENTS system REQUIRED)

set(SOURCE_FILES
    client/client.cpp
    server/server.cpp
    server/server.h
    server/session.cpp
    server/session.h
    server/tcp_echo.cpp)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(client client/client.cpp)
add_executable(tcp_echo server/tcp_echo.cpp server/server.cpp server/session.cpp )
target_link_libraries( tcp_echo ${Boost_SYSTEM_LIBRARY} pthread )
target_link_libraries( client ${Boost_SYSTEM_LIBRARY} pthread )