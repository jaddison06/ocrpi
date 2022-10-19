#include "parser.h"

static void panic(char* msg) {
    printf("\x1b[31m%s\x1b[0m\n", msg);
}

int current = 0;

Token* toks;

static inline Token previous() {
    // todo: sexier way of handling this?
    if (current == 0) panic("Can't have previous token from position 0!");
    return toks[current - 1];
}

static inline Token peek() {
    return toks[current];
}

static inline Token advance() {
    return toks[current++];
}

static bool isAtEnd() {
    return peek().type == Tok_EOF;
}

// todo: refactor w/ varargs to allow matching on multiple types
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

// forward decls
static Declaration declaration();

static inline ParamPassMode passMode(TokType type) {
    if (!(type == Tok_ByRef || type == Tok_ByVal)) panic("Expected 'byRef' or 'byVal'");
    return type == Tok_ByRef ? Param_byRef : Param_byVal;
}

static Parameter param() {
    Parameter out;
    out.name = consume(Tok_Identifier, "Expected parameter name");
    if (match(Tok_Colon)) {
        out.passMode = passMode(advance().type);
    }
    return out;
}

static void params(ParamList out) {
    consume(Tok_LParen, "Expected '('");
    if (!match(Tok_RParen)) {
        Parameter currentParam = param();
        APPEND(out, currentParam);
        while (match(Tok_Comma)) {
            currentParam = param();
            APPEND(out, currentParam);
        }
    }
    consume(Tok_RParen, "Expected ')'");
}

static void block(Scope* scope, TokType end) {
    while (!match(end)) {
        Declaration currentDecl = declaration();
        APPEND(scope->declarations, currentDecl);
    }
}

static FunDecl function() {
    FunDecl out;
    // todo: cleanup
    INIT(out.params);
    INIT(out.block);
    consume(Tok_Function, "Expected 'function'");
    out.name = consume(Tok_Identifier, "Expected function name");
    params(out.params);
    while (!match(Tok_EndFunction)) {

    }
    block(out.block, Tok_EndFunction);
    return out;
}

static ProcDecl procedure() {
    ProcDecl out;
    INIT(out.params);
    INIT(out.block->declarations);
    consume(Tok_Procedure, "Expected 'procedure'");
    out.name = consume(Tok_Identifier, "Expected procedure name");
    params(out.params);
    block(out.block, Tok_EndProcedure);
    return out;
}

static ClassDecl class() {

}

static Expression expression() {

}

static GlobalStmt global() {
    GlobalStmt out;

    consume(Tok_Global, "Expected 'global'");
    out.name = consume(Tok_Identifier, "Expected global name");
    consume(Tok_Equal, "Expected '='");
    out.initializer = expression();

    return out;
}

static ForStmt for_() {
    ForStmt out;

    INIT(out.block->declarations);

    consume(Tok_For, "Expected 'for'");
    out.iterator = consume(Tok_Identifier, "Expected iterator name");
    consume(Tok_Equal, "Expected '='");
    out.min = expression();
    consume(Tok_To, "Expected 'to'");
    out.max = expression();
    block(out.block, Tok_Next);
    Token iteratorCheck = consume(Tok_Identifier, "Expected iterator name");
    // we don't do many checks at parse time but if this doesn't
    // happen here we have to store both the first and last iterator
    // for the checker - seems pointless when on a good day they'll
    // be identical.
    if (!(
        out.iterator.length == iteratorCheck.length &&
        strncmp(out.iterator.start, iteratorCheck.start, iteratorCheck.length) == 0
    )) {
        panic("Differing iterator names!");
    }

    return out;
}

static WhileStmt while_() {
    WhileStmt out;

    INIT(out.block->declarations);

    consume(Tok_While, "Expected 'while'");
    out.condition = expression();
    block(out.block, Tok_EndWhile);

    return out;
}

static DoStmt do_() {
    DoStmt out;

    INIT(out.block->declarations);

    consume(Tok_Do, "Expected 'do'");
    block(out.block, Tok_Until);
    out.condition = expression();

    return out;
}

