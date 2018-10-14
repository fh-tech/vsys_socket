#include <utility>

#include <utility>

#include <utility>

//
// Created by viktorl on 14.10.18.
//

#ifndef VSYS_SOCKET_MESSAGE_H
#define VSYS_SOCKET_MESSAGE_H

#include <string>

class Message {
public:
    Message(std::string subject, std::string payload, std::string from, std::string to)
            : subject(std::move(subject)),
              payload(std::move(payload)),
              from(std::move(from)),
              to(std::move(to)) {}

    std::string from;
    std::string payload;
    std::string subject;
    std::string to;
};

#endif //VSYS_SOCKET_MESSAGE_H
