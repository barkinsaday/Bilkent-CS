#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024

int countTotalLines(FILE *file) {
    int lines = 0;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL) {
        lines++;
    }

    // Rewind the file to the beginning for future reads
    rewind(file);
    return lines;
}

void splitFile(const char *filename, int M, char* outname) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int totalLines = countTotalLines(file);
    int linesPerFile;
    if(totalLines % M == 0) {
    	
    	linesPerFile = (totalLines / M);
    }else{
    	linesPerFile = (totalLines / M)+1;
    }
    int extraLines = totalLines % M; // Lines remaining after equal division
    int lineCount = 0;
    char line[MAX_LINE_LENGTH];
    char newFilename[50];

    for (int i = 0; i < M; i++) {
        sprintf(newFilename, "%s%d.txt", outname, i+1); 
        FILE *newFile = fopen(newFilename, "w");

        if (newFile == NULL) {
            perror("Error opening new file");
            fclose(file);
            return;
        }

        int currentFileLineLimit = linesPerFile + (i < extraLines ? 1 : 0);

        while (lineCount < currentFileLineLimit * (i + 1) && fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            fputs(line, newFile);
            lineCount++;
        }

        fclose(newFile);
    }

    fclose(file);
}
