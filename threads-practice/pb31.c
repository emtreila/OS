// 31. Write a C program that receives a number N as a command-line
// argument. The program creates N threads that will generate random
// numbers between 0 and 111111 (inclusive) until one thread generates a
// number divisible by 1001. The threads will display the generated
// numbers, but the final number that is displayed must be the one that
// is divisible by 1001. No thread will start generating random numbers
// until all threads have been created. Do not use global variables.

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

typedef struct {
	int id;
	int *flag;
	pthread_mutex_t *mtx;
	pthread_barrier_t *barr;
} data;

void* function(void* arg){

	data d = *((data*) arg);
	pthread_barrier_wait(d.barr);
	while(1){
		pthread_mutex_lock(d.mtx);
		int nr = rand() % (111111 - 0 + 1);
		if (*(d.flag) == 0){
			printf("Thread %d -> %d\n", d.id, nr);
			if ( nr % 1001 == 0){
				*(d.flag) = 1;
				break;
			}
		}
		else{
			break;
		}
		pthread_mutex_unlock(d.mtx);
		usleep(100);
	}

	pthread_mutex_unlock(d.mtx);
	return NULL;
}

int main(int argc, char* argv[]){

	if(argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}

	int N = atoi(argv[1]);
	int *flag = malloc(sizeof(int));
	*flag = 0;
	srand(time(NULL));
	data *args = malloc(sizeof(data) * N);
	pthread_t *th = malloc(sizeof(pthread_t) * N);
	pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx,NULL);
	pthread_barrier_t *barr = malloc(sizeof(pthread_barrier_t));
	pthread_barrier_init(barr, NULL, N);

	for (int i = 0; i < N; i++){
		args[i].id = i;
		args[i].mtx = mtx;
		args[i].barr = barr;
		args[i].flag = flag;
		pthread_create(&th[i], NULL, function, &args[i]);
	}

	for (int i = 0; i < N; i++){
		pthread_join(th[i], NULL);
	}
	pthread_barrier_destroy(barr);
    	pthread_mutex_destroy(mtx);
	free(th);
    	free(args);
    	free(barr);
    	free(mtx);
    	free(flag);

	return 0;
}
