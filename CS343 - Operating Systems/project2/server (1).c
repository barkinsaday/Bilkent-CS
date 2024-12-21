#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>

/*
	PROGRESS: 
		  -CMD Argument Parsing is done, works fine (might need to check for wrong args tho)
	          -Can create M many threads with given M as argument

*/

// Define constants and structures as needed
#define MAX_MSG_SIZE 1024
#define MQ_NAME_SIZE 50
#define FILE_NAME_SIZE 100

// Global variables for server configuration
int dcount; // Number of data files
char fname[FILE_NAME_SIZE]; // File name prefix
int M = 5; // Number of worker threads - default: 5
int vsize; // Size of the value
char mqname[MQ_NAME_SIZE]; // Message queue name


// Function prototypes
void parse_arguments(int argc, char *argv[]);
void *worker_thread_function(void *arg);
void *fe_thread_function(void *arg);
void initialize_server();
void cleanup_server();
void* routine(void* arg);//Testing

int main(int argc, char *argv[]) {
    printf("Start Server.c...\n");//DELETE THIS LATER
    
    //CMD Arguments
    //parse_arguments(argc, argv);
    //printf("%d	%d   %d\n", dcount, M, vsize);
    
    // Thread and MQ related structures
    pthread_t t[M];
    pthread_t fe_thread;
    mqd_t mq1, mq2;
    
    initialize_server();

    // Create threads and message queues as required
    for(int i=0; i<M; i++){
    	int* a = malloc(sizeof(int));
    	*a = i;
    	if(pthread_create(&t[i], NULL, &routine, a)){printf("ERROR: Thread Creation: %d\n", i); return 1;}
    }

    // Join threads and clean up before exiting
    for(int i=0; i<M; i++){
    	if(pthread_join(t[i], NULL)){printf("ERROR: Thread Creation: %d\n", i); return 1;}
    }
 
    printf("End Server.c...\n");// DELETE THIS LATER
    return 0;
}

void paarse_arguments(int argc, char *argv[]) {
    // Implement argument parsing
    // ...
}

void initialize_server() {
    // Server initialization logic
    // ...
    printf("Server init function...\n");
}

void cleanup_server() {
    // Server cleanup logic
    // ...
}

void* routine(void* arg){//Testing
	int index  = *((int*) arg);
	printf("In thread i = %d\n", index);
}

// Define other functions as needed
void parse_arguments(int argc, char *argv[]) {
    if (argc != 11) {
        fprintf(stderr, "Usage: %s -d dcount -f fname -t tcount -s vsize -m mqname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-d") == 0) {
            dcount = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            strncpy(fname, argv[i + 1], sizeof(fname) - 1);
            fname[sizeof(fname) - 1] = '\0'; // Ensure null termination
        } else if (strcmp(argv[i], "-t") == 0) {
            M = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-s") == 0) {
            vsize = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            strncpy(mqname, argv[i + 1], sizeof(mqname) - 1);
            mqname[sizeof(mqname) - 1] = '\0'; // Ensure null termination
        } else {
            fprintf(stderr, "Invalid argument: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }
     printf("CHECK ON BETWEEN\n");
    // Add any additional validation if needed
    if (dcount <= 0 || M <= 0 || vsize <= 0) {
        fprintf(stderr, "Invalid configuration values\n");
        exit(EXIT_FAILURE);
    }
}//End of "parse_arguments"
