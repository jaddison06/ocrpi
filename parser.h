#pragma once

#include "lexer.h"

#include "vector.h"

typedef struct {
    int tokId;
    char* msg;
} ParseError;

DECL_VEC(ParseError, ParseErrList)

typedef struct Expression Expression;

typedef struct {

} UnaryExpr;

typedef struct {

} BinaryExpr;

typedef struct {

} CallExpr;

typedef struct {

} SuperExpr;

typedef Expression GroupingExpr;
typedef Token PrimaryExpr;

struct Expression {
    enum { Expr_Unary, Expr_Binary, Expr_Call, Expr_Super, Expr_Grouping, Expr_Literal } tag;
    union {
        UnaryExpr unary;
        BinaryExpr binary;
        CallExpr call;
        SuperExpr super;
        GroupingExpr grouping;
        PrimaryExpr primary;
    };
};

typedef struct {

} ExprStmt;

typedef struct {

} GlobalStmt;

typedef struct {

} ForStmt;

typedef struct {

} WhileStmt;

typedef struct {

} DoStmt;

typedef struct {

} IfStmt;

typedef struct {

} SwitchStmt;

typedef struct {
    enum { Stmt_Expr, Stmt_Global, Stmt_For, Stmt_While, Stmt_Do, Stmt_If, Stmt_Switch } tag;
    union {
        ExprStmt expr;
        GlobalStmt global;
        ForStmt for_;
        WhileStmt while_;
        DoStmt do_;
        IfStmt if_;
        SwitchStmt switch_;
    };
} Statement;

typedef struct {

} FunDecl;

typedef struct {

} ProcDecl;

typedef struct {

} ClassDecl;

typedef struct {

} ArrayDecl;

typedef struct {
    enum { Decl_Stmt, Decl_Fun, Decl_Proc, Decl_Class, Decl_Array } tag;
    union {
        Statement stmt;
        FunDecl fun;
        ProcDecl proc;
        ClassDecl class;
        ArrayDecl array;
    };
} Declaration;

DECL_VEC(Declaration, DeclList)

typedef struct {
    DeclList declarations;
} Scope;

typedef struct {
    Scope ast;
    ParseErrList errors;
} ParserOutput;

ParserOutput parse(LexOutput lo);