#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include "stack.h"

static struct Node* node_create(const int num, const char* name) {
    struct Node* node = malloc(sizeof(struct Node));
    node->key = num;
    node->name = name;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void node_destroy(struct Node* node) {
    if (node) {
        node_destroy(node->left);
        node_destroy(node->right);
        free(node);
    }
}

struct BST* bst_create() {
    struct BST* bst = malloc(sizeof(struct BST));
    bst->root = NULL;
    return bst;
}

void bst_insert(struct BST* bst, const int num, const char* name) {
    assert(bst);

    struct Node* node = node_create(num, name);       // creates a new node
    // check if tree is empty
    if (bst->root == NULL) {
        bst->root = node;
        return;
    }

    struct Node* curr = bst->root;
    while (curr != NULL) {
        if (curr->key == num) {         // key exists
            node_destroy(node);
            break;
        } else if (curr->key < num) {   // go right
            if (curr->right != NULL) {
                curr = curr->right;
            } else {
                curr->right = node;
                break;
            }
        } else {                        // go left
            if (curr->left != NULL) {
                curr = curr->left;
            } else {
                curr->left = node;
                break;
            }
        }
    }
}

static struct Node* node_remove_key(struct Node* node, const int num) {
    if (node == NULL) return node;

    if (node->key < num) {          // go right
        node->right = node_remove_key(node->right, num);
    } else if (node->key > num) {   // go left
        node->left = node_remove_key(node->left, num);
    } else {                        // found the key
        if (node->left == NULL && node->right == NULL) {        // removing leaf node
            free(node);
            return NULL;
        }
        if (node->right == NULL) {                              // node does not have right child
            struct Node* temp = node->left;
            free(node);
            return temp;
        }
        if (node->left == NULL) {                               // node does not have left child
            struct Node* temp = node->right;
            free(node);
            return temp;
        }
        // neither child is not NULL, find left-most child in the right subtree
        struct Node* prev = NULL;
        struct Node* curr = node->right;
        while (curr->left != NULL) {
            prev = curr;
            curr = curr->left;
        }
        node->key = curr->key;
        if (prev == NULL) {
            node->right = curr->right;
        } else {
            prev->left = curr->right;
        }
        free(curr);
    }
    return node;
}

void bst_remove(struct BST* bst, const int num) {
    assert(bst);

    bst->root = node_remove_key(bst->root, num);
}

static void node_count_leaf(const struct Node* node, int* leaf) {
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL) {
            *leaf += 1;
            return;
        }
        node_count_leaf(node->left, leaf);
        node_count_leaf(node->right, leaf);
    }
}

void count_leaf(const struct BST* bst, int* leaf) {
    assert(bst);
    assert(leaf);

    *leaf = 0;
    node_count_leaf(bst->root, leaf);
}

void node_count_all(const struct Node* node, int* leaf, int* total) {
    if (node != NULL) {
        *total += 1;
        if (node->left == NULL && node->right == NULL) {
            *leaf += 1;
        }
        node_count_all(node->left, leaf, total);
        node_count_all(node->right, leaf, total);
    }
}

void count_all(const struct BST* bst, int* leaf, int* total) {
    assert(bst);
    assert(leaf);
    assert(total);

    *leaf = 0;
    *total = 0;
    node_count_all(bst->root, leaf, total);
}

int node_stats(const struct Node* node, int* leaf, int* total) {
    if (node != NULL) {
        *total += 1;
        if (node->left == NULL && node->right == NULL) {
            *leaf += 1;
            return 1;       // leaf node always has height 1
        }
        int left_height = node_stats(node->left, leaf, total);
        int right_height = node_stats(node->right, leaf, total);
        if (left_height > right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    } 
    return 0;
}

int bst_stats(const struct BST* bst, int* leaf, int* total) {
    assert(bst);
    assert(leaf);
    assert(total);

    return node_stats(bst->root, leaf, total);
}

void deepest_node(struct Node* node, struct Node** deepest, int* max_depth, int curr_depth) {
    if (node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        if (curr_depth >= *max_depth) {
            *deepest = node;
            *max_depth = curr_depth;
        }
    } else {
        deepest_node(node->left, deepest, max_depth, curr_depth + 1);
        deepest_node(node->right, deepest, max_depth, curr_depth + 1);
    }
}

struct Node* bst_deepest_node(const struct BST* bst) {
    assert(bst);

    struct Node* retval = NULL;
    int depth = 0;
    deepest_node(bst->root, &retval, &depth, 0);
    return retval;
}

static void node_to_sorted_array(const struct Node* node, int* arr, int* pos) {
    if (node == NULL) {
        return;
    }
    node_to_sorted_array(node->left, arr, pos);
    arr[*pos] = node->key;
    *pos += 1;
    node_to_sorted_array(node->right, arr, pos);
}

int* bst_to_sorted_array(const struct BST* bst, int* len) {
    assert(bst);
    assert(len);
    assert(!bst->root);

    int leaf = 0;
    count_all(bst, &leaf, len);
    int * arr = malloc(sizeof(int) * *len);
    int pos = 0;
    node_to_sorted_array(bst->root, arr, &pos);
    return arr;
}

struct Node* sorted_array_to_node(const int* arr, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = start + (start - end) / 2;
    struct Node* node = node_create(arr[mid], "");
    node->left = sorted_array_to_node(arr, start, mid - 1);
    node->right = sorted_array_to_node(arr, mid + 1, end);
    return node;
}

struct BST* sorted_array_to_balanced_bst(const int* arr, const int len) {
    assert(arr);
    assert(len > 0);

    struct BST* bst = bst_create();
    bst->root = sorted_array_to_node(arr, 0, len - 1);
    return bst;
}

void bst_destroy_recursive(struct BST* bst) {
    if (bst) {
        node_destroy(bst->root);
        free(bst);
    }
}

// helper functions for using stack of generic type
static void* copy_data(const void* data) {
    const struct Node* node = data;
    struct Node* copy = malloc(sizeof(struct Node));
    copy->key = node->key;
    copy->left = node->left;
    copy->right = node->right;
    return copy;
}

static void destroy_data(void* data) {
    struct Node* node = data;
    free(node);
}

static void print_data(const void* data) {
    const struct Node* node = data;
    printf("%d", node->key);
}

/*void bst_destroy_iterative(struct BST* bst) {
    struct Stack* stk = stack_create(copy_data, destroy_data, print_data);
    if (bst && bst->root) {
        stack_push(stk, bst->root);
        free(bst->root);
        while (!stack_empty(stk)) {
            void* tos = stack_top(stk);
            struct Node* curr = tos;
            struct Node* left_child = curr->left;
            struct Node* right_child = curr->right;
            stack_pop(stk);
            if (left_child) {
                stack_push(stk, left_child);
                free(left_child);
            }
            if (right_child) {
                stack_push(stk, right_child);
                free(curr->right);
            }
        }
    }
    free(bst);
    stack_destroy(stk);
}
*/
static void node_print (struct Node* n) {
    if (n != NULL) {
        node_print (n->left);
        printf("%d ", n->key);
        node_print (n->right);
    }
}

void bst_print (struct BST* bst) {
    node_print (bst->root);
    printf("\n");
}
