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
#define AR_NODE '+'
#define REL_NODE '>'
#define LOG_NODE 'a'
#define MEM_NODE 'i'
#define IDENTITY_NODE 's'
#define BIT_NODE '&'
#define UMINUS_NODE 'M'
#define IF_NODE 'e'

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


SyntaxTree* newBoolExp(char *op, SyntaxTree *l, SyntaxTree *r){
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    
    node->nodetype = LOG_NODE;
    
    node->True = malloc(10);
    node->False = malloc(10);
    l->True = malloc(10);
    l->False = malloc(10);
    char lcode[4000], rcode[4000], code[10000];
    
    if (strcmp(op, "or") == 0) {
        sprintf(node->True, "L%d", label++);
        sprintf(node->False, "L%d", label++);

        if((l->addr==NULL)){
            node->False=strdup(l->False); 
            sprintf(lcode, "%s", strdup(l->code));
        } 
        
        if((r->True!=NULL)){
            node->True=strdup(r->True); 
            sprintf(rcode, "%s", strdup(r->code));
        } 
        
        if ((l->addr!=NULL)) {
            l->True = malloc(10);
            l->False = malloc(10);
            l->True=strdup(node->True); 
            sprintf(l->False, "L%d", label++);
            sprintf(lcode, "%sif %s : goto %s\n%s: ", l->code, l->addr, node->True, l->False);
        }
        
        if ((r->True==NULL)) {
            r->True = malloc(10);
            r->False = malloc(10);
            r->True=strdup(node->True); 
            r->False = strdup(node->False);
            sprintf(rcode, "%sif %s : goto %s", r->code, r->addr, node->True);
        }
        node->l = l;
        node->r = r;

    } else if (strcmp(op, "and") == 0) {
        sprintf(node->True, "L%d", label++);
        sprintf(node->False, "L%d", label++);
        if((l->addr==NULL)){
            node->True=strdup(l->True);
            sprintf(lcode, "%s", strdup(l->code));
        } 
        
        if((r->True!=NULL)){
            node->False=strdup(r->False); 
            sprintf(rcode, "%s", strdup(r->code));
        }
        
        if (l->addr!=NULL) {
            l->True = malloc(10);
            l->False = malloc(10);
            sprintf(l->False,"%s", node->False); 
            sprintf(l->True, "L%d", label++);
            sprintf(lcode, "%sif %s : goto %s\n%s: ", l->code, l->addr, l->True, l->True);
        }

        if((r->True==NULL)) {
            r->True = malloc(10);
            r->False = malloc(10);
            r->True=strdup(node->True); 
            r->False = strdup(node->False);
            sprintf(rcode, "%sif %s : goto %s", r->code, r->addr, r->True);
        }

        node->l = l;
        node->r = r;

    } else if (strcmp(op, "not") == 0) {
        node->True = l->False;
        node->False = l->True;
        sprintf(code, "%sif not %s: goto %s", l->code, l->addr, node->True);
    }
    
    sprintf(code, "%s%s", lcode, rcode);
    node->code = code;
    node->value.op = strdup(op);
    printf("\n%s", node->code);
    return node;
}

SyntaxTree* newIfNode(char *op, SyntaxTree*l, SyntaxTree*r){
    //$1.next = newlabel();$2.next= $$.next;$$.code = $1.code || label($1.next) || $2.code ;
    SyntaxTree *node = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    if(!node) {
        fprintf(stderr, "Out of space\n");
        exit(1);
    }
    node->nodetype = IF_NODE;
    l->next = malloc(10);
    node->next = malloc(10);
    sprintf(l->next, "L%d", label++);
    printf("%s",op);
    strcpy(node->next, r->next);
    sprintf(node->code, "%s%s%s", l->code, l->next, r->code);
    printf("\n%s",node->code);
    return node;
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
            case AR_NODE:
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
    //printf("\nAddr : %s",a->addr);
    printf("\ncode : %s",a->code);
    printf("\ntrue : %s",a->True);
    printf("\nfalse : %s\n\n",a->False);
}