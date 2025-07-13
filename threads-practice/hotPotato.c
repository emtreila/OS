// Hot Potato: Write a C program that receives a number N as a command-line
// argument. The main process generates a random integer between 1000 and
// 10000 (we'll call this variable POTATO) and creates N threads and
// assigns them a unique identifier starting at 1. The N threads will
// execute an infinite loop in which they try to subtract a random value
// between 10 and 100 from the POTATO and then sleep for a random amount
// of time between 100 and 200 milliseconds. The first thread that
// causes the POTATO to have a negative value prints a message that
// announces this alongside its given identifier, breaks the loop, and
// terminates. Any thread that observes that the value of the POTATO is
// negative will also break the loop and terminate, but without printing
// a message.

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int POTATO;
pthread_mutex_t mtx;

void* function(void* arg){

	int id = *((int*)arg);
	free(arg);
	while(1){
		pthread_mutex_lock(&mtx);
		if ( POTATO < 0){
			pthread_mutex_unlock(&mtx);
			break;
		}

		int nr = rand() % 101;
		int old = POTATO;
		POTATO = POTATO - nr;
		printf("Thread %d has substracted %d from %d -> %d\n", id, nr,old, POTATO);
		if (POTATO < 0){
			printf("Thread %d finished!\n", id);
			pthread_mutex_unlock(&mtx);
			break;
		}
		pthread_mutex_unlock(&mtx);
		int timeToSleep = rand() % (200 - 100 + 1);
		usleep( timeToSleep * 1000);
	}

	return NULL;
}

int main(int argc, char* argv[]){

	if (argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}

	int N = atoi(argv[1]);

	srand(time(NULL));
	POTATO = rand() % (10000 - 1000 + 1);
	printf("POTATO = %d\n", POTATO);

	pthread_t th[N];
	pthread_mutex_init(&mtx, NULL);
	for (int i = 0; i < N; i++){
		int *index =  malloc(sizeof(int));
		*index = i;
		pthread_create(&th[i], NULL, function, index);
	}

	for (int i = 0; i < N; i++){
		pthread_join(th[i], NULL);
	}
	pthread_mutex_destroy(&mtx);
	return 0;
}
