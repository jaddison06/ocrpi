#include "interpreter.h"

#include <stdlib.h>

#include "generated.h"
#include "common.h"
#include "map.h"
#include "panic.h"

typedef struct InterpreterObj InterpreterObj;
DECL_VEC(InterpreterObj, ObjList);

DECL_MAP(FunDecl, FuncNS)
DECL_MAP(ProcDecl, ProcNS)

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
        FunDecl func;
        ProcDecl proc;
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

STATIC void interpretBlock(DeclList block);

STATIC void interpretExpr(Expression expr) {
    
}

STATIC bool isTruthy(Expression expr) {

}

STATIC void interpretStmt(Statement stmt) {
    switch (stmt.tag) {
        case StmtTag_Expr: {
            interpretExpr(stmt.expr);
            break;
        }
        case StmtTag_Global: {
            break;
        }
        case StmtTag_For: {
            break;
        }
        case StmtTag_While: {
            break;
        }
        case StmtTag_Do: {
            break;
        }
        case StmtTag_If: {
            if (isTruthy(stmt.if_.primary.condition)) {
                interpretBlock(*stmt.if_.primary.block);
            } else {
                for (int i = 0; i < stmt.if_.secondary.len; i++) {
                    if (isTruthy(stmt.if_.secondary.root[i].condition)) {
                        interpretBlock(*stmt.if_.secondary.root[i].block);
                        break;
                    }
                }
                if (stmt.if_.hasElse && isTruthy(stmt.if_.else_.condition)) {
                    interpretBlock(*stmt.if_.else_.block);
                }
            }
            break;
        }
        case StmtTag_Switch: {
            break;
        }
        case StmtTag_Array: {
            break;
        }
    }
}

STATIC void interpretProc(ProcDecl proc) {
    ObjNSSet(currentScope, tokText(proc.name), (InterpreterObj){
        .tag = ObjType_Proc,
        .proc = proc
    });
}

STATIC void interpretFun(FunDecl func) {
    ObjNSSet(currentScope, tokText(func.name), (InterpreterObj){
        .tag = ObjType_Func,
        .func = func
    });
}

STATIC void interpretClass(ClassDecl class) {

}

STATIC void interpretBlock(DeclList block) {
    for (int i = 0; i < block.len; i++) {
        Declaration currentDecl = block.root[i];
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

void interpret(ParseOutput po) {
    pushScope();
    interpretBlock(po.ast);
    popScope();
}