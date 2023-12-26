%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lex/lex.yy.c"

typedef struct Quadruple{
  char op[10];
  char arg1[100];
  char arg2[100];
  char res[100];
}Quadruple;

typedef struct Triple{
  char op[10];
  char arg1[100];
  char arg2[100];
}Triple;

%union {
    char *lexeme;
    int value;
}

%token <lexeme> ID
%token <value> LITERAL

int addQuaduple(char *a, char *b, char *c){
  
}

int yylex();
void yyerror(const char *s);
%}

%token id
%token num
%token ID
%token NUM

%%
/* for expressions */
E : T { printf("Result: %d\n", $1); } // Print the result of the expression
  ;

T : F { $$ = $1; }
  | T '+' F { $$ = $1 + $3; }
  | T '-' F { $$ = $1 - $3; }
  | T '*' F { $$ = $1 * $3; }
  | T '/' F { $$ = $1 / $3; }
  | T '/''/' F { $$ = (int) $1 / $4; }
  | T '*''*' F { $$ = 1;
                 int i=0;
                 for(i=0;i<$4;i++)
                   $$ *= $1; }
  ;

F : NUM { $$ = $1; }
  | '(' E ')' { $$ = $2; }
  ;

I : L '=' R {L.code = R.code;}
  ;

L : id {L.code = id.lexeme;}
  ;

R : num {R.code = num.value;}
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    yyparse(); // Start parsing
    return 0;
}
