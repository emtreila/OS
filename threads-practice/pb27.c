// 27. Write a C program that takes two numbers, N and M, as arguments
// from the command line. The program creates N "generator" threads that
// generate random lowercase letters and append them to a string with 128
// positions. The program will create an additional "printer" thread that
// that waits until all the positions of the string are filled, at which
// point it prints the string and clears it. The N "generator" threads
// must generate a total of M such strings and the "printer"
// thread prints each one as soon as it gets to length 128.

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
int N, M, count = 0;
char str[129];
int lin = 0;
pthread_mutex_t mtx;
pthread_cond_t cond;

void* generator(){


	while(1){
		pthread_mutex_lock(&mtx);
		while (lin  == 128){
			pthread_cond_wait(&cond, &mtx);
		}
		if ( count == M ){

                        pthread_mutex_unlock(&mtx);
                        break;
                }

		char letter = 'a' + (rand() % 26);
		str[lin] = letter;
		lin++;
		if( lin == 128){
			printf("Word %d done generating!\n", count);
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mtx);
			break;
		}
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

void* printer(){

	while(1){
		pthread_mutex_lock(&mtx);
		while(lin < 128){
			pthread_cond_wait(&cond, &mtx);
		}
		str[129] = '\0';
		printf("Word %d : %s\n", count, str);
		lin = 0;
		count++;
		pthread_cond_broadcast(&cond);
		if (count == M){
			pthread_mutex_unlock(&mtx);
			break;
		}
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(int argc, char* argv[]){

	if(argc < 3){
		printf("no!\n");
		exit(1);
	}

	N = atoi(argv[1]);
	M = atoi(argv[2]);
	srand(time(NULL));
	pthread_t th[N+1];
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);

	for (int i = 0; i < N; i++){
		pthread_create(&th[i], NULL, generator, NULL);
	}

	pthread_create(&th[N], NULL, printer, NULL);

	for(int i = 0; i < N; i ++){
		pthread_join(th[i],NULL);
	}
	pthread_join(th[N],NULL);

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);
	return 0;
}
