cmake_minimum_required(VERSION 3.10)
project(vsys_socket)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-pthread -l sqlite3")
find_package(Threads)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(
        "${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")
enable_testing()


FILE(GLOB_RECURSE SOCKET_LIB_SRC src/shared/socket "*.cpp" "*.h")
FILE(GLOB_RECURSE PROTO_LIB_SRC src/shared/protocol "*.cpp" "*.h")

FILE(GLOB_RECURSE SERVER_SRC src/server "*.cpp" "*.h")
FILE(GLOB_RECURSE CLIENT_SRC src/client "*.cpp" "*.h")


############# Libraries #############

#### Socket - lib ####

add_library(socket-lib STATIC ${SOCKET_LIB_SRC})

add_executable(socket-tests
        test/shared/socket/test_socket.cpp)

target_link_libraries(socket-tests ${GTEST_BOTH_LIBRARIES})


#### Protocol - lib ####

add_library(protocol-lib STATIC ${PROTO_LIB_SRC})

add_executable(protocol-tests
        test/shared/protocol/test_protocol.cpp)

target_link_libraries(protocol-tests ${GTEST_BOTH_LIBRARIES})


############# Executables #############

#### Server ####

add_executable(server ${SERVER_SRC})

target_include_directories(server INTERFACE
        src/shared/protocol)
target_include_directories(server INTERFACE
        src/shared/socket)

target_link_libraries(server socket-lib protocol-lib)

add_executable(server-tests test/server/test_server.cpp)
target_link_libraries(server-tests gtest)

add_executable(database-tests test/server/database/test_database.cpp)
target_link_libraries(database-tests gtest)



#### Client ####

add_executable(client ${CLIENT_SRC})
target_link_libraries(client socket-lib protocol-lib)

add_executable(client-tests test/client/test_client.cpp)
target_link_libraries(client-tests gtest)

target_include_directories(client INTERFACE
        src/shared/protocol)
target_include_directories(client INTERFACE
        src/shared/socket)

