extern "C" {
    #include "bool_lib.h"
}
#include <gtest/gtest.h>


TEST(BoolTestSuite, ReturnTrue) {
    ASSERT_EQ(true, ret_true());
}

TEST(BoolTestSuite, ReturnFalse) {
    ASSERT_EQ(false, ret_false());
}