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

typedef void (*NativeProc)();
typedef InterpreterObj (*NativeFunc)();

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
        NativeFunc nativeFunc;
        NativeProc nativeProc;
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

STATIC INLINE Scope* globalScope() {
    Scope* scope = currentScope;
    while (scope->parent != NULL) scope = scope->parent;
    return scope;
}

STATIC void interpretBlock(DeclList block);

STATIC InterpreterObj interpretExpr(Expression expr) {
    InterpreterObj out;

    switch (expr.tag) {
        case ExprTag_Unary: {
            break;
        }
        case ExprTag_Binary: {
            break;
        }
        case ExprTag_Call: {
            switch (expr.call.tag) {
                case Call_Call: {
                    InterpreterObj callee = interpretExpr(*expr.call.callee);
                    if (!(
                        callee.tag == ObjType_Func ||
                        callee.tag == ObjType_Proc ||
                        callee.tag == ObjType_NativeFunc ||
                        callee.tag == ObjType_NativeProc
                    )) {
                        panic(Panic_Interpreter, "Can't call this object!");
                    }
                    break;
                }
                case Call_GetMember: {
                    break;
                }
                case Call_Array: {
                    break;
                }
            }
            break;
        }
        case ExprTag_Super: {
            break;
        }
        case ExprTag_Grouping: {
            interpretExpr(*expr.grouping);
            break;
        }
        case ExprTag_Primary: {
            char* text = tokText(expr.primary);
            switch (expr.primary.type) {
                case Tok_StringLit: {
                    // strip leading & trailing quotes!
                    char* stringContents = malloc(strlen(text) - 1);
                    memcpy(stringContents, text + 1, strlen(text) - 2);
                    stringContents[strlen(text) - 2] = 0;
                    out = (InterpreterObj){
                        .tag = ObjType_String,
                        .string = stringContents
                    };
                    break;
                }
                case Tok_IntLit: {
                    out = (InterpreterObj){
                        .tag = ObjType_Int,
                        .int_ = atoi(text)
                    };
                    break;
                }
                case Tok_FloatLit: {
                    out = (InterpreterObj){
                        .tag = ObjType_Float,
                        .float_ = strtof(text, NULL)
                    };
                    break;
                }
                case Tok_Identifier: {
                    Scope* searchScope = currentScope;
                    InterpreterObjOption obj;
                    while (searchScope != NULL) {
                        obj = ObjNSFind(&searchScope->objects, text);
                        if (obj.exists) break;
                        searchScope = searchScope->parent;
                    }
                    if (searchScope == NULL) {
                        char* prefix = "Unknown variable ";
                        char* error = malloc(strlen(prefix) + strlen(text) + 3);
                        sprintf(error, "%s%s!\n", prefix, error);
                        panic(Panic_Interpreter, error);
                    }
                    out = obj.value;
                    break;
                }
            }
            free(text);
            break;
        }
    }
    return out;
}

STATIC bool isTruthy(Expression expr) {
    InterpreterObj result = interpretExpr(expr);

}

STATIC void interpretStmt(Statement stmt) {
    switch (stmt.tag) {
        case StmtTag_Expr: {
            interpretExpr(stmt.expr);
            break;
        }
        case StmtTag_Global: {
            ObjNSSet(&globalScope()->objects, tokText(stmt.global.name), interpretExpr(stmt.global.initializer));
            break;
        }
        case StmtTag_For: {
            pushScope();
            ObjNSSet(&currentScope->objects, tokText(stmt.for_.iterator), interpretExpr(stmt.for_.min));
            Expression iterator = (Expression){
                .tag = ExprTag_Primary,
                .primary = stmt.for_.iterator,
            };
            Expression cond = (Expression){
                .tag = ExprTag_Binary,
                .binary = (BinaryExpr){
                    .a = &iterator,
                    .b = &stmt.for_.max,
                    .operator = (Token){
                        .line = 0,
                        .col = 0,
                        .start = "<",
                        .length = 1,
                        .type = Tok_Less
                    }
                }
            };
            Expression incr = (Expression){
                .tag = ExprTag_Binary,
                .binary = (BinaryExpr){
                    .a = &iterator,
                    .b = copyExpr((Expression){
                        .tag = ExprTag_Primary,
                        .primary = (Token){
                            .line = 0,
                            .col = 0,
                            .start = "1",
                            .length = 1,
                            .type = Tok_IntLit
                        }
                    }),
                    .operator = (Token){
                        .line = 0,
                        .col = 0,
                        .start = "+=",
                        .length = 2,
                        .type = Tok_PlusEqual
                    }
                }
            };
            while (isTruthy(cond)) {
                interpretBlock(*stmt.for_.block);
                interpretExpr(incr);
            }
            free(incr.binary.b);
            popScope();
            break;
        }
        case StmtTag_While: {
            while (isTruthy(stmt.while_.condition)) {
                interpretBlock(*stmt.while_.block);
            }
            break;
        }
        case StmtTag_Do: {
            //* yikes!! not a do-while but a do-until!
            while (!isTruthy(stmt.do_.condition)) {
                interpretBlock(*stmt.do_.block);
            }
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
    ObjNSSet(&currentScope->objects, tokText(proc.name), (InterpreterObj){
        .tag = ObjType_Proc,
        .proc = proc
    });
}

STATIC void interpretFun(FunDecl func) {
    ObjNSSet(&currentScope->objects, tokText(func.name), (InterpreterObj){
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