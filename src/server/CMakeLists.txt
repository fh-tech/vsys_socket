add_executable(server
        src/main.cpp
        src/ClientConnection.h
        src/ClientConnection.cpp
        src/MailServer.cpp
        src/MailServer.h
        src/database/Database.cpp
        src/database/Database.h
        src/database/Message.h
        src/ServerResponseGenerator.h
        src/ServerResponseGenerator.cpp test/test_serverResponseGenerator.cpp)

target_link_libraries(server socket-lib protocol-lib)

### TESTS
add_executable(test_server
        test/test_server.cpp)

add_executable(test_database
        test/database/test_database.cpp
        src/database/Database.cpp)

target_link_libraries(test_server gtest_main)
target_link_libraries(test_server protocol-lib)
target_link_libraries(test_database gtest_main)
