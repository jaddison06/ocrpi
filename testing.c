#include "testing.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"

static char* module;

// slightly yucky but we move
#define expect(expression) _expect(expression, #expression)
#define expectStr(expression, expected) _expectStr(expression, #expression, expected)
#define expectNStr(expression, length, expected) _expectNStr(expression, #expression, length, expected)

static void _expect(bool expression, char* expressionString) {
    static char* oldModule = NULL;
    static int id;
    if (
        oldModule == NULL ||
        strcmp(oldModule, module) != 0
    ) {
        oldModule = module;
        id = 1;
        printf("\nTesting module '%s':\n", module);
    }

    if (!expression) {
        printf("\033[0;31mTest %i (%s) failed\033[0m\n", id++, expressionString);
        exit(70);
    } else {
        printf("\033[0;32mTest %i passed\033[0m\n", id++);
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
    LexOutput output = lex(source);
    expect(output.errors.len == 0);
    expect(output.toks.len == 8);

#define expectTok(idx, theType) expect(output.toks.root[idx].type == theType)

    expectTok(0, Tok_If);
    expectTok(1, Tok_EndIf);
    expectTok(2, Tok_EndWhile);
    expectTok(3, Tok_Switch);
    expectTok(4, Tok_Case);
    expectTok(5, Tok_Identifier);
    expectTok(6, Tok_LBracket);
    expectTok(7, Tok_RBracket);

    destroyLexOutput(output);
}