%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../C_routines/3AddrCode.h"
#define YYERROR_VERBOSE 1
extern int yylineno;
extern FILE* yyin;
void yyerror(const char *s);
int i=0;
%}

%union {
    char *lexeme;
    char *value;
    double dvalue;
    struct SyntaxTree *Sy;
    int ivalue;
    char *op;
}

%type <Sy> E S
%token <lexeme> id ID 
%token <value> LITERAL
%token <dvalue> FLOAT
%token <ivalue> INT
%token <op> relop arith assign

%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%

S : id assign E { $$ = newOpNode($2, newIDNode($1), $3);
                  //printSyntaxTree($$); 
                  int a =addTriple($2, newIDNode($1), $3);
                  int b= addQuadruple($2, $3, $3, newIDNode($1));
                  printT();
                  }
  ;

E : E arith E { $$ = newOpNode($2, $1, $3);
                int a=addTriple($2, $1, $3);
                addQuadruple($2,$1,$3,$$); }
  | "(" E ")" { $$ = $2; }
  | "-" E %prec UMINUS { $$ = newOpNode("-", 0, $2);
                        printf("Added Tripes of op");
                         addTriple("-", $2, 0);
                         addQuadruple("-",$2,0,$$); }
  | id { $$ = newIDNode($1); }
  | INT { $$ = newIntNode($1); }
  | FLOAT { $$ = newDoubleNode($1); }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error at %d: %s\n", yylineno, s);
}

int main() {
    yyin = fopen("file.py","r");
    yyparse();
    return 0;
}
