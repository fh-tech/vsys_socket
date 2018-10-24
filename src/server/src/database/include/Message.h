#include <utility>

//
// Created by viktorl on 14.10.18.
//

#ifndef VSYS_SOCKET_MESSAGE_H
#define VSYS_SOCKET_MESSAGE_H

#include <string>

struct Mail_in {
    std::string subject;
    std::string payload;
    std::string from;
    std::string to;
};

#endif //VSYS_SOCKET_MESSAGE_H
