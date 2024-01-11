#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "SyntaxTree.h"

#define ID_NODE 'I'
#define INT_NODE 'D'
#define DOUBLE_NODE 'F'
#define PLUS_NODE '+'
#define MINUS_NODE '-'
#define MUL_NODE '*'
#define DIV_NODE '/'
#define MOD_NODE '%'
#define ASS_NODE '='
#define UMINUS_NODE 'M'

SyntaxTree * newOpNode(char *op, SyntaxTree *l, SyntaxTree *r){
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    if (strcmp(op, "+") == 0) {
        node->nodetype = PLUS_NODE;
    } else if (strcmp(op, "-") == 0) {
        node->nodetype = MINUS_NODE;
    } else if (strcmp(op, "*") == 0) {
        node->nodetype = MUL_NODE;
    } else if (strcmp(op, "/") == 0) {
        node->nodetype = DIV_NODE;
    } else if (strcmp(op, "%") == 0) {
        node->nodetype = MOD_NODE;
    } else if (strcmp(op, "=") == 0) {
        node->nodetype = ASS_NODE;
    } else {
        fprintf(stderr, "Unknown operation: %s\n", op);
        exit(1);
    }
    node->value.op = strdup(op);
    node->l = l;
    node->r = r;
    printf("added new op node: %s\n",op);
    return node;
}

SyntaxTree * newDoubleNode(double value){
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = DOUBLE_NODE;
    node->value.doubleval = value;
    node->l = node->r = NULL;
    printf("added new double node : %f\n",value);
    return node;
}

SyntaxTree * newIntNode(int value){
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = INT_NODE;
    node->value.intval = value;
    node->l = node->r = NULL;
    printf("added new int node : %d\n",value);
    return node;
}

SyntaxTree * newIDNode(char* id){
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = ID_NODE;
    node->value.id = strdup(id);
    node->l = node->r = NULL;
    printf("added new id node : %s\n",id);
    return node;
}


double eval(SyntaxTree *a) {
  double v;
  switch(a->nodetype) {
  
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

void printSyntaxTree(SyntaxTree *head) {
    if (head != NULL) {
        printSyntaxTree(head->l);

        switch (head->nodetype) {
            case ID_NODE:
                printf("Identifier : %s ", head->value.id);
                break;
            case INT_NODE:
                printf("Integer : %d ", head->value.intval);
                break;
            case DOUBLE_NODE:
                printf("Double : %f ", head->value.doubleval);
                break;
            case PLUS_NODE:
            case MINUS_NODE:
            case MUL_NODE:
            case DIV_NODE:
            case MOD_NODE:
                printf("Arithmetic Operator : %s ",head->value.op);
                break;
            case ASS_NODE:
                printf("Assignment Operator %s ",head->value.op);
                break;
            default:
                printf("Unknown node type: %c ", head->nodetype);
                break;
        }

        printSyntaxTree(head->r);
    }
}

