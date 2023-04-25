#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "deque.h"

typedef void* (*Copy_data) (const void*);
typedef void (*Destroy_data) (void*);
typedef void (*Print_data) (const void*);

struct Queue {
    struct Deque* deq;
};

struct Queue* queue_create(Copy_data copy, Destroy_data destroy, Print_data print) {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->deq = deque_create(copy, destroy, print);
    return q;
}

void queue_destroy(struct Queue* q) {
    if (q) {
        deque_destroy(q->deq);
        free(q);
    }
}

bool queue_empty(const struct Queue* q) {
    assert(q);

    return deque_empty(q->deq);
}

void queue_enqueue(struct Queue* q, const void* data) {
    assert(q);

    insert_front(q->deq, data);
}

void queue_dequeue(struct Queue* q) {
    assert(q);
    assert(!queue_empty(q));

    remove_front(q->deq);
}

void* queue_front(const struct Queue* q) {
    assert(q);
    assert(!queue_empty(q));

    return deque_front(q->deq);
}

void queue_print(const struct Queue* q) {
    assert(q);

    deque_print_forward(q->deq);
}
