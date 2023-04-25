#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <stdbool.h>

struct Deque;

// deque_create(copy, destroy, print) returns a pointer to heap allocated Deque
// effects: allocates memory, caller must free
// time: O(1)
struct Deque* deque_create(void* (*Copy_data) (const void*),
                           void (*Destroy_data) (void*),
                           void (*Print_data) (const void*));

// destroy_deque(deq) fress the heap allocated Deque
// effects: frees memory
// time: O(n)
void deque_destroy(struct Deque* deq);

// deque_empty(deq) returns true if deq is empty
// requires: deq is not NULL
// time: O(1)
bool deque_empty(const struct Deque* deq);

// insert_front(deq, data) inserts data in front of deq
// effects: mutates deq
// requires: deq is not NULL
// time: O(1)
void insert_front(struct Deque* deq, const void* data);

// insert_back(deq, data) inserts data at back of deq
// effects: mutates deq
// requires: deq is not NULL;
// time: O(1)
void insert_back(struct Deque* deq, const void* data);

// remove_front(deq) removes the front data from deq
// effects: mutates deq
// requires: deq is not NULL and not empty
// time: O(1)
void remove_front(struct Deque* deq);

// remove_back(deq) removes the back data from deq
// effects: mutates deq
// requires: deq is not NULL and not empty
// time: O(1)
void remove_back(struct Deque* deq);

// deque_front(deq) returns the front data of deq
// requires: deq is not NULL and not empty
// time: O(1)
void* deque_front(const struct Deque* deq);

// deque_back(deq) returns the back data of deq
// requires: deq is not NULL and not empty
// time: O(1)
void* deque_back(const struct Deque* deq);

// deque_print_forward(deq) prints the data in order
// requires: deq is not NULL
// time: O(n)
void deque_print_forward(const struct Deque* deq);

// deque_print_backward(deq) prints the data in reverse order
// requires: deq is not NULL
// time: O(n)
void deque_print_backward(const struct Deque* deq);

#endif

