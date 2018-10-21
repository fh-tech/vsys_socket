//
// Created by viktorl on 21.10.18.
//

#include <gtest/gtest.h>
#include "../src/include/ServerResponseGenerator.h"

TEST(test_server_RG, test_Login) {

    ClientRequest cr = Login {
            .username = "if17b077",
            .password = "helloKitty"
    };
    std::string actual_username = "";
    ServerResponse response = std::visit(ServerResponseGenerator(actual_username), cr);
    ASSERT_TRUE(std::holds_alternative<Success>(response));

}