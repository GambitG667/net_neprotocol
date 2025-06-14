cmake_minimum_required(VERSION 3.10)

project(net_protocol)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
