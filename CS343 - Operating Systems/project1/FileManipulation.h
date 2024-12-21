#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXFILENAME 50 // max length of a filename


int countLines(FILE *file);
//Created files will be called:  "output_of_thread%d.txt"
//int createSubFiles(FILE* file, int linesPerFile, int remainder, int fileCount);
int removeSubFiles(int fileCount);
int createSubFiles(int index);

void populateSubFiles(char* INFILE, int N);

void printToFile(char* OUTFILE, char* line){
	// Create subfile
	FILE* f = fopen(OUTFILE, "w");
	
	// Write line to subfile
	fprintf(f, "%s", line);
	
	// Close file
	fclose(f);
}

void handleSubFileCreation(char* INFILE, int N){


	/*
	// Count number of lines:
	int numberOfLines = countLines(mainInputFile);
	
	// !Code doesn't work for N > numberOfLines
	int numberOfLinesPerFile = (int)(numberOfLines / N);
	int remainder = numberOfLines - numberOfLinesPerFile * (N-1);
	*/

	// TODO ERROR CHECKING
	
	//this will only create the files, not write into them
	createSubFiles(N);
	populateSubFiles(INFILE, N);

}

void populateSubFiles(char* INFILE, int N){
	FILE *mainInputFile = fopen(INFILE, "r");
	//! Error catching
	if (mainInputFile == NULL)
	{
		perror("main:");
		exit(1);
	}
	
	//First, open all files for appending
	char filename[MAXFILENAME];
	FILE** subfiles = (FILE**) malloc(sizeof(FILE*) * N);
	for (int i = 0; i < N; i++){
		// Get filename based on index
		sprintf(filename, "output_of_thread%d.txt", i);
		subfiles[i] = fopen(filename, "a");	
	}
	
	int curFileIndex;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	//k'th integer goes to ((k − 1)%N) + 1 th file, so 
	int k = 1;
	read = getline(&line, &len, mainInputFile);
	while (read >= 0){
		curFileIndex = (k-1)%N; //-1, since indices are zero indexed
		
		//Write already red line to current subfile
		fprintf(subfiles[curFileIndex], "%s", line);
		
		//Read line for next iteration
		read = getline(&line, &len, mainInputFile);
		k += 1;
	} 

	free(line);

	
	//Close and free 
	for (int i = 0; i < N; i++){
		fclose(subfiles[i]);
		//free(subfiles[i]);
	}

	free(subfiles);
	
	//Close main file
	fclose(mainInputFile);
}

//TODO REFACTOR: unnecessary abstraction
int createSubFile(int index)
{
	// Get filename based on index
	char filename[MAXFILENAME];
	sprintf(filename, "output_of_thread%d.txt", index);
	
	// Create, and immediately close, subfile
	fclose(fopen(filename, "w"));
}


int createSubFiles(int fileCount)
{
	for (int i = 0; i < fileCount; i++)
	{
		createSubFile(i);
	}

}

#define BUF_SIZE 65536
// Borrowed function
// Credit: https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
int countLines(FILE *file)
{
	char buf[BUF_SIZE];
	int counter = 0;
	for (;;)
	{
		size_t res = fread(buf, 1, BUF_SIZE, file);
		if (ferror(file))
			return -1;

		int i;
		for (i = 0; i < res; i++)
			if (buf[i] == '\n')
				counter++;

		if (feof(file))
			break;
	}

	// The function should return input as it received it
	rewind(file);

	return counter;
}

/*
int createSubFile(FILE *file, int index, int lineCount)
{
	char filename[MAXFILENAME];
	sprintf(filename, "output_of_thread%d.txt", index);
	// Create subfile for writing
	FILE *subfile = fopen(filename, "w");

	//Source code for line reading: https://linux.die.net/man/3/getline
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	for (int i = 0; i < lineCount; i++)
	{
		read = getline(&line, &len, file);
		fprintf(subfile, "%s", line);
	}

	free(line);
	fclose(subfile);
	//! we probably don't need to rewind?
}


int createSubFiles(FILE *file, int linesPerFile, int remainder, int fileCount)
{
	int i = 0;
	// N-1 files of size numberOfLinesPerFile
	for (i = 0; i < fileCount - 1; i++)
	{
		createSubFile(file, i, linesPerFile);
	}

	// 1 file of size remainder
	createSubFile(file, i, remainder);

	// The function should return input as it received it
	rewind(file);
}
*/

int removeSubFile(int index){
	char filename[MAXFILENAME];
	sprintf(filename, "output_of_thread%d.txt", index);

	int ret = remove(filename);

	if (ret == 0)
	{
		//printf("File deleted successfully");
	}
	else
	{
		printf("Error: unable to delete the file");
	}

	return ret;
}

int removeSubFiles(int fileCount)
{
	for (int i = 0; i < fileCount; i++)
	{
		removeSubFile(i);
	}
}





