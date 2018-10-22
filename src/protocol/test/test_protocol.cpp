//
// Created by viktorl on 28.09.18.
//

#include <sstream>

#include <gtest/gtest.h>
#include <ClientRequest.h>
#include <ClientRequestPrinter.h>
#include <ClientRequestParser.h>
#include <ServerResponseParser.h>

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

TEST(server_resp_parser, ok){

    std::string msg = "OK\n";
    ServerResponseParser srp;
    auto result = srp.parse(msg);

    ASSERT_TRUE(std::holds_alternative<ServerResponse>(result));
    auto sresponse = std::get<ServerResponse>(result);
    ASSERT_TRUE(std::holds_alternative<Success>(sresponse));

}

TEST(server_resp_parser, err){

    std::string msg = "ERR\n";
    ServerResponseParser srp;
    auto result = srp.parse(msg);

    ASSERT_TRUE(std::holds_alternative<ServerResponse>(result));
    auto sresponse = std::get<ServerResponse>(result);
    ASSERT_TRUE(std::holds_alternative<Error>(sresponse));

}

TEST(server_resp_parser, mail){

    std::string msg = "MAIL 1\nsub\nto\nfrom\nmsg\nmsg\n.\n";
    ServerResponseParser srp;
    auto result = srp.parse(msg);

    ASSERT_TRUE(std::holds_alternative<ServerResponse>(result));
    auto sresponse = std::get<ServerResponse>(result);
    ASSERT_TRUE(std::holds_alternative<Mail>(sresponse));
    auto mail = std::get<Mail>(sresponse);

    ASSERT_EQ("1", mail.mail.id);
    ASSERT_EQ("sub", mail.mail.subject);
    ASSERT_EQ("to", mail.mail.to);
    ASSERT_EQ("from", mail.mail.from);
    ASSERT_EQ("msg\nmsg", mail.mail.payload);

}

TEST(server_resp_parser, mail_list) {

    std::string msg = "LIST\n1 sub1\n2 sub2\n3 sub3\n.\n";
    ServerResponseParser srp;
    auto result = srp.parse(msg);

    ASSERT_TRUE(std::holds_alternative<ServerResponse>(result));
    auto sresponse = std::get<ServerResponse>(result);
    ASSERT_TRUE(std::holds_alternative<Mail_list>(sresponse));
    auto list = std::get<Mail_list>(sresponse);

    ASSERT_EQ(list.mail_out.size(), 3);
    ASSERT_EQ(list.mail_out[0].subject, "sub1");
    ASSERT_EQ(list.mail_out[1].subject, "sub2");
    ASSERT_EQ(list.mail_out[2].subject, "sub3");

    ASSERT_EQ(list.mail_out[0].id, "1");
    ASSERT_EQ(list.mail_out[1].id, "2");
    ASSERT_EQ(list.mail_out[2].id, "3");
}