#include <stdio.h>
#include "stack.h"

int main() {
    printf("Hello, World!\n");
    Stack* stack = init_stack();
    push_stack(stack, 42);
    if (pop_stack(stack) == 42) {
        printf("Works\n");
    }
    deinit_stack(stack);
    return 0;
}
