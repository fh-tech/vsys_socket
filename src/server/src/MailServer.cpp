//
// Created by daniel on 15.10.18.
//

#include <memory>
#include "include/MailServer.h"
#include "include/ClientConnection.h"

void MailServer::listen() {
    std::cout << "Waiting for connections..." << std::endl;
    serverSocket.listen_socket();
    while(running){
        auto socket = serverSocket.accept_socket();
        next_id++;
        std::cout << "Client assigned id: " << next_id << std::endl;

        {
            std::unique_lock<std::mutex> l(active_conns_lock);
            auto[it, exists] = active_connections.emplace(next_id,
                                                          std::make_unique<ClientConnection>(next_id,
                                                                                             std::move(socket),
                                                                                             connectionDeleter(next_id)));
            if (it != active_connections.end()) {
                std::get<1>(*it)->run();
            }
        }
    }
}