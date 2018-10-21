add_executable(server
        src/main.cpp
        src/include/ClientConnection.h
        src/ClientConnection.cpp
        src/MailServer.cpp
        src/include/MailServer.h
        src/database/Database.cpp
        src/database/include/Database.h
        src/database/include/Message.h
        src/include/ServerResponseGenerator.h
        src/ServerResponseGenerator.cpp)

target_link_libraries(server socket-lib protocol-lib)

### TESTS
add_executable(test_server
        test/test_server.cpp
        test/test_serverResponseGenerator.cpp
        src/ServerResponseGenerator.cpp
        src/database/Database.cpp)

add_executable(test_database
        test/database/test_database.cpp
        src/database/Database.cpp)

target_link_libraries(test_server gtest_main)
target_link_libraries(test_server protocol-lib)
target_link_libraries(test_database gtest_main)
