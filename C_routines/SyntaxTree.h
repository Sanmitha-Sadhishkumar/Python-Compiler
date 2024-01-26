#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SyntaxTree {
    int nodetype;
    union {
        char *id;
        char *intval;
        char *doubleval;
        char *strval;
        char *op;
        char *value[100];
    } value;
    char *addr;
    char *True;
    char *False;
    char *next;
    char *code;
    struct SyntaxTree *l;
    struct SyntaxTree *r;
} SyntaxTree;


SyntaxTree * newOpNode(char *op, SyntaxTree *l, SyntaxTree *r);

SyntaxTree* newLiteralNode(char* value, int type);

SyntaxTree * newIDNode(char* id);

void printSyntaxTree(SyntaxTree * head);

void printSyntaxTreeHelper(FILE *file, SyntaxTree *node, int depth) ;

void printNode(SyntaxTree* a);

SyntaxTree* newIfNode(char *op, SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newBoolExp(SyntaxTree *node);

SyntaxTree* newElseNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newBoolLabelNode(char* type, SyntaxTree* node);

SyntaxTree* newElifJoinNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newStJoinNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newWhileNode(char *op, SyntaxTree*l, SyntaxTree*r);


#define ID_NODE 101
#define INT_NODE 102
#define DOUBLE_NODE 103
#define ASS_NODE 104
#define AR_NODE 105
#define REL_NODE 106
#define LOG_NODE 107
#define MEM_NODE 108
#define IDENTITY_NODE 109
#define BIT_NODE 110
#define UMINUS_NODE 111
#define IF_NODE 112
#define ST_NODE 113
#define ELSE_NODE 114
#define ELIF_NODE 115
#define WHILE_NODE 116
#define STR_NODE 117