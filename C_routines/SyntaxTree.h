#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SyntaxTree {
    int nodetype;
    union {
        char *id;
        int intval;
        double doubleval;
        char *op;
    } value;
    struct SyntaxTree *l;
    struct SyntaxTree *r;
} SyntaxTree;


SyntaxTree * newOpNode(char *op, SyntaxTree *l, SyntaxTree *r);

SyntaxTree * newDoubleNode(double value);

SyntaxTree * newIntNode(int value);

SyntaxTree * newIDNode(char* id);

double eval(SyntaxTree *a);

void treefree(SyntaxTree *a);

void printSyntaxTree(SyntaxTree * head);
