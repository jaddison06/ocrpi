#include "parser.h"

#include <stdbool.h>

static void panic(char* msg) {
    printf("\x1b[31m%s\x1b[0m\n", msg);
}

int current = 0;

Token* toks;

static inline Token peek() {
    return toks[current];
}

static inline Token advance() {
    return toks[current++];
}

static bool isAtEnd() {
    return peek().type == Tok_EOF;
}

static bool match(TokType type) {
    if (isAtEnd()) return false;
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

static Token consume(TokType type, char* message) {
    if (peek().type == type) return advance();
    panic(message);
}

static inline ParamPassMode passMode(TokType type) {
    if (!(type == Tok_ByRef || type == Tok_ByVal)) panic("Expected 'byRef' or 'byVal'");
    return type == Tok_ByRef ? Param_byRef : Param_byVal;
}

static FunDecl function() {
    FunDecl out;
    // todo: cleanup
    INIT(out.params);
    consume(Tok_Function, "Expected 'function'");
    out.name = consume(Tok_Identifier, "Expected function name");
    consume(Tok_LParen, "Expected '('");
    if (!match(Tok_RParen)) {
        Parameter currentParam;
        currentParam.name = consume(Tok_Identifier, "Expected parameter name");
        if (match(Tok_Colon)) {
            currentParam.passMode = passMode(advance().type);
        }
        while (match(Tok_Comma)) {

        }
    }
}

static ProcDecl procedure() {

}

static ClassDecl class() {

}

static Statement statement() {
    // how d'you even go about handling an expr stmt?

}

static Declaration declaration() {
    Declaration out;
    switch (peek().type) {
        case Tok_Function:
            out.tag = Decl_Fun;
            out.fun = function();
            return out;
        case Tok_Procedure:
            out.tag = Decl_Proc;
            out.proc = procedure();
            return out;
        case Tok_Class:
            out.tag = Decl_Class;
            out.class = class();
            return out;
        default:
            out.tag = Decl_Stmt;
            out.stmt = statement();
            return out;
    }
}

ParseOutput parse(LexOutput lo) {
    toks = lo.toks.root;

    ParseOutput out;
    INIT(out.ast.declarations);
    INIT(out.errors);

    Declaration newDecl;
    while (!isAtEnd()) {
        newDecl = declaration();
        APPEND(out.ast.declarations, newDecl);
    }

    return out;
}

void DestroyParseOutput(ParseOutput po) {
    DESTROY(po.ast.declarations);
    DESTROY(po.errors);
}