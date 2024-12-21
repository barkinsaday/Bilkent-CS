/*
primeT -n N -i INFILE -o OUTFILE

N: number of threads
INFILE: input file(name)
OUTFILE: output file(name)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include "LinkedList.h"
#include "PrimalityTest.h"
#include "FileManipulation.h"


#define MAXTHREADS 20  // max number of threads

DoubleList** Lists; // array of list pointers

struct arg
{
	int t_index; // the index of the created thread
};

void *runner(void *arg_ptr);

int main(int argc, char *argv[])
{
	pthread_t tids[MAXTHREADS];	   // thread ids
	struct arg t_args[MAXTHREADS]; // thread function arguments


	// Error checking
	int ret;
	char *retmsg;


	
	// Parsing the command line arguments
	    int N = 5;  // Default value
	    char *INFILE = NULL;
	    char *OUTFILE = NULL;
	    int c;

	    while ((c = getopt(argc, argv, "n:i:o:")) != -1) {
		switch (c) {
		    case 'n':
		        N = atoi(optarg);
		        break;
		    case 'i':
		        INFILE = optarg;
		        break;
		    case 'o':
		        OUTFILE = optarg;
		        break;
		    default:
		        fprintf(stderr, "Invalid option\n");
		        exit(1);
		}
	    }

    	printf("N= %d\t  INFILE= %s\t OUTFILE= %s\n", N, INFILE, OUTFILE);
    	
    	if (!INFILE || !OUTFILE){
    		printf("INFILE AND OUTFILE SHOULDN'T BE NULL");
    		exit(1);
    	}//

	handleSubFileCreation(INFILE, N);

	
	Lists = (DoubleList**) malloc(sizeof(DoubleList*) * N);
	//Allocate memory for N lists
	for (int i = 0; i < N; i++){
		Lists[i] = (DoubleList*) malloc(sizeof(DoubleList));
		Lists[i]->head = NULL;
		Lists[i]->tail = NULL;
		Lists[i]->current = NULL;
		Lists[i]->size = 0;
	}
	
	//Call threads
	for (int i = 0; i < N; i++)
	{
		t_args[i].t_index = i;
		//t_args[i].n = countLines(fopen(INFILE, "r"));

		ret = pthread_create(&(tids[i]),
							 NULL, runner, (void *)&(t_args[i]));

		if (ret != 0)
		{
			printf("thread create failed \n");
			exit(1);
		}
		//! DEBUG MESSAGE
		//printf("thread %i with tid %u created\n", i,(unsigned int)tids[i]);
	}

	// joins
	printf("main: waiting for all threads to terminate\n");
	for (int i = 0; i < N; ++i)
	{
		ret = pthread_join(tids[i], (void **)&retmsg);
		if (ret != 0)
		{
			printf("thread join failed \n");
			exit(1);
		}
		//printf("thread terminated, msg = %s\n", retmsg);
		// we got the reason as the string pointed by retmsg.
		// space for that was allocated in thread function.
		// now we are freeing the allocated space.
		free(retmsg);
	}

	//! Debug line
	//printf("main: all threads terminated\n");

	removeSubFiles(N);
	
	printf("\n");

	FILE* f = fopen(OUTFILE, "w");
	int started = 0;
	for (int i = 0; i < N; i++){		
		DoubleNode* curElem = iterate(Lists[i]);

		while (curElem != NULL){
			for (int j = 0; j < curElem->frequency; j++){
				if (started){
					fprintf(f, "\n");
				}else {
					started = 1;
				}
				
				fprintf(f, "%d", curElem->data);
			}
			curElem = iterate(Lists[i]);
		}
		resetIterator(Lists[i]);			
	}

	//TODO: print this to OUTFILE

	
	fclose(f);
	
	//Free Lists
    for (int i = 0; i < N; i++){
	clean(Lists[i]);
	free(Lists[i]);
    }
    free(Lists);


	return 0;
}


void *runner(void *arg_ptr)
{ /* thread start function */
	char *retreason;

	int t_index = ((struct arg *)arg_ptr)->t_index;
	// Get filename based on t_index
	char filename[MAXFILENAME];
	sprintf(filename, "output_of_thread%d.txt", t_index);


	// Open already created file for reading
	FILE *fp = fopen(filename, "r");

	//! Debug line
	//printf("thread %d started\n", t_index);

	//! Error catching
	if (fp == NULL)
	{
		perror("runner:");
		exit(1);
	}

	//Source code for line reading: https://linux.die.net/man/3/getline
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	int currentNumber;
	bool isPrime;
	
	read = getline(&line, &len, fp);
	while (read >= 0){
		// 1)Change it to int
		currentNumber = atoi(line);
		
		// !DEBUG LINE 
		//printf("%d\n", currentNumber); 
		
		// 2)Check primality
		isPrime = checkPrimality(currentNumber);

		// 3)Add to list
		if (isPrime){
			insertDataAndFrequency(Lists[t_index], currentNumber, 1);
		}

		// 4)Read line for next iteration
		read = getline(&line, &len, fp);
	} 

	free(line);

	fclose(fp);

	retreason = (char *)malloc(200);
	strcpy(retreason, "normal termination of thread");
	pthread_exit(retreason); //  tell a reason to thread waiting in join
	// we could simple exit as below, if we don't want to pass a reason
	// pthread_exit(NULL);
	// then we would also modify pthread_join call.
}


