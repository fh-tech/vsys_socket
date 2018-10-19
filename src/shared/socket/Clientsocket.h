//
// Created by viktorl on 30.09.18.
//

#ifndef VSYS_SOCKET_CLIENTSOCKET_H
#define VSYS_SOCKET_CLIENTSOCKET_H

#include <arpa/inet.h> // inet_ntoa(), ...
#include "Socket.h"

class ClientSocket {
public:
    ClientSocket();
    virtual ~ClientSocket();
    Socket connect_to(uint16_t port, std::string ip);

private:
    int sockfd;
    struct sockaddr_in sock_addr;
};


#endif //VSYS_SOCKET_CLIENTSOCKET_H
