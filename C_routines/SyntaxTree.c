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

int quad=1;

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
    char code[40000], addr1[40];
    
    if (node->nodetype==ASS_NODE){
        sprintf(code, "%s%s%s%s%s\n", l->code, r->code, l->addr, op, r->addr);
        strcpy(addr1, r->addr);
    }
    else{
        sprintf(addr1,"t%d",quad);
        sprintf(code, "%s%s%s=%s%s%s\n", l->code, r->code, addr1, l->addr, op, r->addr);
    }
    node->addr = (char*)malloc(sizeof(strlen(addr1)+1));
    node->code = (char*)malloc(sizeof(strlen(code)+1));
    node->addr = strdup(addr1); 
    node->code = strdup(code);
    node->value.op = strdup(op);
    node->l = l;
    node->r = r;
    quad++;
    //printf("\nadded new op node: %s with with addr %s\n",op, node->addr);
    return node;
}

SyntaxTree * newDoubleNode(char* value){
    printf("value : %s\n",value);
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = DOUBLE_NODE;
    node->value.doubleval = value;
    node->addr = malloc(20);
    sprintf(node->addr, "%s", value);
    node->code = malloc(1);
    node->code[0] = '\0'; 
    node->l = node->r = NULL;
    node->code="";
    printf("added new double node : %s with addr %s and code %s\n",value, node->addr, node->code);
    return node;
}

SyntaxTree * newIntNode(char* value){
    printf("value : %s\n",value);
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = INT_NODE;
    node->value.intval = value;
    node->addr = malloc(20);
    sprintf(node->addr, "%s", value);
    node->code = malloc(1);
    node->code[0] = '\0'; 
    node->l = node->r = NULL;
    node->code="";
    printf("added new int node : %s with addr %s and code %s\n",value, node->addr, node->code);
    return node;
}

SyntaxTree * newIDNode(char* id){
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = ID_NODE;
    node->value.id = node->addr=strdup(id);
    node->l = node->r = NULL;
    node->code="";
    //printf("added new id node : %s with addr %s and code %s\n",id, node->addr, node->code);
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

void printNode(SyntaxTree* a){
    printf("\nNodetype : %d",a->nodetype);
    printf("\nAddr : %s",a->addr);
    printf("\ncode : %s",a->code);
}