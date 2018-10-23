//
// Created by viktorl on 20.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSEGENERATOR_H
#define VSYS_SOCKET_SERVERRESPONSEGENERATOR_H

#include<ClientRequest.h>
#include <ServerResponse.h>

// forward declaration
class ClientConnection;

class ServerResponseGenerator {
public:
    explicit ServerResponseGenerator(ClientConnection * clientConnection);

    ServerResponse operator()(Send const &Send);
    ServerResponse operator()(Login const &login);
    ServerResponse operator()(List const &list);
    ServerResponse operator()(Read const &read);
    ServerResponse operator()(Delete const &del);
    ServerResponse operator()(Quit const &quit);

private:
    ClientConnection * clientConnection;
};


#endif //VSYS_SOCKET_SERVERRESPONSEGENERATOR_H
