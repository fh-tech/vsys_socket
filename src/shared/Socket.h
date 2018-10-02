//
// Created by viktorl on 30.09.18.
//

#ifndef VSYS_SOCKET_SOCKET_H
#define VSYS_SOCKET_SOCKET_H

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

class Socket {
public:
    explicit Socket(int sockfd);

    ~Socket();

    ssize_t send_msg(std::string message);

    ssize_t receive(char *buf, size_t len) const;

    operator bool() { return sockfd > 0; }

private:
    int sockfd;
};


#endif //VSYS_SOCKET_SOCKET_H
