//
// Created by viktorl on 23.10.18.
//

#ifndef VSYS_SOCKET_MAIL_H
#define VSYS_SOCKET_MAIL_H

#include <iostream>

struct Mail_out {
    std::string id;
    std::string subject;
    std::string payload;
    std::string from;
    std::string to;
};

#endif //VSYS_SOCKET_MAIL_H
