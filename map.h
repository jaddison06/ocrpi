#pragma once

#include "string.h"

#include "vector.h"

#define DECL_MAP(type, name) \
    typedef Map name; \
    static inline type* name##Find(name map, char* key) { return (type*)_mapFind(map, key); } \
    static inline void name##Set(name map, char* key, type* value) { _mapSet(map, key, (void*)value); } \
    static inline void name##Remove(name map, char* key) { _mapRemove(map, key); }

typedef struct {
    char* name;
    void* value;
} _MapEntry;

DECL_VEC(_MapEntry, Map)

static inline Map NewMap() {
    Map out;
    INIT(out);
    return out;
}

static inline int _mapFindIdx(Map map, char* key) {
    for (int i = 0; i < map.len; i++) {
        if (strcmp(map.root[i].name, key) == 0) return i;
    }
    return -1;
}

static inline void** _mapFindValue(Map map, char* key) {
    for (int i = 0; i < map.len; i++) {
        if (strcmp(map.root[i].name, key) == 0) return &map.root[i].value;
    }
    return NULL;
}

static inline void* _mapFind(Map map, char* key) {
    void** pos = _mapFindValue(map, key);
    if (pos == NULL) return NULL;
    return *pos;
}

static inline void _mapSet(Map map, char* key, void* value) {
    void** pos = _mapFindValue(map, key);
    if (pos == NULL) {
        APPEND(map, ((_MapEntry){
            .name = key,
            .value = value
        }));
    } else {
        *pos = value;
    }
}

static inline void _mapRemove(Map map, char* key) {
    int idx = _mapFindIdx(map, key);
    if (idx >= 0) {
        REMOVE(map, idx);
    }
}