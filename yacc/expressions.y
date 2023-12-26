%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../lex/lex.yy.c"
int yylex();
void yyerror(const char *s);
int i=0;
%}

%union {
    char *lexeme;
    int value;
    char *code;
    char *addr;
    struct {
        char *code;
        char *addr;
    } exp;
};

%left '+' '-'
%token <lexeme> id
%token <value> LITERAL
%type <code> S
%type <exp> E

%%

S : id '=' E   { $$.code = strcat($3.exp.code, strcat($1.lexeme, strcat("=", $3.exp.addr))); }
  ;

E : E '+' E    { 
                    $$.exp.addr = (char*)malloc(sizeof(char) * 10);
                    char c[10];
                    sprintf(c, "t%d", i);
                    i++;
                    strcpy($$.exp.addr, c);
                    $$.code = strcat($1.exp.code, strcat($3.exp.code, strcat($$.exp.addr, "=", strcat($1.exp.addr, "+", $3.exp.addr))));
                }
  | '-' E      {
                    $$.addr = (char*)malloc(sizeof(char) * 10);
                    char c[10];
                    sprintf(c, "t%d", i);
                    i++;
                    strcpy($$.addr, c);
                    $$.code = strcat($2.exp.code, strcat($$.exp.addr, "=-", $2.exp.addr));
                }
  | '(' E ')'  { $$.exp.addr = $2.exp.addr; $$.exp.code = $2.exp.code; }
  | id         { $$.exp.addr = $1.lexeme; $$.exp.code = ""; }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    yyparse(); // Start parsing
    return 0;
}
