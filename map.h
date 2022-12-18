#pragma once

#include <string.h>
#include <stdbool.h>

#include "vector.h"

#define _NewMap(name) static inline name New##name() { \
    name out; \
    INIT(out); \
    return out; \
}

#define _Find(type, name) static inline type##Option name##Find(name* map, char* key) { \
    for (int i = 0; i < map->len; i++) { \
        if (strcmp(map->root[i].key, key) == 0) return (type##Option){.value = map->root[i].value, .exists = true}; \
    } \
    return (type##Option){.exists = false}; \
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
    typedef struct { \
        type value; \
        bool exists; \
    } type##Option; \
    DECL_VEC(_##name##Entry, name) \
    _NewMap(name) \
    _Find(type, name) \
    _Set(type, name) \
    _Remove(name)
