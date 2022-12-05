// https://gist.github.com/jaddison06/4508382d4595570b485a8390d986540e

#pragma once

#include "common.h"

#if OCRPI_DEBUG

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

#else // OCRPI_DEBUG

#define BACKTRACE(length)

#endif