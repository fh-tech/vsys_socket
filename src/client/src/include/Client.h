

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
    Client(uint16_t port, const std::string &ip);

    void start();

private:
    ServerResponse get_Response() const;

    void showOptions_preLogin() const;
    void showOptions_postLogin() const;
    char getOption () const;
    void handleRequest(char option);
    std::string getRequestString(ClientRequest &cr) const;

    // building
    Send buildSendRequest() const;
    List buildListRequest() const;
    Read buildReadRequest() const;
    Delete buildDeleteRequest() const;
    Quit buildQuitRequest() const;
    Login buildLoginRequest() const;

    // handling
    void handleLoginResponse(ServerResponse response);

    std::string getUsername() const;

    std::vector<MailDetail> inbox;
    std::unique_ptr<Socket> socket;
    bool loggedIn;
};

#endif //VSYS_SOCKET_CLIENT_H
