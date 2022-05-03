//
// Created by azzentys on 5/2/22.
//

#include "stack.h"
#include <errno.h>

/**
 * @brief init_stack
 *
 * Initializes the stack with an empty HEAD node. This node shall always be present
 *
 * @return Stack* - returns pointer on success, NULL on failure
 */
Stack*
init_stack(void)
{
    DataNode* head = (DataNode*) calloc(1, sizeof(DataNode));
    if (head == NULL) {
        errno = ENOMEM;
        goto head_fail;
    }

    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    if (stack == NULL) {
        errno = ENOMEM;
        goto stack_fail;
    }

    stack->head = head;
    stack->tail = head;
    // Don't count head
    stack->size = 0;

    return stack;

    stack_fail:
    free(head);
    head_fail:
    return NULL;
}


/**
 * @brief push_stack
 *
 * Push data into the stack
 *
 * @param stack - pointer to the stack
 * @param data - uint8_t
 * @return int - returns 0 on success, -1 otherwise with errno
 */
int
push_stack(Stack* stack, uint8_t data)
{
    if (stack == NULL) {
        errno = EINVAL;
        return -1;
    }

    DataNode* element = (DataNode*) calloc(1, sizeof(DataNode));
    if (element == NULL) {
        errno = ENOMEM;
        return -1;
    }

    DataNode* tail = stack->tail;
    tail->next = element;
    element->prev = tail;
    element->data = data;
    element->next = NULL;
    stack->tail = element;
    stack->size += 1;

    return 0;
}

/**
 * @brief pop_stack
 *
 * Pop from stack
 *
 * @param stack - pointer to the stack
 * @return int - returns 0 on success, returns -1 when stack is empty or error
 */
int
pop_stack(Stack* stack, uint8_t* dest)
{
    if (stack == NULL || dest == NULL)
    {
        errno = EINVAL;
        return -1;
    }
    DataNode* tail = stack->tail;
    if (tail == NULL)
    {
        return 0;
    }
    DataNode* new_tail = tail->prev;
    uint8_t data = tail->data;

    stack->tail = new_tail;
    new_tail->next = NULL;
    stack->size -= 1;
    free(tail);
    *dest = data;

    return 0;
}

/**
 * @brief deinit_stack
 *
 * @param stack - pointer to the stack
 * @return int - returns 0 on success
 */
int
deinit_stack(Stack* stack)
{
    DataNode* head = stack->head;
    do {
        DataNode* new_head = head->next;
        free(head);
        stack->size -= 1;
        head = new_head;
    }
    while(head != NULL);

    free(stack);
    stack = NULL;
    return 0;
}