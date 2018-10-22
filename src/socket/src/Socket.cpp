//
// Created by viktorl on 30.09.18.
//

#include <array>
#include "../include/Socket.h"
#include <algorithm>
#include <vector>


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
        perror("recv: ");
        throw std::runtime_error("failed to receive message: ");
    } else {
        return rSize;
    }
}

std::string Socket::read_line() const {
    std::vector<char> string{};
    string.reserve(100);
    char buf;
    while(true) {
        if (receive(&buf, 1)) {
            string.emplace_back(buf);
            if (buf == '\n') {
                return std::string{string.begin(), string.end()};
            }
        } else {
            throw std::runtime_error("Connection closed");
        }
    }
}

int Socket::getSockfd() const {
    return sockfd;
}



