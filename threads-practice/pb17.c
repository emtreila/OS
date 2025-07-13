// 17. Write a C program that reads a number N and creates 2
// threads. One of the threads will generate an even number and will
// append it to an array that is passed as a parameter to the
// thread. The other thread will do the same, but using odd numbers.
// Implement a synchronization between the two threads so that they
// alternate in appending numbers to the array, until they reach the
// maximum length N.

#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

int *arr;
pthread_mutex_t mtx;
pthread_cond_t cond;
int N;
int indx = 0;

void* f1(){

	pthread_mutex_lock(&mtx);
	while(indx % 2 != 0){
		pthread_cond_wait(&cond, &mtx);
	}

	while ( indx < N){
		int nr = (random() % 51) * 2;
		arr[indx] = nr;
		indx++;

		printf("T1: ");
		for (int i = 0; i < indx; i++){
			printf("%d ", arr[i]);
		}
		printf("\n");

		pthread_cond_signal(&cond);
		while (indx % 2 != 0 && indx < N){
			pthread_cond_wait(&cond, &mtx);
		}
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	return NULL;
}


void* f2(){

	pthread_mutex_lock(&mtx);
	while(indx % 2 != 1){
		pthread_cond_wait(&cond, &mtx);
	}

	while ( indx < N){
		int nr = (random() % 51) * 2 + 1;
		arr[indx] = nr;
		indx++;

		printf("T2: ");
		for (int i = 0; i < indx; i++){
			printf("%d ", arr[i]);
		}
		printf("\n");

		pthread_cond_signal(&cond);
		while (indx % 2 != 1 && indx < N){
			pthread_cond_wait(&cond, &mtx);
		}
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char *argv[]){

	if (argc < 2){
		printf("not enough");
		exit(1);
	}

	N = atoi(argv[1]);
	srandom(time(NULL));
	pthread_t th[2];
	
	arr = malloc(sizeof(int) * N);
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);


	pthread_create(&th[0], NULL, f1, NULL);
	pthread_create(&th[1], NULL, f2, NULL);


	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);

	pthread_mutex_destroy(&mtx);
	return 0;
}
