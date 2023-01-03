#include "panic.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void panic(PanicCode code, char* fmt, ...) {
    printf("\033[0;31m");
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    printf("\033[0m\n");
    exit(code);
}