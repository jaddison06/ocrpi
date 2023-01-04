#include "interpreter.h"

#include <stdlib.h>

#include "common.h"
#include "panic.h"
#include "ocrpi_stdlib.h"

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
    if (currentScope == NULL) panic(Panic_Interpreter, "Can't exit the root scope!");
    Scope* parentScope = currentScope->parent;
    DESTROY(currentScope->objects);
    free(currentScope);
    currentScope = parentScope;
}

InterpreterObj* interpretExpr(Expression expr);
STATIC void interpretDecl(Declaration decl);
STATIC void interpretBlock(DeclList block);

STATIC INLINE InterpreterObj* findObj(char* name) {
    Scope* searchScope = currentScope;
    InterpreterObj* obj = NULL;
    while (searchScope != NULL) {
        obj = ObjNSFind(&searchScope->objects, name);
        if (obj != NULL) break;
        searchScope = searchScope->parent;
    }
    return obj;
}

STATIC INLINE void setVar(char* name, InterpreterObj value) {
    ObjNSSet(&currentScope->objects, name, value);
}

//* needs destroy!
STATIC ObjList parseArgs(CallExpr call) {
    ObjList out;
    INIT(out);
    for (int i = 0; i < call.arguments.len; i++) {
        APPEND(out, *interpretExpr(call.arguments.root[i]));
    }
    return out;
}

// todo: where do we alloc out? where do we free it?
// sometimes we don't need it cos we want to return the ADDRESS!! not just the value - 
// think getting objs for byRef passing
//
// also setVar refactor needed to use findObj - search parent scopes for the name before
// creating a new val!
//
// (issue being this'd create duplication with both findObj and ObjNSSet searching in the current scope - 
// create a forced XXXNSSet alternative which just appends w/o searching for the name? Or something similar -
// risky but we don't want to be searching the NS twice for the target if we already know we want to declare it as
// a new var. Or do we?? It's 3:15am and I don't know if i actually genuinely care that much about nitpicking performance - 
// this interpreter is really only a halfway step to the eventual compiler. Does it matter!!!!!!!!)
//
// Eventual expressions - want to use em print em and test em !! (this is the reason for the setVar rabbit hole - was thinking
// about assignment expression evaluation)
//
// goodnight!!!!!!!!!!!

InterpreterObj* interpretExpr(Expression expr) {
    InterpreterObj* out = malloc(sizeof(InterpreterObj));

    switch (expr.tag) {
        case ExprTag_Unary: {
            break;
        }
        case ExprTag_Binary: {
            switch (expr.binary.operator.type) {
                
            }
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
                    ))
                        panic(Panic_Interpreter, "Can't call this object!");

                    switch (calleeObj->tag) {
                        case ObjType_Func: {
                            Scope* outerScope = currentScope;
                            // no closures for you!!
                            currentScope = _globalScope;
                            pushScope();

                            if (expr.call.arguments.len != calleeObj->func.params.len)
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

                            // we've interpreted everything in the func - why haven't we returned!!
                            panic(Panic_Interpreter, "Function %s must return a value!", tokText(calleeObj->func.name));

                            // popScope();
                            // currentScope = outerScope;

                            break;
                        }
                        case ObjType_Proc: {

                        }
                        case ObjType_NativeFunc: {
                            ObjList args = parseArgs(expr.call);
                            *out = calleeObj->nativeFunc(args);
                            DESTROY(args);
                        }
                        case ObjType_NativeProc: {
                            ObjList args = parseArgs(expr.call);
                            calleeObj->nativeProc(args);
                            DESTROY(args);
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
                    InterpreterObj* obj = findObj(text);
                    if (obj == NULL) panic(Panic_Interpreter, "Unknown variable %s!\n", text);
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

typedef struct {
    char* name;
    NativeFunc func;
} STLFuncDef;

typedef struct {
    char* name;
    NativeProc proc;
} STLProcDef;

STATIC STLFuncDef stl_funcs[] = {
    {"typeof", stl_typeof},
    {"", NULL}
};

STATIC STLProcDef stl_procs[] = {
    {"print", stl_print},
    {"", NULL}
};

STATIC void setupSTL() {
    for (int i = 0; stl_funcs[i].name[0] != '\0'; i++) {
        setVar(stl_funcs[i].name, (InterpreterObj){
            .tag = ObjType_NativeFunc,
            .nativeFunc = stl_funcs[i].func
        });
    }

    for (int i = 0; stl_procs[i].name[0] != '\0'; i++) {
        setVar(stl_procs[i].name, (InterpreterObj){
            .tag = ObjType_NativeProc,
            .nativeProc = stl_procs[i].proc
        });
    }
}

void interpret(ParseOutput po) {
    pushScope();
    setupSTL();
    interpretBlock(po.ast);
    popScope();
}