//
// Created by azzentys on 5/2/22.
//

#ifndef CHIP_8_STACK_H
#define CHIP_8_STACK_H
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief DataNode
 *
 * Doubly Linked-List implementation
 * for DataNode
 *
 */
struct DataNode {
    uint8_t data;
    struct DataNode* prev;
    struct DataNode* next;
};

typedef struct DataNode DataNode;

/**
 * @brief Stack
 *
 * Represents a stack
 */
typedef struct {
    DataNode* head;
    DataNode* tail;
    size_t size;
} Stack;

/* Function Declarations */
Stack* init_stack(void);
int push_stack(Stack* stack, uint8_t data);
int pop_stack(Stack* stack, uint8_t* dest);
int deinit_stack(Stack* stack);

#endif //CHIP_8_STACK_H
