#include "parser.h"

int current = 0;
Token* toks;

static void panic(char* msg) {
    Token errorTok = toks[current];
    char* text = tokText(errorTok);
    printf("Parse error at token #%i (line %i, column %i)\n'%s':\n\x1b[31m%s\x1b[0m\n", current + 1, errorTok.line, errorTok.col, text, msg);
    free(text);
    exit(-1);
}

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

// forward decl
static Declaration declaration();
static Expression expression();

// malloc & get a pointer to a locally held expression
static inline Expression* copyExpr(Expression expr) {
    Expression* new = malloc(sizeof(Expression));
    memcpy(new, &expr, sizeof(Expression));
    return new;
}

static Expression primary() {
    if (!(
        match(Tok_Self) ||
        match(Tok_StringLit) ||
        match(Tok_IntLit) ||
        match(Tok_FloatLit) ||
        match(Tok_Identifier)
    )) {
        panic("Unexpected token!");
    }
    return (Expression){
        .tag = primary,
        .primary = previous()
    };
}

static Expression grouping() {
    if (match(Tok_LParen)) {
        return (Expression){
            .tag = Expr_Grouping,
            .grouping = copyExpr(expression())
        };
    }
    return primary();
}

static Expression super() {
    Expression out;
    if (match(Tok_Super)) {
        consume(Tok_Dot, "Expected '.' after 'super'");
        return (Expression){
            .tag = Expr_Super,
            .super = (SuperExpr){
                .memberName = consume(Tok_Identifier, "Expected an identifier")
            }
        };
    }

    return grouping();
}

static ExprList argList() {
    ExprList out;
    INIT(out);
    APPEND(out, expression());
    while (match(Tok_Comma)) {
        APPEND(out, expression());
    }
    return out;
}

static Expression call() {
    Expression out = super();
    while (
        match(Tok_LParen) ||
        match(Tok_LSquare) ||
        match(Tok_Dot)
    ) {
        out = (Expression){
            .tag = Expr_Call,
            .call = (CallExpr){
                .callee = copyExpr(out)
            }
        };
        switch (previous().type) {
            case Tok_LParen: {
                out.call.tag = Call_Call;
                out.call.arguments = argList();
                consume(Tok_RParen, "Expected ')'");
            }
            case Tok_LSquare: {
                out.call.tag = Call_Array;
                out.call.arguments = argList();
                consume(Tok_RSquare, "Expected ']'");
            }
            case Tok_Dot: {
                out.call.tag = Call_GetMember;
                out.call.memberName = consume(Tok_Identifier, "Expected an identifier");
                break;
            }
        }
    }

    return out;
}

static Expression unary() {
    if (
        match(Tok_Not) ||
        match(Tok_Minus) ||
        match(Tok_New)
    ) {
        return (Expression){
            .tag = Expr_Unary,
            .unary = (UnaryExpr){
                .operator = previous(),
                .operand = copyExpr(unary())
            }
        };
    }
    return call();
}

static Expression factor() {
    Expression out = unary();
    while (match(Tok_Star) || match(Tok_Slash)) {
        out = (Expression){
            .tag = Expr_Binary,
            .binary = (BinaryExpr) {
                .a = copyExpr(out),
                .b = copyExpr(unary()),
                .operator = previous()
            }
        };
    }
    return out;
}

static Expression term() {
    Expression out = factor();
    while (match(Tok_Plus) || match(Tok_Minus)) {
        out = (Expression){
            .tag = Expr_Binary,
            .binary = (BinaryExpr) {
                .a = copyExpr(out),
                .b = copyExpr(factor()),
                .operator = previous()
            }
        };
    }
    return out;
}

static Expression comparison() {
    Expression out = term();
    while (
        match(Tok_Less) ||
        match(Tok_LessEqual) ||
        match(Tok_Greater) ||
        match(Tok_GreaterEqual)
    ) {
        out = (Expression){
            .tag = Expr_Binary,
            .binary = (BinaryExpr) {
                .a = copyExpr(out),
                .b = copyExpr(term()),
                .operator = previous()
            }
        };
    }
    return out;
}

static Expression equality() {
    Expression out = comparison();
    while (match(Tok_EqualEqual) || match(Tok_BangEqual)) {
        out = (Expression){
            .tag = Expr_Binary,
            .binary = (BinaryExpr) {
                .a = copyExpr(out),
                .b = copyExpr(comparison()),
                .operator = previous()
            }
        };
    }
    return out;
}

static Expression logicAnd() {
    Expression out = equality();
    while (match(Tok_And)) {
        out = (Expression){
            .tag = Expr_Binary,
            .binary = (BinaryExpr) {
                .a = copyExpr(out),
                .b = copyExpr(equality()),
                .operator = previous()
            }
        };
    }
    return out;
}

static Expression logicOr() {
    Expression out = logicAnd();
    while (match(Tok_Or)) {
        out = (Expression){
            .tag = Expr_Binary,
            .binary = (BinaryExpr) {
                .a = copyExpr(out),
                .b = copyExpr(logicAnd()),
                .operator = previous()
            }
        };
    }
    return out;
}

