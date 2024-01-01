#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "SyntaxTree.h"

SyntaxTree * newST(int nodetype, SyntaxTree *l, SyntaxTree *r){
  SyntaxTree *a = malloc(sizeof(SyntaxTree));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  if(l) a->l = l;
  if(r) a->r = r;
  return a;
 }

SyntaxTree * newdouble(double d){
  doubleval *a = malloc(sizeof(doubleval));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'F';
  a->number = d;
  return (SyntaxTree *)a;
 }

SyntaxTree * newint(int d){
  intval *a = malloc(sizeof(intval));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = 'I';
  a->number = d;
  return (SyntaxTree *)a;
 }

SyntaxTree* newid(char* d){
  idval *a = malloc(sizeof(idval));
  if(!a) {
    yyerror("out of space");
    exit(0);
  }
  a->nodetype = (char*)malloc(strlen("ID") + 1);
  strcpy(a->nodetype, "ID");
  a->id = d;
  return (SyntaxTree *)a;
 }


double eval(SyntaxTree *a) {
  double v;
  switch(a->nodetype) {
  case 'I': v = ((intval *)a)->number; break;
  case 'F': v = ((doubleval *)a)->number; break;
  case '+': v = eval(a->l) + eval(a->r); break;
  case '-': v = eval(a->l) - eval(a->r); break;
  case '*': v = eval(a->l) * eval(a->r); break;
  case '/': v = eval(a->l) / eval(a->r); break;
  case '|': v = eval(a->l); if(v < 0) v = -v; break;
  case 'M': v = -eval(a->l); break;
  default: printf("internal error: bad node %c\n", a->nodetype);
  }
  return v;
 }

 void treefree(SyntaxTree *a) {
  switch(a->nodetype) {
  case '+':
  case '-':
  case '*':
  case '/':
    treefree(a->r);
  case '|':
  case 'M':
    treefree(a->l);
    case 'K':
    free(a);
    break;
  default: printf("internal error: free bad node %c\n", a->nodetype);
  }
 }
