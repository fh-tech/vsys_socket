

//
// Created by viktorl on 23.10.18.
//

#ifndef VSYS_SOCKET_CLIENT_H
#define VSYS_SOCKET_CLIENT_H

#include <utility>
#include <sstream>
#include <Clientsocket.h>
#include <ClientRequest.h>
#include <ClientRequestPrinter.h>
#include <ServerResponse.h>
#include <ServerResponseParser.h>

class Client {
public:
    Client(uint16_t port, const std::string &ip);;

    void start();

private:
    std::variant<ServerResponse, const char *> get_Response();

    void showOptions_preLogin();
    void showOptions_postLogin();
    int getOption(int min, int max);
    ClientRequest handleOption(int option);
    Send buildSendRequest();
    List buildListRequest();
    Read buildReadRequest();
    Delete buildDeleteRequest();
    Quit buildQuitRequest();
    //will be implemented in part2
    Login buildLoginRequest();
    std::string getUsername();


    std::unique_ptr<Socket> socket;
    bool loggedIn;
};

#endif //VSYS_SOCKET_CLIENT_H
