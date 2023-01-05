#include "parser.h"

#include <setjmp.h>

#include "backtrace.h"
#include "panic.h"

int current;
Token* toks;
jmp_buf syncJump;
ParseError currentError;

STATIC void printError(char* msg) {
    Token errorTok = toks[current];
    char* text = tokText(errorTok);
    printf("Parse error at token #%i (line %i, column %i)\n'%s':\n\x1b[31m%s\x1b[0m\n", current + 1, errorTok.line, errorTok.col, text, msg);
    free(text);
    BACKTRACE(8);
}

// Recoverable error - synchronise & continue
//
// todo: refactor w/ panic() catching
STATIC void error(char* msg) {
    printError(msg);
    currentError = (ParseError){
        .tok = toks[current],
        .msg = msg
    };
    longjmp(syncJump, 1);
}

// Unrecoverable error - panic & exit
STATIC void parserPanic(char* msg) {
    printError(msg);
    panic(Panic_Parser, "");
}

STATIC INLINE Token previous() {
    // todo: sexier way of handling this?
    if (current == 0) parserPanic("Can't have previous token from position 0!");
    return toks[current - 1];
}

STATIC INLINE Token peek() {
    return toks[current];
}

STATIC INLINE Token advance() {
    return toks[current++];
}

STATIC bool isAtEnd() {
    return peek().type == Tok_EOF;
}

// todo: refactor w/ varargs to allow matching on multiple types
STATIC bool match(TokType type) {
    if (isAtEnd()) return false;
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

STATIC Token consume(TokType type, char* message) {
    if (peek().type == type) return advance();
    error(message);
}

// forward decl
STATIC Declaration declaration();
STATIC Expression expression();

STATIC Expression primary() {
    if (!(
        match(Tok_Self) ||
        match(Tok_Nil) ||
        match(Tok_True) ||
        match(Tok_False) ||
        match(Tok_StringLit) ||
        match(Tok_IntLit) ||
        match(Tok_FloatLit) ||
        match(Tok_Identifier)
    )) {
        error("Unexpected token!");
    }
    return (Expression){
        .tag = ExprTag_Primary,
        .primary = previous()
    };
}

STATIC Expression grouping() {
    if (match(Tok_LParen)) {
        return (Expression){
            .tag = ExprTag_Grouping,
            .grouping = copyExpr(expression())
        };
    }
    return primary();
}

STATIC Expression super() {
    Expression out;
    if (match(Tok_Super)) {
        consume(Tok_Dot, "Expected '.' after 'super'");
        return (Expression){
            .tag = ExprTag_Super,
            .super = (SuperExpr){
                .memberName = consume(Tok_Identifier, "Expected an identifier")
            }
        };
    }

    return grouping();
}

STATIC ExprList argList(TokType end) {
    ExprList out;
    INIT(out);
    if (match(end)) return out;
    APPEND(out, expression());
    while (match(Tok_Comma)) {
        APPEND(out, expression());
    }
    consume(end, "Expected close bracket after arguments");
    return out;
}

STATIC Expression call() {
    Expression out = super();
    while (
        match(Tok_LParen) ||
        match(Tok_LSquare) ||
        match(Tok_Dot)
    ) {
        out = (Expression){
            .tag = ExprTag_Call,
            .call = (CallExpr){
                .callee = copyExpr(out)
            }
        };
        switch (previous().type) {
            case Tok_LParen: {
                out.call.tag = Call_Call;
                out.call.arguments = argList(Tok_RParen);
                break;
            }
            case Tok_LSquare: {
                out.call.tag = Call_Array;
                out.call.arguments = argList(Tok_RSquare);
                break;
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

STATIC Expression unary() {
    if (
        match(Tok_Not) ||
        match(Tok_Minus) ||
        match(Tok_New)
    ) {
        return (Expression){
            .tag = ExprTag_Unary,
            .unary = (UnaryExpr){
                .operator = previous(),
                .operand = copyExpr(unary())
            }
        };
    }
    return call();
}

STATIC Expression exponent() {
    Expression out = unary();
    while (match(Tok_Exp)) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(unary()),
                .operator = previous()
            }
        };
    }
    return out;
}

STATIC Expression factor() {
    Expression out = exponent();
    while (match(Tok_Star) || match(Tok_Slash)) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(exponent()),
                .operator = previous()
            }
        };
    }
    return out;
}

STATIC Expression term() {
    Expression out = factor();
    while (match(Tok_Plus) || match(Tok_Minus)) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(factor()),
                .operator = previous()
            }
        };
    }
    return out;
}

STATIC Expression comparison() {
    Expression out = term();
    while (
        match(Tok_Less) ||
        match(Tok_LessEqual) ||
        match(Tok_Greater) ||
        match(Tok_GreaterEqual)
    ) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(term()),
                .operator = previous()
            }
        };
    }
    return out;
}

