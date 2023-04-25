#include "deque.h"
#include <stdio.h>
#include <stdlib.h>


char* char_cp (const char* ch) {
  char *new = malloc(sizeof(char));
  *new = *ch;
  return new;
}

void* char_cp_adt (const void* data) {
    const char* ch = data;
    char *new = char_cp (ch);
    return new;
}

void char_destroy (char* ch) {
    free(ch);
}

void char_destroy_adt (void* ch) {
    char* data = ch;
    char_destroy (data);
}

void char_print (const char* ch) {
    printf("%c\n", *ch);
}

void char_print_adt (const void* data) {
    const char* ch = data;
    char_print (ch);
}

int main() {
    struct Deque *new = deque_create(char_cp_adt, char_destroy_adt, char_print_adt);
    deque_destroy(new);
}

