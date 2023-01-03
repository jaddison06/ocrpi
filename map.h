// https://gist.github.com/jaddison06/39df5e0dd4b01a02285d57f71fa6d45e/edit

#pragma once

#include <string.h>
#include <stdbool.h>

#include "vector.h"

#define _NewMap(name) static inline name New##name() { \
    name out; \
    INIT(out); \
    return out; \
}

#define _Destroy(name) static inline void Destroy##name(name* map) { DESTROY(*map); }

#define _Find(type, name) static inline type* name##Find(name* map, char* key) { \
    for (int i = 0; i < map->len; i++) { \
        if (strcmp(map->root[i].key, key) == 0) return &map->root[i].value; \
    } \
    return NULL; \
}

#define _Set(type, name) static inline void name##Set(name* map, char* key, type value) { \
    for (int i = 0; i < map->len; i++) { \
        if (strcmp(map->root[i].key, key) == 0) { \
            map->root[i].value = value; \
            return; \
        } \
    } \
    APPEND(*map, ((_##name##Entry) {.key = key, .value = value})); \
}

#define _Remove(name) static inline void name##Remove(name* map, char* key) { \
    for (int i = 0; i < map->len; i++) { \
        if (strcmp(map->root[i].key, key) == 0) { \
            REMOVE(*map, i); \
            return; \
        } \
    } \
}

#define DECL_MAP(type, name) \
    typedef struct { \
        char* key; \
        type value; \
    } _##name##Entry; \
    DECL_VEC(_##name##Entry, name) \
    _NewMap(name) \
    _Destroy(name) \
    _Find(type, name) \
    _Set(type, name) \
    _Remove(name)
