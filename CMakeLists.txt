cmake_minimum_required(VERSION 3.10)
project(vsys_socket)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

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

############# Library #############
add_library(socket-lib
        src/socket-lib/Socket.cpp
        src/socket-lib/Clientsocket.cpp
        src/socket-lib/Serversocket.cpp
        src/socket-lib/protocol/ClientRequest.h
        src/socket-lib/protocol/ClientRequestVisitor.h
        src/socket-lib/protocol/ClientRequestPrinter.h
        src/socket-lib/protocol/ClientRequestPrinter.cpp
        src/socket-lib/protocol/ClientRequestParser.cpp
        src/socket-lib/protocol/ClientRequestParser.h)

include_directories(src)

add_executable(library-tests
        test/socket-lib/test_library.cpp)

target_link_libraries(library-tests gtest socket-lib)
##############

############# Server #############
add_executable(server
        src/server/main.cpp src/server/MailServer.cpp src/server/MailServer.h src/server/ClientConnection.cpp src/server/ClientConnection.h)
target_link_libraries(server socket-lib)

add_executable(server-tests
        test/server/test_server.cpp)

target_link_libraries(server-tests gtest)
#############

############# Client #############
add_executable(client src/client/main.cpp)

target_link_libraries(client socket-lib)

add_executable(client-tests
        test/client/test_client.cpp)

target_link_libraries(client-tests gtest)
#############

