//
// Created by daniel on 15.10.18.
//

#include <memory>
#include "include/MailServer.h"
#include "include/ClientConnection.h"

void MailServer::listen() {
    while(running){
        auto socket = serverSocket.listen_accept();
        next_id++;
        std::cout << "Client assigned id: " << next_id << std::endl;
        auto [it, exists] = active_connections.emplace(next_id, std::make_unique<ClientConnection>(next_id, socket,
                [this](){
                    this->active_connections.erase(next_id);
                    std::cout << "Client removed with id" << next_id << std::endl;
                }));

        if(it != active_connections.end()){
            std::get<1>(*it)->run();
        }
    }
}