%{
/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap
digit   		                              ([0-9])
letter  		                              ([a-zA-Z])
printable_letters                             ([\x20-\x21\x23-\x7e]|((\\)(\\))|((\\)(\"))|((\\)(n))|((\\)(r))|((\\)(t))|((\\)x))
no_new_line                                   [\x00-\x09\x0b-\x0c\x0e-\x7f]
whitespace                                    ([\t\n\r ])

%x                                            START_STRING

%%

void                                          return VOID;
int                                           return INT;
byte                                          return BYTE;
b                                             return B;
bool                                          return BOOL;
auto                                          return AUTO;
and                                           return AND;
or                                            return OR;
not                                           return NOT;
true                                          return TRUE;
false                                         return FALSE;
return                                        return RETURN;
if                                            return IF;
else                                          return ELSE;
while                                         return WHILE;
break                                         return BREAK;
continue                                      return CONTINUE;
;                                             return SC;
,                                             return COMMA;
(\()                                          return LPAREN;
(\))                                          return RPAREN;
(\{)                                          return LBRACE;
(\})                                          return RBRACE;
=                                             return ASSIGN;
([<>]=?)|!=|==                                return RELOP;
(\+|\-|\*|\/)                                 return BINOP;
\/\/{no_new_line}*                            return COMMENT;
{letter}({letter}|{digit})*                   return ID;
[1-9]{digit}*|0                               return NUM;
[0]{digit}+                                   return ZERO_FIRST;
{whitespace}                                  return WHITESPACE;

(\")                                          BEGIN(START_STRING);
<START_STRING><<EOF>>                         return UNCLOSED_STRING;
<START_STRING>{printable_letters}*(\")        { BEGIN(INITIAL); return STRING; }
<START_STRING>([^(\")])*((\")?)               return UNCLOSED_STRING;
<START_STRING>.                               return UNCLOSED_STRING;

.                                             return WRONG_CHAR;
%%
