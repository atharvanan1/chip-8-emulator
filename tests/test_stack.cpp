extern "C" {
    #include "stack.h"
}
#include <gtest/gtest.h>


TEST(StackTest, PushPopTest) {
    Stack* stack = init_stack();
    push_stack(stack, 1);
    push_stack(stack, 2);
    push_stack(stack, 3);
    ASSERT_EQ(3, stack->size);
    ASSERT_EQ(3, pop_stack(stack));
    ASSERT_EQ(2, pop_stack(stack));
    ASSERT_EQ(1, pop_stack(stack));
    push_stack(stack, 4);
    ASSERT_EQ(4, pop_stack(stack));
    push_stack(stack, 4);
    deinit_stack(stack);
}
