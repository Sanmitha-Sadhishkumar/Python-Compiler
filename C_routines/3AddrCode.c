#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "3AddrCode.h"

int addTriple(char *o, char *a1, char *a2){
    strcpy(T[t].op, o);
    strcpy(T[t].arg1, a1);
    strcpy(T[t].arg2, a2);
    t++;
    return t-1;
}

void addQuadruple(char *o, char *a1, char *a2, char *r){
    strcpy(Q[q].op, o);
    strcpy(Q[q].arg1, a1);
    strcpy(Q[q].arg2, a2);
    q++;
    return q-1;
}