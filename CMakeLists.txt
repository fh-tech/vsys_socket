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
add_subdirectory(
        "${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")
enable_testing()

############# Libraries #############

#### Socket-Lib ####
add_library(socket-lib
        src/shared/socket/socket.cpp)

add_executable(socket-tests
        test/shared/socket/test_socket.cpp)

target_link_libraries(socket-tests gtest)
####

#### Database ####
add_library(database
        src/shared/database/Database.cpp)

add_executable(database-tests
        test/shared/database/test_database.cpp)

target_link_libraries(database-tests gtest)

####

##############

############# Server #############
add_executable(server
        src/server/main.cpp)
target_link_libraries(server socket-lib)

add_executable(server-tests
        test/server/test_server.cpp)

target_link_libraries(server-tests gtest)
#############

############# Client #############
add_executable(client
        src/client/main.cpp)
target_link_libraries(client socket-lib)

add_executable(client-tests
        test/client/test_client.cpp)

target_link_libraries(client-tests gtest)
#############

