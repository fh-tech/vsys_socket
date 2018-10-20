#include <utility>

//
// Created by viktorl on 20.10.18.
//

#include "ServerResponseGenerator.h"
#include "database/Message.h"
#include "database/Database.h"

ServerResponse ServerResponseGenerator::operator()(const Send &Send) {
    try {
        //TODO: add from also

        Mail_in m = {
                .subject = Send.subject,
                .payload = Send.msg,
                .from = "",
                .to = Send.to
        };
        Database db = Database();
        db.save_msg(m);
        return Success();
    } catch(std::runtime_error &e) {
        return Error();
    }
}

ServerResponse ServerResponseGenerator::operator()(const Login &login) {
    // TODO implement LDAP
    return Success();
}

ServerResponse ServerResponseGenerator::operator()(const List &list) {
//    Database db = Database();
//    db.getMsgFor()
    return Success();
}

ServerResponse ServerResponseGenerator::operator()(const Read &read) {
//    Database db = Database();
    return Error();
}

ServerResponse ServerResponseGenerator::operator()(const Delete &del) {
    return Error();
}

ServerResponse ServerResponseGenerator::operator()(const Quit &quit) {
    return Error();
}

ServerResponseGenerator::ServerResponseGenerator(std::string username) :username(std::move(username)) {

}



