//
// Created by viktorl on 02.10.18.
//

#include <gtest/gtest.h>
#include "../../../src/shared/database/include/include.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test_database, test_gtest) {
    int i = 10;
    ASSERT_TRUE(i < 200);
}