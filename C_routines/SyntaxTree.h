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

void printSyntaxTreeHelper(FILE *file, SyntaxTree *node, int depth) ;

void printNode(SyntaxTree* a);

SyntaxTree* newIfNode(char *op, SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newBoolExp(SyntaxTree *node);

SyntaxTree* newElseNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newBoolLabelNode(char* type, SyntaxTree* node);

SyntaxTree* newElifJoinNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newStJoinNode(SyntaxTree*l, SyntaxTree*r);

SyntaxTree* newWhileNode(char *op, SyntaxTree*l, SyntaxTree*r);


#define ID_NODE 'I'
#define INT_NODE 'D'
#define DOUBLE_NODE 'F'
#define ASS_NODE '='
#define AR_NODE '+'
#define REL_NODE '>'
#define LOG_NODE 'a'
#define MEM_NODE 'i'
#define IDENTITY_NODE 's'
#define BIT_NODE '&'
#define UMINUS_NODE 'M'
#define IF_NODE 'e'
#define ELSE_NODE 'E'
#define ELIF_NODE 'L'
#define WHILE_NODE 'W'