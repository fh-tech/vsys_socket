//
// Created by viktorl on 29.09.18.
//

#include <cstring>

#ifndef VSYS_SOCKET_SERVER_SOCKET_H
#define VSYS_SOCKET_SERVER_SOCKET_H

#endif //VSYS_SOCKET_SERVER_SOCKET_H

class Serversocket {
public:
    Serversocket(const char * ip, u_int16_t port);
    int start_listen() const;
    int close_conn() const;
    int accept_conn();


private:
    int bind_sock() const;

    //socket filedescriptor
    int sockfd;
    struct in_addr addr{};
    struct sockaddr_in sin{};
};