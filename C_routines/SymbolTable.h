#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SymbolTable{
  char token[10];
  char attr[100];
  char type[10];
} SymbolTable;

void printST();

int installID(char *a, char *t);

int installLit(char *b, char *t);