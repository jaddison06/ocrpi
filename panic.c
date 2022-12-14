#include "panic.h"

#include <stdio.h>

void panic(PanicCode code, char* msg) {
    printf("\033[0;31m%s\033[0m\n", msg);
    exit(code);
}