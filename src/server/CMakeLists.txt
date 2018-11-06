find_package(Ldap)
if (LDAP_INCLUDE_DIR)
    include_directories(${LDAP_INCLUDE_DIR})
endif()

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
        src/ServerResponseGenerator.cpp
        src/ldap/LDAPAuthenticator.h)

target_link_libraries(server socket-lib protocol-lib)
target_link_libraries(server -lldap -llber)

### TESTS
add_executable(test_server
        test/test_server.cpp
        test/test_serverResponseGenerator.cpp
        src/ServerResponseGenerator.cpp
        src/include/ServerResponseGenerator.h
        src/database/Database.cpp)

add_executable(test_database
        test/database/test_database.cpp
        src/database/Database.cpp)

target_link_libraries(test_server gtest_main -lldap -llber)
target_link_libraries(test_server protocol-lib -lldap -llber)
target_link_libraries(test_database gtest_main)
target_link_libraries(test_database protocol-lib)
