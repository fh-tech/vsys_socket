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

    Socket(Socket&& other){
        sockfd = other.sockfd;
        other.sockfd = 0;
    }

    Socket()
    : sockfd(-1)
    {};

    ~Socket();

    ssize_t send_msg(std::string message);

    ssize_t receive(char *buf, size_t len) const;

    operator bool() { return sockfd > 0; }

    std::string read_line() const;

    int getSockfd() const;

    uint32_t get_remote_ip() const;


private:
    int sockfd;
};


#endif //VSYS_SOCKET_SOCKET_H
