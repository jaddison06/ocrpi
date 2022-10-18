#include "parser.h"

#include <stdbool.h>

int current = 0;

Token* toks;

static bool isAtEnd() {
    return toks[current].type == Tok_EOF;
}

static Token advance() {
    return toks[current++];
}

static Token peek() {
    return toks[current];
}

ParserOutput parse(LexOutput lo) {
    toks = lo.toks.root;

    ParserOutput out;
    INIT(out.ast.declarations);
    INIT(out.errors);

    while (!isAtEnd()) {
        
    }
}