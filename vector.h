// https://gist.github.com/jaddison06/f9288ab0e138421cf38fcca12ac49a6c

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// doesn't do any additional typedefs so theoretically ur in the clear
// to have multiple identical vec types. probs best not to tho -
// keep this in .c files where poss
#define DECL_VEC(type, name) typedef struct name { \
    type* root; \
    int len, cap; \
    type* elemTempStorage; \
} name;

#define DECL_VEC_NO_TYPEDEF(type, name) struct name { \
    type* root; \
    int len, cap; \
    type* elemTempStorage; \
};

#define INIT(vec) do { \
    (vec).root = malloc(sizeof(*(vec).root)); \
    (vec).cap = 1; \
    (vec).len = 0; \
    (vec).elemTempStorage = malloc(sizeof(*(vec).root)); \
} while(0)

#define DESTROY(vec) do { \
    free((vec).root); \
    free((vec).elemTempStorage); \
} while(0)

#define FOREACH(type, iterator, vec) for (type iterator = vec.root; iterator - vec.root < vec.len; iterator++)


// new and improved! can take an rvalue - no need to pass in temporary variables!!
//
// when passing struct literals w/ multiple members put BRACKETS around them - i know
// what you mean but the precompiler doesn't :(
#define APPEND(vec, item) do { \
    *(vec).elemTempStorage = (item); \
    _append((void**)&((vec).root), (vec).elemTempStorage, sizeof(*(vec).elemTempStorage), &(vec).len, &(vec).cap); \
} while(0)

static void _append(void** vec, void* item, size_t size, int* currentLength, int* currentCapacity) {
    if (*currentLength == *currentCapacity) {
        *vec = realloc(*vec, *currentCapacity * size * 2);
        *currentCapacity *= 2;
    }
    memcpy(&((*(char**)vec)[(*currentLength) * size]), item, size);
    *currentLength += 1;
}

#define REMOVE(vec, idx) do { \
    memcpy(&(vec).root[idx], &(vec).root[idx + 1], sizeof(*(vec).root) * ((vec).len - idx - 1)); \
    (vec).len--; \
} while(0)
