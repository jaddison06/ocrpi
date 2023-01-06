#include "interpreter.h"

#include <stdlib.h>
#include <math.h>

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

// Interpret the expression & return the result
InterpreterObj interpretExpr(Expression expr);
STATIC INLINE InterpreterObj IOAbs(InterpreterObj obj);
bool isTruthy(InterpreterObj obj);
STATIC void interpretDecl(Declaration decl);
STATIC void interpretBlock(DeclList block);

#define MAKE_ABS(obj) obj = IOAbs(obj);

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

STATIC INLINE InterpreterObj* setVar(char* name, InterpreterObj value) {
    InterpreterObj* obj = findObj(name);
    if (obj != NULL) {
        *obj = value;
        return obj;
    }
    // todo: searches, we already know it won't find anthing
    else return ObjNSSet(&currentScope->objects, name, value);
}

STATIC bool isExprTruthy(Expression expr) {
    return isTruthy(interpretExpr(expr));
}

STATIC INLINE InterpreterObj assign(Expression a, InterpreterObj b) {
    InterpreterObj* ref;

    // assignment or initialization!!
    PANIC_TRY {
        // try and find the object and assign to it
        InterpreterObj target = interpretExpr(a);
        if (target.tag != ObjType_Ref) panic(Panic_Interpreter, "Can't assign - not an lvalue! (%s)", ExprTagToString(a.tag));
        *target.reference = b;
        ref = target.reference;
    } PANIC_CATCH(PCC_InterpreterUnknownVar) {
        // the object doesn't exist - create it!

        // we can't create a new class member dynamically (because i said so), and if we're assigning to an assignment then
        // why the fuck wouldn't it already exist?
        if (a.tag != ExprTag_Primary) {
            panic(Panic_Interpreter, "This type of value can only be assigned to!");
        }

        ref = setVar(tokText(a.primary), b);
    } PANIC_END_TRY

    return (InterpreterObj){
        .tag = ObjType_Ref,
        .reference = ref
    };
}

STATIC bool equal(InterpreterObj a, InterpreterObj b) {
    if (a.tag != b.tag) return false;
    switch (a.tag) {
        case ObjType_Class:
        case ObjType_Func:
        case ObjType_Proc:
        case ObjType_NativeFunc:
        case ObjType_NativeProc:
        case ObjType_Instance: panic(Panic_Interpreter, "Can't check %s for equality yet!", ObjTypeToString(a.tag));

        case ObjType_Nil: return true;
        case ObjType_Bool: return a.bool_ == b.bool_;
        case ObjType_Int: return a.int_ == b.int_;
        case ObjType_String: return strcmp(a.string, b.string) == 0;
        case ObjType_Float: return a.float_ == b.float_;
        case ObjType_Array: {
            if (a.array.len != b.array.len) return false;
            for (int i = 0; i < a.array.len; i++) {
                if (!equal(a.array.root[i], b.array.root[i])) return false;
            }
            return true;
        }
    }
}

STATIC bool exprEqual(Expression a, Expression b) {
    return equal(interpretExpr(a), interpretExpr(b));
}

#define _EXPR_SHORTCUT(returnType, name) STATIC returnType name##Exprs(Expression a, Expression b) { return name(interpretExpr(a), interpretExpr(b)); }

#define NUMERIC_OP(name, op) STATIC InterpreterObj name(InterpreterObj a, InterpreterObj b) { \
    MAKE_ABS(a); \
    MAKE_ABS(b); \
    if (a.tag == ObjType_Float) { \
        float aNum = a.float_; \
        if (b.tag == ObjType_Float) { \
            float bNum = b.float_; \
            return (InterpreterObj){.tag = ObjType_Float, .float_ = op}; \
        } else if (b.tag == ObjType_Int) { \
            int bNum = b.int_; \
            return (InterpreterObj){.tag = ObjType_Float, .float_ = op}; \
        } \
    } else if (a.tag == ObjType_Int) { \
        float aNum = a.int_; \
        if (b.tag == ObjType_Float) { \
            float bNum = b.float_; \
            return (InterpreterObj){.tag = ObjType_Int, .int_ = op}; \
        } else if (b.tag == ObjType_Int) { \
            int bNum = b.int_; \
            return (InterpreterObj){.tag = ObjType_Int, .int_ = op}; \
        } \
    } \
    panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag)); \
} \
_EXPR_SHORTCUT(InterpreterObj, name)

