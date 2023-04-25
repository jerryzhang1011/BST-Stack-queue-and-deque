#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

struct Stack;

// stack_create(copy, desotry, print) 
//  returns a pointer to heap allocated Stack
// effects: allocates memory, caller must free
// time: O(1)
struct Stack* stack_create(void* (*Copy_data) (const void*),
                           void (*Destroy_data) (void*),
                           void (*Print_data) (const void*));
                           
// stack_destroy(stk) fress the heap allocated Stack
// effects: frees memory
// time: O(n)
void stack_destroy(struct Stack* stk);

// stack_empty(stk) returns true if stk is empty
// requires: stk is not NULL
// time: O(1)
bool stack_empty(const struct Stack* stk);

// stack_push(stk, data) pushes data onto stk
// effects: mutates stk
// requires: stk is not NULL
// time: O(1)
void stack_push(struct Stack* stk, const void* data);

// stack_pop(stk) pops the top data from stk
// effects: mutates stk
// requires: stk is not NULL and not empty
// time: O(1)
void stack_pop(struct Stack* stk);

// stack_top(stk) returns the top data from stk
// requires: stk is not NULL and not empty
// time: O(1)
void* stack_top(const struct Stack* stk);

// stack_print(stk) prints the stack from top to bottom
void stack_print(const struct Stack* stk);

#endif

