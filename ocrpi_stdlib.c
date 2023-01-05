#include "ocrpi_stdlib.h"

#include <stdlib.h>

#include "panic.h"

#define ANY -1

static inline void checkTypes(int count, ObjType types[], ObjList arguments) {
    if (arguments.len != count) panic(Panic_Stdlib, "Expected %i arguments but got %i!", count, arguments.len);
    for (int i = 0; i < count; i++) {
        if (types[i] == ANY) continue;
        if (arguments.root[i].tag != types[i]) panic(Panic_Stdlib, "Expected argument of type %s, but got %s!", ObjTypeToString(types[i]), ObjTypeToString(arguments.root[i].tag));
    }
}

#define TYPELIST(types) (ObjType[]){types}

static char* objToString(InterpreterObj obj) {
    switch (obj.tag) {
        case ObjType_Ref: {
            return "<reference>";
            // printf("<reference -> ");
            // printObj(*obj.reference);
            // printf(">");
        }
        case ObjType_Class: {
            return "<class>";
            // printf("<class at %p>", &obj);
        }
        case ObjType_Func: {
            return "<func>";
            // printf("<func at %p>", &obj);
        }
        case ObjType_Proc: {
            return "<proc>";
            // printf("<proc at %p>", &obj);
        }
        case ObjType_NativeFunc: {
            return "<native func>";
            // printf("<native func at %p>", &obj);
        }
        case ObjType_NativeProc: {
            return "<native proc>";
            // printf("<native proc at %p>", &obj);
        }
        case ObjType_Nil: {
            return "nil";
        }
        case ObjType_Bool: {
            return obj.bool_ ? "true" : "false";
        }
        case ObjType_Int: {
            // todo: enough?
            char* buf = malloc(20);
            sprintf(buf, "%i", obj.int_);
            return buf;
        }
        case ObjType_String: {
            return obj.string;
        }
        case ObjType_Float: {
            // todo: enough?
            char* buf = malloc(40);
            sprintf(buf, "%f", obj.float_);
            return buf;
        }
        case ObjType_Array: {
            int len = 1;
            int cap = 1;
            char* buf = malloc(1);
            buf[0] = '[';
            for (int i = 0; i < obj.array.len; i++) {
                char* thisObj = objToString(obj.array.root[i]);
                int thisLen = strlen(thisObj);
                while (len + thisLen + 2 > cap) buf = realloc(buf, cap * 2);
                memcpy(buf + len, thisObj, thisLen);
                len += thisLen;
                if (i != obj.array.len - 1) memcpy(buf + len, ", ", 2);
                len += 2;
            }
            if (cap - len < 2) buf = realloc(buf, cap - (2 - (cap - len)));
            buf[len] = ']';
            buf[len + 1] = '\0';
            return buf;
        }
        case ObjType_Instance: {
            return "<class instance>";
            // printf("<class instance at %p>", &obj);
        }
    }
}

void stl_print(ObjList args) {
    for (int i = 0; i < args.len; i++) {
        printf("%s", objToString(args.root[i]));
    }
    printf("\n");
}

InterpreterObj stl_typeof(ObjList args) {
    checkTypes(1, TYPELIST(ANY), args);
    return (InterpreterObj){
        .tag = ObjType_String,
        .string = ObjTypeToString(args.root[0].tag)
    };
}

InterpreterObj stl_bool(ObjList args) {
    checkTypes(1, TYPELIST(ANY), args);
    return (InterpreterObj){
        .tag = ObjType_Bool,
        .bool_ = isTruthy(args.root[0])
    };
}

InterpreterObj stl_string(ObjList args) {
    checkTypes(1, TYPELIST(ANY), args);
    return (InterpreterObj){
        .tag = ObjType_String,
        .string = objToString(args.root[0])
    };
}

InterpreterObj stl_float(ObjList args) {
    checkTypes(1, TYPELIST(ANY), args);
    float out;
    InterpreterObj obj = args.root[0];
    switch (obj.tag) {
        case ObjType_String: {
            out = atof(obj.string);
            break;
        }
        case ObjType_Int: {
            out = obj.int_;
            break;
        }
        case ObjType_Float: {
            out = obj.float_;
            break;
        }
        case ObjType_Nil: {
            out = 0.0f;
            break;
        }
        default: panic(Panic_Stdlib, "Can't convert a %s to a float!", ObjTypeToString(obj.tag));
    }
    return (InterpreterObj){
        .tag = ObjType_Float,
        .float_ = out
    };
}

InterpreterObj stl_int(ObjList args) {
    checkTypes(1, TYPELIST(ANY), args);
    int out;
    InterpreterObj obj = args.root[0];
    switch (obj.tag) {
        case ObjType_String: {
            out = atoi(obj.string);
            break;
        }
        case ObjType_Int: {
            out = obj.int_;
            break;
        }
        case ObjType_Float: {
            out = obj.float_;
            break;
        }
        case ObjType_Nil: {
            out = 0;
            break;
        }
        default: panic(Panic_Stdlib, "Can't convert a %s to an int!", ObjTypeToString(obj.tag));
    }
    return (InterpreterObj){
        .tag = ObjType_Int,
        .int_ = out
    };
}