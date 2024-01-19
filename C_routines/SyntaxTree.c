#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "SyntaxTree.h"

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

int quad=1;
int label =1;

SyntaxTree * newOpNode(char *op, SyntaxTree *l, SyntaxTree *r){
    SyntaxTree *node = malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }

    if ((strcmp(op, "+") == 0) || (strcmp(op, "-") == 0) || (strcmp(op, "*") == 0) || (strcmp(op, "/") == 0) || (strcmp(op, "%") == 0) || 
        (strcmp(op, "**") == 0) || (strcmp(op, "//") == 0)){
        node->nodetype = AR_NODE;
    } else if ((strcmp(op, ">") == 0) || (strcmp(op, ">=") == 0) || (strcmp(op, "<") == 0) || (strcmp(op, "<=") == 0) || (
        strcmp(op, "==") == 0) || (strcmp(op, "!=") == 0)) {
        node->nodetype = REL_NODE;
    } else if ((strcmp(op, "=") == 0) || (strcmp(op, "+=") == 0) || (strcmp(op, "-=") == 0) || (strcmp(op, "*=") == 0) || 
        (strcmp(op, "/=") == 0) || (strcmp(op, "//=") == 0) || (strcmp(op, "%=") == 0) || (strcmp(op, "**=") == 0) || 
        (strcmp(op, "&=") == 0) || (strcmp(op, "|=") == 0) || (strcmp(op, "^=") == 0) || (strcmp(op, ">>=") == 0) || (strcmp(op, "&&=") == 0)){
        node->nodetype = ASS_NODE;
    } else if ((strcmp(op, "&") == 0) || (strcmp(op, "|") == 0) || (strcmp(op, "^") == 0) || (strcmp(op, ">>") == 0) || (strcmp(op, "&&") == 0)){
        node->nodetype = BIT_NODE;
    } else if ((strcmp(op, "and") == 0) || (strcmp(op, "or") == 0) || (strcmp(op, "not") == 0)){
        node->nodetype = LOG_NODE;
    } else if ((strcmp(op, "is") == 0) || (strcmp(op, "is not") == 0)){
        node->nodetype = IDENTITY_NODE;
    } else if ((strcmp(op, "in") == 0) || (strcmp(op, "not in") == 0)){
        node->nodetype = MEM_NODE;
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
    
    node->True = malloc(10);
    node->False = malloc(10);
    node->True= node->False= NULL;
    quad++;
    //printf("\nadded new op node: %s with with addr %s\n",op, node->addr);
    return node;
}

SyntaxTree * newDoubleNode(char* value){
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
    node->True= node->False= NULL;
    node->code="";
    //printf("added new double node : %s with addr %s and code %s\n",value, node->addr, node->code);
    return node;
}

SyntaxTree * newIntNode(char* value){
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
    node->True= node->False= NULL;
    node->code="";
    //printf("added new int node : %s with addr %s and code %s\n",value, node->addr, node->code);
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
    node->True= node->False= NULL;
    node->code="";
    //printf("added new id node : %s with addr %s and code %s\n",id, node->addr, node->code);
    return node;
}


SyntaxTree* newBoolExp(SyntaxTree *node){
    if ((node!=NULL) && (node->nodetype==LOG_NODE)){
        newBoolExp(node->l);
        newBoolExp(node->r);
        char lcode[40000], rcode[40000], code[100000];
    
        if (strcmp(node->value.op, "or") == 0) {
            if((node->l->nodetype==LOG_NODE)){
                sprintf(lcode, "%s\n%s : ", strdup(node->l->code), node->l->False);
            } else {
                sprintf(lcode, "%sif %s : goto %s\ngoto %s\n%s: ", node->l->code, node->l->addr, node->l->True, node->l->False, node->l->False);
            }
            if((node->r->nodetype==LOG_NODE)){
                sprintf(rcode, "%s\n%s : ", strdup(node->r->code), node->r->True);
            } else {
                sprintf(rcode, "%sif %s : goto %s\n goto %s", node->r->code, node->r->addr, node->r->True, node->r->False);
            }
        } else if (strcmp(node->value.op, "and") == 0) {
            if((node->l->nodetype==LOG_NODE)){
                sprintf(lcode, "%s\n%s : ", strdup(node->l->code), node->l->True);
            } else {
                sprintf(lcode, "%sif %s : goto %s\ngoto %s\n%s: ", node->l->code, node->l->addr, node->l->True, node->l->False, node->l->True);
            }
            if((node->r->nodetype==LOG_NODE)){
                sprintf(rcode, "%s\n%s : ", strdup(node->r->code), node->r->False);
            } else {
                sprintf(rcode, "%sif %s : goto %s\n goto %s", node->r->code, node->r->addr, node->r->True, node->r->False);
           }

        } else if (strcmp(node->value.op, "not") == 0) {
            sprintf(code, "%sif not %s: goto %s\n", node->l->code, node->l->addr, node->True);
        }
        sprintf(code, "%s %s", strdup(lcode),  strdup(rcode));
        node->code = strdup(code);
        node->addr = NULL;
    //printf("\n\n%s : %s", op, node->code);
        return node;
    }
}

