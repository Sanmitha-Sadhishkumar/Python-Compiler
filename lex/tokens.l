%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../yacc/expressions.tab.h"
#include "../C_routines/SymbolTable.h"

%}

id [a-zA-Z_][a-zA-Z_0-9]*

int [-]?[0-9]+
float [-]?[0-9]+([.][0-9]+)?([Ee][+-]?[0-9]+)?
bool "True" | "False"
str (\"([^\"\\\\]|\\\\.)*\")|('([^'\\\\]|\\\\.)*')

%%

{id} {
    printf("\nIdentifier : %s ", yytext);
    int a = installID(yytext, NULL);
    yylval.lexeme = strdup(yytext);
    return ID;
}

{int} {printf("\nInteger : %s ",yytext);
      int a = installLit(yytext,"INT");
      yylval.value = strdup(yytext);
      return LITERAL;}

{str} {printf("String ");
      int a = installLit(yytext,"STR");
      yylval.value = strdup(yytext);
      return LITERAL;}

{float} {printf("Float ");
      int a = installLit(yytext,"FLOAT");
      yylval.value = strdup(yytext);
      return LITERAL;}
%%

int yywrap(){
  return 1;
}