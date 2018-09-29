//
// Created by viktorl on 29.09.18.
//

#include <sys/socket.h> // socket(), bind(), ...
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_ntoa(), ...
#include <unistd.h> // read(), write(), close()
#include <errno.h> // global var errno
#include <cstdio>
#include <cstdlib>

#include "Serversocket.h"


// .sin_addr = htonl(INADDR_ANY) and .sin_port = 0 (for automatic choosing)
Serversocket::Serversocket(const char * ip, u_int16_t port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // make necessary structs
    inet_aton(ip, &addr);

    memset(&sin, 0, sizeof(sockaddr_in));
    sin = {.sin_family = AF_INET, .sin_addr = addr, .sin_port = htons(port)};

    bind_sock();
}

//TODO: think about number here (5 stands for backlog - amount of connections that are allowed to wait for accept())
int Serversocket::start_listen() const {
    return listen(sockfd, 5);
}

//associates descriptor (sockfd) with ip-address and port and makes it visible from outside
int Serversocket::bind_sock() const {
    if(bind(sockfd, (const struct sockaddr *) &sin, sizeof(sin)) == -1) {
        perror("bind error");
        exit(1);
    }
}

int Serversocket::close_conn() const {
    return close(sockfd);
}

// will produce new sockfd for the connection
int Serversocket::accept_conn() {
    return 0;
}


