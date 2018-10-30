//
// Created by daniel on 15.10.18.
//


#include <ServerResponsePrinter.h>
#include "include/ClientConnection.h"

void ClientConnection::run() {
    this->thread = std::make_unique<std::thread>([this](){this->handle_connection();});
}

void ClientConnection::handle_connection() {
    while (keep_running) {
        try {
            std::variant < ClientRequest, const char*> msg = get_msg();
            handle_message(msg);
        }catch(std::runtime_error& e){
            std::cerr << e.what() << std::endl;
            keep_running = false;
        }
    }
    deleter();
}

std::variant<ClientRequest, const char *> ClientConnection::get_msg() {
    ClientRequestParser parser;
    std::string msg;
    std::variant < ClientRequest, const char*> result;
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
    if (auto req = std::get_if<ClientRequest>(&request)) {
        // ClientRequestPrinter is a visitor (a callable that accepts every possible alternative from every variant
        auto response = std::visit(sg, *req);

        std::stringstream ss{};
        std::visit(ServerResponsePrinter(ss), response);
        client.send_msg(ss.str());

    } else {
        std::cout << std::get<const char *>(request) << std::flush;
    }
}

const Socket &ClientConnection::getSocket() const {
    return this->client;
}

ClientConnection::~ClientConnection() {
    std::cout << "client conn dtor" << std::endl;
}
