cmake_minimum_required(VERSION 3.12)
project(vsys_socket)

set(CMAKE_CXX_STANDARD 14)

add_executable(server src/server/main.cpp)

add_executable(client src/client/main.cpp)

add_library(socket-lib src/shared/socket.cpp)

target_link_libraries(server socket-lib)

target_link_libraries(client socket-lib)

set_target_properties(socket-lib PROPERTIES LINKER_LANGUAGE CXX)
