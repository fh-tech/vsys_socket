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
#include <functional>
#include "../../../socket/include/Socket.h"
#include "../database/include/Database.h"
#include "ServerResponseGenerator.h"


class ClientConnection {
public:

    ClientConnection(size_t id, Socket &&socket, std::function<void()> deleter)
            : id(id)
            , client(std::move(socket))
            , deleter(std::move(deleter))
            , sg(this)
    {}

    void run();
    void handle_connection();
    std::variant<ClientRequest, const char*> get_msg();
    bool operator==(const ClientConnection& other) const;
    void handle_message(const std::variant<ClientRequest, const char*>& request);
    const Socket& getSocket() const;

    ~ClientConnection();

    Database db;
    std::string username = "";
    std::atomic<bool> keep_running = true;
    std::unique_ptr<std::thread> thread;
private:
    Socket client;
    ServerResponseGenerator sg;

    size_t id;
    std::function<void()> deleter;

//    enum Status: char {
//        waiting,
//        parsing,
//        processing,
//        closed,
//    } status = waiting;
//    std::array<char, 100> buf;
};




#endif //VSYS_SOCKET_CLIENTCONNECTION_H
