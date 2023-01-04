#include "panic.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

#include "vector.h"

jmp_buf _panicJump;
static bool shouldJump = false;

void _catchPanic()  { shouldJump = true;  }
void _releasePanic() { shouldJump = false; }

void _panicFailure(uint16_t code) {
    printf("\033[0;31m--- UNCAUGHT ---\033[0m\n");
    exit(code & _PANIC_CODE_MASK);
}

void panic(uint16_t code, char* fmt, ...) {
    if (shouldJump && (code & _PANIC_CATCHABLE_FLAG)) longjmp(_panicJump, code);
    printf("\033[0;31m");
    va_list va;
    va_start(va, fmt);
    vprintf(fmt, va);
    va_end(va);
    printf("\033[0m\n");
    exit(code & _PANIC_CODE_MASK);
}