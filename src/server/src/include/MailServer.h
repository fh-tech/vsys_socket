//
// Created by daniel on 15.10.18.
//



#ifndef VSYS_SOCKET_MAILSERVER_H
#define VSYS_SOCKET_MAILSERVER_H

#include <unordered_map>
#include <Serversocket.h>
#include "Clientsocket.h"
#include "ClientConnection.h"


class MailServer {
private:
    Serversocket serverSocket;
    bool running = true;

    std::unordered_map<size_t , std::unique_ptr<ClientConnection>> active_connections{};

    size_t next_id = 0;

public:
    MailServer(std::string ip, uint16_t port)
        :serverSocket(std::move(ip), port, 10)
    {
    }

    void listen();

};


#endif //VSYS_SOCKET_MAILSERVER_H
