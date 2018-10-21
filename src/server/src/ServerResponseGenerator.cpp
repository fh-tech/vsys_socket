#include <utility>

//
// Created by viktorl on 20.10.18.
//

#include "include/ServerResponseGenerator.h"
#include "database/include/Message.h"
#include "database/include/Database.h"

ServerResponseGenerator::ServerResponseGenerator(std::string username) {}

ServerResponse ServerResponseGenerator::operator()(const Send &Send) {
    try {
        Mail_in m = {
                .subject = Send.subject,
                .payload = Send.msg,
                .from = "",
                .to = Send.to
        };
        Database db = Database();
        db.save_msg(m);
        return Success();
    } catch (std::runtime_error &e) {
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Login &login) {
    // TODO implement LDAP
    return Success();
}

ServerResponse ServerResponseGenerator::operator()(const List &list) {
    try {
        Database db = Database();
        std::vector<Mail_out> mail_out = db.getMsgFor(this->username);
        return Mail_list{.mail_out = mail_out};
    } catch (std::runtime_error &e) {
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Read &read) {
    try {
        Database db = Database();
        Mail_out m = db.getMsg(std::to_string(read.id));
        return Mail{.mail = m};
    } catch (std::runtime_error &e) {
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Delete &del) {
    return Error();
}

ServerResponse ServerResponseGenerator::operator()(const Quit &quit) {
    return Error();
}





