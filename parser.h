#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "generated.h"

#include "lexer.h"
#include "vector.h"
#include "common.h"

typedef struct {
    Token tok;
    char* msg;
} ParseError;

DECL_VEC(ParseError, ParseErrList)

typedef struct Expression Expression;
typedef struct Declaration Declaration;
typedef struct DeclList DeclList;

DECL_VEC(Expression, ExprList)

typedef struct {
    Token operator;
    Expression* operand;
} UnaryExpr;

typedef struct {
    Token operator;
    Expression* a, * b;
} BinaryExpr;

typedef struct {
    Expression* callee;
    enum { Call_Call, Call_Array, Call_GetMember} tag;
    union {
        ExprList arguments;
        Token memberName;
    };
} CallExpr;

typedef struct {
    Token memberName;
} SuperExpr;

typedef Expression* GroupingExpr;
typedef Token PrimaryExpr;

struct Expression {
    ExprTag tag;
    union {
        UnaryExpr unary;
        BinaryExpr binary;
        CallExpr call;
        SuperExpr super;
        GroupingExpr grouping;
        PrimaryExpr primary;
    };
};

typedef Expression ExprStmt;

typedef struct {
    Token name;
    Expression initializer;
} GlobalStmt;

typedef struct {
    Token iterator;
    Expression min;
    Expression max;
    DeclList* block;
} ForStmt;

typedef struct {
    Expression condition;
    DeclList* block;
} ConditionalBlock;

typedef ConditionalBlock WhileStmt;
typedef ConditionalBlock DoStmt;

DECL_VEC(ConditionalBlock, ElseIfList)

typedef struct {
    ConditionalBlock primary;
    ElseIfList secondary;
    bool hasElse;
    ConditionalBlock else_;
} IfStmt;

DECL_VEC(ConditionalBlock, SwitchCaseList)

typedef struct {
    Expression expr;
    SwitchCaseList cases;
    bool hasDefault;
    DeclList* default_;
} SwitchStmt;

DECL_VEC(Expression, ArrayDimensions)

typedef struct {
    Token name;
    ArrayDimensions dimensions;
} ArrayStmt;

typedef struct {
    StmtTag tag;
    union {
        ExprStmt expr;
        GlobalStmt global;
        ForStmt for_;
        WhileStmt while_;
        DoStmt do_;
        IfStmt if_;
        SwitchStmt switch_;
        ArrayStmt array;
    };
} Statement;

typedef enum {
    Param_byRef, Param_byVal
} ParamPassMode;

typedef struct {
    Token name;
    ParamPassMode passMode;
} Parameter;

DECL_VEC(Parameter, ParamList)

// todo: slightly yikes - better grammar? otoh this does do the job
typedef struct {
    enum { DOR_decl, DOR_return } tag;
    union {
        Declaration* declaration;
        Expression return_;
    };
} DeclOrReturn;

DECL_VEC(DeclOrReturn, FuncDeclList)

typedef struct {
    Token name;
    ParamList params;
    FuncDeclList block;
} FunDecl;

typedef struct {
    Token name;
    ParamList params;
    DeclList* block;
} ProcDecl;

typedef struct {

} ClassDecl;

struct Declaration {
    DeclTag tag;
    union {
        Statement stmt;
        FunDecl fun;
        ProcDecl proc;
        ClassDecl class;
    };
};

DECL_VEC_NO_TYPEDEF(Declaration, DeclList)

#define DECL_LIST_INIT(dl) do { \
    dl = malloc(sizeof(DeclList)); \
    INIT(*(dl)); \
} while (0)

typedef struct {
    DeclList ast;
    ParseErrList errors;
} ParseOutput;

ParseOutput parse(LexOutput lo);
void destroyParseOutput(ParseOutput po);

// todo: let's hope i never have to debug this!!
//
// malloc & get a pointer to a locally held expression
static inline Expression* copyExpr(Expression expr) {
    Expression* new = malloc(sizeof(Expression));
    memcpy(new, &expr, sizeof(Expression));
    return new;
}