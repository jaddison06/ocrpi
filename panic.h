#pragma once

#include <setjmp.h>
#include <stdint.h>

// panic code is a uint16!
// bit 1: catchable flag
// bit 2-8: catchable ID
// bit 9-16: source code 

// max width 8 bits
typedef enum {
    Panic_Main = 1,
    Panic_Parser = 2,
    Panic_Interpreter = 3,
    Panic_Stdlib = 4
} PanicCode;

// max width 7 bits
typedef enum {
    PCC_InterpreterUnknownVar
} PanicCatchableCode;

#define _PANIC_CATCHABLE_FLAG 1 << 15
#define _PANIC_CATCHABLE_ID_MASK 0b1111111 << 14
#define _PANIC_CODE_MASK 0x00FF

#define PANIC_CATCHABLE(code, catchID) _PANIC_CATCHABLE_FLAG | (catchID << 14) | code

jmp_buf _panicJump;

#define PANIC_TRY { _catchPanic(); uint16_t _panicRet = setJmp(_panicJump); bool caught = false; if (!_panicRet) {

#define PANIC_CATCH(code) } else if ((_panicRet & _PANIC_CATCHABLE_ID_MASK) == (code >> 14)) { caught = true;

#define PANIC_END_TRY } if (!caught) { _panicFailure(); } _releasePanic(); }

void _catchPanic();
void _releasePanic();
void _panicFailure();

void panic(uint16_t code, char* msg, ...);