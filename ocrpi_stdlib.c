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

//* cheeky!! allocates!!
INLINE char* forceString(InterpreterObj obj) {
    if (obj.tag != ObjType_String) panic(Panic_Stdlib, "Can't force get a C String from a %s!", ObjTypeToString(obj.tag));
    char* out = malloc(obj.string.length + 1);
    memcpy(out, obj.string.start, obj.string.length);
    out[obj.string.length] = '\0';
    return out;
}

static StringObj objToString(InterpreterObj obj) {
    char* out;
    bool allocated = false;
    int length = -1;

    switch (obj.tag) {
        case ObjType_Ref: {
            out = "<reference>";
            // printf("<reference -> ");
            // printObj(*obj.reference);
            // printf(">");
            break;
        }
        case ObjType_Class: {
            out = "<class>";
            // printf("<class at %p>", &obj);
            break;
        }
        case ObjType_Func: {
            out = "<func>";
            // printf("<func at %p>", &obj);
            break;
        }
        case ObjType_Proc: {
            out = "<proc>";
            // printf("<proc at %p>", &obj);
            break;
        }
        case ObjType_NativeFunc: {
            out = "<native func>";
            // printf("<native func at %p>", &obj);
            break;
        }
        case ObjType_NativeProc: {
            out = "<native proc>";
            // printf("<native proc at %p>", &obj);
            break;
        }
        case ObjType_Nil: {
            out = "nil";
            break;
        }
        case ObjType_Bool: {
            out = obj.bool_ ? "true" : "false";
            break;
        }
        case ObjType_Int: {
            // todo: enough?
            out = malloc(20);
            sprintf(out, "%i", obj.int_);
            allocated = true;
            break;
        }
        case ObjType_String: {
            //* yeah okay basically the vibe is we're returning a strong independent young object, if it's allocated
            //* it'll get freed at some point so it needs to own its string ref!!
            if (obj.string.allocated) {
                out = malloc(obj.string.length);
                memcpy(out, obj.string.start, obj.string.length);
                allocated = true;
                length = obj.string.length;
            } else {
                return obj.string;
            }
            break;
        }
        case ObjType_Float: {
            // todo: enough?
            char* out = malloc(40);
            sprintf(out, "%f", obj.float_);
            allocated = true;
            break;
        }
        case ObjType_Array: {
            // todo: use length instead of null-term
            int len = 1;
            int cap = 1;
            out = malloc(1);
            out[0] = '[';
            for (int i = 0; i < obj.array.len; i++) {
                StringObj thisObj = objToString(obj.array.root[i]);
                while (len + thisObj.length + 2 > cap) out = realloc(out, cap * 2);
                memcpy(out + len, thisObj.start, thisObj.length);
                len += thisObj.length;
                if (i != obj.array.len - 1) memcpy(out + len, ", ", 2);
                len += 2;
            }
            if (cap - len < 2) out = realloc(out, cap - (2 - (cap - len)));
            out[len] = ']';
            out[len + 1] = '\0';
            break;
        }
        case ObjType_Instance: {
            out = "<class instance>";
            // printf("<class instance at %p>", &obj);
            break;
        }
    }
    return (StringObj){
        .length = length == -1 ? strlen(out) : length,
        .start = out,
        .allocated = allocated
    };
}

void stl_print(ObjList args) {
    for (int i = 0; i < args.len; i++) {
        // todo: what the fuck!!
        InterpreterObj strObj = (InterpreterObj){.tag = ObjType_String, .string = objToString(args.root[i])};
        char* str = forceString(strObj);
        printf("%s", str);
        if (strObj.string.allocated) {
            free(strObj.string.start);
        }
        free(str);
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
            char* str = forceString(obj);
            out = atof(str);
            free(str);
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
            char* str = forceString(obj);
            out = atoi(str);
            free(str);
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