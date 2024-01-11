#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "3AddrCode.h"

triple T[1000];
int t=0;
quadruple Q[1000];
int q=0;

int addTriple(char *o, SyntaxTree *a1, SyntaxTree *a2){
    T[t].op = (char*)malloc(sizeof(o));
    T[t].arg1 = (char*)malloc(strlen(a1->addr) + 1);
    T[t].arg2 = (char*)malloc(strlen(a2->addr) + 1);
    strcpy(T[t].op, o);
    strcpy(T[t].arg1, a1->addr);
    strcpy(T[t].arg2, a2->addr);
    t++;
    return t-1;
}

int addQuadruple(char *o, SyntaxTree *a1, SyntaxTree *a2, SyntaxTree *r){
    Q[q].op = (char*)malloc(sizeof(o));
    Q[q].arg1 = (char*)malloc(strlen(a1->addr) + 1);
    Q[q].arg2 = (char*)malloc(strlen(a2->addr) + 1);
    Q[q].res = (char*)malloc(strlen(r->addr) + 1);
    strcpy(Q[q].op, o);
    strcpy(Q[q].arg1, a1->addr);
    strcpy(Q[q].arg2, a2->addr);
    strcpy(Q[q].res, r->addr);
    q++;
    return q-1;
}

void printT(){
  int i;
  printf("\nPrinting Triples \n");
  for(i=0;i<t;i++){
    printf("\n%s , %s , %s",T[i].op, T[i].arg1, T[i].arg2);
  }

  printf("\n\nPrinting Quadriples \n");
  for(i=0;i<q;i++){
    printf("\n%s , %s , %s, %s",Q[i].op, Q[i].arg1, Q[i].arg2, Q[i].res);
  }
}