SyntaxTree* newIfNode(char *op, SyntaxTree*l, SyntaxTree*r){
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = IF_NODE;
    l->next = malloc(10);
    node->next = malloc(10);
    node->True = malloc(10);
    node->False = malloc(10);
    char code[400000];
    sprintf(l->next, "%s", l->True);
    sprintf(node->True, "%s", l->True);
    sprintf(node->False, "%s", l->False);
    sprintf(node->next, "L%d", label++);
    sprintf(code, "%s\n%s :%s",  strdup(l->code), l->True, strdup(r->code));
    node->code = strdup(code);
    return node;
}

SyntaxTree* newElseNode(SyntaxTree*l, SyntaxTree*r){
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    char code[400000];
    node->next = malloc(10);
    r->next = malloc(10);
    sprintf(node->next, "%s", l->next);
    sprintf(r->next, "%s", l->next);
    node->nodetype = IF_NODE;
    sprintf(code, "%sgoto %s\n%s : %s\n", strdup(l->code), l->next, l->False, strdup(r->code));
    node->code = strdup(code);
    return node;
}

SyntaxTree* newElifJoinNode(SyntaxTree*l, SyntaxTree*r){
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    char code[400000];
    node->next = malloc(10);
    r->next = malloc(10);
    node->nodetype = ELIF_NODE;
    node->True = malloc(10);
    node->False = malloc(10);
    node->True = l->True;
    node->False = r->False;
    sprintf(node->next, "%s", l->next);
    sprintf(r->next, "%s", l->next);
    sprintf(code, "%sgoto %s\n%s : %s\n", strdup(l->code), l->next ,l->False, strdup(r->code));
    node->code = strdup(code);
    return node;
}

SyntaxTree* newStJoinNode(SyntaxTree*l, SyntaxTree*r){
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    char code[400000];
    sprintf(code, "%s%s", strdup(l->code), strdup(r->code));
    node->code = strdup(code);
    return node;
}

SyntaxTree* newBoolJoinNode(char *op, SyntaxTree* l, SyntaxTree* r){
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = LOG_NODE;
    node->l = l;
    node->r = r;
    node->value.op = op;
    return node;
}

SyntaxTree* newBoolLabelNode(char* type, SyntaxTree* node){
    if ((node!=NULL) && (node->nodetype==LOG_NODE)){
        if (strcmp("root", type)==0){
            node->True = malloc(10);
            node->False = malloc(10);
            sprintf(node->True, "L%d", label++);
            sprintf(node->False, "L%d", label++);
        }
        if (node->l!=NULL){
            if (strcmp(node->value.op, "and")==0){
                node->l->True = malloc(10);
                sprintf(node->l->True, "L%d", label++);
                node->l->False = node->False;
            } else if (strcmp(node->value.op, "or")==0){
                node->l->False = malloc(10);
                sprintf(node->l->False, "L%d", label++);
                node->l->True = node->True;
            } else if (strcmp(node->value.op, "not") == 0) {
                node->True = node->l->False;
                node->False = node->l->True;
            }
            newBoolLabelNode("leaf", node->l);
        }
        if (node->r!=NULL){
            node->r->True = node->True;
            node->r->False = node->False;
            newBoolLabelNode("leaf", node->r);
        }
    }
}

SyntaxTree* newWhileNode(char *op, SyntaxTree*l, SyntaxTree*r){
    //begin = newlabel();$2.true = newlabel();$2.false = $$.next; $4.next = begin; $$.code = label(begin) || $2.code ||  label($2.true) || $4.code || gen('goto' begin); }
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = WHILE_NODE;
    l->next = malloc(10);
    r->next = malloc(10);
    node->next = malloc(10);
    node->True = malloc(10);
    node->False = malloc(10);
    char code[400000];
    sprintf(l->next, "%s", l->True);
    sprintf(node->True, "%s", l->True);
    sprintf(node->False, "%s", l->False);
    sprintf(node->next, "L%d", label++);
    sprintf(r->next, "L%d", label++);
    sprintf(code, "%s : %s\n%s :%sgoto %s", r->next, strdup(l->code), l->True, strdup(r->code), r->next);
    node->code = strdup(code);
    return node;
}

void printSyntaxTree(SyntaxTree *head) {
    if (head != NULL) {
        printSyntaxTree(head->l);

        switch (head->nodetype) {
            case ID_NODE:
                printf("\nIdentifier : %s ", head->value.id);
                break;
            case INT_NODE:
                printf("\nInteger : %d ", head->value.intval);
                break;
            case DOUBLE_NODE:
                printf("\nDouble : %f ", head->value.doubleval);
                break;
            case AR_NODE:
                printf("\nArithmetic Operator : %s ",head->value.op);
                break;
            case ASS_NODE:
                printf("\nAssignment Operator %s ",head->value.op);
                break;
            case LOG_NODE:
                printf("\nLogical Operator %s ",head->value.op);
                printf("\n %s - %s",head->True, head->False);
                break;
            default:
                printf("\nUnknown node type: %c ", head->nodetype);
                break;
        }

        printSyntaxTree(head->r);
    }
}

void printNode(SyntaxTree* a){
    printf("\nNodetype : %d",a->nodetype);
    //printf("\nAddr : %s",a->addr);
    printf("\ncode : %s",a->code);
    printf("\ntrue : %s",a->True);
    printf("\nfalse : %s\n\n",a->False);
}