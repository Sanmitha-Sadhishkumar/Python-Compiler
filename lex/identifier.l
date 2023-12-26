%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../yacc/grammer.tab.h"

typedef struct SymbolTable{
  char token[10];
  char attr[100];
  char type[10];
} SymbolTable;

SymbolTable ST[1000];
int STn=0;

void printST(){
  int i;
  printf("\nPrinting Symbol Table ");
  for(i=0;i<STn;i++){
    printf("\n%s : %s",ST[i].token, ST[i].attr);
  }
}

int installID(char *a, char *t){
  int i;
  for(i=0;i<STn;i++){
    if((strcmp(ST[i].token, "ID")==0)&&(strcmp(ST[i].attr, a)==0)){
      return i;
    }
  }
  strcpy(ST[STn].token,"ID");
  strcpy(ST[STn].attr,a);
  strcpy(ST[STn].type,t);
  STn++;
  return STn-1;
}

%}

id [a-zA-Z_][a-zA-Z_0-9]*

%%

%union {
    char *lexeme;
    int value;
}

%token <lexeme> ID

{id} {
    printf("\nIdentifier : %s ", yytext);
    int a = installID(yytext, NULL);
    yylval.lexeme = strdup(yytext);
    return ID;
}

%%

int yywrap() { 
  return 1; 
} 