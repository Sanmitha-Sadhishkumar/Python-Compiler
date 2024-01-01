%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../C_routines/SyntaxTree.h"

int yylex();
void yyerror(const char *s);
int i=0;

typedef struct Exp {
        char *code;
        char *addr;
    } Exp;
%}

%union {
    char *lexeme;
    char *value;
    double d;
    struct SyntaxTree *Sy;
    int i;
}

%type <Sy> E S
%token <lexeme> id ID 
%token <value> LITERAL num
%token <d> doublenum
%token <i> intnum

%left '+' '-'
%%

S : id '=' E {$$ = newST('=',newid($1), $3);}


E : E '+' E { $$ = newST('+',$1, $3); }

| '-' E {$$ = newST('-',$2, NULL);}

| '(' E ')' {$$ = $2;}

| id { $$ = newid($1);}

| intnum { $$ = newint($1);}

| doublenum { $$ = newdouble($1);}
%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    yyparse(); // Start parsing
    return 0;
}
