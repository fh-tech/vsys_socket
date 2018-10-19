cmake_minimum_required(VERSION 3.10)
project(vsys_socket)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-pthread -l sqlite3")
find_package(Threads)

## gtest-magic from their github ##
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()
############

FILE(GLOB_RECURSE SOCKET_LIB_SRC src/shared/socket "*.cpp")
FILE(GLOB_RECURSE PROTO_LIB_SRC src/shared/protocol "*.cpp")

FILE(GLOB_RECURSE SERVER_SRC src/server "*.cpp")
FILE(GLOB_RECURSE CLIENT_SRC src/client "*.cpp")


############# Libraries #############

#### Socket - lib ####

add_library(socket-lib STATIC
        ${SOCKET_LIB_SRC})

add_executable(socket-tests
        test/shared/socket/test_socket.cpp)

target_link_libraries(socket-tests gtest_main)


#### Protocol - lib ####

add_library(protocol-lib STATIC
        ${PROTO_LIB_SRC})

add_executable(protocol-tests
        test/shared/protocol/test_protocol.cpp)

target_link_libraries(protocol-tests gtest_main)


############# Executables #############

#### Server ####

add_executable(server
        ${SERVER_SRC})

target_link_libraries(server socket-lib protocol-lib)

add_executable(server-tests test/server/test_server.cpp)
target_link_libraries(server-tests gtest_main)

add_executable(database-tests test/server/database/test_database.cpp)
target_link_libraries(database-tests gtest_main)


#### Client ####
add_executable(client ${CLIENT_SRC})
target_link_libraries(client socket-lib protocol-lib)

add_executable(client-tests test/client/test_client.cpp)
target_link_libraries(client-tests gtest_main)

