//
// Created by daniel on 15.10.18.
//

#ifndef VSYS_SOCKET_CLIENTCONNECTION_H
#define VSYS_SOCKET_CLIENTCONNECTION_H

#include <sstream>
#include <atomic>
#include <array>
#include <variant>
#include <thread>
#include <ClientRequest.h>
#include <ClientRequestParser.h>
#include <ClientRequestPrinter.h>
#include "../../../socket/include/Socket.h"
#include "../database/include/Database.h"
#include "ServerResponseGenerator.h"


class ClientConnection {
public:
    explicit ClientConnection(const Socket &socket);
    void run();
    void handle_connection();
    std::variant<ClientRequest, const char*> get_msg();
    bool operator==(const ClientConnection& other) const;
    void handle_message(const std::variant<ClientRequest, const char*>& request);
    const Socket& getSocket() const;

    Database db;
    std::string username = "";
    std::atomic<bool> keep_running = true;

private:
    Socket client;
    ServerResponseGenerator sg;

//    enum Status: char {
//        waiting,
//        parsing,
//        processing,
//        closed,
//    } status = waiting;
//    std::array<char, 100> buf;
//    std::thread thread;
};




#endif //VSYS_SOCKET_CLIENTCONNECTION_H