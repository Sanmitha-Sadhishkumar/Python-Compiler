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
    char *True;
    char *False;
    char* next;
    char *code;
    struct SyntaxTree *l;
    struct SyntaxTree *r;
} SyntaxTree;


SyntaxTree * newOpNode(char *op, SyntaxTree *l, SyntaxTree *r);

SyntaxTree * newDoubleNode(char* value);

SyntaxTree * newIntNode(char* value);

SyntaxTree * newIDNode(char* id);

void printSyntaxTree(SyntaxTree * head);

void printNode(SyntaxTree* a);

SyntaxTree* newIfNode(char *op, SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newBoolExp(SyntaxTree *node);

SyntaxTree* newElseNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newBoolLabelNode(char* type, SyntaxTree* node);

SyntaxTree* newJoinNode(SyntaxTree*l, SyntaxTree*r);
