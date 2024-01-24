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

%type <Sy> E S B P G if_statement else_elif elif_statement else_statement while_statement indent_statement
%token <lexeme> id ID 
%token <value> LITERAL FLOAT INT
%token <op> relop arith assign AND OR NOT membership identity bitwise
%token <key> IF ELSE ELIF WHILE FOR TRUE FALSE
%token <delim> DELIMITER COLON TAB NL SPACE

%left ELSE ELIF WHILE FOR TRUE FALSE
%right assign
%right IF
%left OR
%left AND
%right NOT
%left relop membership identity
%left bitwise
%left arith
%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%%
G : P { $$ = $1; printNode($$);saveTriple(); saveQuadruple(); gen3addr($$);  printSyntaxTree($$);};

P : S {$$ = $1; }
  | S NL P {$$ = newStJoinNode($1, $3);}
  | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

S : if_statement else_elif{ $$ = newElseNode($1, $2);}
  | while_statement else_statement {$$ = newStJoinNode($1, $2);}
  | id assign E  { SyntaxTree* id=newIDNode($1);
                  $$ = newOpNode($2, id , $3);
                  SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1;
                  addTriple($2, $3, s); addQuadruple($2, $3, s, id);
                  }
  ;

if_statement : IF B COLON NL indent_statement { newBoolLabelNode("root", $2); newBoolExp($2); $$ = newIfNode($1, $2, $5); } ;

else_elif: elif_statement else_statement {$$ = newElifJoinNode($1, $2);} ;

else_statement: ELSE COLON NL indent_statement   { $$ = $4; }
              | /* empty */  {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

elif_statement: ELIF B COLON NL indent_statement  {newBoolLabelNode("root", $2); newBoolExp($2); $$ = newIfNode($1, $2, $5);}
              | elif_statement elif_statement {$$ = newElifJoinNode($1, $2);}
              | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

while_statement : WHILE B COLON NL indent_statement { newBoolLabelNode("root", $2); newBoolExp($2); $$ = newWhileNode($1, $2, $5);};

indent_statement : SPACE S { $$ = $2;}
                 | indent_statement NL indent_statement {$$ = newStJoinNode($1, $3);}
                 | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

B : B OR B    { $$ = newBoolJoinNode($2, $1, $3);}
  | B AND B   { $$ = newBoolJoinNode($2, $1, $3);}
  | NOT B     { SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); }
  | E         { $$ = $1; }
  | TRUE      {/*$$.code = gen('goto' $$.true) ;*/}
  | FALSE     {/*$$.code = gen('goto' $$.false) ;*/}
  ;

E : E arith E { $$ = newOpNode($2, $1, $3); addTriple($2, $1, $3); addQuadruple($2,$1,$3,$$); }
  | E "-" E { $$ = newOpNode("-", $1, $3); addTriple("-", $1, $3); addQuadruple("-",$1,$3,$$); }
  | E relop E { $$ = newOpNode($2, $1, $3); addTriple($2, $1, $3); addQuadruple($2,$1,$3,$$); }
  | "(" E ")" { $$ = $2; }
  | "-" E %prec UMINUS { $$ = newOpNode("-", 0, $2); addTriple("-", $2, 0); addQuadruple("-",$2,0,$$); }
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
