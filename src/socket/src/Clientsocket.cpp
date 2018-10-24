//
// Created by viktorl on 30.09.18.
//

#include <memory>
#include "../include/Clientsocket.h"
#include "../include/Socket.h"

ClientSocket::ClientSocket() {

}


std::unique_ptr<Socket> ClientSocket::connect_to(uint16_t port, std::string ip) {

    memset(&sock_addr, 0, sizeof(sockaddr_in));
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket error");
        exit(1);
    }

    sock_addr.sin_family = AF_INET;
    inet_aton(ip.c_str(), &sock_addr.sin_addr);
    sock_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &sock_addr, sizeof(sockaddr_in)) == 0) {
        printf("Connection with server (%s) established\n", inet_ntoa(sock_addr.sin_addr));
        return std::make_unique<Socket>(sockfd);
    } else {
        perror("Connect error - no server available");
        exit(1);
    }
}

