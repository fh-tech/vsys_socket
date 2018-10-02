//
// Created by viktorl on 30.09.18.
//

#include "Socket.h"

Socket::Socket(int sockfd) : sockfd(sockfd) {}

Socket::~Socket() {
    close(sockfd);
}

void Socket::send_msg(std::string message) {
    send(sockfd, message.c_str(), message.length() + 1, 0);
}

std::string Socket::receive() const {
    std::string compMessage;
    std::string newPart = receive_helper();
    int i = 0;
    while(!newPart.empty()) {
        std::cout << i++ << std::endl;
        compMessage += newPart;
        newPart = receive_helper();
    }
    return compMessage;
}

std::string Socket::receive_helper() const {
    char buffer[10];
    // should be blocking i guess
    ssize_t size = recv(sockfd, buffer, 9, 0);
    if(size > 0) {
        buffer[size] = '\0';
        return std::string(buffer);
    } else {
        return "";
    }
}


