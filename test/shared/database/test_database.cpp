//
// Created by viktorl on 02.10.18.
//

#include <gtest/gtest.h>
#include "../../../src/shared/database/include/include.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

static void cleanup(std::string filename) {
    struct stat buffer{};
    if(stat(filename.c_str(), &buffer) == 0) {
        if(remove(filename.c_str()) != 0) {
            perror("failed to remove db");
        } else {
            std::cout << "cleanup successful" << std::endl;
        }
    }
}


TEST(test_creation, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    cleanup("mail.db");
}

TEST(test_insert, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Message msg = Message(subject, payload, from, to);
    db.save_msg(msg);

    cleanup("mail.db");
}

TEST(test_save_getMsg, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Message msg = Message(subject, payload, from, to);
    db.save_msg(msg);

    std::vector<Message> msgs = db.getMsgFor(to);
    Message m = msgs.at(0);
    ASSERT_EQ(subject, m.subject);
    ASSERT_EQ(payload, m.payload);
    ASSERT_EQ(from, m.from);
    ASSERT_EQ(to, m.to);

    cleanup("mail.db");
}

TEST(test_save_getMsg_multiple, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    std::string subject = "moin moin";
    std::string subject2 = "abend";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Message msg = Message(subject, payload, from, to);
    Message msg2 = Message(subject2, payload, from, to);
    db.save_msg(msg);
    db.save_msg(msg2);


    std::vector<Message> msgs = db.getMsgFor(to);
    ASSERT_EQ(2, msgs.size());
    Message m = msgs.at(0);
    ASSERT_EQ(subject, m.subject);
    ASSERT_EQ(payload, m.payload);
    ASSERT_EQ(from, m.from);
    ASSERT_EQ(to, m.to);

    Message m2 = msgs.at(1);
    ASSERT_EQ(subject2, m2.subject);
    ASSERT_EQ(payload, m2.payload);
    ASSERT_EQ(from, m2.from);
    ASSERT_EQ(to, m2.to);

    cleanup("mail.db");
}

TEST(test_save_delete_getMsg, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Message msg = Message(subject, payload, from, to);
    db.save_msg(msg);

    db.delete_msg(1);

    std::vector<Message> msgs = db.getMsgFor(to);
    ASSERT_EQ(0, msgs.size());

    cleanup("mail.db");
}

TEST(delete_not_there, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    db.delete_msg(1);

    std::vector<Message> msgs = db.getMsgFor("if17b094");
    ASSERT_EQ(0, msgs.size());

    cleanup("mail.db");
}

TEST(test_from_should_be_empty, test_db) {
    cleanup("mail.db");
    Database db = Database("mail.db");
    std::string subject = "moin moin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Message msg = Message(subject, payload, from, to);
    db.save_msg(msg);

    std::vector<Message> msgs = db.getMsgFor(from);
    ASSERT_EQ(0, msgs.size());

    cleanup("mail.db");
}