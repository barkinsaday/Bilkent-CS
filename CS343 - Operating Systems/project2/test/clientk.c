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
#include "splitter.h"


//NOTE: IN THE REAL PROJECT-- EACH THREAD HAS ITS OWN INPUT FILE SO WE DO NOT CHECK FOR RACE-CONDITIONS ON itemp/inputfile
//OUR CONDITION FOR client_T IS THE RESPONSE THAT SERVER GIVES NOT RACE-CONDITION OF MULTIPLE CLIENTS MODIFIYING SAME FILE



//Function Prototypes
void* C_FE();
void* client_T(void* argp);

//CMD Arguments
int M = 7;//num of threads (client_T)

//User Variables
int bufferlen;//length of the send buffer
pthread_mutex_t cliLock;
pthread_cond_t cliCond;
mqd_t mq;
mqd_t mq2;
int isSuccessfull = 0;


int numClientThreads;
char* filePrefix;
int valueSize;
char* mqName;
int debugLevel;
int main(int argc, char* argv[])
{
   // Parse command line arguments
    int numClientThreads = 0;
    char* filePrefix = NULL;
    int valueSize = 0;
    char* mqName = NULL;
    int debugLevel = 0;

    // Check if the correct number of arguments is provided
    if (argc != 11) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        fprintf(stderr, "Usage: %s -n clicount -f fname -s vsize -m mqname -d dlevel\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Process command line arguments
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-n") == 0) {
            numClientThreads = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            filePrefix = argv[i + 1];
        } else if (strcmp(argv[i], "-s") == 0) {
            valueSize = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            mqName = argv[i + 1];
        } else if (strcmp(argv[i], "-d") == 0) {
            debugLevel = atoi(argv[i + 1]);
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            fprintf(stderr, "Usage: %s -n clicount -f fname -s vsize -m mqname -d dlevel\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Check if required options are provided
    if (numClientThreads <= 0 || filePrefix == NULL || valueSize <= 0 || mqName == NULL || debugLevel < 0) {
        fprintf(stderr, "Error: Missing or invalid command line arguments\n");
        fprintf(stderr, "Usage: %s -n clicount -f fname -s vsize -m mqname -d dlevel\n", argv[0]);
        exit(EXIT_FAILURE);
    }
	
    //MQ1: Producer to Consumer -- initialize
    M = numClientThreads;
    struct mq_attr mq_attr;
    mq = mq_open(MQNAME, O_RDWR);
    if (mq == -1) {
        perror("can not open msg queue\n");
        exit(1);
    }
    printf("MQ1 opened, mq id = %d\n", (int) mq);
    mq_getattr(mq, &mq_attr);
    printf("MQ1 maximum msgsize = %d\n", (int) mq_attr.mq_msgsize);
    
    //MQ2: Consumer to Producer -- initialize
    
    struct mq_attr mq_attr_2;
    mq2 = mq_open(MQ2, O_RDWR);
    if(mq2 == -1){printf("Can not oppen MQ2\n"); return -2;}
    printf("MQ2 opened MQ2 id = %d\n", (int)mq2);
    mq_getattr(mq2, &mq_attr_2);
    printf("MQ2 maximum msgsize = %d\n", (int)mq_attr_2.mq_msgsize);
    printf("\n");
    printf("\n");
    
//Define a length for the buffer (used in client_T)
    bufferlen = mq_attr.mq_msgsize;
    
//SPLIT THE FILES AND PUT TO THREADS
    char *fname = "deneme"; // We need to read this as fname
    splitFile(fname, M, fname);//M is num of client threads
    

//Create and call client_T() to send the first inputs to server
     pthread_t t[M+1];
     pthread_mutex_init(&cliLock, NULL);
     pthread_cond_init(&cliCond, NULL);
     for(int i=0; i<M+1; i++){
        //Get inputfile
        char* num = (char*)malloc(bufferlen);
        char* res = (char*)malloc(bufferlen);
        sprintf(num, "%d", i+1);
        strcpy(res, fname);
        strcat(res, num);
        strcat(res, ".txt");
     
        
        //Each thread has its own arg_mq but all point to same MQ which is what we want
        
     	struct arg* argp = malloc(sizeof(struct arg));
     	argp->arg_mq = mq;//THIS IS FIXED IN EACH THREAD
     	argp->arg_mq2 = mq2;//THIS IS FIXED IN EACH THREAD
        argp->a = malloc(sizeof(int));//Each thread has its own a and all point to somewhere else which is what we want
        *(argp->a) = i;
        if(i == M){//call S_FE as last thread (workers will wait on condition anyways)
        	if(pthread_create(&t[i], NULL, &C_FE, argp)){printf("Error on thread creation\n"); return -1;}
        }else{
        	FILE *file = fopen(res, "r");
        	argp->file = file;
        	if(pthread_create(&t[i], NULL, &client_T, argp)){printf("Error on thread creation\n"); return -1;}
        	printf("CLIENT_THREAD\n");
        }
       	
     }
     
     //Join client_T()
     for(int i=0;i<M+1;i++)
		if(pthread_join(t[i], NULL)){printf("ERROR: Thread Join: %d\n", i); return 2;}
    
    return 0;
}//End of main...


//FUNTION IMPLEMENTATIONS
void* C_FE()
{
	//================================================
        //RECIEVE UPDATED MESSAGE VIA MQ2:
        //Message comes from worker_T() via MQ2
        //Always try to catch/receive message in a loop
        //Signal client_T() upon successfull response
        //================================================
        
        printf("In cli\n");
        while(1)
        {
        	char* bufferp2 = (char *) malloc(bufferlen);
        	if(mq_receive(mq2, bufferp2, bufferlen, NULL) == -1){printf("ERROR: MQ2 Receive Failed\n");}
        	pthread_mutex_lock(&cliLock);
        	struct item* itemp2 = (struct item*)bufferp2;
       		printf("After receiving id = %d\n", itemp2->id);
        	printf("\n");
        	pthread_mutex_unlock(&cliLock);
        	pthread_cond_signal(&cliCond);
       
        	
        }
        //BURAYA MQ2 RECEİVELEME EKLE
        //SONRA SYNC
        
	
}

//================================================
//SEND MESSAGE VIA MQ1:
//client_T() will do this
//After creating-initializing MQ's -- this is how our program starts
//client_T() is ALWAYS --> either working or waiting on signal from C_FE()
//work: read request form input file - create request message - sen to MQ1
//The first time client_T() works condition must be satisfied so our program can start (unlike worker_T())
//Message is sent to S_FE() in serverk.c via MQ1
//================================================
void* client_T(void* argp)
{

   pthread_mutex_lock(&cliLock);
   pthread_cond_init(&cliCond, NULL);
   struct item* request = malloc(sizeof(struct item));
   struct arg* p = argp;
   char* bufferp = (char *) malloc(bufferlen);
   int i = *(p->a);
   mqd_t mq = p->arg_mq;
   mqd_t mq2 = p->arg_mq2;
   //BURDA P->FILE'DAN OKU STRUCTA ÇEVIR ONU BUFFERP'DEN MQYA AT

    char * line = NULL;
    char * type = malloc(sizeof(bufferlen));
    //char * value = malloc(sizeof(bufferlen));
    size_t len = 0;
    ssize_t read;
    int id;

    if (p->file == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, p->file)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
        len = strlen(line);
        strncpy(type,line,3);
        
        if(len >= 8){
          char value[5];
          int i,j;
          for(i = 4,j =0; i<=7;i++,j++ ){
             value[j] = line[i];          
          }
          value[j] = '\0';
          id = atoi(value);
          //printf("%s%d while \n", type, id);
        }
        
        if(len >= 10){ //start 9, end 15
          char strval[8];
          int i,j;
          
          for(i = 8,j =0; i<=15;i++,j++ ){
             strval[j] = line[i];          
          }
          strval[j] = '\0';
          request->value = strval;//Only PUT has a value
          	
        }else{
        	request->value = NULL;
        }
        
       
        request->id = id; 
	request->request_type = type;
          
        
        struct item* itemp = (struct item *) bufferp;
   	i = 1;
        itemp->id = request->id; 
 
        itemp->value = request->value; 
   	itemp->request_type = request->request_type; 
        
      
	  //...code here: Wait on condition: Condition initially TRUE

          int n;
          n = mq_send(mq, bufferp, sizeof(struct item), 0);
          if (n == -1) {
            	perror("mq_send failed\n");
            	exit(1);
	   }
          printf("Send item id = %d\n", itemp->id);
          //sleep(2);
   	
   	  
    }//end of while
    free(bufferp);
    
   
   pthread_mutex_unlock(&cliLock);
   pthread_cond_destroy(&cliCond);
}//end of cli_T

//EXPECTATION: same code as before but 0, 10, 20, 30... inputs are sent and revieved back as 1, 11, 21, 31... non sequantial

/* PREVIOUS CODE
    i  = 0;
    while (1) {
    	//================================================
	//SEND MESSAGE VIA MQ1:
	//client_T() will do this
	//After creating-initializing MQ's -- this is how our program starts
	//client_T() is ALWAYS --> either working or waiting signal from C_FE()
	//The first time client_T() works condition must be satisfied so our program can start (unlike worker_T())
	//Message is sent to S_FE() in serverk.c via MQ1
	//================================================
	itemp = (struct item *) bufferp;
        itemp->id = i*10;
        strcpy(itemp->astr, "this string is sample data\n");
        n = mq_send(mq, bufferp, sizeof(struct item), 0);
        if (n == -1) {
            perror("mq_send failed\n");
            exit(1);
        }
        printf("mq_send success, item size = %d\n",(int) sizeof(struct item));
        printf("item.id   = %d\n", itemp->id);
        printf("item.astr = %s\n", itemp->astr);
        
        //================================================
        //RECIEVE UPDATED MESSAGE VIA MQ2:
        //C_FE() will do this
        //Message comes from worker_T() via MQ2
        //Always try to catch/receive message in a loop
        //Signal client_T() upon successfull response
        //================================================
        sleep(1);//wait for consumer to manipulate data
        if(mq_receive(mq2, bufferp, bufferlen, NULL) == -1){printf("ERROR: MQ2 Receive Failed\n"); return -4;}
        itemp = (struct item*)bufferp;
        printf("After receiving id = %d\n", itemp->id);
        printf("\n");
        i++;
        sleep(1);
        
        
        
        
        
             
        //BURAYI SİL
        char* bufferp2 = (char *) malloc(bufferlen);
        if(mq_receive(mq2, bufferp2, bufferlen, NULL) == -1){printf("ERROR: MQ2 Receive Failed\n"); return -4;}
        struct item* itemp2 = (struct item*)bufferp2;
        printf("After receiving id = %d\n", itemp2->id);
        printf("\n");
        i++;
        
        
        //---
    }
    
    
    char* a = "put 110 abcdefg";
-->
struct item 
 {
 	int id - > 110
 	req del
 	value 
 	}
    
*/

   







