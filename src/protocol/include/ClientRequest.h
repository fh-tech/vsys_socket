//
// Created by daniel on 05.10.18.
//

#ifndef VSYS_SOCKET_CLIENTREQUEST_H
#define VSYS_SOCKET_CLIENTREQUEST_H

#include <string>
#include <variant>

using msg_id = u_int32_t;

struct Login { std::string username; std::string password; };

struct List {};

struct Read   { msg_id id; };

struct Delete { msg_id id; };

struct Send {
    std::string to;
    std::string subject;
    std::string msg;
};

struct Quit {};


using ClientRequest = std::variant<Login, Send, List, Read, Delete, Quit>;

#endif //VSYS_SOCKET_CLIENTREQUEST_H
