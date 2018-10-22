#include <utility>

//
// Created by daniel on 15.10.18.
//

#ifndef VSYS_SOCKET_CLIENTCONNECTION_H
#define VSYS_SOCKET_CLIENTCONNECTION_H


#include <atomic>
#include <array>
#include <variant>
#include <thread>
#include <functional>

#include <Socket.h>
#include <ClientRequest.h>
#include <ClientRequestParser.h>
#include <ClientRequestPrinter.h>

using connection_id = size_t;

class MailServer;

class ClientConnection {
public:
    ClientConnection(connection_id id, const Socket &socket, std::function<void()> deleter)
            : id(id), client(socket), deleter(std::move(deleter)) {}


    void run() {
        this->handle_connection();
        deleter();
    }

    void handle_connection() {
        while (keep_running) {
            try {
                std::variant < ClientRequest,
                const char*> msg = get_msg();
                handle_message(msg);
            }catch(std::runtime_error){
                keep_running = false;
            }
        }
    }

    std::variant<ClientRequest, const char *> get_msg() {
        ClientRequestParser parser;
        std::string msg;
        std::variant < ClientRequest,
        const char*> result;

        do {
            msg += client.read_line();
            result = parser.parse(msg);
        } while (std::holds_alternative<const char *>(result) && !strcmp(std::get<const char *>(result), "incomplete"));

        return result;
    }

    bool operator==(const ClientConnection &other) const {
        return client.getSockfd() == other.client.getSockfd();
    }

    void handle_message(const std::variant<ClientRequest, const char *> &request) {
        if (auto req = std::get_if<ClientRequest>(&request)) {
            std::visit(ClientRequestPrinter{std::cout}, *req);
        } else {
            std::cout << std::get<const char *>(request) << std::flush;
        }
    }

    const Socket &getSocket() const {
        return this->client;
    }

private:
    Socket client;
    connection_id id;
    std::function<void()> deleter;


    std::atomic<bool> keep_running = true;

    std::string username = "";

};


#endif //VSYS_SOCKET_CLIENTCONNECTION_H
