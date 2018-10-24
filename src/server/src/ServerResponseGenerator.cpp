

//
// Created by viktorl on 20.10.18.
//
#include <utility>
#include "include/ServerResponseGenerator.h"
#include "database/include/Message.h"
#include "database/include/Database.h"

// also hack with forward declaration
#include "include/ClientConnection.h"

ServerResponseGenerator::ServerResponseGenerator(ClientConnection *clientConnection) :clientConnection(clientConnection) {}

ServerResponse ServerResponseGenerator::operator()(const Send &Send) {
    try {
        Mail_in m = {
                .subject = Send.subject,
                .payload = Send.msg,
                .from = clientConnection->username,
                .to = Send.to
        };
        this->clientConnection->db.save_msg(m);
        return Success();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Login &login) {
    //TODO: LDAPÜ-sama
    clientConnection->username = login.username;
    return Success();
}

ServerResponse ServerResponseGenerator::operator()(const List &list) {
    try {
        std::vector<Mail_out> mail_out = this->clientConnection->db.getMsgFor(this->clientConnection->username);
        std::vector<MailDetail> mail_detail{};
        mail_detail.reserve(mail_out.size());
        for(auto &m : mail_out) {
            mail_detail.push_back(MailDetail{.id = m.id, .subject = m.subject});
        }
        return Mail_list{.mail_out = mail_detail};
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Read &read) {
    try {
        Mail_out m = this->clientConnection->db.getMsg(std::to_string(read.id));
        return m;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Delete &del) {
    try {
        this->clientConnection->db.delete_msg(static_cast<uint16_t>(del.id));
        return Success();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Quit &quit) {
    this->clientConnection->keep_running = false;
    return Success();
}





