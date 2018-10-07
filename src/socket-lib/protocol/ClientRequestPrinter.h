//
// Created by daniel on 05.10.18.
//

#ifndef VSYS_SOCKET_CLIENTREQUESTPRINTER_H
#define VSYS_SOCKET_CLIENTREQUESTPRINTER_H

#include "iostream"
#include "ClientRequest.h"

class ClientRequestPrinter {
private:
    std::ostream& os;
public:

    explicit ClientRequestPrinter(std::ostream& os): os(os)
    {}

    void operator()(Login const &l);

    void operator()(List const &l);

    void operator()(Read const &l);

    void operator()(Delete const &l);

    void operator()(Quit const &l);

};


#endif //VSYS_SOCKET_CLIENTREQUESTPRINTER_H
