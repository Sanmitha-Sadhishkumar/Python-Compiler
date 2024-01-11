#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

triple T[1000];
int t=0;
quadruple Q[1000];
int q=0;

void addTriple(char *o, char *a1, char *a2);

void addQuadruple(char *o, char *a1, char *a2, char *r);