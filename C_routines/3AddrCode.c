#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "3AddrCode.h"

triple T[1000];
int t=0;
quadruple Q[1000];
int q=0;

int TripleIndex(char* t){
  int i;
  for(i=0;i<q;i++){
    if(strcmp(t,Q[i].res)==0)
      return i;
  }
  return -1;
}

int addTriple(char *o, SyntaxTree *a1, SyntaxTree *a2){
    T[t].op = (char*)malloc(sizeof(o));
    T[t].arg1 = (char*)malloc(strlen(a1->addr) + 1);
    strcpy(T[t].op, o);
    int t1index = TripleIndex(a1->addr);
    if (t1index==-1)
      strcpy(T[t].arg1, a1->addr);
    else
      sprintf(T[t].arg1, "( %d )", t1index);
    if(a2->nodetype==-1){
      T[t].arg2 = (char*)malloc(strlen("None") + 1);
      strcpy(T[t].arg2, "None");
    } else {
      int t2index = TripleIndex(a2->addr);
      T[t].arg2 = (char*)malloc(strlen(a2->addr) + 1);
      if (t2index==-1){
        strcpy(T[t].arg2, a2->addr);
      }
      else{
        sprintf(T[t].arg2, "( %d )", t2index);
      }
    }
    t++;
    return t-1;
}

int addQuadruple(char *o, SyntaxTree *a1, SyntaxTree *a2, SyntaxTree *r){
    Q[q].op = (char*)malloc(sizeof(o));
    Q[q].arg1 = (char*)malloc(strlen(a1->addr) + 1);
    if(a2->nodetype==-1){
      Q[q].arg2 = (char*)malloc(strlen("None") + 1);
      strcpy(Q[q].arg2, "None");
    } else {
      Q[q].arg2 = (char*)malloc(strlen(a2->addr) + 1);
      strcpy(Q[q].arg2, a2->addr);
    }
    Q[q].res = (char*)malloc(strlen(r->addr) + 1);
    strcpy(Q[q].op, o);
    strcpy(Q[q].arg1, a1->addr);
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

void saveTriple(){
  FILE *file = fopen("../Data Structures/Triples.txt","w");
  fprintf(file, "------------------------------------------");
  fprintf(file, "\n| %s | %s | %8s | %8s |", "Index", "Operator", "Arg1", "Arg2");
  int i;
  for(i=0;i<t;i++){
    fprintf(file, "\n------------------------------------------");
    fprintf(file, "\n| %5d | %8s | %8s | %8s |", i, T[i].op, T[i].arg1, T[i].arg2);
  }
  fprintf(file, "\n------------------------------------------");
  fclose(file);
}

void saveQuadruple(){
  FILE *file = fopen("../Data Structures/Quadruple.txt","w");
  fprintf(file, "-----------------------------------------------------");
  fprintf(file, "\n| %s | %s | %8s | %8s | %8s |","Index","Operator", "Arg1", "Arg2", "Res");
  int i;
  for(i=0;i<q;i++){
    fprintf(file, "\n-----------------------------------------------------");
    fprintf(file, "\n| %5d | %8s | %8s | %8s | %8s |", i, Q[i].op, Q[i].arg1, Q[i].arg2, Q[i].res);
  }
  fprintf(file, "\n-----------------------------------------------------");
  fclose(file);
}

void gen3addr(SyntaxTree* head){
  FILE *file = fopen("../Data Structures/3Addrcode.txt","w");
  fprintf(file, head->code);
  fclose(file);
}