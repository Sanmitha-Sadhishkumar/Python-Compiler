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
%token if else elif while and or not True False
%token <lexeme> id
%token <value> assign
%type <code> S
%type <exp> E

%%

P : S                               {S.next = newlabel(); P.code = S.code || label(S.next)}
  ;

S : assign                          {$$.code = $1.code;}
  | if_statement                    {$$.code = $1.code;}
  | while_statement                 {$$.code = $1.code;}
  | S S                             {$1.next = newlabel();$2.next= $$.next;$$.code = $1.code || label($1.next) || $2.code ;}
  ;

if_statement : if B ':' S           {$2.true = newlabel();$2.false = $4.next = $$.next; $$.code = $2.code || label($2.true) || $4.code;}
             | if B ':' S else S    {$2.true = newlabel();$2.false = newlabel();  $4.next  = $6.next =$$.next; $$.code = $2.code || label($2.true) || $4.code || gen('goto' $$.next) || label($2.false) || $6.code;}
             | if B ':' S elif_list
             ;

elif_list : elif B ':' S            {}
          | elif B ':' S elif_list  {}
          ;

while_statement : while B ':' S ;   {begin = newlabel();$2.true = newlabel();$2.false = $$.next; $4.next = begin; $$.code = label(begin) || $2.code ||  label($2.true) || $4.code || gen('goto' begin); }


B : B or B                          {$1.true = $$.true; $1.false = newlabel(); $2.true=$$.true; $2.false=$$.false;$$.code = $1.code || label($1.false)||$2.code;}
  | B and B                         {$1.true = newlabel(); $1.false = $$.false; $2.true=$$.true; $2.false=$$.false;$$.code = $1.code || label($1.true)||$2.code;}
  | not B                           {$1.true = $$.false; $1.false = $$.true;}
  | E relop E                         {$$.code = $1.code || $3.code || gen('if' $1.addr relop $3.addr 'goto' $$.true) || gen('goto' $$.false);}
  | True                            {$$.code = gen('goto' $$.true) ;}
  | False                           {$$.code = gen('goto' $$.false) ;}
  ;

rel : '>='
    | '<='
    | '<'
    | '>'
    | '=='
    | '!='
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    yyparse(); // Start parsing
    return 0;
}
