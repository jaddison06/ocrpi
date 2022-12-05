// https://gist.github.com/jaddison06/4508382d4595570b485a8390d986540e

#pragma once

#if BACKTRACE_ENABLED

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#define BACKTRACE(length) \
    do { \
        void* buf[length]; \
        char **strings; \
        int size = backtrace(buf, length); \
        strings = backtrace_symbols(buf, size); \
        if (strings != NULL) { \
            printf("--- BACKTRACE ---\n"); \
            for (int i = 0; i < size; i++) { \
                printf("%i | %s\n", i, strings[i]); \
            } \
        } \
        free(strings); \
    } while(false)

#else // BACKTRACE_ENABLED

#define BACKTRACE(length)

#endif