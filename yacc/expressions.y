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
    char *coll[100];
}

%type <Sy> E S B P G if_statement else_elif elif_statement else_statement while_statement indent_statement
%type <op> arith relop identity assign membership bitwise oper
%token <lexeme> id ID 
%token <value> LITERAL FLOAT INT
%token <op> AND OR NOT PLUS MINUS MUL DIV MOD EXP FDIV LT GT LTE GTE DEQ NE EQ AEQ SEQ MEQ DIEQ FDEQ EEQ MOEQ BLEQ BREQ IS ISN IN NIN LSHIFT RSHIFT BAND BOR BXOR BNOT
%token <key> IF ELSE ELIF WHILE FOR TRUE FALSE
%token <delim> DELIMITER COLON TAB NL SPACE
%token <coll> LIST SET TUPLE DICT

%left ELSE ELIF WHILE FOR TRUE FALSE
%right EQ AEQ SEQ MEQ DIEQ FDEQ EEQ MOEQ BLEQ BREQ
%right IF

%left OR
%left AND
%right NOT
%left LT GT LTE GTE DEQ NE IS ISN IN NIN
%left BOR
%left BXOR
%left BAND
%left LSHIFT RSHIFT
%left PLUS MINUS
%left MUL DIV FDIV MOD
%left BNOT
%left EXP

%%
G : P { $$ = $1; printNode($$); gen3addr($$);  printSyntaxTree($$);};

P : S {$$ = $1; }
  | S NL P {$$ = newStJoinNode($1, $3);}
  | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

S : if_statement else_elif { $$ = newElseNode($1, $2);}
  | while_statement else_statement {$$ = newStJoinNode($1, $2);}
  | id assign E  { SyntaxTree* id=newIDNode($1);
                  $$ = newOpNode($2, id , $3);
                  SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1;
                  addTriple($2, $3, s); addQuadruple($2, $3, s, id);
                  }
  | E {$$ = $1}
  | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

if_statement : IF B COLON NL indent_statement { newBoolLabelNode("root", $2); newBoolExp($2); $$ = newIfNode($1, $2, $5); } ;

else_elif: elif_statement else_statement {$$ = newElifJoinNode($1, $2);} ;

else_statement: ELSE COLON NL indent_statement   { $$ = $4; }
              | /* empty */  {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

elif_statement: ELIF B COLON NL indent_statement  {newBoolLabelNode("root", $2); newBoolExp($2); $$ = newIfNode($1, $2, $5);}
              | elif_statement elif_statement {$$ = newElifJoinNode($1, $2);}
              | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

while_statement : WHILE B COLON NL indent_statement { newBoolLabelNode("root", $2); newBoolExp($2); $$ = newWhileNode($1, $2, $5);};

indent_statement : SPACE S NL{ $$ = $2;}
                 | indent_statement indent_statement {$$ = newStJoinNode($1, $2);}
                 | /* empty */ {SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); s->nodetype = -1; s->code = ""; $$ = s;} ;

B : B OR B    { $$ = newBoolJoinNode($2, $1, $3);}
  | B AND B   { $$ = newBoolJoinNode($2, $1, $3);}
  | NOT B     { SyntaxTree* s = (SyntaxTree*)malloc(sizeof(SyntaxTree)); }
  | E         { $$ = $1; }
  | TRUE      {/*$$.code = gen('goto' $$.true) ;*/}
  | FALSE     {/*$$.code = gen('goto' $$.false) ;*/}
  ;

E : E oper E { $$ = newOpNode($2, $1, $3); addTriple($2, $1, $3); addQuadruple($2,$1,$3,$$); }
  | "(" E ")" { $$ = $2; }
  | MINUS E { $$ = newOpNode("-", 0, $2); addTriple("-", $2, 0); addQuadruple("-",$2,0,$$); }
  | id { $$ = newIDNode($1); }
  | INT { $$ = newLiteralNode($1,1);}
  | FLOAT { $$ = newLiteralNode($1,2);}
  ;

oper : arith {$$ = $1;}
     | relop {$$ = $1;}
     | identity {$$ = $1;}
     | membership {$$ = $1;}
     | bitwise {$$ = $1;}
     ;

arith : PLUS {$$ = $1;}
      | MINUS {$$ = $1;}
      | MUL {$$ = $1;}
      | DIV {$$ = $1;}
      | FDIV {$$ = $1;}
      | EXP {$$ = $1;}
      | MOD {$$ = $1;}
      ;

relop : LT {$$ = $1;}
      | LTE {$$ = $1;}
      | GT {$$ = $1;}
      | GTE {$$ = $1;}
      | NE {$$ = $1;}
      | DEQ {$$ = $1;}
      ;

assign : EQ {$$ = $1;}
       | AEQ {$$ = $1;}
       | SEQ {$$ = $1;}
       | MEQ {$$ = $1;}
       | DIEQ {$$ = $1;}
       | FDEQ {$$ = $1;}
       | EEQ {$$ = $1;}
       | MOEQ {$$ = $1;}
       | BLEQ {$$ = $1;}
       | BREQ {$$ = $1;}
       ;

identity : IS {$$ = $1;}
         | ISN {$$ = $1;}
         ;

membership : IN {$$ = $1;}
           | NIN {$$ = $1;}
           ;

bitwise : BAND {$$ = $1;}
        | BOR {$$ = $1;}
        | BXOR {$$ = $1;}
        | BNOT {$$ = $1;}
        | LSHIFT {$$ = $1;}
        | RSHIFT {$$ = $1;}
        ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error at %d: %s\n", yylineno, s);
}

int main() {
    yyin = fopen("file.py","r");
    yyparse();
    saveTriple(); saveQuadruple();
    return 0;
}
