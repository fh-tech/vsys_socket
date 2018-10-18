//
// Created by daniel on 15.10.18.
//

#ifndef VSYS_SOCKET_MAILSERVER_H
#define VSYS_SOCKET_MAILSERVER_H

#include <unordered_set>
#include "socket-lib/include/include.h"
#include "ClientConnection.h"

class MailServer {
private:
    Serversocket serverSocket;
    std::unordered_set<std::unique_ptr<ClientConnection>> active_connections{};
    bool running = true;

public:
    MailServer(std::string ip, uint16_t port)
        :serverSocket(std::move(ip), port, 10)
    {
    }

    void listen();

};


#endif //VSYS_SOCKET_MAILSERVER_H
