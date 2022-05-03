#include "gtest/gtest.h"
extern "C" {
#include "stack.h"
#include <errno.h>
}

class StackTestFixture : public ::testing::Test {
protected:
    virtual void SetUp()
    {
        stack = init_stack();
    }
    virtual void TearDown()
    {
        deinit_stack(stack);
    }

    Stack* stack = NULL;
};

TEST_F(StackTestFixture, NullPush) {
    ASSERT_EQ(-1, push_stack((Stack*) NULL, 1));
    ASSERT_EQ(EINVAL, errno);
}

TEST_F(StackTestFixture, NullPop) {
    ASSERT_EQ(-1, pop_stack((Stack*) NULL, (uint8_t*) NULL));
    ASSERT_EQ(EINVAL, errno);
    ASSERT_EQ(-1, pop_stack(stack, (uint8_t*) NULL));
    ASSERT_EQ(EINVAL, errno);
}

TEST_F(StackTestFixture, EmptyStack) {
    ASSERT_EQ(-1, pop_stack(stack, (uint8_t*) NULL));
    ASSERT_EQ(EINVAL, errno);
    ASSERT_EQ(0, stack->size);
}

TEST_F(StackTestFixture, PushOne) {
    ASSERT_EQ(0, push_stack(stack, 1));
    ASSERT_EQ(1, stack->size);
}

TEST_F(StackTestFixture, PushOnePopOne) {
    uint8_t data = 1;
    uint8_t ret_data = 0;
    ASSERT_EQ(0, push_stack(stack, data));
    ASSERT_EQ(1, stack->size);
    ASSERT_EQ(0, pop_stack(stack, &ret_data));
    ASSERT_EQ(0, stack->size);
    ASSERT_EQ(data, ret_data);
}

TEST_F(StackTestFixture, PushTwoPopOne) {
    uint8_t data = 1;
    uint8_t data_next = 10;
    uint8_t ret_data = 0;
    ASSERT_EQ(0, push_stack(stack, data));
    ASSERT_EQ(1, stack->size);
    ASSERT_EQ(0, push_stack(stack, data_next));
    ASSERT_EQ(2, stack->size);
    ASSERT_EQ(0, pop_stack(stack, &ret_data));
    ASSERT_EQ(1, stack->size);
}

TEST_F(StackTestFixture, PushManyPopMany) {
    uint8_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint8_t ret_data = 0;
    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(0, push_stack(stack, data[i]));
        ASSERT_EQ(i + 1, stack->size);
    }
    ASSERT_EQ(10, stack->size);
    for (int i = 0, j = 9; i < 10; i++, j--) {
        ASSERT_EQ(0, pop_stack(stack, &ret_data));
        ASSERT_EQ(data[j], ret_data);
        ASSERT_EQ(j, stack->size);
    }
    ASSERT_EQ(0, stack->size);
}