static Expression assignment() {
    
}

static Expression expression() {
    return assignment();
}

static inline ParamPassMode passMode() {
    if (match(Tok_ByRef)) return Param_byRef;
    else if (match(Tok_ByVal)) return Param_byVal;
    panic("Expected 'byRef' or 'byVal'");
}

static Parameter param() {
    Parameter out;
    out.name = consume(Tok_Identifier, "Expected parameter name");
    if (match(Tok_Colon)) {
        out.passMode = passMode();
    } else {
        out.passMode = Param_byVal;
    }
    return out;
}

static void params(ParamList* out) {
    consume(Tok_LParen, "Expected '('");
    if (!match(Tok_RParen)) {
        APPEND(*out, param());
        while (match(Tok_Comma)) {
            APPEND(*out, param());
        }
    }
    consume(Tok_RParen, "Expected ')'");
}

static void block(DeclList* block, TokType end) {
    while (!match(end)) {
        APPEND(*block, declaration());
    }
}

static FunDecl function() {
    FunDecl out;
    // todo: cleanup
    INIT(out.params);
    INIT(out.block);
    consume(Tok_Function, "Expected 'function'");
    out.name = consume(Tok_Identifier, "Expected function name");
    params(&out.params);
    while (!match(Tok_EndFunction)) {
        DeclOrReturn currentDOR;
        if (match(Tok_Return)) {
            currentDOR.tag = DOR_return;
            currentDOR.return_ = expression();
        } else {
            currentDOR.tag = DOR_decl;
            // todo: i'm really tired there's gotta be an easier way of doing this
            currentDOR.declaration = malloc(sizeof(Declaration));
            Declaration theDeclaration = declaration();
            memcpy(currentDOR.declaration, &theDeclaration, sizeof(Declaration));
        }
        APPEND(out.block, currentDOR);
    }
    return out;
}

static ProcDecl procedure() {
    ProcDecl out;
    INIT(out.params);
    DECL_LIST_INIT(out.block);
    consume(Tok_Procedure, "Expected 'procedure'");
    out.name = consume(Tok_Identifier, "Expected procedure name");
    params(&out.params);
    block(out.block, Tok_EndProcedure);
    return out;
}

static ClassDecl class() {

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

    DECL_LIST_INIT(out.block);

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

    DECL_LIST_INIT(out.block);

    consume(Tok_While, "Expected 'while'");
    out.condition = expression();
    block(out.block, Tok_EndWhile);

    return out;
}

static DoStmt do_() {
    DoStmt out;

    DECL_LIST_INIT(out.block);

    consume(Tok_Do, "Expected 'do'");
    block(out.block, Tok_Until);
    out.condition = expression();

    return out;
}

// this is what happens when you mistakenly think including
// "elseif" in the specification is a good idea
static IfStmt if_() {
    IfStmt out;

    DECL_LIST_INIT(out.primary.block);
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
        APPEND(*out.primary.block, declaration());
    }

    if (previous().type == Tok_ElseIf) {
        do {
            while (!(
                match(Tok_ElseIf) ||
                match(Tok_Else) ||
                match(Tok_EndIf)
            )) {
                ConditionalBlock currentBlock;
                DECL_LIST_INIT(currentBlock.block);
                currentBlock.condition = expression();
                consume(Tok_Then, "Expected 'then'");
                while (!(
                    match(Tok_ElseIf) ||
                    match(Tok_Else) ||
                    match(Tok_EndIf)
                )) {
                    APPEND(*currentBlock.block, declaration());
                }
                APPEND(out.secondary, currentBlock);
            }
        } while (previous().type == Tok_ElseIf);
        
        if (previous().type == Tok_Else) {
            out.hasElse = true;
            DECL_LIST_INIT(out.else_.block);
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
            DECL_LIST_INIT(currentBlock.block);
            consume(Tok_Colon, "Expected ':'");
            while (!(
                match(Tok_Case) ||
                match(Tok_Default) ||
                match(Tok_EndSwitch)
            )) {
                APPEND(*currentBlock.block, declaration());
            }
            APPEND(out.cases, currentBlock);
        } else if (match(Tok_Default)) {
            out.hasDefault = true;
            DECL_LIST_INIT(out.default_);
            consume(Tok_Colon, "Expected ':'");
            // todo: this makes the default check redundant -
            // update when we (eventually) figure out
            // isAtEnd checks everywhere
            while (!match(Tok_EndSwitch)) {
                APPEND(*out.default_, declaration());
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
    APPEND(out.dimensions, expression());
    while (match(Tok_Comma)) {
        APPEND(out.dimensions, expression());
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
    INIT(out.ast);
    INIT(out.errors);

    Declaration newDecl;
    while (!isAtEnd()) {
        APPEND(out.ast, declaration());
    }

    return out;
}

// yoooooooooooo
void DestroyParseOutput(ParseOutput po) {
    DESTROY(po.ast);
    DESTROY(po.errors);
}