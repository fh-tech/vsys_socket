#include <utility>

#include <utility>

//
// Created by viktorl on 23.10.18.
//

#ifndef VSYS_SOCKET_CLIENT_H
#define VSYS_SOCKET_CLIENT_H

#include <sstream>
#include <Clientsocket.h>
#include <ClientRequest.h>
#include <ClientRequestPrinter.h>
#include <ServerResponse.h>
#include <ServerResponseParser.h>

class Client {
public:
    Client(uint16_t port, std::string ip) :socket(ClientSocket{}.connect_to(port, std::move(ip))), loggedIn(false) {};

    std::variant<ServerResponse, const char *> get_Response() {
        ServerResponseParser parser;
        std::string msg;
        std::variant <ServerResponse ,const char*> result;
        do {
            msg += this->socket.read_line();
            result = parser.parse(msg);
        } while (std::holds_alternative<const char *>(result) && !strcmp(std::get<const char *>(result), "incomplete"));
        return result;
    }

private:
    Socket socket;
    bool loggedIn;
};

#endif //VSYS_SOCKET_CLIENT_H
