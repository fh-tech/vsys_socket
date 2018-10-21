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
    os << "Amount of messages: " << l.mail_out.size() << std::endl;
    for(auto &m : l.mail_out) {
        os << "(" << m.id << ") " << m.subject << std::endl;
    }
}

void ServerResponsePrinter::operator()(Mail const &l) {
    Mail_out m = l.mail;
    os << "Subject: " << m.subject << std::endl;
    os << "From: " << m.from << std::endl;
    os << "To: " << m.to << std::endl;
    os << "Message: " << m.payload << std::endl;
}
