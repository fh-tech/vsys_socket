//
// Created by viktorl on 28.09.18.
//

#include <gtest/gtest.h>
#include "../../src/client/include/include.h"


int main() {
    RUN_ALL_TESTS();
}

TEST(test_client, test_gtest) {
    int i = 10;
    ASSERT_TRUE(i < 200);
}