//
// Created by viktorl on 20.10.18.
//

#ifndef VSYS_SOCKET_SERVERRESPONSE_H
#define VSYS_SOCKET_SERVERRESPONSE_H

#include <string>
#include <variant>
#include <vector>
#include "Mail.h"

struct Success {};

struct Error {};

struct MailDetail{
    std::string id;
    std::string subject;
};

struct Mail_list{
    std::vector<MailDetail> mail_out;
};

// Mail_out is used in Response and Server (ServerResponseGenerator)
using ServerResponse = std::variant<Success, Error, Mail_list, Mail_out>;


#endif //VSYS_SOCKET_SERVERRESPONSE_H
