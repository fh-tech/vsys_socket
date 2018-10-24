//
// Created by viktorl on 20.10.18.
//

#include "../include/ClientRequestPrinter.h"
#include <iostream>
#include <ServerResponsePrinter.h>


void ServerResponsePrinter::operator()(const Success &l) {
    os << "OK" << std::endl;
}

void ServerResponsePrinter::operator()(Error const &l) {
    os << "ERR" << std::endl;
}

// \n . \n only necessary for parser to know the end of the message
void ServerResponsePrinter::operator()(Mail_list const &l) {
    os << "LIST" << std::endl;
    for(auto &m : l.mail_out) {
        os << m.id  << " " << m.subject << std::endl;
    }
    os << "." << std::endl;
}

//\n . \n only necessary for parser to know the end of the message
void ServerResponsePrinter::operator()(Mail_out const &l) {
    os << "MAIL " << l.id << std::endl;
    os << l.subject << std::endl;
    os << l.from << std::endl;
    os << l.to << std::endl;
    os << l.payload << std::endl;
    os << "." << std::endl;
}
