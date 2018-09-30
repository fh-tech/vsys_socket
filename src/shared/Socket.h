//
// Created by viktorl on 30.09.18.
//

#ifndef VSYS_SOCKET_SOCKET_H
#define VSYS_SOCKET_SOCKET_H

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

class Socket {
public:
    explicit Socket(int sockfd);
    ~Socket();
    void send_msg(std::string message);
    std::string receive();

private:
    int sockfd;
};




#endif //VSYS_SOCKET_SOCKET_H
