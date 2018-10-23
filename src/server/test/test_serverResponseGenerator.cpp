//
// Created by viktorl on 21.10.18.
//

#include <gtest/gtest.h>
#include <ServerResponsePrinter.h>
#include "../src/include/ServerResponseGenerator.h"

/*
TEST(test_server_RG, test_Login) {

    ClientRequest cr = Login {
            .username = "if17b077",
            .password = "helloKitty"
    };
    std::string actual_username = "";
    Database db(nullptr);
    ServerResponseGenerator sg = ServerResponseGenerator(db, actual_username);
    ServerResponse response = std::visit(sg, cr);
    ASSERT_TRUE(std::holds_alternative<Success>(response));
}

TEST(test_server_RG, test_LIST) {
    std::string actual_username = "if17b094";
    Database db(nullptr);
    std::string subject = "moin moin";
    std::string subject2 = "abend";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Mail_in msg = {
            .subject = subject,
            .payload = payload,
            .from = from,
            .to = to
    };
    Mail_in msg2 = {
            .subject = subject2,
            .payload = payload,
            .from = from,
            .to = to
    };
    db.save_msg(msg);
    db.save_msg(msg2);

    ServerResponseGenerator sg = ServerResponseGenerator(db, actual_username);
    ClientRequest l = List{};
    ServerResponse response = std::visit(sg, l);
    std::stringstream ss{};
    std::visit(ServerResponsePrinter{ss}, response);

    std::cout << ss.str() << std::endl;


    ASSERT_TRUE(std::holds_alternative<Success>(response));
}*/
