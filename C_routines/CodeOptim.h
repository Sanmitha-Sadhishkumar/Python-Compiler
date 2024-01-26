#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 10000
#define MAX_COLS 1000
char* lines[MAX_ROWS];

void splitLines();

int LabeltoIndex(char* s);

int* RemoveDupandSort();

char** BasicBlocks(int* uniqueArr);

void printBlocks(char **blocks);