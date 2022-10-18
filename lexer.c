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
    return (Token) {
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
                        if (start[2] != 'd') break;
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
        case 'f':
            if (current - start > 1) {
                switch (start[1]) {
                    case 'o': return makeTok(checkKeyword(2, "r", Tok_For));
                    case 'u': return makeTok(checkKeyword(2, "nction", Tok_Function));
                }
            }
            break;
        case 'g': return makeTok(checkKeyword(1, "lobal", Tok_Global));
        case 'i':
            if (current - start == 2 && start[1] == 'f') return makeTok(Tok_If);
            if (current - start > 1) return makeTok(checkKeyword(1, "nherits", Tok_Inherits));
        case 'M': return makeTok(checkKeyword(1, "OD", Tok_Mod));
        case 'n':
            if (current - start > 2 && start[1] == 'e') {
                if (current - start == 3 && start[2] == 'w') return makeTok(Tok_New);
                return makeTok(checkKeyword(2, "xt", Tok_Next));
            }
            break;
        case 'N': return makeTok(checkKeyword(1, "OT", Tok_Not));
        case 'O': return makeTok(checkKeyword(1, "R", Tok_Or));
        case 'p':
            if (current - start > 2) {
                switch (start[1]) {
                    case 'r':
                        switch (start[2]) {
                            case 'i': return makeTok(checkKeyword(3, "vate", Tok_Private));
                            case 'o': return makeTok(checkKeyword(3, "cedure", Tok_Procedure));
                        }
                    case 'u': return makeTok(checkKeyword(2, "blic", Tok_Public));
                }
            }
            break;
        case 'r': return makeTok(checkKeyword(1, "eturn", Tok_Return));
        case 's':
            if (current - start > 1) {
                switch (start[1]) {
                    case 'e': return makeTok(checkKeyword(2, "lf", Tok_Self));
                    case 'u': return makeTok(checkKeyword(2, "per", Tok_Super));
                    case 'w': return makeTok(checkKeyword(2, "itch", Tok_Switch));
                }
            }
            break;
        case 't': return makeTok(checkKeyword(1, "hen", Tok_Then));
        case 'u': return makeTok(checkKeyword(1, "ntil", Tok_Until));
        case 'w': return makeTok(checkKeyword(1, "hile", Tok_While));
    }
    
    return makeTok(Tok_Identifier);
}

static Token number() {
    bool isFloat = false;
    while (isDigit(peek())) advance();
    if (peek() == '.' && isDigit(peekNext())) {
        isFloat = true;
        advance();
        while (isDigit(peek())) advance();
    }
    return makeTok(isFloat ? Tok_FloatLit : Tok_IntLit);
}

static Token string() {
    while (peek() != '"' && !isAtEnd()) advance();

    // todo: handle error
    if (isAtEnd());

    advance();

    return makeTok(Tok_StringLit);
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
        case ',': return makeTok(Tok_Comma);
        case '(': return makeTok(Tok_LParen);
        case ')': return makeTok(Tok_RParen);
        case '[': return makeTok(Tok_LSquare);
        case ']': return makeTok(Tok_RSquare);

        case '"': return string();
    }
}

LexOutput lex(char* source) {
    start = current = source;

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
        if (isAtEnd()) {
            addTok(makeTok(Tok_EOF));
            break;
        }

        char c = advance();

        if (isAlpha(c)) addTok(identifier());
        else if (isDigit(c)) addTok(number());
        else addTok(symbol(c));
    }

    return (LexOutput){
        .toks = toks,
        .errors = errors
    };
}