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

void ServerResponsePrinter::operator()(Mail_list const &l) {
    os << "LIST" << std::endl;
    for(auto &m : l.mail_out) {
        os << m.id  << " " << m.subject << std::endl;
    }
    os << "." << std::endl;
}

void ServerResponsePrinter::operator()(Mail const &l) {
    Mail_out m = l.mail;
    os << "MAIL " << m.id << std::endl;
    os << m.subject << std::endl;
    os << m.from << std::endl;
    os << m.to << std::endl;
    os << m.payload << std::endl;
    os << "." << std::endl;
}
