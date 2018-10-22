#include <utility>

#include <utility>

//
// Created by viktorl on 20.10.18.
//

#include "include/ServerResponseGenerator.h"
#include "database/include/Message.h"
#include "database/include/Database.h"

ServerResponseGenerator::ServerResponseGenerator(Database db, std::string username)
:db(db), username(std::move(username)){}

ServerResponse ServerResponseGenerator::operator()(const Send &Send) {
    try {
        Mail_in m = {
                .subject = Send.subject,
                .payload = Send.msg,
                .from = "",
                .to = Send.to
        };
        db.save_msg(m);
        return Success();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Login &login) {
    // TODO implement LDAP
    return Success();
}

ServerResponse ServerResponseGenerator::operator()(const List &list) {
    try {
        std::vector<Mail_out> mail_out = db.getMsgFor(this->username);
        return Mail_list{.mail_out = mail_out};
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Read &read) {
    try {
        Mail_out m = db.getMsg(std::to_string(read.id));
        return Mail{.mail = m};
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Delete &del) {
    return Error();
}

ServerResponse ServerResponseGenerator::operator()(const Quit &quit) {
    return Error();
}





