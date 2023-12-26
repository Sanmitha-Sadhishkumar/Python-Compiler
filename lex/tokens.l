%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../yacc/grammer.tab.h";
#include "keywords.l"
#include "literals.l"
#include "identifier.l"
%}

%%

%union {
    char *lexeme;
    int value;
}

%token <lexeme> ID

%%

int yywrap(){
  return 1;
}