#include "lexer.h"

#include <stdbool.h>

static char* start;
static char* current;

void destroyLexOutput(LexOutput lo) {
    DESTROY(lo.toks);
    DESTROY(lo.errors);
}

static bool isAtEnd() {
    return *current == 0;
}

LexOutput lex(char* source) {
    TokList toks;
    LexErrList errors;
    INIT(toks);
    INIT(errors);

    while (!isAtEnd()) {

    }

    return (LexOutput){toks, errors};
}