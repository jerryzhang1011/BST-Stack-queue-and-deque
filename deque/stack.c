#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "deque.h"

typedef void* (*Copy_data) (const void*);
typedef void (*Destroy_data) (void*);
typedef void (*Print_data) (const void*);

struct Stack {
    struct Deque* deq;
};

struct Stack* stack_create(Copy_data copy, Destroy_data destroy, Print_data print) {
    struct Stack* stk = malloc(sizeof(struct Stack));
    stk->deq = deque_create(copy, destroy, print);
    return stk;
}

void stack_destroy(struct Stack* stk) {
    if (stk) {
        deque_destroy(stk->deq);
        free(stk);
    }
}

bool stack_empty(const struct Stack* stk) {
    assert(stk);

    return deque_empty(stk->deq);
}

void stack_push(struct Stack* stk, const void* data) {
    assert(stk);

    insert_back(stk->deq, data);
}

void stack_pop(struct Stack* stk) {
    assert(stk);
    assert(!stack_empty(stk));

    remove_back(stk->deq);
}

void* stack_top(const struct Stack* stk) {
    assert(stk);
    assert(!stack_empty(stk));

    return deque_back(stk->deq);
}

void stack_print(const struct Stack* stk) {
    assert(stk);

    deque_print_backward(stk->deq);
}
