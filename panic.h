#pragma once

typedef enum {
    Panic_Main = 1,
    Panic_Parser = 2,
    Panic_Interpreter = 3
} PanicCode;

void panic(PanicCode code, char* msg);