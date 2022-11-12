#ifndef TOKENS_HPP_
#define TOKENS_HPP_

#include <cstdlib>

enum tokentype {
    VOID = 1,
    INT = 2,
    BYTE = 3,
    B = 4,
    BOOL = 5,
    AND = 6,
    OR = 7,
    NOT = 8,
    TRUE = 9,
    FALSE = 10,
    RETURN = 11,
    IF = 12,
    ELSE = 13,
    WHILE = 14,
    BREAK = 15,
    CONTINUE = 16,
    SC = 17,
    COMMA = 18,
    LPAREN = 19,
    RPAREN = 20,
    LBRACE = 21,
    RBRACE = 22,
    ASSIGN = 23,
    RELOP = 24,
    BINOP = 25,
    COMMENT = 26,
    ID = 27,
    NUM = 28,
    STRING = 29,
    WHITESPACE = 30,
    UNCLOSED_STRING = 31,
    WRONG_CHAR = 32,
    ZERO_FIRST = 33
};

static const char* tokenNames[] = {
    "",
    "VOID",
    "INT",
    "BYTE",
    "B",
    "BOOL",
    "AND",
    "OR",
    "NOT",
    "TRUE",
    "FALSE",
    "RETURN",
    "IF",
    "ELSE",
    "WHILE",
    "BREAK",
    "CONTINUE",
    "SC",
    "COMMA",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "ASSIGN",
    "RELOP",
    "BINOP",
    "COMMENT",
    "ID",
    "NUM",
    "STRING",
    "WHITESPACE",
    "UNCLOSED_STRING",
    "WRONG_CHAR",
    "ZERO_FIRST"
};

extern int yylineno;
extern char* yytext;
extern int yyleng;
extern int yylex();

#endif /* TOKENS_HPP_ */
