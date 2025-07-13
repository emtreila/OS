// 16.Write a C program that receives integers as command line argument.
// The program will keep a frequency vector for all digits. The program
// will create a thread for each argument that counts the number of
// occurences of each digit and adds the result to the frequency vector.
// Use efficient synchronization.

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include<stdio.h>

int frq[10];
pthread_mutex_t mtx;

void* function (void* arg){
	int nr = *((int*)arg);
	free(arg);
	pthread_mutex_lock(&mtx);
	while(nr != 0){
		frq[nr%10]++;
		nr = nr/10;
	}
	pthread_mutex_unlock(&mtx);

	return NULL;
}
int main(int argc, char *argv[]){

	if (argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}


	pthread_mutex_init(&mtx, NULL);
	pthread_t th[argc - 1];
	for (int i = 0; i < argc - 1; i++){
		int *number = malloc(sizeof(int));
    		*number = atoi(argv[i + 1]);
    		pthread_create(&th[i], NULL, function, number);
	}

	for (int i = 0; i < argc - 1; i++){
		pthread_join(th[i], NULL);
	}

	for (int i = 0; i < 10; i++) {
		printf("Digit %d : %d times\n", i, frq[i]);
	}

	pthread_mutex_destroy(&mtx);
	return 0;
}