STATIC Expression equality() {
    Expression out = comparison();
    while (match(Tok_EqualEqual) || match(Tok_BangEqual)) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(comparison()),
                .operator = previous()
            }
        };
    }
    return out;
}

STATIC Expression logicAnd() {
    Expression out = equality();
    while (match(Tok_And)) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(equality()),
                .operator = previous()
            }
        };
    }
    return out;
}

STATIC Expression logicOr() {
    Expression out = logicAnd();
    while (match(Tok_Or)) {
        out = (Expression){
            .tag = ExprTag_Binary,
            .binary = (BinaryExpr){
                .a = copyExpr(out),
                .b = copyExpr(logicAnd()),
                .operator = previous()
            }
        };
    }
    return out;
}

#define ASSIGNMENT(name, matchCond, parent) STATIC Expression name() { \
    Expression out = parent(); \
    if (matchCond) { \
        if (!( \
            out.tag == ExprTag_Call || \
            out.tag == ExprTag_Super || \
            out.tag == ExprTag_Primary \
        )) { \
            error("Can't assign to this type of expression!"); \
        } \
        out = (Expression){ \
            .tag = ExprTag_Binary, \
            .binary = (BinaryExpr){ \
                .a = copyExpr(out), \
                .b = copyExpr(name()), \
                .operator = previous() \
            } \
        }; \
    } \
    return out; \
}

ASSIGNMENT(expAssignment, match(Tok_ExpEqual), logicOr)
ASSIGNMENT(factorAssignment, match(Tok_StarEqual) || match(Tok_SlashEqual), expAssignment)
ASSIGNMENT(termAssignment, match(Tok_PlusEqual) || match(Tok_MinusEqual), factorAssignment)
ASSIGNMENT(assignment, match(Tok_Equal), termAssignment)

STATIC Expression expression() {
    return assignment();
}

STATIC INLINE ParamPassMode passMode() {
    if (match(Tok_ByRef)) return Param_byRef;
    else if (match(Tok_ByVal)) return Param_byVal;
    error("Expected 'byRef' or 'byVal'");
}

STATIC Parameter param() {
    Parameter out;
    out.name = consume(Tok_Identifier, "Expected parameter name");
    if (match(Tok_Colon)) {
        out.passMode = passMode();
    } else {
        out.passMode = Param_byVal;
    }
    return out;
}

STATIC void params(ParamList* out) {
    consume(Tok_LParen, "Expected '('");
    if (!match(Tok_RParen)) {
        APPEND(*out, param());
        while (match(Tok_Comma)) {
            APPEND(*out, param());
        }
        consume(Tok_RParen, "Expected ')'");
    }
}

STATIC void block(DeclList* block, TokType end) {
    while (!match(end)) {
        APPEND(*block, declaration());
    }
}

STATIC FunDecl function() {
    FunDecl out;
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

STATIC ProcDecl procedure() {
    ProcDecl out;
    INIT(out.params);
    DECL_LIST_INIT(out.block);
    consume(Tok_Procedure, "Expected 'procedure'");
    out.name = consume(Tok_Identifier, "Expected procedure name");
    params(&out.params);
    block(out.block, Tok_EndProcedure);
    return out;
}

STATIC ClassDecl class() {
    parserPanic("not a thing yet :(");
}

STATIC GlobalStmt global() {
    GlobalStmt out;

    consume(Tok_Global, "Expected 'global'");
    out.name = consume(Tok_Identifier, "Expected global name");
    consume(Tok_Equal, "Expected '='");
    out.initializer = expression();

    return out;
}

STATIC ForStmt for_() {
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
        error("Differing iterator names!");
    }

    return out;
}

STATIC WhileStmt while_() {
    WhileStmt out;

    DECL_LIST_INIT(out.block);

    consume(Tok_While, "Expected 'while'");
    out.condition = expression();
    block(out.block, Tok_EndWhile);

    return out;
}

STATIC DoStmt do_() {
    DoStmt out;

    DECL_LIST_INIT(out.block);

    consume(Tok_Do, "Expected 'do'");
    block(out.block, Tok_Until);
    out.condition = expression();

    return out;
}

