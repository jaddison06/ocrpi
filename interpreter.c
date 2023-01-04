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
static Scope* globalScope = NULL;

STATIC Scope* newScope() {
    Scope* out = malloc(sizeof(Scope));
    out->objects = NewObjNS();
    return out;
}

STATIC void destroyScope(Scope* scope) {
    DESTROY(scope->objects);
    free(scope);
}

STATIC void pushScope() {
    Scope* oldScope = currentScope;
    currentScope = newScope();
    currentScope->parent = oldScope;
    if (oldScope == NULL) globalScope = currentScope;
}

STATIC void popScope() {
    if (currentScope == NULL) panic(Panic_Interpreter, "Can't exit the root scope!");
    Scope* parentScope = currentScope->parent;
    destroyScope(currentScope);
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
    InterpreterObj* obj = findObj(name);
    if (obj != NULL) *obj = value;
    // todo: searches, we already know it won't find anthing
    else ObjNSSet(&currentScope->objects, name, value);
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

// 3 types of lvalue:
//   - call().member = value
//   - identifier = value
//   - (lvalue = assignedValue) = anotherAssignedValue <-- normally useless but kinda nice if you want to take a reference to the lvalue of an assignment!!
STATIC bool isLvalue(Expression expr) {
    if (
        (expr.tag == ExprTag_Call && expr.call.tag == Call_GetMember) ||
        (expr.tag == ExprTag_Primary && expr.primary.type == Tok_Identifier) ||
        (expr.tag == ExprTag_Binary && (
            expr.binary.operator.type == Tok_Equal ||
            expr.binary.operator.type == Tok_ExpEqual ||
            expr.binary.operator.type == Tok_StarEqual ||
            expr.binary.operator.type == Tok_SlashEqual ||
            expr.binary.operator.type == Tok_PlusEqual ||
            expr.binary.operator.type == Tok_MinusEqual
        ))
    ) return true;

    return false;
}

STATIC INLINE void assign(char* name, Expression* a, InterpreterObj b) {
    if (!isLvalue(*a)) panic(Panic_Interpreter, "Can't assign - not an lvalue! (%s)", ExprTagToString(a->tag));
    // assignment or initialization!!
    PANIC_TRY {
        // try and find the object and assign to it
        InterpreterObj* target = interpretExpr(*a);
        *target = b;
    } PANIC_CATCH(PCC_InterpreterUnknownVar) {
        
    }
    PANIC_END_TRY;
}

InterpreterObj binaryExpr(TokType operator, Expression* a, Expression* b) {
    switch (operator) {
        case Tok_Equal: {
            
        }
        case Tok_ExpEqual: {
            // binaryExpr(Tok_Equal, a, binaryExpr(Tok_Exp, a, b));
        }
    }
}

// todo: where do we alloc out? where do we free it?
// sometimes we don't need it allocated cos we want to return the ADDRESS!! not just the value - 
// think evaluating variables for byRef passing
InterpreterObj* interpretExpr(Expression expr) {
    InterpreterObj* out = malloc(sizeof(InterpreterObj));

    switch (expr.tag) {
        case ExprTag_Unary: {
            break;
        }
        case ExprTag_Binary: {
            *out = binaryExpr(expr.binary.operator.type, expr.binary.a, expr.binary.b);
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
                            // Create a new scope as the function's context
                            Scope* executionScope = newScope();
                            // no closures for you!!
                            executionScope->parent = globalScope;

                            if (expr.call.arguments.len != calleeObj->func.params.len)
                                panic(Panic_Interpreter, "Called function %s with %i args instead of %i", tokText(calleeObj->func.name), expr.call.arguments.len, calleeObj->func.params.len);

                            // Evaluate function arguments in the CURRENT SCOPE, adding results to the NEW SCOPE
                            for (int i = 0; i < expr.call.arguments.len; i++) {
                                InterpreterObj* arg = interpretExpr(expr.call.arguments.root[i]);
                                if (calleeObj->func.params.root[i].passMode == Param_byRef) {
                                    // todo: error if not an lvalue (what is an lvalue!!!!!!)
                                    // allow assignment as an lvalue?? (`a = 3` returns a instead of 3)
                                    ObjNSSet(&executionScope->objects, tokText(calleeObj->func.params.root[i].name), (InterpreterObj){
                                        .tag = ObjType_Ref,
                                        .reference = arg
                                    });
                                } else {
                                    ObjNSSet(&executionScope->objects, tokText(calleeObj->func.params.root[i].name), *arg);
                                }
                            }

                            // Now we've evaluated the arguments, we can setup the scope as the
                            // function's execution context.
                            Scope* outerScope = currentScope;
                            currentScope = executionScope;

                            for (int i = 0; i < calleeObj->func.block.len; i++) {
                                DeclOrReturn currentDOR = calleeObj->func.block.root[i];
                                if (currentDOR.tag == DOR_return) {
                                    out = interpretExpr(currentDOR.return_);
                                    destroyScope(executionScope);
                                    currentScope = outerScope;
                                    // boo!
                                    // (double break)
                                    goto returned;
                                }
                                interpretDecl(*currentDOR.declaration);
                            }

                            // we've interpreted everything in the func - why haven't we returned!!
                            panic(Panic_Interpreter, "Function %s must return a value!", tokText(calleeObj->func.name));

                            returned: break;
                        }
                        case ObjType_Proc: {
                            break;
                        }
                        case ObjType_NativeFunc: {
                            ObjList args = parseArgs(expr.call);
                            *out = calleeObj->nativeFunc(args);
                            DESTROY(args);
                            break;
                        }
                        case ObjType_NativeProc: {
                            ObjList args = parseArgs(expr.call);
                            calleeObj->nativeProc(args);
                            DESTROY(args);
                            out->tag = ObjType_Nil;
                            break;
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
                    if (obj == NULL) panic(PANIC_CATCHABLE(Panic_Interpreter, PCC_InterpreterUnknownVar), "Unknown variable %s!\n", text);
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
            ObjNSSet(&globalScope->objects, tokText(stmt.global.name), *interpretExpr(stmt.global.initializer));
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