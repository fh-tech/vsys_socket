//
// Created by viktorl on 20.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSEPRINTER_H
#define VSYS_SOCKET_SERVERRESPONSEPRINTER_H

#include "iostream"
#include "ServerResponse.h"

class ServerResponsePrinter {
private:
    std::ostream& os;
public:
    explicit ServerResponsePrinter(std::ostream &os) :os(os) {}

    void operator()(Success const &l);

    void operator()(Error const &l);

    void operator()(Mail_list const &l);

    void operator()(Mail const &l);
};


#endif //VSYS_SOCKET_SERVERRESPONSEPRINTER_H
