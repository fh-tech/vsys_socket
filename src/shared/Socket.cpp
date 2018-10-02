//
// Created by viktorl on 30.09.18.
//

#include "Socket.h"

Socket::Socket(int sockfd) : sockfd(sockfd) {}

Socket::~Socket() {
    close(sockfd);
}

// returns - 1 on failure and on success number of characters sent
ssize_t Socket::send_msg(std::string message) {
    // with 0 flag equivalent to write()
    return send(sockfd, message.c_str(), message.length() + 1, 0);
}

ssize_t Socket::receive(char *buf, size_t len) const {
    ssize_t rSize;
    if((rSize = recv(sockfd, buf, len, 0)) == -1) {
        throw new std::runtime_error("failed to receive message");
    } else {
        return rSize;
    }
}





