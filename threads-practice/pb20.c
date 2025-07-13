// 20. Write a C program that takes as command line arguments 2 numbers:
// N and M. The program will simulate a thread race that have to
// pass through M checkpoints. Through each checkpoint the threads must
// pass one at a time (no 2 threads can be inside the same checkpoint).
// Each thread that enters a checkpoint will wait between 100 and 200
// milliseconds (usleep(100000) makes a thread or process wait for 100
// milliseconds) and will print a message indicating the thread number and
// the checkpoint number, then it will exit the checkpoint. Ensure that
// no thread will try to pass through a checkpoint until all threads
// have been created.

#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

int N, M;
pthread_mutex_t *mtx;
pthread_barrier_t barrier;

void* function(void* arg){

	int id = *((int*)arg);
	free(arg);

	printf("Thread %d waiting...\n", id);
	pthread_barrier_wait(&barrier);
	for (int i = 0; i < M; i++){
		pthread_mutex_lock(&mtx[i]);
		printf("Thread %d at checkpoint %d\n", id, i);
		int sec = rand() % (200-100+1);
		usleep(1000 * sec);
		pthread_mutex_unlock(&mtx[i]);
	}
	printf("Thread %d finished...\n", id);
	return NULL;
}

int main(int argc, char* argv[]){

	if (argc < 3){
		printf("Not enough arguments!");
		exit(1);
	}
	srand(time(NULL));
	N = atoi(argv[1]);
	M = atoi(argv[2]);

	mtx = malloc(sizeof(pthread_mutex_t) * M);
	for (int i = 0; i < M; i++){
		pthread_mutex_init(&mtx[i],NULL);
	}
	pthread_barrier_init(&barrier, NULL, N);
	pthread_t th[N];

	for (int i = 0; i < N; i++){
		int *index = malloc(sizeof(int));
		*index = i;
		pthread_create(&th[i], NULL, function, index);
	}

	for (int i = 0; i < N;i++){
		pthread_join(th[i], NULL);
	}

	for (int i = 0; i < M; i++){
		pthread_mutex_destroy(&mtx[i]);
	}

	return 0;
}
