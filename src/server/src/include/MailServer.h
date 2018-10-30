//
// Created by daniel on 15.10.18.
//



#ifndef VSYS_SOCKET_MAILSERVER_H
#define VSYS_SOCKET_MAILSERVER_H

#include <unordered_map>
#include <Serversocket.h>
#include <mutex>
#include "Clientsocket.h"
#include "ClientConnection.h"


class MailServer {
private:
    Serversocket serverSocket;
    bool running = true;
    std::mutex active_conns_lock;
    std::unordered_map<size_t , std::unique_ptr<ClientConnection>> active_connections{};

    size_t next_id = 0;

public:
    MailServer(std::string ip, uint16_t port)
        :serverSocket(std::move(ip), port, 10)
    {
    }

    void listen();

    std::function<void()> connectionDeleter(size_t con_id){
        return [con_id, this](){
            {
                std::unique_lock<std::mutex> l(active_conns_lock);
                (*this->active_connections[con_id]).thread->detach();
                this->active_connections.erase(con_id);
            }
            std::cout << "Client removed with id" << con_id << std::endl;
        };
    }

};


#endif //VSYS_SOCKET_MAILSERVER_H
