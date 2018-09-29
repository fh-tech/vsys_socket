//
// Created by viktorl on 28.09.18.
//

#include <gtest/gtest.h>
#include "../../src/server/include/include.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_server, test_gtest) {
    int i = 10;
    ASSERT_TRUE(i < 200);
}