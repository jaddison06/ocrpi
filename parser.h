#pragma once

#include "lexer.h"

#include "vector.h"

typedef struct {
    int tokId;
    char* msg;
} ParseError;

DECL_VEC(ParseError, ParseErrList)

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
    enum { Stmt_Expr, Stmt_Global, Stmt_For, Stmt_ } tag;
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