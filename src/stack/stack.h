#ifndef STACK_H_
#define STACK_H_
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
uint8_t pop_stack(Stack* stack);
int deinit_stack(Stack* stack);

#endif /* STACK_H_ */
