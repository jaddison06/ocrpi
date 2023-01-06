#include "testing.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "panic.h"

#include "readFile.h"
#include "map.h"

static char* module;
static int testCount = 0;

// slightly yucky but we move
#define expect(expression) _expect(expression, #expression)
#define expectStr(expression, expected) _expectStr(expression, #expression, expected)
#define expectNStr(expression, length, expected) _expectNStr(expression, #expression, length, expected)

static void _expect(bool expression, char* expressionString) {
    static char* oldModule = NULL;
    static int id;

    testCount++;

    if (
        oldModule == NULL ||
        strcmp(oldModule, module) != 0
    ) {
        oldModule = module;
        id = 1;
        printf("\n ! Testing module '%s':\n", module);
    }

    if (!expression) {
        printf(" ! \033[0;31mTest %i (%s) failed :-(\033[0m\n", id++, expressionString);
        exit(70);
    } else {
        printf("<3 \033[0;32mTest %i passed\033[0m\n", id++);
    }
}

static void _expectStr(char* expression, char* expressionStr, char* expected) {
    char* buf = malloc(strlen(expressionStr) + strlen(expression) + strlen(expected) + 13);
    sprintf(buf, "%s (-> \"%s\") == \"%s\"", expressionStr, expression, expected);
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

static void test_lexer() {
    char* source = readFile("test/lex.ocr");
    LexOutput lo = lex(source);
    expect(lo.len == 25);

#define expectTok(idx, theType) expect(lo.root[idx].type == theType)

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
    expectTok(13, Tok_Nil);
    expectTok(14, Tok_New);
    expectTok(15, Tok_Next);
    expectTok(16, Tok_Identifier);
    expectTok(17, Tok_False);
    expectTok(18, Tok_For);
    expectTok(19, Tok_Function);
    expectTok(20, Tok_Identifier);
    expectTok(21, Tok_To);
    expectTok(22, Tok_True);
    expectTok(23, Tok_Then);
    expectTok(24, Tok_EOF);
}

static void test_parser() {
    char* source = readFile("test/parse.ocr");
    LexOutput lo = lex(source);
    expect(lo.len == 35);

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
}

static void test_parser_error_reporting() {
    char* source = readFile("test/errorRecovery.ocr");
    LexOutput lo = lex(source);
    ParseOutput po = parse(lo);

    expect(po.errors.len == 2);
    expectStr(po.errors.root[0].msg, "Unexpected token!");
    expectStr(po.errors.root[1].msg, "Expected function name");
}

DECL_MAP(int, IntMap)

static void test_map() {
    IntMap intMap = NewIntMap();
    expect(IntMapFind(&intMap, "eeee") == NULL);
    IntMapSet(&intMap, "eeee", 3);
    expect(IntMapFind(&intMap, "eeee") != NULL);
    expect(*IntMapFind(&intMap, "eeee") == 3);
    IntMapSet(&intMap, "eeee", 5);
    expect(IntMapFind(&intMap, "eeee") != NULL);
    expect(*IntMapFind(&intMap, "eeee") == 5);
    int count = 0;
    FOREACH(IntMap, intMap, entry) {
        count++;
        expectStr(entry->key, "eeee");
        expect(entry->value == 5);
    }
    expect(count == 1);
    IntMapRemove(&intMap, "eeee");
    expect(IntMapFind(&intMap, "eeee") == NULL);
}

static void test_interpreter() {
    InterpreterObj* result = interpretExpr((Expression){
        .tag = ExprTag_Primary,
        .primary = (Token){
            .col = 0,
            .length = 7,
            .line = 0,
            .start = "\"balls\"",
            .type = Tok_StringLit
        }
    });
    expect(result->tag == ObjType_String);
    expectStr(result->string, "balls");

    Expression a = ((Expression){
        .tag = ExprTag_Primary,
        .primary = (Token){
            .col = 0,
            .length = 1,
            .line = 0,
            .start = "3",
            .type = Tok_IntLit
        }
    });

    Expression b = ((Expression){
        .tag = ExprTag_Primary,
        .primary = (Token){
            .col = 0,
            .length = 1,
            .line = 0,
            .start = "5",
            .type = Tok_IntLit
        }
    });

    result = interpretExpr((Expression){
        .tag = ExprTag_Binary,
        .binary = (BinaryExpr){
            .operator = (Token){
                .col = 0,
                .length = 1,
                .line = 0,
                .start = "+",
                .type = Tok_Plus
            },
            .a = &a,
            .b = &b
        }
    });

    expect(result->tag == ObjType_Int);
    expect(result->int_ == 8);
}

static void panickingFunc() {
    printf("panicking\n");
    panic(PANIC_CATCHABLE(Panic_Test, PCC_Test), "balls!!!!!!!");
}

static void test_panic() {
    PANIC_TRY {
        panickingFunc();
    } PANIC_CATCH(PCC_Test) {
        expect((_panicRet & _PANIC_CODE_MASK) == Panic_Test);
        expect((_panicRet & _PANIC_CATCHABLE_CODE_MASK) >> 8 == PCC_Test);
        expect(_panicRet & _PANIC_CATCHABLE_FLAG);
    } PANIC_END_TRY
}

DECL_VEC(int, IntVec)

static void test_vector() {
    IntVec ints;
    INIT(ints);
    APPEND(ints, 1);
    APPEND(ints, 2);
    APPEND(ints, 3);
    int j = 1;
    FOREACH(IntVec, ints, i) {
        expect(*i == j++);
    }
}

#define TEST_MODULE(name) do { module = #name; test_##name(); } while (0)

void testAll() {
    TEST_MODULE(lexer);
    TEST_MODULE(parser);
    TEST_MODULE(parser_error_reporting);
    TEST_MODULE(map);
    TEST_MODULE(interpreter);
    TEST_MODULE(panic);
    TEST_MODULE(vector);   
    printf("\n ! \033[0;32m%i tests passed!! <333333\033[0m\n", testCount);
}