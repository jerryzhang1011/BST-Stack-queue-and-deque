#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

struct Queue;

// queue_create(copy, destroy, print)
//  returns a pointer to heap allocated Queue
// effects: allocates memory
// time: O(1)
struct Queue* queue_create(void* (*Copy_data) (const void*),
                           void (*Destroy_data) (void*),
                           void (*Print_data) (const void*));

// queue_destroy(q) fress the heap allocated Queue
// effects: frees memory
// time: O(n);
void queue_destroy(struct Queue* q);

// queue_empty(q) returns true if q is empty
// requires: q is not NULL
// time: O(1)
bool queue_empty(const struct Queue* q);

// queue_enqueue(q, data) enqueues data onto q
// effects: mutates q
// requires: q is not NULL
// time: O(1)
void queue_enqueue(struct Queue* q, const void* data);

// queue_dequeue(q) pops the front data from q
// effects: mutates q
// requires: q is not NULL and not empty
// time: O(1)
void queue_dequeue(struct Queue* q);

// queue_front(q) returns the front data from q
// requires: q is not NULL and not empty
// time: O(1)
void* queue_front(const struct Queue* q);

// queue_print(q) prints the queue from front to back
// effects: produces output
// requires: q is not NULL
// time: O(n)
void queue_print(const struct Queue* q);

#endif

