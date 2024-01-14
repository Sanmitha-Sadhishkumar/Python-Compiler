#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SyntaxTree {
    int nodetype;
    union {
        char *id;
        char* intval;
        char* doubleval;
        char *op;
    } value;
    char *addr;
    char *code;
    struct SyntaxTree *l;
    struct SyntaxTree *r;
} SyntaxTree;


SyntaxTree * newOpNode(char *op, SyntaxTree *l, SyntaxTree *r);

SyntaxTree * newDoubleNode(char* value);

SyntaxTree * newIntNode(char* value);

SyntaxTree * newIDNode(char* id);

double eval(SyntaxTree *a);

void treefree(SyntaxTree *a);

void printSyntaxTree(SyntaxTree * head);

void printNode(SyntaxTree* a);