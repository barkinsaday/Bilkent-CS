#include <stdlib.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "PrimalityTest.h"
#include "FileManipulation.h"

#include <sys/types.h>
#include <sys/wait.h>
  
struct item {
	int primes[20];
	int size;
	int processFinished;
};


#define MQNAME "/justaname"


char *bufferp;  // pointer to receive buffer - allocated with malloc()
int bufferlen; // length of the receive buffer


int producer(int, int, mqd_t);


int main(int argc, char *argv[]){
	// Parsing the command line arguments
	    int N = 5;  // Default value
	    int M = 3;  // Default value
	    char *INFILE = NULL;
	    char *OUTFILE = NULL;
	    int c;

	    while ((c = getopt(argc, argv, "n:m:i:o:")) != -1) {
		switch (c) {
		    case 'n':
		        N = atoi(optarg);
		        break;
		    case 'm':
		        M = atoi(optarg);
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
    	
    	//printf("N= %d\t M= %d\t INFILE= %s\t OUTFILE= %s\n", N, M, INFILE, OUTFILE);
    	
    	if (!INFILE || !OUTFILE){
    		printf("INFILE AND OUTFILE SHOULDN'T BE NULL");
    		exit(1);
    	}
	
	//Create N subfiles
	handleSubFileCreation(INFILE, N);

	//Create message queue
	mqd_t mq;
	struct mq_attr mq_attr;
	
	mq = mq_open(MQNAME, O_RDWR | O_CREAT, 0666, NULL);
	if (mq == -1) {
		perror("can not create msg queue\n");
		exit(1);
	}
	//printf("mq created, mq id = %d\n", (int) mq);

	mq_getattr(mq, &mq_attr);
	//printf("mq maximum msgsize = %d\n", (int) mq_attr.mq_msgsize);

	//allocate large enough space for the buffer to store
	//an incoming message
	int bufferlen = mq_attr.mq_msgsize;
	char* bufferp = (char *) malloc(bufferlen);
	
	pid_t child_pid, wpid;
	int status = 0;
    	
	//fork N times and in each child process run producer(id), and exit with 0 
	for (int id=0; id<N; id++) {
		if ((child_pid = fork()) == 0) {
			producer(id, M, mq);
			exit(0);
		}
	}
	
	struct item* itemptr;
		
	FILE* f = fopen(OUTFILE, "w");
	
	//Wait for messages
	int finishedProcesses = 0;
	int started = 0;
	while (finishedProcesses < N){
		int n = mq_receive(mq, (char *) bufferp, bufferlen, NULL);
		if (n == -1) { 
			printf("not ready?\n");
		}
		itemptr = (struct item *) bufferp; // for easy access to item
		//printf("mq_receive success, first item =%p\n", (void*) &(itemptr->primes));
		//printf("size: %d finished: %d items: %d %d %d ", curItem.size, curItem.processFinished, curItem.primes[0], curItem.primes[1], curItem.primes[2]);
	

		//printf("%d\n", itemptr->size);
		
		for(int i = 0; i < itemptr->size; i++){
			//TODO print to OUTPUT.txt
			if (started){
				fprintf(f, "\n");
			}else{
				started = 1;
			}
			
			fprintf(f, "%d", (itemptr->primes)[i]);
			

		}
		
		finishedProcesses += itemptr->processFinished;
	}
	fclose(f);
	

	removeSubFiles(N);
	free(bufferp);
	mq_close(mq);
	return 0;
}

//TODO do we have to free curItem.primes after we are done with each item?
int producer(int id, int M, mqd_t mq){
	//Open message queue
	int n;


	//Prepare item
	struct item curItem;

	curItem.size = 0;
	curItem.processFinished = 0;
	

	// Get filename based on id
	char filename[MAXFILENAME];
	sprintf(filename, "output_of_thread%d.txt", id);
	
	// Open already created file for reading
	FILE *fp = fopen(filename, "r");
	
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

		// 3)Add to item
		if (isPrime){
			curItem.primes[curItem.size] = currentNumber;
			curItem.size += 1;
			//printf("%d\n", curItem.primes[curItem.size-1]);
		}
		
		// 4) Check if message is full. If it is, send it
		if (curItem.size == M){
			//printf("WE ARE HERE");
			//Send item
			n = mq_send(mq, (char *) &curItem, sizeof(struct item), 0);
			if (n == -1) {perror("mq_send failed\n"); exit(1); }
			
			/*
			//Free item
			free(curItem.primes);
			*/
			
			//Reinitialize item
			

			curItem.size = 0;
		}
		// 5)Read line for next iteration
		read = getline(&line, &len, fp);
	} 
	
	//Send one last time, signaling the end of a process(this message can also potentially contain less than M primes)
	curItem.processFinished = 1;
	//Send item
	n = mq_send(mq, (char *) &curItem, sizeof(struct item), 0);
	if (n == -1) {perror("mq_send failed\n"); exit(1); }
		
	/*	
	//Free item
	free(curItem.primes);
	*/
			
	free(line);
	fclose(fp);
}
