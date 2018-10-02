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
    void send_msg(std::string message);

    std::string receive() const;

private:
    std::string receive_helper() const;
    int sockfd;
};




#endif //VSYS_SOCKET_SOCKET_H
