#include <stdio.h>
#include "stack.h"

int main(void)
{
    Stack* stack = init_stack();
    push_stack(stack, 1);
    push_stack(stack, 2);
    push_stack(stack, 3);
    printf("%d\n", pop_stack(stack));
    printf("%d\n", pop_stack(stack));
    printf("%d\n", pop_stack(stack));
    push_stack(stack, 4);
    push_stack(stack, 4);
    deinit_stack(stack);
    if (stack == NULL)
    {
        printf("stack was freed\n");
    }
    return 0;
}
