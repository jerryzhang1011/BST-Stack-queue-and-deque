#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "deque.h"

typedef void* (*Copy_data) (const void*);
typedef void (*Destroy_data) (void*);
typedef void (*Print_data) (const void*);

typedef struct Node {
    void* data;
    struct Node* prev;
    struct Node* next;
} Node;

static Node* node_create(const void* data, Copy_data copy) {
    Node* node = malloc(sizeof(Node));
    node->data = copy(data);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

static void node_destroy(Node* node, Destroy_data destroy) {
    if (node != NULL) {
        node_destroy(node->next, destroy);
        destroy(node->data);
        free(node);
    }
}

struct Deque {
    Node* head;
    Node* tail;
    Copy_data copy;
    Destroy_data destroy;
    Print_data print;
};

struct Deque* deque_create(Copy_data copy, Destroy_data destroy, Print_data print) {
    struct Deque* deq = malloc(sizeof(struct Deque));
    deq->head = NULL;
    deq->tail = NULL;
    deq->copy = copy;
    deq->destroy = destroy;
    deq->print = print;
    return deq;
}

void deque_destroy(struct Deque* deq) {
    if (deq != NULL) {
        node_destroy(deq->head, deq->destroy);
        free(deq);
    }
}

bool deque_empty(const struct Deque* deq) {
    assert(deq);

    return deq->head == NULL;
}

void insert_front(struct Deque* deq, const void* data) {
    assert(deq);

    Node* node = node_create(data, deq->copy);
    if (deq->head == NULL) {
        deq->head = node;
        deq->tail = node;
    } else {
        node->next = deq->head;
        deq->head = node;
    }
}

void insert_back(struct Deque* deq, const void* data) {
    assert(deq);

    Node* node = node_create(data, deq->copy);
    if (deq->tail == NULL) {
        deq->tail = node;
        deq->head = node;
    } else {
        deq->tail->next = node;
        deq->tail = node;
    }
}

void remove_front(struct Deque* deq) {
    assert(deq);
    assert(!deque_empty(deq));

    Node* temp = deq->head;
    deq->head = deq->head->next;
    if (deq->head) {
        deq->head->prev = NULL;
    } else {
        deq->tail = NULL;
    }
    deq->destroy(temp->data);
    free(temp);
}

void remove_back(struct Deque* deq) {
    assert(deq);
    assert(!deque_empty(deq));

    Node* temp = deq->tail;
    deq->tail = deq->tail->prev;
    if (deq->tail) {
        deq->tail->next = NULL;
    } else {
        deq->head = NULL;
    }
    deq->destroy(temp->data);
    free(temp);
}

void* deque_front(const struct Deque* deq) {
    assert(deq);
    assert(!deque_empty(deq));

    return deq->head->data;
}

void* deque_back(const struct Deque* deq) {
    assert(deq);
    assert(!deque_empty(deq));

    return deq->tail->data;
}

void deque_print_forward(const struct Deque* deq) {
    assert(deq);

    printf("[");
    if (!deque_empty(deq)) {
        deq->print(deq->head->data);
        Node* curr = deq->head->next;
        while (curr) {
            printf(" -> ");
            deq->print(curr->data);
            curr = curr->next;
        }
    } else {
        printf("empty");
    }
    printf("]\n");
}

void deque_print_backward(const struct Deque* deq) {
    assert(deq);

    printf("[");
    if (!deque_empty(deq)) {
        deq->print(deq->tail->data);
        Node* curr = deq->tail->prev;
        while (curr) {
            printf(" <- ");
            deq->print(curr->data);
            curr = curr->prev;
        }
    } else {
        printf("empty");
    }
    printf("]\n");
}


