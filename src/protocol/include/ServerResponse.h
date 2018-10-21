//
// Created by viktorl on 20.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSE_H
#define VSYS_SOCKET_SERVERRESPONSE_H

#include <string>
#include <variant>
#include <vector>
#include "../../server/src/database/include/Message.h"

struct Success {};

struct Error {};

struct Mail_list{
    std::vector<Mail_out> mail_out;
};

struct Mail {
    Mail_out mail;
};

using ServerResponse = std::variant<Success, Error, Mail_list, Mail>;


#endif //VSYS_SOCKET_SERVERRESPONSE_H
