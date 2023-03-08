#include "alloc.h"
#include "common.h"
#include "backtrace.h"

void* alloc(size_t size) {
    void* out = malloc(size);
#ifdef OCRPI_DEBUG
    printf("Allocated %i bytes at %p\n", size, out);
    BACKTRACE(5);
#endif
    return out;
}