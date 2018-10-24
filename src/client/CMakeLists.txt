add_executable(client
        src/main.cpp
        src/include/Client.h src/Client.cpp src/include/UserServerResponsePrinter.h src/UserServerResponsePrinter.cpp src/include/ServerResponseHandler.h src/ServerResponseHandler.cpp)

target_link_libraries(client socket-lib protocol-lib)

