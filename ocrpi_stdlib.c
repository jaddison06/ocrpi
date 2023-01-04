#include "ocrpi_stdlib.h"

static void printObj(InterpreterObj obj) {
    switch (obj.tag) {
        case ObjType_Ref: {
            printf("<reference -> ");
            printObj(*obj.reference);
            printf(">");
            break;
        }
        case ObjType_Class: {
            printf("<class at %p>", &obj);
            break;
        }
        case ObjType_Func: {
            printf("<func at %p>", &obj);
        }
        case ObjType_Proc: {
            printf("<proc at %p>", &obj);
            break;
        }
        case ObjType_NativeFunc: {
            printf("<native func at %p>", &obj);
            break;
        }
        case ObjType_NativeProc: {
            printf("<native proc at %p>", &obj);
            break;
        }
        case ObjType_Nil: {
            printf("nil");
            break;
        }
        case ObjType_Int: {
            printf("%i", obj.int_);
            break;
        }
        case ObjType_String: {
            printf("%s", obj.string);
            break;
        }
        case ObjType_Float: {
            printf("%f", obj.float_);
        }
        case ObjType_Array: {
            printf("[");
            for (int i = 0; i < obj.array.len; i++) {
                printObj(obj.array.root[i]);
                if (i != obj.array.len - 1) printf(", ");
            }
            printf("]");
            break;
        }
        case ObjType_Instance: {
            printf("<class instance at %p>", &obj);
            break;
        }
    }
}

void stl_print(ObjList args) {
    for (int i = 0; i < args.len; i++) {
        printObj(args.root[i]);
    }
    printf("\n");
}