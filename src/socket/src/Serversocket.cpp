//
// Created by viktorl on 29.09.18.
//

#include "../include/Serversocket.h"

// .sin_addr = htonl(INADDR_ANY) and .sin_port = 0 (for automatic choosing)
Serversocket::Serversocket(std::string ip, uint16_t port, int backlog)
        : backlog(backlog) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // make necessary structs
    inet_aton(ip.c_str(), &addr);

    memset(&sin, 0, sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr = addr;

    bind_sock();
}

Serversocket::Serversocket(uint16_t port, int backlog) : Serversocket("0.0.0.0", port, backlog) {}

Serversocket::~Serversocket() {
    close(sockfd);
}

//associates descriptor (sockfd) with ip-address and port and makes it visible from outside
void Serversocket::bind_sock() const {
    if (bind(sockfd, (const struct sockaddr *) &sin, sizeof(sin)) == -1) {
        perror("bind error");
        exit(1);
    }
}

Socket Serversocket::listen_accept() const {
    listen(sockfd, backlog);

    struct sockaddr_in cli_addr{};
    int clilen = sizeof(cli_addr);
    int cli_sockfd = -1;
    bool connected = false;

    cli_sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (cli_sockfd > 0) {
        printf("Client connected from %s:%d...\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    } else {
        std::cout << "connection error" << std::endl;
    }
    return Socket(cli_sockfd);
}






