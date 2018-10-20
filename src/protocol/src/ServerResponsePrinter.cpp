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
