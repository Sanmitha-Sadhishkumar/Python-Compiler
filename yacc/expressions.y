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
    char *key;
    char *delim;
}

%type <Sy> E S B if_statement
%token <lexeme> id ID 
%token <value> LITERAL FLOAT INT
%token <op> relop arith assign AND OR NOT membership identity bitwise
%token <key> IF ELSE ELIF WHILE FOR TRUE FALSE
%token <delim> DELIMITER COLON TAB NL SPACE

%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%

S : if_statement { $$ = $1;}
  | /* empty */
  ;

if_statement : IF B COLON NL SPACE S  { $$ = newIfNode($1, $2, $6);
                                     //$2.true = newlabel();$2.false = $4.next = $$.next; $$.code = $2.code || label($2.true) || $4.code;
                                     }
                                     ;
else_elif: ELSE S    {
                                     //$2.true = newlabel();$2.false = newlabel();  $4.next  = $6.next =$$.next; $$.code = $2.code || label($2.true) || $4.code || gen('goto' $$.next) || label($2.false) || $6.code;
                                     }
        | ELIF S  {}
        | /* */
        ;

B : B OR B    { $$ = newBoolExp($2, $1, $3);}
  | B AND B   { $$ = newBoolExp($2, $1, $3);}
  | NOT B     { SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); $$ = newBoolExp($1, $2, s);}
  | E         { $$ = $1; }
  | TRUE      {/*$$.code = gen('goto' $$.true) ;*/}
  | FALSE     {/*$$.code = gen('goto' $$.false) ;*/}
  ;

S : id assign E { SyntaxTree* id=newIDNode($1);
                  $$ = newOpNode($2, id , $3);
                  SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree));
                  s->nodetype = -1;
                  addTriple($2, $3, s);
                  addQuadruple($2, $3, s, id);
                  saveTriple();
                  saveQuadruple();
                  gen3addr($$);
                  }
  ;

E : E arith E { $$ = newOpNode($2, $1, $3);
                addTriple($2, $1, $3);
                addQuadruple($2,$1,$3,$$);
                }

  | E "-" E { $$ = newOpNode("-", $1, $3);
                addTriple("-", $1, $3);
                addQuadruple("-",$1,$3,$$);
                }

  | E relop E { $$ = newOpNode($2, $1, $3);
                addTriple($2, $1, $3);
                addQuadruple($2,$1,$3,$$);
                }
                
  | "(" E ")" { $$ = $2; }
  | "-" E %prec UMINUS { $$ = newOpNode("-", 0, $2);
                         addTriple("-", $2, 0);
                         addQuadruple("-",$2,0,$$); }
  | id { $$ = newIDNode($1); }
  | INT { $$ = newIntNode($1);}
  | FLOAT { $$ = newDoubleNode($1);}
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
