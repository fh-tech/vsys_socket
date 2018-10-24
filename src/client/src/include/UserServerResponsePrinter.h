//
// Created by viktorl on 24.10.18.
//

#ifndef VSYS_SOCKET_USERSERVERRESPONSEPRINTER_H
#define VSYS_SOCKET_USERSERVERRESPONSEPRINTER_H

#include <iostream>
#include <ServerResponse.h>

class UserServerResponsePrinter {
private:
    std::ostream& os;
public:
    explicit UserServerResponsePrinter(std::ostream &os) :os(os) {}

    void operator()(Success const &l);

    void operator()(Error const &l);

    void operator()(Mail_list const &l);

    void operator()(Mail_out const &l);
};

#endif //VSYS_SOCKET_USERSERVERRESPONSEPRINTER_H
