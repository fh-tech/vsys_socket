//
// Created by daniel on 15.10.18.
//


#include "include/ClientConnection.h"

ClientConnection::ClientConnection(const Socket &socket) : client(socket) {}

void ClientConnection::run() {
    this->handle_connection();
}

void ClientConnection::handle_connection() {
    while (keep_running) {
        std::variant < ClientRequest,
        const char*> msg = get_msg();
        handle_message(msg);
    }
}

std::variant<ClientRequest, const char *> ClientConnection::get_msg() {
    ClientRequestParser parser;
    std::string msg;
    std::variant < ClientRequest,const char*> result;
    do {
        msg += client.read_line();
        result = parser.parse(msg);
    } while (std::holds_alternative<const char *>(result) && !strcmp(std::get<const char *>(result), "incomplete"));
    return result;
}

bool ClientConnection::operator==(const ClientConnection &other) const {
    return client.getSockfd() == other.client.getSockfd();
}

void ClientConnection::handle_message(const std::variant<ClientRequest, const char *> &request) {
    if(auto req = std::get_if<ClientRequest>(&request)) {
        // ClientRequestPrinter is a visitor (a callable that accepts every possible alternative from every variant
        std::visit(ClientRequestPrinter{std::cout}, *req);

        auto response = std::visit(ServerResponseGenerator(username), *req);
        std::stringstream ss{};
//        std::visit(ServerResponsePrinter(ss), response);

        if(std::holds_alternative<Login>(*req)) {
            if(std::holds_alternative<Success>(response)) {
                auto login = std::get<Login>(*req);
                this->username = login.username;
            }
        }


        client.send_msg(ss.str());
    } else {
        std::cout << std::get<const char *>(request) << std::flush;
    }
}

const Socket &ClientConnection::getSocket() const {
    return this->client;
}