// this is what happens when you mistakenly think including
// "elseif" in the specification is a good idea
static IfStmt if_() {
    IfStmt out;

    INIT(out.primary.block->declarations);
    INIT(out.secondary);
    out.hasElse = false;

    consume(Tok_If, "Expected 'if'");
    out.primary.condition = expression();
    consume(Tok_Then, "Expected 'then'");
    while (!(
        match(Tok_ElseIf) ||
        match(Tok_Else) ||
        match(Tok_EndIf)
    )) {
        Declaration currentDecl = declaration();
        APPEND(out.primary.block->declarations, currentDecl);
    }

    if (previous().type == Tok_ElseIf) {
        do {
            while (!(
                match(Tok_ElseIf) ||
                match(Tok_Else) ||
                match(Tok_EndIf)
            )) {
                ConditionalBlock currentBlock;
                INIT(currentBlock.block->declarations);
                currentBlock.condition = expression();
                consume(Tok_Then, "Expected 'then'");
                while (!(
                    match(Tok_ElseIf) ||
                    match(Tok_Else) ||
                    match(Tok_EndIf)
                )) {
                    Declaration currentDecl = declaration();
                    APPEND(currentBlock.block->declarations, currentDecl);
                }
                APPEND(out.secondary, currentBlock);
            }
        } while (previous().type == Tok_ElseIf);
        
        if (previous().type == Tok_Else) {
            out.hasElse = true;
            INIT(out.else_.block->declarations);
            out.else_.condition = expression();
            consume(Tok_Then, "Expected 'then'");
            block(out.else_.block, Tok_EndIf);
        }
    }

    return out;
}

static SwitchStmt switch_() {
    SwitchStmt out;

    INIT(out.cases);
    out.hasDefault = false;

    consume(Tok_Switch, "Expected 'switch'");
    out.expr = expression();


    while (!match(Tok_EndSwitch)) {
        if (out.hasDefault) panic("'default' must be the last case in a switch statement!");
        if (match(Tok_Case)) {
            ConditionalBlock currentBlock;
            currentBlock.condition = expression();
            INIT(currentBlock.block->declarations);
            consume(Tok_Colon, "Expected ':'");
            while (!(
                match(Tok_Case) ||
                match(Tok_Default) ||
                match(Tok_EndSwitch)
            )) {
                Declaration currentDecl = declaration();
                APPEND(currentBlock.block->declarations, currentDecl);
            }
            APPEND(out.cases, currentBlock);
        } else if (match(Tok_Default)) {
            out.hasDefault = true;
            INIT(out.default_->declarations);
            consume(Tok_Colon, "Expected ':'");
            // todo: this makes the default check redundant -
            // update when we (eventually) figure out
            // isAtEnd checks everywhere
            while (!match(Tok_EndSwitch)) {
                Declaration currentDecl = declaration();
                APPEND(out.default_->declarations, currentDecl);
            }
        }
    }

    return out;
}

static ArrayStmt array() {
    ArrayStmt out;
    
    INIT(out.dimensions);

    consume(Tok_Array, "Expected 'array'");
    out.name = consume(Tok_Identifier, "Expected array name");
    consume(Tok_LSquare, "Expected '['");
    Expression currentExpr = expression();
    APPEND(out.dimensions, currentExpr);
    while (match(Tok_Comma)) {
        currentExpr = expression();
        APPEND(out.dimensions, currentExpr);
    }

    consume(Tok_RSquare, "Expected ']'");

    return out;
}

static Statement statement() {
    Statement out;
    // how d'you even go about handling an expr stmt?
    switch (peek().type) {
        case Tok_Global:
            out.tag = Stmt_Global;
            out.global = global();
            return out;
        case Tok_For:
            out.tag = Stmt_For;
            out.for_ = for_();
            return out;
        case Tok_While:
            out.tag = Stmt_While;
            out.while_ = while_();
            return out;
        case Tok_Do:
            out.tag = Stmt_Do;
            out.do_ = do_();
            return out;
        case Tok_If:
            out.tag = Stmt_If;
            out.if_ = if_();
            return out;
        case Tok_Switch:
            out.tag = Stmt_Switch;
            out.switch_ = switch_();
            return out;
        case Tok_Array:
            out.tag = Stmt_Array;
            out.array = array();
            return out;
    }
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