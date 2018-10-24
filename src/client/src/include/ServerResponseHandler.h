//
// Created by viktorl on 24.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSEHANDLER_H
#define VSYS_SOCKET_SERVERRESPONSEHANDLER_H


#include <ServerResponse.h>

// forward declaration
class Client;

class ServerResponseHandler {

    explicit ServerResponseHandler(Client * client);

public:
    void operator()(Success const &l);

    void operator()(Error const &l);

    void operator()(Mail_list const &l);

    void operator()(Mail_out const &l);

private:
    Client * client;
};



#endif //VSYS_SOCKET_SERVERRESPONSEHANDLER_H
