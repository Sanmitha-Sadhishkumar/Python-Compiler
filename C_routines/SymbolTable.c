#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "SymbolTable.h"

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