//
// Created by viktorl on 02.10.18.
//

#include <gtest/gtest.h>
#include "../../../src/shared/database/include/include.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_creation, test_db) {
    Database db = Database();
}

TEST(test_insert, test_db) {
    Database db = Database();
    std::string subject = "moinmoin";
    std::string payload = "hallo";
    std::string from = "if17b077";
    std::string to = "if17b094";
    Message msg = Message(subject, payload, from, to);
    db.save_msg(msg);
}

TEST(test_delete, test_db) {

}