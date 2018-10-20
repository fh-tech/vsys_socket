add_executable(server
        src/main.cpp
        src/ClientConnection.cpp
        src/MailServer.cpp
        src/database/Database.cpp
        src/ClientConnection.h
        src/MailServer.h
        src/database/Database.h
        src/database/Message.h)

target_link_libraries(server socket-lib protocol-lib)

#[[
add_executable(test_server
        test/test_server.cpp
        src/MailServer.cpp
        src/ClientConnection.cpp)

add_executable(test_database
        test/database/test_database.cpp
        src/database/Database.cpp)


target_link_libraries(test_server gtest_main)
target_link_libraries(test_database gtest_main)
#]]