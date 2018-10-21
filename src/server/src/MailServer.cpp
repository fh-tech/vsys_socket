//
// Created by daniel on 15.10.18.
//

#include <memory>
#include "include/MailServer.h"
#include "include/ClientConnection.h"

void MailServer::listen() {
    while(running){
        auto socket = serverSocket.listen_accept();
        auto [it, exists] = active_connections.emplace(std::make_unique<ClientConnection>(socket));
        if(it != active_connections.end()){
            (*it)->run();
        }
    }
}