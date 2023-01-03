#include "lexer.h"

#include <stdbool.h>
#include <string.h>

static char* start;
static char* current;
static int line;
static int col;

void destroyLexOutput(LexOutput lo) {
    DESTROY(lo);
}

static bool isAtEnd() {
    return *current == 0;
}

static char advance() {
    col++;
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
    advance();
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
                advance();
                break;
            case '\n':
                line++;
                advance();
                col = 1;
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
        .length = current - start,
        .line = line,
        // todo: does this work for multiline tokens? how do we even
        // parse multiline tokens??????
        .col = col - (current - start)
    };
    // Token out = (Token) {
    //     .type = type,
    //     .start = start,
    //     .length = current - start,
    //     .line = line,
    //     .col = col - (current - start)
    // };
    // char* text = tokText(out);
    // printf("'%s' at line %i, column %i\n", text, out.line, out.col);
    // free(text);
    // return out;
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
                    case 'R': return makeTok(checkKeyword(3, "ef", Tok_ByRef));
                    case 'V': return makeTok(checkKeyword(3, "al", Tok_ByVal));
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
                            case 's': return makeTok(checkKeyword(4, "witch", Tok_EndSwitch));
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
            break;
        case 'M': return makeTok(checkKeyword(1, "OD", Tok_Mod));
        case 'n':
            // todo: test
            if (current - start == 3 && start[1] == 'i' && start[2] == 'l') return makeTok(Tok_Nil);
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
        case 't':
            if (current - start == 2 && start[1] == 'o') return makeTok(Tok_To);
            if (current - start > 1) return makeTok(checkKeyword(1, "hen", Tok_Then));
            break;
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

        case '+': return makeTok(match('=')
            ? Tok_PlusEqual
            : Tok_Plus
        );
        case '-': return makeTok(match('=')
            ? Tok_MinusEqual
            : Tok_Minus
        );
        case '*': return makeTok(match('=')
            ? Tok_StarEqual
            : Tok_Star
        );
        case '/': return makeTok(match('=')
            ? Tok_SlashEqual
            : Tok_Slash
        );
        case '^': return makeTok(match('=')
            ? Tok_ExpEqual
            : Tok_Exp
        );

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
    line = 1;
    col = 1;

    TokList toks;
    INIT(toks);

    while (!isAtEnd()) {
        skipWhitespace();
        
        start = current;

        char c = advance();

        if (isAlpha(c)) APPEND(toks, identifier());
        else if (isDigit(c)) APPEND(toks, number());
        else APPEND(toks, symbol(c));
    }

    APPEND(toks, ((Token){
        .type = Tok_EOF,
        .start = current,
        .length = 0,
        .line = line,
        .col = col - (current - start)
    }));

    return toks;
}

char* tokText(Token tok) {
    char* out = malloc(tok.length + 1);
    memcpy(out, tok.start, tok.length);
    out[tok.length] = '\0';
    return out;
}