NUMERIC_OP(iExponent, pow(aNum, bNum))
NUMERIC_OP(multiply, aNum * bNum)
NUMERIC_OP(divide, aNum / bNum)
NUMERIC_OP(subtract, aNum - bNum)
NUMERIC_OP(_addNum, aNum + bNum)

STATIC InterpreterObj add(InterpreterObj a, InterpreterObj b) {
    MAKE_ABS(a);
    MAKE_ABS(b);

    if (a.tag == ObjType_String && b.tag == ObjType_String) {
        char* out = malloc(strlen(a.string) + strlen(b.string) + 1);
        memcpy(out, a.string, strlen(a.string) + 1);
        strcat(out, b.string);
        return (InterpreterObj){
            .tag = ObjType_String,
            .string = out
        };
    } else if (a.tag == ObjType_Array && b.tag == ObjType_Array) {
        ObjList out;
        INIT(out);

        APPEND_ALL(ObjList, out, a.array);
        APPEND_ALL(ObjList, out, b.array);
        
        return (InterpreterObj){
            .tag = ObjType_Array,
            .array = out
        };
    }
    return _addNum(a, b);
}

_EXPR_SHORTCUT(InterpreterObj, add)

STATIC bool less(InterpreterObj a, InterpreterObj b) {
    MAKE_ABS(a);
    MAKE_ABS(b);

    if (a.tag == ObjType_Float) {
        if (b.tag == ObjType_Float) return a.float_ < b.float_;
        else if (b.tag == ObjType_Int) return a.float_ < b.int_;
    } else if (a.tag == ObjType_Int) {
        if (b.tag == ObjType_Float) return a.int_ < b.float_;
        else if (b.tag == ObjType_Int) return a.int_ < b.int_;
    }
    panic(Panic_Interpreter, "Invalid operator between %s and %s", ObjTypeToString(a.tag), ObjTypeToString(b.tag));
}

STATIC INLINE bool greaterEqual(InterpreterObj a, InterpreterObj b) {
    return !less(a, b);
}

STATIC INLINE bool lessEqual(InterpreterObj a, InterpreterObj b) {
    return less(a, b) || equal(a, b);
}

STATIC INLINE bool greater(InterpreterObj a, InterpreterObj b) {
    return !lessEqual(a, b);
}

_EXPR_SHORTCUT(bool, less)
_EXPR_SHORTCUT(bool, greater)
_EXPR_SHORTCUT(bool, lessEqual)
_EXPR_SHORTCUT(bool, greaterEqual)

InterpreterObj binaryExpr(TokType operator, Expression a, Expression b) {
#define BOOLOBJ(val) (InterpreterObj){.tag = ObjType_Bool, .bool_ = val}

    switch (operator) {
        case Tok_Equal: {
            assign(a, interpretExpr(b));
            break;
        }
        case Tok_ExpEqual: {
            assign(a, binaryExpr(Tok_Exp, a, b));
            break;
        }
        case Tok_StarEqual: {
            assign(a, binaryExpr(Tok_Star, a, b));
            break;
        }
        case Tok_SlashEqual: {
            assign(a, binaryExpr(Tok_Slash, a, b));
            break;
        }
        case Tok_PlusEqual: {
            assign(a, binaryExpr(Tok_Plus, a, b));
            break;
        }
        case Tok_MinusEqual: {
            assign(a, binaryExpr(Tok_Minus, a, b));
            break;
        }

        case Tok_Or: return BOOLOBJ(isExprTruthy(a) || isExprTruthy(b));
        case Tok_And: return BOOLOBJ(isExprTruthy(a) && isExprTruthy(b));

        case Tok_EqualEqual: return BOOLOBJ(exprEqual(a, b));
        case Tok_BangEqual: return BOOLOBJ(!exprEqual(a, b));

        case Tok_Less: return BOOLOBJ(lessExprs(a, b));
        case Tok_LessEqual: return BOOLOBJ(lessEqualExprs(a, b));
        case Tok_Greater: return BOOLOBJ(greaterExprs(a, b));
        case Tok_GreaterEqual: return BOOLOBJ(greaterEqualExprs(a, b));

        case Tok_Exp: return iExponentExprs(a, b);
        case Tok_Star: return multiplyExprs(a, b);
        case Tok_Slash: return divideExprs(a, b);
        case Tok_Plus: return addExprs(a, b);
        case Tok_Minus: return subtractExprs(a, b);
    }
    
#undef BOOLOBJ
}

