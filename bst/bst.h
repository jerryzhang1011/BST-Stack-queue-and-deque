#ifndef __BST_H__
#define __BST_H__

struct Node {
    int key;
    char *name;
    struct Node* left;
    struct Node* right;
};

struct BST {
    struct Node* root;
};

// bst_create() returns a pointer to heap allocated BST
// effects: allocates memory, caller must free
// time: O(1)
struct BST* bst_create();

// bst_insert(bst, num) inserts num into bst
//  if num exists in bst already, bst remains the same
// effects: may mutate bst
// time: O(log n) if bst is balanced, otherwise O(n)
void bst_insert(struct BST* bst, const int num, const char* name);

// bst_remove(bst, num) removes num from bst
// if num does not exist in bst, bst remains the same
// effects: may mutate bst
// time: O(log n) if bst is balanced, otherwise O(n)
void bst_remove(struct BST* bst, const int num);

// count_leaf(bst, leaf) stores the number of leaf nodes of bst in leaf
// effects: mutates leaf
// requires: bst is not NULL, leaf is not NULL
// time: O(n)
void count_leaf(const struct BST* bst, int* leaf);

// count_all(bst, leaf, total)
//  stores the number of leaf nodes of bst in leaf
//  stores the total number of nodes of bst in total
// effects: mutates leaf and total
// requires: bst is not NULL, leaf is not NULL, total is not NULL
// time: O(n)
void count_all(const struct BST* bst, int* leaf, int* total);

// bst_stats(bst, leaf, total) returns the height of bst
//  stores the number of leaf nodes of bst in leaf
//  stores the total number of nodes of bst in total
// effects: mutates leaf and total
// requires: bst is not NULL, leaf is not NULL, total is not NULL
// time: O(n)
int bst_stats(const struct BST* bst, int* leaf, int* total);

// bst_deepest_node(bst) returns the pointer to the deepest node in bst
//  returns NULL is bst is empty
// requires: bst is not NULL
// time: O(n)
struct Node* bst_deepest_node(const struct BST* bst);

// bst_to_sorted_array(bst, len) 
//  returns a dynamic array containing all keys in bst in ascending order
//  stores the length of array in len
// effects: allocates memory, caller must free
//          mutates len
// requires: bst is not NULL and bst is not empty
// time: O(n)
int* bst_to_sorted_array(const struct BST* bst, int* len);

// sorted_array_to_balanced_bst(arr, len)
//  returns a balanced BST containing all elements in arr
// effects: allocates memory, caller must free
// requires: len > 0
// time: O(n)
struct BST* sorted_array_to_balanced_bst(const int* arr, const int len);

// bst_destroy_recursive(bst) frees the heap allocated bst
// effects: frees memory
// requires: use recursion only
// time: O(n)
void bst_destroy_recursive(struct BST* bst);

// bst_destroy_iterative(bst) frees the heap allocated bst
// effects: frees memory
// requires: use iteration only, use stack as a hint
// time: O(n)
void bst_destroy_iterative(struct BST* bst);

// print bst
void bst_print (struct BST* bst);

#endif
