add_executable(client
        src/main.cpp
        src/include/Client.h src/Client.cpp)

target_link_libraries(client socket-lib protocol-lib)

