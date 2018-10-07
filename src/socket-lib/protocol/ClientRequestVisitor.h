//
// Created by daniel on 05.10.18.
//

#ifndef VSYS_SOCKET_CLIENTREQUESTVISITOR_H
#define VSYS_SOCKET_CLIENTREQUESTVISITOR_H


#include "ClientRequest.h"

class ClientRequestVisitor {
public:
    virtual void operator()(Login const &login) = 0;

    virtual void operator()(List const &list) = 0;

    virtual void operator()(Read const &read) = 0;

    virtual void operator()(Delete const &del) = 0;

    virtual void operator()(Quit const &quit) = 0;
};


#endif //VSYS_SOCKET_CLIENTREQUESTVISITOR_H
