//
// Created by viktorl on 21.10.18.
//
#include <sstream>
#include <gtest/gtest.h>
#include <ClientRequest.h>
#include "../../server/src/ServerResponseGenerator.h"
#include <ServerResponse.h>

TEST(server_response, LOGIN){
    ClientRequest cr = Login {
        .username = "if17b077",
        .password = "helloKitty"
    };
    std::string actual_username = "";
    ServerResponse response = std::visit(ServerResponseGenerator(actual_username), cr);
    ASSERT_TRUE(std::holds_alternative<Success>(response));
}