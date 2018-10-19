//
// Created by viktorl on 29.09.18.
//


#ifndef VSYS_SOCKET_SERVER_SOCKET_H
#define VSYS_SOCKET_SERVER_SOCKET_H

#include <arpa/inet.h> // inet_ntoa(), ...
#include "Socket.h"

class Serversocket {
public:
    Serversocket(std::string ip, uint16_t port, int backlog);
    Serversocket(uint16_t port, int backlog);
    ~Serversocket();
    Socket listen_accept() const;

private:
    void bind_sock() const;
    //socket filedescriptor
    int sockfd;
    // amount of clients waiting for accept
    int backlog;
    in_addr addr;
    sockaddr_in sin;
};


#endif //VSYS_SOCKET_SERVER_SOCKET_H
