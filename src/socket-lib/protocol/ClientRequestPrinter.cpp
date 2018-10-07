//
// Created by daniel on 05.10.18.
//

#include "ClientRequestPrinter.h"
#include <iostream>

void ClientRequestPrinter::operator()(Login const &l) {
    os << "LOGIN" << '\n'
       <<  l.username << '\n'
       << l.password << std::endl;
}

void ClientRequestPrinter::operator()(List const &l) {
    os << "LIST" << std::endl;
}

void ClientRequestPrinter::operator()(Read const &l) {
    os << "READ" << '\n'
       << l.id << std::endl;
}

void ClientRequestPrinter::operator()(Delete const &l) {
    os << "DELETE" << '\n'
       << l.id << std::endl;
}

void ClientRequestPrinter::operator()(Quit const &l) {
    os << "QUIT" << std::endl;
}
