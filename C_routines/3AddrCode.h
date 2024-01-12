#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "SyntaxTree.h"

typedef struct triple{
    char *op;
    char *arg1;
    char *arg2;
}triple;

typedef struct quadruple{
    char *op;
    char *arg1;
    char *arg2;
    char *res;
}quadruple;

int addTriple(char *o, SyntaxTree *a1, SyntaxTree *a2);

int addQuadruple(char *o, SyntaxTree *a1, SyntaxTree *a2, SyntaxTree *r);

void printT();

void saveTriple();

void saveQuadruple();

void gen3addr(SyntaxTree* head);