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

DECL_MAP(InterpreterObj, ObjNS);

typedef struct Scope Scope;

struct Scope {
    ObjNS objects;
    Scope* parent;
};

static Scope* currentScope = NULL;
static Scope* _globalScope = NULL;

STATIC void pushScope() {
    Scope* oldScope = currentScope;
    currentScope = malloc(sizeof(Scope));
    currentScope->parent = oldScope;
    currentScope->objects = NewObjNS();
    if (oldScope == NULL) _globalScope = currentScope;
}

STATIC void popScope() {
    Scope* parentScope = currentScope->parent;
    if (parentScope == NULL) panic(Panic_Interpreter, "Can't exit the root scope!");
    DESTROY(currentScope->objects);
    free(currentScope);
    currentScope = parentScope;
}

STATIC void interpretDecl(Declaration decl);
STATIC void interpretBlock(DeclList block);

INLINE void setVar(char* name, InterpreterObj value) {
    ObjNSSet(&currentScope->objects, name, value);
}

STATIC InterpreterObj* interpretExpr(Expression expr) {
    InterpreterObj* out;

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
                    InterpreterObj* calleeObj = interpretExpr(*expr.call.callee);
                    if (!(
                        calleeObj->tag == ObjType_Func ||
                        calleeObj->tag == ObjType_Proc ||
                        calleeObj->tag == ObjType_NativeFunc ||
                        calleeObj->tag == ObjType_NativeProc
                    )) {
                        panic(Panic_Interpreter, "Can't call this object!");
                    }
                    switch (calleeObj->tag) {
                        case ObjType_Func: {
                            Scope* outerScope = currentScope;
                            // no closures for you!!
                            currentScope = _globalScope;
                            if (expr.call.arguments.len != calleeObj->func.params.len)
                            pushScope();

                                panic(Panic_Interpreter, "Called function %s with %i args instead of %i", tokText(calleeObj->func.name), expr.call.arguments.len, calleeObj->func.params.len);

                            for (int i = 0; i < expr.call.arguments.len; i++) {
                                InterpreterObj* arg = interpretExpr(expr.call.arguments.root[i]);
                                if (calleeObj->func.params.root[i].passMode == Param_byRef) {
                                    setVar(tokText(calleeObj->func.params.root[i].name), (InterpreterObj){
                                        .tag = ObjType_Ref,
                                        .reference = arg
                                    });
                                } else {
                                    setVar(tokText(calleeObj->func.params.root[i].name), *arg);
                                }
                            }

                            for (int i = 0; i < calleeObj->func.block.len; i++) {
                                DeclOrReturn currentDOR = calleeObj->func.block.root[i];
                                if (currentDOR.tag == DOR_return) {
                                    out = interpretExpr(currentDOR.return_);
                                    break;
                                }
                                interpretDecl(*currentDOR.declaration);
                            }

                            popScope();
                            currentScope = outerScope;

                            break;
                        }
                        case ObjType_Proc: {

                        }
                        case ObjType_NativeFunc: {
                            
                        }
                        case ObjType_NativeProc: {

                        }
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
                // todo: handle self
                case Tok_Nil: {
                    out->tag = ObjType_Nil;
                    break;
                }
                case Tok_StringLit: {
                    // strip leading & trailing quotes!
                    char* stringContents = malloc(strlen(text) - 1);
                    memcpy(stringContents, text + 1, strlen(text) - 2);
                    stringContents[strlen(text) - 2] = 0;
                    out->tag = ObjType_String;
                    out->string = stringContents;
                    break;
                }
                case Tok_IntLit: {
                    out->tag = ObjType_Int;
                    out->int_ = atoi(text);
                    break;
                }
                case Tok_FloatLit: {
                    out->tag = ObjType_Float;
                    out->float_ = strtof(text, NULL);
                    break;
                }
                case Tok_Identifier: {
                    Scope* searchScope = currentScope;
                    InterpreterObj* obj;
                    while (searchScope != NULL) {
                        obj = ObjNSFind(&searchScope->objects, text);
                        if (obj != NULL) break;
                        searchScope = searchScope->parent;
                    }
                    if (searchScope == NULL) {
                        panic(Panic_Interpreter, "Unknown variable %s!\n", text);
                    }
                    out = obj;
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
    InterpreterObj* result = interpretExpr(expr);

}

STATIC void interpretStmt(Statement stmt) {
    switch (stmt.tag) {
        case StmtTag_Expr: {
            interpretExpr(stmt.expr);
            break;
        }
        case StmtTag_Global: {
            ObjNSSet(&_globalScope->objects, tokText(stmt.global.name), *interpretExpr(stmt.global.initializer));
            break;
        }
        case StmtTag_For: {
            pushScope();
            setVar(tokText(stmt.for_.iterator), *interpretExpr(stmt.for_.min));
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
    setVar(tokText(proc.name), (InterpreterObj){
        .tag = ObjType_Proc,
        .proc = proc
    });
}

STATIC void interpretFun(FunDecl func) {
    setVar(tokText(func.name), (InterpreterObj){
        .tag = ObjType_Func,
        .func = func
    });
}

STATIC void interpretClass(ClassDecl class) {

}

STATIC void interpretDecl(Declaration decl) {
    switch (decl.tag) {
        case DeclTag_Class: {
            interpretClass(decl.class);
            break;
        }
        case DeclTag_Fun: {
            interpretFun(decl.fun);
            break;
        }
        case DeclTag_Proc: {
            interpretProc(decl.proc);
            break;
        }
        case DeclTag_Stmt: {
            interpretStmt(decl.stmt);
            break;
        }
    }
}

STATIC void interpretBlock(DeclList block) {
    for (int i = 0; i < block.len; i++) {
        interpretDecl(block.root[i]);
    }
}

void interpret(ParseOutput po) {
    pushScope();
    interpretBlock(po.ast);
    popScope();
}