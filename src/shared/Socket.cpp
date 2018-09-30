//
// Created by viktorl on 30.09.18.
//

#include "Socket.h"

Socket::Socket(int sockfd) : sockfd(sockfd) {}

Socket::~Socket() {
    close(sockfd);
}

void Socket::send_msg(std::string message) {
    char buffer[message.length() + 1];
    strcpy(buffer, message.c_str());
    buffer[message.length()] = '\0';
    send(sockfd, buffer, strlen(buffer), 0);
}

std::string Socket::receive() {
    char buffer[1024];
    // should be blocking i guess
    ssize_t size = recv(sockfd, buffer, 1023, 0);
    if(size > 0) {
        buffer[size] = '\0';
        std::cout << "Message received" << std::endl;
        return std::string(buffer);
    } else if(size == 0) {
        std::cout << "Client closed remote socket" << std::endl;
        //TODO: should we quit here?
        exit(1);
    } else {
        perror("recv error");
        exit(1);
    }
}
