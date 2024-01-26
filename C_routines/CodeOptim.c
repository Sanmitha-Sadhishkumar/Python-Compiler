#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CodeOptim.h"

int li=0;

void splitLines() {
    FILE *file = fopen("../Data Structures/3Addrcode.txt", "r");
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
    for(i=0; i<li; i++){
        if(strncmp(s, lines[i], strlen(s))==0){
            return i+1;
        }
    }
    return -1;
}

void Convert() {
    char code[1000] = "";
    const char *delimiter = "\n";
    int lineNumber;
    char string1[100];
    char string2[100];
    int i;

    for (i = 0; i < li; i++) {
        if (sscanf(lines[i], "L%d : %[^\n]", &lineNumber, string1) == 2) {
            if (string1 != NULL) {
                if (sscanf(string1, "if %s : goto L%d", string2, &lineNumber) == 2){
                    char buf[10];
                    sprintf(buf, "L%d", lineNumber);
                    int index = LabeltoIndex(buf);
                    sprintf(code, "%sif %s : goto (%d)\n", code, string2, index);
                } else {
                    strcat(code, string1);
                    strcat(code, "\n");
                }
            }
        } else if ((sscanf(lines[i], "%s L%d", string1, &lineNumber) == 2)){
            char buf[10];
            sprintf(buf, "L%d", lineNumber);
            int index = LabeltoIndex(buf);
            sprintf(code, "%s%s (%d)\n", code, string1, index);
        } else if (sscanf(lines[i], "if %s : goto L%d", string1, &lineNumber) == 2){
            char buf[10];
            sprintf(buf, "L%d", lineNumber);
            int index = LabeltoIndex(buf);
            sprintf(code, "%sif %s : goto (%d)\n", code, string1, index);
        } else {
            if (string1 != NULL) {
                strcat(code, lines[i]);
            }
        }
    }
    FILE *file = fopen("../Data Structures/3AddrcodewithoutLabel.txt", "w");
    fprintf(file, "%s", code);
    fclose(file);
}

int main(){
    splitLines();
    Convert();
    return 1;
}