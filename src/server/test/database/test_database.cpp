//
// Created by viktorl on 02.10.18.
//


#include <gtest/gtest.h>
#include "../../src/database/Database.h"


TEST(test_creation, test_db) {
    Database db = Database(nullptr);
}

TEST(test_insert, test_db) {
    Database db = Database(nullptr);
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Mail_in msg = {
            .subject = subject,
            .payload = payload,
            .from = from,
            .to = to
    };
    db.save_msg(msg);
}

TEST(test_save_getMsg, test_db) {
    Database db = Database(nullptr);
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Mail_in msg = {
            .subject = subject,
            .payload = payload,
            .from = from,
            .to = to
    };
    db.save_msg(msg);

    std::vector<Mail_out> msgs = db.getMsgFor(to);
    Mail_out m = msgs.at(0);
    ASSERT_EQ(subject, m.subject);
    ASSERT_EQ(payload, m.payload);
    ASSERT_EQ(from, m.from);
    ASSERT_EQ(to, m.to);
}

TEST(test_save_getMsg_multiple, test_db) {
    Database db = Database(nullptr);
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


    std::vector<Mail_out> msgs = db.getMsgFor(to);
    ASSERT_EQ(2, msgs.size());
    Mail_out m = msgs.at(0);
    ASSERT_EQ(subject, m.subject);
    ASSERT_EQ(payload, m.payload);
    ASSERT_EQ(from, m.from);
    ASSERT_EQ(to, m.to);

    Mail_out m2 = msgs.at(1);
    ASSERT_EQ(subject2, m2.subject);
    ASSERT_EQ(payload, m2.payload);
    ASSERT_EQ(from, m2.from);
    ASSERT_EQ(to, m2.to);
}

TEST(test_save_delete_getMsg, test_db) {
    Database db = Database(nullptr);
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Mail_in msg = {
            .subject = subject,
            .payload = payload,
            .from = from,
            .to = to
    };
    db.save_msg(msg);

    db.delete_msg(1);
    std::vector<Mail_out> msgs = db.getMsgFor(to);
    ASSERT_EQ(0, msgs.size());
}

TEST(delete_not_there, test_db) {
    Database db = Database(nullptr);
    db.delete_msg(1);

    std::vector<Mail_out> msgs = db.getMsgFor("if17b094");
    ASSERT_EQ(0, msgs.size());
}

TEST(test_from_should_be_empty, test_db) {
    Database db = Database(nullptr);
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Mail_in msg = {
            .subject = subject,
            .payload = payload,
            .from = from,
            .to = to
    };
    db.save_msg(msg);
    std::vector<Mail_out> msgs = db.getMsgFor(from);
    ASSERT_EQ(0, msgs.size());
}