#pragma once

#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

#include "common.h"

// panic code is a uint16!
// bit 1: catchable flag
// bit 2-8: catchable ID
// bit 9-16: source code 

// max width 8 bits
typedef enum {
    Panic_Main = 1,
    Panic_Parser = 2,
    Panic_Interpreter = 3,
    Panic_Stdlib = 4,
    Panic_Test = 5
} PanicCode;

// max width 7 bits
typedef enum {
    PCC_InterpreterUnknownVar,
    PCC_Test
} PanicCatchableCode;

#define _PANIC_CATCHABLE_FLAG (1 << 15)
#define _PANIC_CATCHABLE_CODE_MASK (0b1111111 << 8)
#define _PANIC_CODE_MASK 0x00FF

#define PANIC_CATCHABLE(panicCode, catchCode) _PANIC_CATCHABLE_FLAG | (catchCode << 8) | panicCode

extern jmp_buf _panicJump;

#define PANIC_TRY { _catchPanic(); uint16_t _panicRet = setjmp(_panicJump); printU16(_panicRet); if (!_panicRet) {

#define PANIC_CATCH(code) } else if ((_panicRet & _PANIC_CATCHABLE_CODE_MASK) == (code << 8)) { _releasePanic();

#define PANIC_END_TRY _panicRet = 0; } if (_panicRet) _panicFailure(_panicRet); }

// just in case 
#if defined(OCRPI_DEBUG) && OCRPI_PRINT_PANIC_CODES
static void printU16(uint16_t val) {
    printf("0b");
    for (int i = 15; i >= 0; i--) {
        if (val & (1 << i)) printf("1");
        else printf("0");
    }
    printf("\n");
}
#else
#define printU16(val)
#endif

void _catchPanic();
void _releasePanic();
void _panicFailure(uint16_t code);

void panic(uint16_t code, char* msg, ...);