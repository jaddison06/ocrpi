#pragma once

#include "vector.h"

typedef enum {
    // Single and double symbols
    Tok_Equal, Tok_EqualEqual, Tok_BangEqual, Tok_Less, Tok_LessEqual, Tok_Greater, Tok_GreaterEqual,
    Tok_Plus, Tok_Minus, Tok_Star, Tok_Slash, Tok_Exp,
    Tok_PlusEqual, Tok_MinusEqual, Tok_StarEqual, Tok_SlashEqual, Tok_ExpEqual,
    Tok_Colon, Tok_Dot, Tok_Comma, Tok_LParen, Tok_RParen, Tok_LSquare, Tok_RSquare,

    // Keywords
    Tok_Global, Tok_For, Tok_To, Tok_Next, Tok_While, Tok_EndWhile, Tok_Do, Tok_Until, Tok_If, Tok_Then, Tok_ElseIf, Tok_Else, Tok_EndIf,
    Tok_Switch, Tok_Case, Tok_Default, Tok_EndSwitch,
    Tok_And, Tok_Or, Tok_Not, Tok_Mod, Tok_Div,
    Tok_Function, Tok_Return, Tok_EndFunction, Tok_Procedure, Tok_EndProcedure, Tok_ByVal, Tok_ByRef,
    Tok_Class, Tok_EndClass, Tok_Inherits, Tok_Public, Tok_Private, Tok_Super, Tok_Self, Tok_New,
    Tok_Array,

    // Literals + identifiers
    Tok_StringLit, Tok_IntLit, Tok_FloatLit, Tok_Nil, Tok_Identifier,

    // EOF
    Tok_EOF
} TokType;

typedef struct {
    TokType type;
    char* start;
    int length;
    int line, col;
} Token;

DECL_VEC(Token, TokList)
typedef TokList LexOutput;

// ALLOCATES!
//
// Copy token contents into a standalone, null-terminated string
char* tokText(Token tok);

void destroyLexOutput(LexOutput lo);
LexOutput lex(char* source);