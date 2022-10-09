#include "lexer.h"

#include <stdbool.h>
#include <string.h>

static char* start;
static char* current;

void destroyLexOutput(LexOutput lo) {
    DESTROY(lo.toks);
    DESTROY(lo.errors);
}

static bool isAtEnd() {
    return *current == 0;
}

static char advance() {
    return *current++;
}

static char peek() {
    return *current;
}

static char peekNext() {
    if (isAtEnd()) return 0;
    return current[1];
}

static bool match(char expected) {
    if (isAtEnd()) return false;
    if (peek() != expected) return false;
    current++;
    return true;
}

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static bool isAlpha(char c) {
    return
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

static void skipWhitespace() {
    for (;;) {
        switch (peek()) {
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else return;
                break;
            default:
                return;
        }
    }
}

static inline Token makeTok(TokType type) {
    return (Token){
        .type = type,
        .start = start,
        .length = current - start
    };
}

static TokType checkKeyword(int kwStart, char* rest, TokType type) {
    int length = strlen(rest);
    if (
        current - start == kwStart + length &&
        strncmp(start + kwStart, rest, length) == 0
    ) return type;

    return Tok_Identifier;
}

static Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();

    switch (start[0]) {
        case 'a': return makeTok(checkKeyword(1, "rray", Tok_Array));
        case 'A': return makeTok(checkKeyword(1, "ND", Tok_And));
        case 'b':
            if (current - start > 2 && start[1] == 'y') {
                switch (start[2]) {
                    case 'R': return makeTok(checkKeyword(2, "ef", Tok_ByRef));
                    case 'V': return makeTok(checkKeyword(2, "al", Tok_ByVal));
                }
            }
            break;
        case 'c':
            if (current - start > 1) {
                switch (start[1]) {
                    case 'a': return makeTok(checkKeyword(2, "se", Tok_Case));
                    case 'l': return makeTok(checkKeyword(2, "ass", Tok_Class));
                }
            }
            break;
        case 'd':
            if (current - start == 1 && start[1] == 'o') return makeTok(Tok_Do);
            if (current - start > 1) return makeTok(checkKeyword(1, "efault", Tok_Default));
            break;
        case 'D': return makeTok(checkKeyword(1, "IV", Tok_Div));
        //! uh oh
        case 'e':
            if (current - start > 3) {
                switch (start[1]) {
                    case 'l':
                        if (current - start == 4) return makeTok(checkKeyword(2, "se", Tok_Else));
                        else return makeTok(checkKeyword(2, "seif", Tok_ElseIf));
                    case 'n':
                        if (start[2] != 'd') return;
                        switch (start[3]) {
                            case 'c': return makeTok(checkKeyword(4, "lass", Tok_EndClass));
                            case 'f': return makeTok(checkKeyword(4, "unction", Tok_EndFunction));
                            case 'i': return makeTok(checkKeyword(4, "f", Tok_EndIf));
                            case 'p': return makeTok(checkKeyword(4, "rocedure", Tok_EndProcedure));
                            case 's': return makeTok(checkKeyword(4, "witch", Tok_Endswitch));
                            case 'w': return makeTok(checkKeyword(4, "hile", Tok_EndWhile));
                        }
                }
            }
            break;
    }
    
    return makeTok(Tok_Identifier);
}

static Token number() {

}

static Token string() {

}


static Token symbol(char c) {
    // todo: fallthrough to an error-handling default
    switch (c) {
        case '=': return makeTok(match('=')
            ? Tok_EqualEqual
            : Tok_Equal
        );
        case '!': return makeTok(match('=')
            ? Tok_BangEqual
            : Tok_Not // todo: this is actually a serious error
        );
        case '<': return makeTok(match('=')
            ? Tok_LessEqual
            : Tok_Less
        );
        case '>': return makeTok(match('=')
            ? Tok_GreaterEqual
            : Tok_Greater
        );

        case '+': return makeTok(Tok_Plus);
        case '-': return makeTok(Tok_Minus);
        case '*': return makeTok(Tok_Star);
        case '/': return makeTok(Tok_Slash);
        case '^': return makeTok(Tok_Exp);
        case ':': return makeTok(Tok_Colon);
        case '.': return makeTok(Tok_Dot);
        case '(': return makeTok(Tok_LBracket);
        case ')': return makeTok(Tok_RBracket);
        case '[': return makeTok(Tok_LSquare);
        case ']': return makeTok(Tok_RSquare);

        case '"': return string();
    }
}

LexOutput lex(char* source) {

// workaround for my horrible macro being unable to append literals to an array
    Token newTok;
    LexError newErr;
#define addTok(tok) do { \
    newTok = tok; \
    APPEND(toks, newTok); \
} while (0)

#define addErr(err) do { \
    newErr = err; \
    APPEND(errors, newErr); \
} while(0)

    TokList toks;
    LexErrList errors;
    INIT(toks);
    INIT(errors);

    while (!isAtEnd()) {
        skipWhitespace();
        
        start = current;
        if (isAtEnd) {
            addTok(makeTok(Tok_EOF));
        }

        char c = advance();

        if (isAlpha(c)) addTok(identifier());
        if (isDigit(c)) addTok(number());

        addTok(symbol(c));
    }

    return (LexOutput){
        .toks = toks,
        .errors = errors
    };
}