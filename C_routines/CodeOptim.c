#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CodeOptim.h"

int li=0;
int block_num[100];
int b=0;

void splitLines(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s for writing");
        return;
    }
    char line[256];
    size_t len = 0;
    ssize_t read;
    while (fgets(line, sizeof(line), file) != NULL) {
        lines[li]=(char*)malloc(strlen(line)+1);
        sprintf(lines[li],"%s", line);
        li++;
    }
    fclose(file);
}

int LabeltoIndex(char* s){
    int i;
    sprintf(s, "%s : ", s);
    for(i=0; i<li; i++){
        if(strstr(lines[i], s)){
            return i+1;
        }
    }
    return -1;
}

void Convert() {
    char code[1000] = "";
    int check=0;
    const char *delimiter = "\n";
    int lineNumber1, lineNumber2;
    char string1[100];
    char string2[100];
    int i;

    for (i = 0; i < li; i++) {
        check=0;
        strcpy(string1, strdup(lines[i]));
        while (sscanf(string1, "L%d : %[^\n]", &lineNumber1, string1) == 2) {
            if (string1 != NULL) {
                check=1;
                if (sscanf(string1, "if %s : goto L%d", string2, &lineNumber2) == 2){
                    char buf[10];
                    sprintf(buf, "L%d", lineNumber2);
                    int index = LabeltoIndex(buf);
                    block_num[b++]=index;
                    block_num[b++]=i+2;
                    sprintf(code, "%sif %s : goto (%d)\n", code, string2, index);
                } else {
                    char s[100];
                    if(sscanf(string1, "L%d : %[^\n]", &lineNumber1, s) != 2){
                    strcat(code, string1);
                    strcat(code, "\n");
                    }
                }
            }
        } if ((sscanf(lines[i], "%s L%d", string1, &lineNumber1) == 2)){
            char buf[10];
            sprintf(buf, "L%d", lineNumber1);
            int index = LabeltoIndex(buf);
            sprintf(code, "%s%s (%d)\n", code, string1, index);
            block_num[b++]=index;
            block_num[b++]=i+2;
        } else if (sscanf(lines[i], "if %s : goto L%d", string1, &lineNumber1) == 2){
            char buf[10];
            sprintf(buf, "L%d", lineNumber1);
            int index = LabeltoIndex(buf);
            sprintf(code, "%sif %s : goto (%d)\n", code, string1, index);
            block_num[b++]=index;
            block_num[b++]=i+2;
        } else if (check==0){
            if (string1 != NULL) {
                strcat(code, lines[i]);
            }
        }
    }
    FILE *file = fopen("../Data Structures/3AddrcodewithoutLabel.txt", "w");
    fprintf(file, "%s", code);
    fclose(file);
}

int* RemoveDupandSort(){
    int* uniqueArr = (int*)malloc(b*sizeof(int));
    int index = 1, j, i, temp;
    uniqueArr[0] = block_num[0];

    for (i = 1; i < b; i++) {
        for (j = 0; j < index; j++) {
            if (block_num[i] == uniqueArr[j]) {
                break;
            }
        }
        if (j == index) {
            uniqueArr[index] = block_num[i];
            index++;
        }
    }
    for (i = 0; i < index - 1; i++) {
        for (j = 0; j < index - i - 1; j++) {
            if (uniqueArr[j] > uniqueArr[j + 1]) {
                temp = uniqueArr[j];
                uniqueArr[j] = uniqueArr[j + 1];
                uniqueArr[j + 1] = temp;
            }
        }
    }
    b=index;
    return uniqueArr;
}

int NumIndex(int *uniqueArr, int data){
    int i;
    for(i=0;i<b;i++)
        if(data==uniqueArr[i])
            return i+1;
    return -1;
}

char** BasicBlocks(int* uniqueArr){
    int i=0, j=0, b1=0;
    char** blocks = malloc(b * sizeof(char*));
    blocks[0] = (char*)malloc(1000 * sizeof(char));
    blocks[b1][0]='\0';
    li=0;
    int index, num=-1;
    char string1[256];
    splitLines("../Data Structures/3AddrcodewithoutLabel.txt");
    for(i=0;i<li;i++){
        int bnum = uniqueArr[j];
        if((bnum-1)==li)
            break;
        if((i==bnum-1) && (i!=0)){
            blocks[++b1] = (char*)malloc(1000 * sizeof(char));
            blocks[b1][0]='\0';
            j++;
        }
        if (sscanf(lines[i], "%s (%d)", string1, &index)==2){
            num = NumIndex(uniqueArr, index);
            sprintf(blocks[b1], "%s%s B%d\n", blocks[b1], string1, num);
        } else if (sscanf(lines[i], "if %s : goto (%d)", string1, &index)==2){
            num = NumIndex(uniqueArr, index);
            sprintf(blocks[b1], "%sif %s : goto B%d\n", blocks[b1], string1, num);
        } else 
            sprintf(blocks[b1], "%s%s", blocks[b1], lines[i]);
    }
    return blocks;
}

void printBlocks(char **blocks){
    FILE *file = fopen("../Data Structures/BasicBlocks.txt", "w");
    int i;
    char *B = (char*)malloc(sizeof(6));
    for(i=0;i<=b;i++){
        sprintf(B, "B%d", i);
        fprintf(file, "%s: \n%s\n", B, blocks[i]);
    }
    fclose(file);
}
