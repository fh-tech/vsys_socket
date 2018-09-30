//
// Created by viktorl on 30.09.18.
//

#ifndef VSYS_SOCKET_CLIENTSOCKET_H
#define VSYS_SOCKET_CLIENTSOCKET_H

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h> // socket(), bind(), ...
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_ntoa(), ...
#include <unistd.h> // read(), write(), close()
#include <cerrno> // global var errno
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