// this is what happens when you mistakenly think including
// "elseif" in the specification is a good idea
STATIC IfStmt if_() {
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

STATIC SwitchStmt switch_() {
    SwitchStmt out;

    INIT(out.cases);
    out.hasDefault = false;

    consume(Tok_Switch, "Expected 'switch'");
    out.expr = expression();


    while (!match(Tok_EndSwitch)) {
        if (out.hasDefault) error("'default' must be the last case in a switch statement!");
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

STATIC ArrayStmt array() {
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

STATIC Statement statement() {
    Statement out;
    // how d'you even go about handling an expr stmt?
    switch (peek().type) {
        case Tok_Global:
            out.tag = StmtTag_Global;
            out.global = global();
            return out;
        case Tok_For:
            out.tag = StmtTag_For;
            out.for_ = for_();
            return out;
        case Tok_While:
            out.tag = StmtTag_While;
            out.while_ = while_();
            return out;
        case Tok_Do:
            out.tag = StmtTag_Do;
            out.do_ = do_();
            return out;
        case Tok_If:
            out.tag = StmtTag_If;
            out.if_ = if_();
            return out;
        case Tok_Switch:
            out.tag = StmtTag_Switch;
            out.switch_ = switch_();
            return out;
        case Tok_Array:
            out.tag = StmtTag_Array;
            out.array = array();
            return out;
        default:
            out.tag = StmtTag_Expr;
            out.expr = expression();
            return out;
    }
}

STATIC Declaration declaration() {
    Declaration out;
    switch (peek().type) {
        case Tok_Function:
            out.tag = DeclTag_Fun;
            out.fun = function();
            return out;
        case Tok_Procedure:
            out.tag = DeclTag_Proc;
            out.proc = procedure();
            return out;
        case Tok_Class:
            out.tag = DeclTag_Class;
            out.class = class();
            return out;
        default:
            out.tag = DeclTag_Stmt;
            out.stmt = statement();
            return out;
    }
}

ParseOutput parse(LexOutput lo) {
    current = 0;
    toks = lo.root;

    ParseOutput out;
    INIT(out.ast);
    INIT(out.errors);

    Declaration newDecl;
    while (!isAtEnd()) {
        if (! setjmp(syncJump)) {
            APPEND(out.ast, declaration());
        } else {
            APPEND(out.errors, currentError);
            while (!(
                peek().type == Tok_Global ||
                peek().type == Tok_For ||
                peek().type == Tok_While ||
                peek().type == Tok_Do ||
                peek().type == Tok_If ||
                peek().type == Tok_Switch ||
                peek().type == Tok_Array ||
                peek().type == Tok_Function ||
                peek().type == Tok_Procedure ||
                peek().type == Tok_Class ||
                isAtEnd()
            )) {
                advance();
            }
        }
    }

    return out;
}

STATIC void destroyBlock(DeclList block);

#define DECL_LIST_DESTROY(dl) do { \
    destroyBlock(*(dl)); \
    DESTROY(*(dl)); \
    free(dl); \
} while (0)

STATIC void destroyExpression(Expression expr) {

}

STATIC void destroyConditionalBlock(ConditionalBlock cb) {
    destroyExpression(cb.condition);
    DECL_LIST_DESTROY(cb.block);
}

STATIC void destroyStatement(Statement stmt) {
    switch (stmt.tag) {
        case StmtTag_Global: {
            break;
        }
        case StmtTag_For: {
            break;
        }
        case StmtTag_While: {
            destroyConditionalBlock(stmt.while_);
            break;
        }
        case StmtTag_Do: {
            destroyConditionalBlock(stmt.do_);
            break;
        }
        case StmtTag_If: {
            destroyConditionalBlock(stmt.if_.primary);
            FOREACH(ConditionalBlock*, currentBranch, stmt.if_.secondary) {

            }
            break;
        }
        case StmtTag_Switch: {
            destroyExpression(stmt.switch_.expr);
            FOREACH(ConditionalBlock*, currentCase, stmt.switch_.cases) {
                destroyConditionalBlock(*currentCase);
            }
            DESTROY(stmt.switch_.cases);
            if (stmt.switch_.hasDefault) {
                DECL_LIST_DESTROY(stmt.switch_.default_);
            }
            break;
        }
        case StmtTag_Array: {
            FOREACH(Expression*, currentDimension, stmt.array.dimensions) {
                destroyExpression(*currentDimension);
            }
            DESTROY(stmt.array.dimensions);
            break;
        }
        case StmtTag_Expr: {
            break;
        }
    }
}

STATIC void destroyDeclaration(Declaration decl) {
    switch (decl.tag) {
        case DeclTag_Class: {
            break;
        }
        case DeclTag_Fun: {
            DESTROY(decl.fun.params);
            FOREACH(DeclOrReturn*, currentDOR, decl.fun.block) {
                switch (currentDOR->tag) {
                    case DOR_decl: {
                        destroyDeclaration(*currentDOR->declaration);
                        free(currentDOR->declaration);
                    }
                    case DOR_return: {
                        destroyExpression(currentDOR->return_);
                    }
                }
            }
            DESTROY(decl.fun.block);
            break;
        }
        case DeclTag_Proc: {
            DESTROY(decl.proc.params);
            DECL_LIST_DESTROY(decl.proc.block);
            break;
        }
        case DeclTag_Stmt: {
            destroyStatement(decl.stmt);
            break;
        }
    }
}

STATIC void destroyBlock(DeclList block) {
    FOREACH (Declaration*, currentDecl, block) {
        destroyDeclaration(*currentDecl);
    }
}

// yoooooooooooo
void destroyParseOutput(ParseOutput po) {
    destroyBlock(po.ast);
    DESTROY(po.ast);
    DESTROY(po.errors);
}