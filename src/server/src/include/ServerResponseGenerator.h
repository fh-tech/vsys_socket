//
// Created by viktorl on 20.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSEGENERATOR_H
#define VSYS_SOCKET_SERVERRESPONSEGENERATOR_H


#include <ClientRequest.h>
#include <ServerResponse.h>
#include "../database/include/Database.h"

class ServerResponseGenerator {
public:

    explicit ServerResponseGenerator(Database db, std::string username);

    ServerResponse operator()(Send const &Send);
    ServerResponse operator()(Login const &login);
    ServerResponse operator()(List const &list);
    ServerResponse operator()(Read const &read);
    ServerResponse operator()(Delete const &del);
    ServerResponse operator()(Quit const &quit);

private:
    Database db;
    std::string username;
};


#endif //VSYS_SOCKET_SERVERRESPONSEGENERATOR_H
