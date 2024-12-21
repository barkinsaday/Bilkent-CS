#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int M = 8; // Num of threads


void* routine(void* arg)
{
	int index = *((int*)arg);
	printf("In thread: %d, will sleep 1 sec\n", index);
}

void* fe()
{
	while(1){
		printf("FE Thread is working will: sleep 1 sec\n");
		sleep(1);
	}
}

int main()
{
	printf("Begin...\n");
	
	//Init Threads
	pthread_t t[M];
	
	//Create and Run Threads
	for(int i=0;i<M;i++){
		int* a = malloc(sizeof(int));
		*a = i;
		if(i == 0){
			pthread_create(&t[i], NULL, &fe, NULL);
		}else{
			if(pthread_create(&t[i], NULL, &routine, a)){printf("ERROR: Thread Creation: %d\n", i); return 1;}
		}
	}
		
	//Join Threads
	for(int i=0;i<M;i++)
		if(pthread_join(t[i], NULL)){printf("ERROR: Thread Join: %d\n", i); return 2;}
	
	printf("End...\n");
	return 0;
}
