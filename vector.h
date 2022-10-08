// https://gist.github.com/jaddison06/f9288ab0e138421cf38fcca12ac49a6c

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define APPEND(vec, item) _append((void**)&((vec).root), &(item), sizeof(item), &(vec).len, &(vec).cap)

#define REMOVE(vec, idx) do { \
    memcpy(&(vec).root[idx], &(vec).root[idx + 1], sizeof(*(vec).root) * ((vec).len - idx - 1)); \
    (vec).len--; \
} while(0)

#define INIT(vec) do { \
    vec.root = malloc(sizeof(*vec.root)); \
    vec.cap = 1; \
    vec.len = 0; \
} while(0)

#define DESTROY(vec) free(vec.root)

// doesn't do any additional typedefs so theoretically ur in the clear
// to have multiple identical vec types. probs best not to tho -
// keep this in .c files where poss
#define DECL_VEC(type, name) typedef struct name { \
    type* root; \
    int len, cap; \
} name;

void _append(void** vec, void* item, size_t size, int* currentLength, int* currentCapacity) {
    if (*currentLength == *currentCapacity) {
        *vec = realloc(*vec, *currentCapacity * size * 2);
        *currentCapacity *= 2;
    }
    memcpy(&((*(char**)vec)[(*currentLength) * size]), item, size);
    *currentLength += 1;
}