//* needs destroy!
//
// everything is a VALUE NOT A REFERENCE!!
STATIC ObjList parseArgsForNative(CallExpr call) {
    ObjList out;
    INIT(out);
    FOREACH(ExprList, call.arguments, current) {
        APPEND(out, IOAbs(interpretExpr(*current)));
    }
    return out;
}

//* Expression ground rules:
//*   - Expressions should be kept as expressions until as late as possible - only evaluate it when you need it!!
//*   - If a function needs a non-referenced value it's the responsibility of THAT FUNCTION to call IOAbs - slightly more work but means
//*     some actual consistency

InterpreterObj interpretExpr(Expression expr) {
    InterpreterObj out;
#define SET_OUT(...) out = (InterpreterObj)__VA_ARGS__

    switch (expr.tag) {
        case ExprTag_Unary: {
            break;
        }
        case ExprTag_Binary: {
            out = binaryExpr(expr.binary.operator.type, *expr.binary.a, *expr.binary.b);
            break;
        }
        case ExprTag_Call: {
            switch (expr.call.tag) {
                case Call_Call: {
                    InterpreterObj calleeObj = IOAbs(interpretExpr(*expr.call.callee));

                    if (!(
                        calleeObj.tag == ObjType_Func ||
                        calleeObj.tag == ObjType_Proc ||
                        calleeObj.tag == ObjType_NativeFunc ||
                        calleeObj.tag == ObjType_NativeProc
                    ))
                        panic(Panic_Interpreter, "Can't call this object!");

                    switch (calleeObj.tag) {
                        case ObjType_Func: {
                            // Create a new scope as the function's context
                            Scope* executionScope = newScope();
                            // no closures for you!!
                            executionScope->parent = globalScope;

                            if (expr.call.arguments.len != calleeObj.func.params.len)
                                panic(Panic_Interpreter, "Called function %s with %i args instead of %i", tokText(calleeObj.func.name), expr.call.arguments.len, calleeObj.func.params.len);

                            // We're gonna be passing these in as POINTERS so 
                            ObjList referenceArgs;
                            INIT(referenceArgs);

                            // Evaluate function arguments in the CURRENT SCOPE, adding results to the NEW SCOPE
                            for (int i = 0; i < expr.call.arguments.len; i++) {
                                InterpreterObj arg = interpretExpr(expr.call.arguments.root[i]);
                                if (calleeObj.func.params.root[i].passMode == Param_byRef) {
                                    if (!arg.tag == ObjType_Ref) panic(Panic_Interpreter, "Can't pass a %s by reference!", ExprTagToString(expr.call.arguments.root[i].tag));
                                    ObjNSSet(&executionScope->objects, tokText(calleeObj.func.params.root[i].name), (InterpreterObj){
                                        .tag = ObjType_Ref,
                                        .reference = &arg
                                    });
                                } else {
                                    ObjNSSet(&executionScope->objects, tokText(calleeObj.func.params.root[i].name), IOAbs(arg));
                                }
                            }

                            // Now we've evaluated the arguments, we can setup the scope as the
                            // function's execution context.
                            Scope* outerScope = currentScope;
                            currentScope = executionScope;

                            FOREACH(FuncDeclList, calleeObj.func.block, currentDOR) {
                                if (currentDOR->tag == DOR_return) {
                                    out = IOAbs(interpretExpr(currentDOR->return_));
                                    destroyScope(executionScope);
                                    currentScope = outerScope;
                                    // boo!
                                    // (double break)
                                    goto returned;
                                }
                                interpretDecl(*currentDOR->declaration);
                            }

                            // we've interpreted everything in the func - why haven't we returned!!
                            panic(Panic_Interpreter, "Function %s must return a value!", tokText(calleeObj.func.name));

                            returned: break;
                        }
                        case ObjType_Proc: {
                            break;
                        }
                        case ObjType_NativeFunc: {
                            ObjList args = parseArgsForNative(expr.call);
                            out = calleeObj.nativeFunc(args);
                            DESTROY(args);
                            break;
                        }
                        case ObjType_NativeProc: {
                            ObjList args = parseArgsForNative(expr.call);
                            calleeObj.nativeProc(args);
                            DESTROY(args);
                            SET_OUT({.tag = ObjType_Nil});
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
                    SET_OUT({.tag = ObjType_Nil});
                    break;
                }
                case Tok_True:
                case Tok_False: {
                    SET_OUT({.tag = ObjType_Bool, .bool_ = expr.primary.type == Tok_True});
                    break;
                }
                case Tok_StringLit: {
                    // strip leading & trailing quotes!
                    char* stringContents = malloc(strlen(text) - 1);
                    memcpy(stringContents, text + 1, strlen(text) - 2);
                    stringContents[strlen(text) - 2] = 0;
                    SET_OUT({.tag = ObjType_String, .string = stringContents});
                    break;
                }
                case Tok_IntLit: {
                    SET_OUT({.tag = ObjType_Int, .int_ = atoi(text)});
                    break;
                }
                case Tok_FloatLit: {
                    SET_OUT({.tag = ObjType_Float, .float_ = strtof(text, NULL)});
                    break;
                }
                case Tok_Identifier: {
                    InterpreterObj* obj = findObj(text);
                    if (obj == NULL) panic(PANIC_CATCHABLE(Panic_Interpreter, PCC_InterpreterUnknownVar), "Unknown variable %s!", text);
                    SET_OUT({.tag = ObjType_Ref, .reference = obj});
                    break;
                }
            }
            free(text);
            break;
        }
    }
    return out;

#undef SET_OUT
}

STATIC INLINE InterpreterObj IOAbs(InterpreterObj obj) {
    while (obj.tag == ObjType_Ref) obj = *obj.reference;
    return obj;
}

bool isTruthy(InterpreterObj obj) {
    switch (obj.tag) {
        case ObjType_Ref: return isTruthy(*obj.reference);

        case ObjType_Class:
        case ObjType_Func:
        case ObjType_Proc:
        case ObjType_NativeFunc:
        case ObjType_NativeProc:
        case ObjType_Instance: panic(Panic_Interpreter, "Can't (yet) use a %s as a boolean!", ObjTypeToString(obj.tag));

        case ObjType_Nil: return false;
        case ObjType_Bool: return obj.bool_;
        case ObjType_Int: return obj.int_ > 0;
        case ObjType_String: return obj.string[0] != 0;
        case ObjType_Float: return obj.float_ > 0;
        case ObjType_Array: return obj.array.len > 0;
    }
}

STATIC void interpretStmt(Statement stmt) {
    switch (stmt.tag) {
        case StmtTag_Expr: {
            interpretExpr(stmt.expr);
            break;
        }
        case StmtTag_Global: {
            ObjNSSet(&globalScope->objects, tokText(stmt.global.name), interpretExpr(stmt.global.initializer));
            break;
        }
        case StmtTag_For: {
            pushScope();
            setVar(tokText(stmt.for_.iterator), interpretExpr(stmt.for_.min));
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
            while (isExprTruthy(cond)) {
                interpretBlock(*stmt.for_.block);
                interpretExpr(incr);
            }
            free(incr.binary.b);
            popScope();
            break;
        }
        case StmtTag_While: {
            while (isExprTruthy(stmt.while_.condition)) {
                interpretBlock(*stmt.while_.block);
            }
            break;
        }
        case StmtTag_Do: {
            //* yikes!! not a do-while but a do-until!
            while (!isExprTruthy(stmt.do_.condition)) {
                interpretBlock(*stmt.do_.block);
            }
            break;
        }
        case StmtTag_If: {
            if (isExprTruthy(stmt.if_.primary.condition)) {
                interpretBlock(*stmt.if_.primary.block);
            } else {
                FOREACH(ElseIfList, stmt.if_.secondary, currentBranch) {
                    if (isExprTruthy(currentBranch->condition)) {
                        interpretBlock(*currentBranch->block);
                        break;
                    }
                }
                if (stmt.if_.hasElse && isExprTruthy(stmt.if_.else_.condition)) {
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
    {"bool", stl_bool},
    {"string", stl_string},
    {"float", stl_float},
    {"int", stl_int},
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