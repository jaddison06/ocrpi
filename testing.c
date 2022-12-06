#include "testing.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

static char* module;

// slightly yucky but we move
#define expect(expression) _expect(expression, #expression)
#define expectStr(expression, expected) _expectStr(expression, #expression, expected)
#define expectNStr(expression, length, expected) _expectNStr(expression, #expression, length, expected)

static bool _allPassed = true;
static bool _exitRegistered = false;

static void _onExit() {
    if (_allPassed) printf("\n ! \033[0;32mAll tests passed!! <333333\033[0m\n");
}

static void _expect(bool expression, char* expressionString) {
    if (!_exitRegistered) {
        atexit(_onExit);
        _exitRegistered = true;
    }

    static char* oldModule = NULL;
    static int id;
    if (
        oldModule == NULL ||
        strcmp(oldModule, module) != 0
    ) {
        oldModule = module;
        id = 1;
        printf("\n ! Testing module '%s':\n", module);
    }

    if (!expression) {
        _allPassed = false;
        printf(" ! \033[0;31mTest %i (%s) failed :(\033[0m\n", id++, expressionString);
        exit(70);
    } else {
        printf("<3 \033[0;32mTest %i passed\033[0m\n", id++);
    }
}

static void _expectStr(char* expression, char* expressionStr, char* expected) {
    char* buf = malloc(strlen(expressionStr) + strlen(expression) + strlen(expected) + 13);
    sprintf(buf, "%s -> '%s' == '%s'", expressionStr, expression, expected);
    _expect(strcmp(expression, expected) == 0, buf);
    free(buf);
}

static void _expectNStr(char* expression, char* expressionStr, int length, char* expected) {
    char* buf = malloc(length + 1);
    strncpy(buf, expression, length);
    buf[length] = 0;
    int lengthStrLen = snprintf(NULL, 0, "%d", length);
    char* newExpressionStr = malloc(strlen(expressionStr) + lengthStrLen + 3);
    sprintf(newExpressionStr, "%s :%d", expressionStr, length);
    _expectStr(buf, newExpressionStr, expected);
    free(newExpressionStr);
    free(buf);
}

static char* readFile(char* path) {
    FILE* fp = fopen(path, "rb");

    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);
    rewind(fp);

    char* out = malloc(fileSize + 1);

    fread(out, sizeof(char), fileSize, fp);

    out[fileSize] = 0;

    fclose(fp);

    return out;
}

void testAll() {
    module = "lexer";
    char* source = readFile("test/lex.ocr");
    LexOutput lo = lex(source);
    expect(lo.errors.len == 0);
    expect(lo.toks.len == 14);

#define expectTok(idx, theType) expect(lo.toks.root[idx].type == theType)

    expectTok(0, Tok_If);
    expectTok(1, Tok_EndIf);
    expectTok(2, Tok_EndWhile);
    expectTok(3, Tok_Switch);
    expectTok(4, Tok_Case);
    expectTok(5, Tok_Identifier);
    expectTok(6, Tok_LParen);
    expectTok(7, Tok_RParen);
    expectTok(8, Tok_Comma);
    expectTok(9, Tok_Comma);
    expectTok(10, Tok_Comma);
    expectTok(11, Tok_ByRef);
    expectTok(12, Tok_ByVal);
    expectTok(13, Tok_EOF);

    module = "parser";
    source = readFile("test/parse.ocr");
    lo = lex(source);
    expect(lo.toks.len == 35);

    ParseOutput po = parse(lo);
    // general checks
    expect(po.errors.len == 0);
    expect(po.ast.len == 1);
    // function parsed correctly?
    expect(po.ast.root[0].tag == DeclTag_Fun);
    FunDecl fun = po.ast.root[0].fun;
    // name
    expect(fun.name.length == 11);
    expectNStr(fun.name.start, 11, "doSomething");
    // params
    expect(fun.params.len == 3);
    Parameter* params = fun.params.root;
    expect(params[0].name.length == 1);
    expect(params[0].name.start[0] == 'a');
    expect(params[0].passMode == Param_byVal);
    expect(params[1].name.length == 1);
    expect(params[1].name.start[0] == 'b');
    expect(params[1].passMode == Param_byVal);
    expect(params[2].name.length == 1);
    expect(params[2].name.start[0] == 'c');
    expect(params[2].passMode == Param_byRef);

    // contents
    expect(fun.block.len == 2);
    
    expect(fun.block.root[0].tag == DOR_decl);
    Declaration* declA = fun.block.root[0].declaration;
    expect(declA->tag == DeclTag_Stmt);
    expect(declA->stmt.tag == StmtTag_Expr);
    expect(declA->stmt.expr.tag = ExprTag_Binary);
    BinaryExpr binary = declA->stmt.expr.binary;
    expect(binary.operator.length == 1);
    expectNStr(binary.operator.start, 1, "+");
    expect(binary.a->tag = ExprTag_Primary);
    expect(binary.a->primary.length == 1);
    expectNStr(binary.a->primary.start, 1, "1");
    expect(binary.b->tag = ExprTag_Primary);
    expect(binary.b->primary.length == 1);
    expectNStr(binary.b->primary.start, 1, "2");

    expect(fun.block.root[1].tag == DOR_decl);
    Declaration* declB = fun.block.root[1].declaration;
    expect(declB->tag == DeclTag_Stmt);
    expect(declB->stmt.tag == StmtTag_Expr);
    expect(declB->stmt.expr.tag == ExprTag_Call);
    CallExpr call = declB->stmt.expr.call;
    expect(call.tag == Call_Call);
    expect(call.callee->tag == ExprTag_Super);
    expect(call.callee->super.memberName.length == 6);
    expectNStr(call.callee->super.memberName.start, 6, "method");
    expect(call.arguments.len == 3);
    Expression* args = call.arguments.root;

    expect(args[0].tag == ExprTag_Primary);
    expect(args[0].primary.type == Tok_Identifier);
    expect(args[0].primary.length == 1);
    expectNStr(args[0].primary.start, 1, "b");

    expect(args[1].tag == ExprTag_Primary);
    expect(args[1].primary.type == Tok_Identifier);
    expect(args[1].primary.length == 1);
    expectNStr(args[1].primary.start, 1, "c");

    expect(args[2].tag == ExprTag_Binary);
    BinaryExpr binaryB = args[2].binary;
    expect(binaryB.operator.length == 1);
    expectNStr(binaryB.operator.start, 1, "*");
    expect(binaryB.a->tag == ExprTag_Call);
    CallExpr callB = binaryB.a->call;
    expect(callB.tag == Call_Array);
    expect(callB.arguments.len == 2);
    Expression* argsB = callB.arguments.root;
    
    expect(argsB[0].tag == ExprTag_Primary);
    expect(argsB[0].primary.length == 1);
    expectNStr(argsB[0].primary.start, 1, "3");

    expect(argsB[1].tag == ExprTag_Primary);
    expect(argsB[1].primary.length == 1);
    expectNStr(argsB[1].primary.start, 1, "4");

    expect(binaryB.b->tag == ExprTag_Primary);
    expect(binaryB.b->primary.length == 1);
    expectNStr(binaryB.b->primary.start, 1, "5");

    module = "checker";
    source = readFile("test/check.ocr");
    lo = lex(source);
    po = parse(lo);
}