
add_library(socket-lib
        src/Clientsocket.cpp
        src/Socket.cpp
        src/Serversocket.cpp)

target_include_directories(socket-lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

### TESTS
add_executable(test_socket-lib
        test/test_socket.cpp)
target_link_libraries(test_socket-lib socket-lib gtest_main)
add_test(test_socket-lib test_socket-lib)