%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../yacc/grammer.tab.h"

typedef struct SymbolTable{
  char token[10];
  char attr[100];
  char type[10];
}SymbolTable;

SymbolTable ST[1000];
int STn=0;

void printST(){
  int i;
  printf("\nPrinting Symbol Table ");
  for(i=0;i<STn;i++){
    printf("\n%s : %s",ST[i].token, ST[i].attr);
  }
}

int installLit(char *b, char *t){
  int i;
  for(i=0;i<STn;i++){
    if((strcmp(ST[i].token, "NUM")==0)&&(strcmp(ST[i].attr, b)==0)){
      return i;
    }
  }
  strcpy(ST[STn].token,"LITERAL");
  strcpy(ST[STn].attr,b);
  strcpy(ST[STn].type,t);
  STn++;
  return STn-1;
}

%}

int [-]?[0-9]+
float [-]?[0-9]+([.][0-9]+)?([Ee][+-]?[0-9]+)?
bool (True|False)
str (\"([^\"\\\\]|\\\\.)*\")|('([^'\\\\]|\\\\.)*')

%%
{int} {printf("\nInteger : %s ",yytext);
      int a = installLit(yytext,"INT");
      yylval.value = = strdup(yytext);
      return LITERAL;}

{str} {printf("String ");
      int a = installLit(yytext,"STR");
      yylval.value = = strdup(yytext);
      return LITERAL;}

{float} {printf("Float ");
      int a = installLit(yytext,"FLOAT");
      yylval.value = = strdup(yytext);
      return LITERAL;}

{bool} {printf("Boolean ");
      int a = installLit(yytext,"BOOL");
      yylval.value = = strdup(yytext);
      return LITERAL;}

%union {
    char *lexeme;
    int value;
}

%token <value> LITERAL
%%

int yywrap() { 
  return 1; 
} 