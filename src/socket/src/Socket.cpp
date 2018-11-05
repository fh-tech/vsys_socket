//
// Created by viktorl on 30.09.18.
//

#include <array>
#include "../include/Socket.h"
#include <algorithm>
#include <vector>
#include <Socket.h>
#include <sys/socket.h>
#include <netinet/in.h>


Socket::Socket(int sockfd) : sockfd(sockfd) {}

Socket::~Socket() {
    close(sockfd);
}

// returns - 1 on failure and on success number of characters sent
ssize_t Socket::send_msg(std::string message) {
    // with 0 flag equivalent to write()
    return send(sockfd, message.c_str(), message.length(), 0);
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

uint32_t Socket::get_remote_ip() const {
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(addr);
    int res = getpeername(sockfd, (struct sockaddr*) &addr, &addr_size);
    return static_cast<uint32_t >(addr.sin_addr.s_addr);
}



