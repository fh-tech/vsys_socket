//
// Created by viktorl on 28.09.18.
//

#include <sstream>

#include <gtest/gtest.h>
#include <socket-lib/include/include.h>
#include <socket-lib/protocol/ClientRequestParser.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_library, test_gtest) {
    int i = 10;
    ASSERT_TRUE(i < 200);
}

TEST(client_request, print){

    ClientRequest client_rq = Login {"username", "password"};

    std::stringstream ss{};
    ClientRequestPrinter crp{ss};

    std::visit(crp, client_rq);

    ASSERT_EQ("LOGIN\nusername\npassword\n", ss.str());

}

TEST(client_req_parser, login){

    std::string client_req = "LOGIN\ndaniel\nhello_kitty\n";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);

    ASSERT_TRUE(std::holds_alternative<ClientRequest>(crq_result));
    auto crq = std::get<ClientRequest>(crq_result);
    ASSERT_TRUE(std::holds_alternative<Login>(crq));
    Login login = std::get<Login>(crq);
    ASSERT_EQ(login.username, "daniel");
    ASSERT_EQ(login.password, "hello_kitty");

}

TEST(client_req_parser, login_fails_incomplete){

    std::string client_req = "LOGIN\ndaniel\nhello_kitty";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);

    ASSERT_TRUE(std::holds_alternative<const char*>(crq_result));
    auto crq = std::get<const char*>(crq_result);
    ASSERT_EQ(crq, "ERR");

}

TEST(client_req_parser, read){

    std::string client_req = "READ\n123\n";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);

    ASSERT_TRUE(std::holds_alternative<ClientRequest>(crq_result));
    auto crq = std::get<ClientRequest>(crq_result);
    ASSERT_TRUE(std::holds_alternative<Read>(crq));
    Read read = std::get<Read>(crq);
    ASSERT_EQ(read.id, 123);

}


TEST(client_req_parser, del){

    std::string client_req = "DELETE\n123\n";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);

    ASSERT_TRUE(std::holds_alternative<ClientRequest>(crq_result));
    auto crq = std::get<ClientRequest>(crq_result);
    ASSERT_TRUE(std::holds_alternative<Delete>(crq));
    Delete del = std::get<Delete>(crq);
    ASSERT_EQ(del.id, 123);

}

TEST(client_req_parser, list){

    std::string client_req = "LIST\n";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);

    ASSERT_TRUE(std::holds_alternative<ClientRequest>(crq_result));
    auto crq = std::get<ClientRequest>(crq_result);
    ASSERT_TRUE(std::holds_alternative<List>(crq));
}


TEST(client_req_parser, quit){

    std::string client_req = "QUIT\n";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);

    ASSERT_TRUE(std::holds_alternative<ClientRequest>(crq_result));
    auto crq = std::get<ClientRequest>(crq_result);
    ASSERT_TRUE(std::holds_alternative<Quit>(crq));
}

TEST(client_req_parser, send){
    std::string client_req = "SEND\nhello_kitty\nHello World\nThis is a\n multiline message.\n\n.\n";
    ClientRequestParser parser;
    std::variant<ClientRequest, const char*> crq_result = parser.parse(client_req);
    ASSERT_TRUE(std::holds_alternative<ClientRequest>(crq_result));
    auto req = std::get<ClientRequest>(crq_result);
    ASSERT_TRUE(std::holds_alternative<Send>(req));

    auto send = std::get<Send>(req);
    ASSERT_EQ("hello_kitty", send.to);
    ASSERT_EQ("Hello World", send.subject);
    ASSERT_EQ("This is a\n multiline message.\n", send.msg);

}