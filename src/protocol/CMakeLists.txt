add_library(protocol-lib
        src/ClientRequestPrinter.cpp
        src/ClientRequestParser.cpp include/ServerResponse.h include/ServerResponsePrinter.h src/ServerResponsePrinter.cpp ../server/src/ServerResponseGenerator.h ../server/src/ServerResponseGenerator.cpp)

target_include_directories(protocol-lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)

### TESTS
add_executable(test_protocol-lib
        test/test_protocol.cpp test/testServerResponse.cpp)
target_link_libraries(test_protocol-lib protocol-lib gtest_main)
add_test(test_protocol-lib test_protocol-lib)