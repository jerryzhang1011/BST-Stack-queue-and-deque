#include "bst.h"

int main() {
    struct BST* bst = bst_create();
    for (int i = 0; i < 10; i++) {
        bst_insert(bst, i, "");
    }
    bst_print(bst);
    bst_destroy_recursive(bst);
}
