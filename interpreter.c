#include "interpreter.h"

#include <stdlib.h>

#include "generated.h"
#include "common.h"
#include "vector.h"
#include "panic.h"

typedef struct {

} FunctionObj;

typedef struct {

} ProcObj;

DECL_VEC(FunctionObj, FuncList)
DECL_VEC(ProcObj, ProcList)

typedef struct {
    FuncList funcs; //? again, names!! THINK JADS THINK
    ProcList procs;
} ClassObj;

typedef struct {

} InstanceObj;

typedef struct InterpreterObj InterpreterObj;

DECL_VEC(InterpreterObj, ObjList);

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

typedef struct Scope Scope;

struct Scope {
    ObjList objects; //? need names at THIS LEVEL!
    Scope* parent;
};

static Scope* currentScope = NULL;

STATIC void pushScope() {
    Scope* oldScope = currentScope;
    currentScope = malloc(sizeof(Scope));
    currentScope->parent = oldScope;
    INIT(currentScope->objects);
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