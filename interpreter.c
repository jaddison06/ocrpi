#include "interpreter.h"

#include <stdlib.h>

#include "generated.h"
#include "common.h"
#include "map.h"
#include "panic.h"

typedef struct InterpreterObj InterpreterObj;
DECL_VEC(InterpreterObj, ObjList);

typedef struct {

} FunctionObj;

typedef struct {

} ProcObj;

DECL_MAP(FunctionObj, FuncNS)
DECL_MAP(ProcObj, ProcNS)

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
        int int_;
        float float_;
        FunctionObj func;
        ProcObj proc;
        ClassObj class;
        ObjList array;
        InstanceObj instance;
    };
};

DECL_MAP(InterpreterObj, ObjNS);

typedef struct Scope Scope;

struct Scope {
    ObjNS objects;
    Scope* parent;
};

static Scope* currentScope = NULL;

STATIC void pushScope() {
    Scope* oldScope = currentScope;
    currentScope = malloc(sizeof(Scope));
    currentScope->parent = oldScope;
    currentScope->objects = NewObjNS();
}

STATIC void popScope() {
    Scope* parentScope = currentScope->parent;
    if (parentScope == NULL) panic(Panic_Interpreter, "Can't exit the root scope!");
    DESTROY(currentScope->objects);
    free(currentScope);
    currentScope = parentScope;
}

STATIC void interpretStmt(Statement stmt) {

}

STATIC void interpretProc(ProcDecl proc) {
    
}

STATIC void interpretFun(FunDecl func) {
    
}

STATIC void interpretClass(ClassDecl class) {

}


void interpret(ParseOutput po) {
    pushScope();
    
    for (int i = 0; i < po.ast.len; i++) {
        Declaration currentDecl = po.ast.root[i];
        switch (currentDecl.tag) {
            case DeclTag_Class: {
                interpretClass(currentDecl.class);
                break;
            }
            case DeclTag_Fun: {
                interpretFun(currentDecl.fun);
                break;
            }
            case DeclTag_Proc: {
                interpretProc(currentDecl.proc);
                break;
            }
            case DeclTag_Stmt: {
                interpretStmt(currentDecl.stmt);
                break;
            }
        }
    }
}