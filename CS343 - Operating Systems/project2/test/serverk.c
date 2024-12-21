#include <stdlib.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "shareddefs.h"

//Continue: Implement worker thread and run (check for race-condition)

//FUNCTION PROTOTYPES
void* S_FE(void* argp);
void* worker_T();

//Gloabl variables
char* bufferp; //pointer to receive via MQ1 buffer - allocated with malloc()
int bufferlen;//length of the receive buffer
int M = 5;//num of worker threads (default 5, for faster debuging)
struct item* itemp = NULL;//since we pass from S_FE to worker one message at a time we can pass using this global var
pthread_mutex_t serLock;
pthread_cond_t serCond;


int dcount;
char* fname;
int tcount;
int vsize;
char* mqname;
int main(int argc, char* argv[])
{
    // Parse command line arguments
    int dcount = 0;
    char *fname = NULL;
    int tcount = 0;
    int vsize = 0;
    char *mqname = NULL;

    // Check if the correct number of arguments is provided
    if (argc != 11) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        fprintf(stderr, "Usage: %s -d dcount -f fname -t tcount -s vsize -m mqname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Process command line arguments
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-d") == 0) {
            dcount = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            fname = argv[i + 1];
        } else if (strcmp(argv[i], "-t") == 0) {
            tcount = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-s") == 0) {
            vsize = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            mqname = argv[i + 1];
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            fprintf(stderr, "Usage: %s -d dcount -f fname -t tcount -s vsize -m mqname\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Check if required options are provided
    if (dcount <= 0 || fname == NULL || tcount <= 0 || vsize <= 0 || mqname == NULL) {
        fprintf(stderr, "Error: Missing or invalid command line arguments\n");
        fprintf(stderr, "Usage: %s -d dcount -f fname -t tcount -s vsize -m mqname\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    M = tcount;
    
    //================================================
    //CREATE MQ's IN SERVER_START():
    //Give arguments from cmd
    //MQ1: Producer to Consumer -- create
    //================================================
    mqd_t mq;
    struct mq_attr mq_attr;
    int n;
    mq = mq_open(MQNAME, O_RDWR | O_CREAT, 0666, NULL);
    if (mq == -1) {
        perror("can not create msg queue\n");
        exit(1);
    }
    printf("MQ1 created, MQ1 id = %d\n", (int) mq);
    mq_getattr(mq, &mq_attr);
    printf("MQ1 maximum msgsize = %d\n", (int) mq_attr.mq_msgsize);
    
    //MQ2: Consumer to Producer -- create
    mqd_t mq2;
    struct mq_attr mq_attr_2;
    mq2 = mq_open(MQ2, O_RDWR | O_CREAT, 0666, NULL);
    if(mq2 == -1){printf("Can not create MQ2\n"); return -22;}
    printf("MQ2 created, MQ2 id = %d\n", (int)mq2);
    mq_getattr(mq2, &mq_attr_2);
    printf("MQ2 maximum msgsize = %d\n", (int)mq_attr_2.mq_msgsize);
    printf("\n");
    printf("\n");
    
    //Allocate large enough space for the buffers to store incoming/ongoing messages
    bufferlen = mq_attr.mq_msgsize;
    bufferp = (char *) malloc(bufferlen);
    
    
	
//MAIN CAN CALL C_FE OR CLIENT_T AFTER THIS POINT...

//Create and call client_T() to send the first inputs to server
     //Init mutex and condition
     pthread_mutex_init(&serLock, NULL);
     pthread_cond_init(&serCond, NULL);
     pthread_t w[M+1];
     for(int i=0; i<M+1; i++){
        //PASSING ARGUMENT TO THREADS (defining "argp" outside of the loop(?))
        //Each thread has its own arg_mq but all point to same MQ which is what we want
        
     	struct arg* argp = malloc(sizeof(struct arg));
     	argp->arg_mq = mq;//THIS IS FIXED IN EACH THREAD
     	argp->arg_mq2 = mq2;//THIS IS FIXED IN EACH THREAD
     	argp->a = malloc(sizeof(int));
     	*(argp->a) = i;
     	
        if(i == M){//call S_FE as last thread (workers will wait on condition anyways)
        	if(pthread_create(&w[i], NULL, &S_FE, argp)){printf("Error on thread creation\n"); return -1;}
        }else{
        	if(pthread_create(&w[i], NULL, &worker_T, argp)){printf("Error on thread creation\n"); return -1;}
        }
     }
     
     //S_FE here after workers start to run
     
     
     //Join client_T()
     for(int i=0;i<M+1;i++)
		if(pthread_join(w[i], NULL)){printf("ERROR: Thread Join: %d\n", i); return 2;}
     printf("end of main...\n");
   
    
    free (bufferp);
    mq_close(mq);
    mq_close(mq2);
    pthread_mutex_destroy(&serLock);
    pthread_cond_destroy(&serCond);
    return 0;
}//End of main...

//FUNCTION IMPLEMENTATIONS
void* S_FE(void* argp)//IMPORTANT TIP: SEND SİGNAL TO WORKER UPON SUCCESSFULL RECEIVE
{
   printf("Inside S_FE\n");
   struct arg* p = argp;
   
   mqd_t mq = p->arg_mq;
   mqd_t mq2 = p->arg_mq2;
   while(1){
	
    	//================================================
    	//RECIEVE MESSAGE VIA MQ1: 
    	//S_FE() will do this
    	//Message comes from client_T() in clientk.c via MQ1
    	//This will be in a loop: Always try to catch/receive message, always signal to worker upon receiving
    	//================================================
        int n = mq_receive(mq, bufferp, bufferlen, NULL);
        if (n == -1) {
            perror("mq_receive failed\n");
            exit(1);
        }
        pthread_mutex_lock(&serLock);
        itemp = (struct item *) bufferp;
        printf("Recieved item id = %d\n", itemp->id);
        pthread_mutex_unlock(&serLock);
        pthread_cond_signal(&serCond);
   }
}//End of S_FE...

void* worker_T(void* argp)
{
	sleep(1);
	struct arg* p = argp;
   	mqd_t mq = p->arg_mq;
   	mqd_t mq2 = p->arg_mq2;
	pthread_mutex_lock(&serLock);//LOCK
	while(itemp == NULL)//condition
	{
		pthread_cond_wait(&serCond, &serLock);//WAIT ON CONDITION
	}
	//Send via MQ2
	
	char* bufferp = (char*) malloc(bufferlen);
	struct item* temp = (struct item*) bufferp;
	temp->id = (itemp->id)+1;
	itemp = NULL;
	int n;
        n = mq_send(mq2, bufferp, sizeof(struct item), 0);
        printf("Ressponse send: %d\n", temp->id);
        if (n == -1) {
            perror("mq_send failed\n");
            exit(1);
        }
        free(bufferp);
	pthread_mutex_unlock(&serLock);
	//sleep(1);
}




/*
PREVIOUS CODE
	while (1) {
    	//================================================
    	//RECIEVE MESSAGE VIA MQ1: 
    	//S_FE() will do this
    	//Message comes from client_T() in clientk.c via MQ1
    	//This will be in a loop: Always try to catch/receive message
    	//================================================
        n = mq_receive(mq, bufferp, bufferlen, NULL);
        if (n == -1) {
            perror("mq_receive failed\n");
            exit(1);
        }
        printf("mq_receive success, message size = %d\n", n);
        itemp = (struct item *) bufferp;
        printf("received item.id = %d\n", itemp->id);
        printf("received item.astr = %s\n", itemp->astr);
        
        //================================================
        //SEND UPDATED MESSAGE VIA MQ2: 
        //WORKER_T() will do this
        //We will have condition variable which is signaled by S_FE()
        //A thread is ALWAYS--> either working or waiting on the condition
        //Message is send to C_FE() in clientk.c via MQ2
        //================================================
       
        (itemp->id)++;//Update the Message may need to define itemp again
        if(mq_send(mq2, bufferp, sizeof(struct item), 0) == -1){printf("EROR: MQ2 Send Failed\n"); return -44;}
        printf("\n");
    }

*/






