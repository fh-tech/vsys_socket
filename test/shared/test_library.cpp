//
// Created by viktorl on 28.09.18.
//

#include <gtest/gtest.h>
#include <linux/in.h>
#include "../../src/shared/include/include.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_library, test_gtest) {
    const char * ip = "127.0.0.1";
    Serversocket ssocket(ip, 25);
}