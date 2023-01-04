#pragma once

typedef enum {
    Panic_Main = 1,
    Panic_Parser = 2,
    Panic_Interpreter = 3,
    Panic_Stdlib = 4
} PanicCode;

void panic(PanicCode code, char* msg, ...);