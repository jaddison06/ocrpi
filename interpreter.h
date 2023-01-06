#pragma once

#include "parser.h"
#include "vector.h"
#include "map.h"
#include "generated.h"

typedef struct InterpreterObj InterpreterObj;
DECL_VEC(InterpreterObj, ObjList);

DECL_MAP(FunDecl, FuncNS)
DECL_MAP(ProcDecl, ProcNS)

typedef void (*NativeProc)(ObjList);
typedef InterpreterObj (*NativeFunc)(ObjList);

typedef struct {
    FuncNS funcs;
    ProcNS procs;
} ClassObj;

typedef struct {
    ClassObj class;
} InstanceObj;

struct InterpreterObj {
    ObjType tag;
    union {
        char* string;
        bool bool_;
        int int_;
        float float_;
        FunDecl func;
        ProcDecl proc;
        NativeFunc nativeFunc;
        NativeProc nativeProc;
        ClassObj class;
        ObjList array;
        InstanceObj instance;
        InterpreterObj* reference;
    };
};

InterpreterObj interpretExpr(Expression expr);
bool isTruthy(InterpreterObj obj);
void interpret(ParseOutput po);