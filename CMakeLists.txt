cmake_minimum_required(VERSION 3.12)
project(vsys_socket)
set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")
enable_testing()

############# Library #############
add_library(socket-lib
        src/shared/socket.cpp)

add_executable(library-tests
        src/shared/include/include.h
        test/shared/test_library.cpp)

target_link_libraries(library-tests gtest)
##############

############# Server #############
add_executable(server
        src/server/main.cpp)
target_link_libraries(server socket-lib)

add_executable(server-tests
        src/server/include/include.h
        test/server/test_server.cpp)

target_link_libraries(server-tests gtest)
#############

############# Client #############
add_executable(client
        src/client/main.cpp test/shared/test_library.cpp src/shared/socket.cpp src/shared/socket.h)
target_link_libraries(client socket-lib)

add_executable(client-tests
        src/client/include/include.h
        test/client/test_client.cpp)

target_link_libraries(client-tests gtest)
#############

