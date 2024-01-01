#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SyntaxTree {
  int nodetype;
  struct SyntaxTree *l;
  struct SyntaxTree *r;
}SyntaxTree;

typedef struct doubleval {
  int nodetype; 
  double number;
}doubleval;

typedef struct intval {
  int nodetype; 
  int number;
}intval;

typedef struct idval {
  char* nodetype; 
  char *id;
}idval;

SyntaxTree * newST(int nodetype, SyntaxTree *l, SyntaxTree *r);

SyntaxTree * newdouble(double d);

SyntaxTree * newint(int d);

double eval(SyntaxTree *a);

void treefree(SyntaxTree *a);

void printSyntaxTree(SyntaxTree * head);

SyntaxTree* newid(char* d);