#include "panic.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "vector.h"

jmp_buf _panicJump;
static int catchLevel = 0;

void _catchPanic()   { catchLevel++; }
void _releasePanic() { catchLevel--; }

void _panicFailure(uint16_t code) {
    printf("\033[0;31m--- UNCAUGHT ---\033[0m\n");
    exit(code & _PANIC_CODE_MASK);
}

void panic(uint16_t code, char* fmt, ...) {
#ifndef OCRPI_DEBUG
    if (catchLevel > 0 && (code & _PANIC_CATCHABLE_FLAG)) longjmp(_panicJump, code);
#endif
    printf("\033[0;31m");
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    printf("\033[0m\n");
#ifdef OCRPI_DEBUG
    if (catchLevel > 0 && (code & _PANIC_CATCHABLE_FLAG)) {
        printf("[panic caught!]\n");
        longjmp(_panicJump, code);
    }
#endif
    exit(code & _PANIC_CODE_MASK);
}