// Write a C program that creates 2 threads: One thread prints "Ping"
// The other thread prints "Pong"
// The goal is for them to alternate their output exactly like this:
// Ping
// Pong
// Ping
// Pong


#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

int flag = 0;
pthread_mutex_t mtx;
pthread_cond_t cond;
int count = 0;
int N;
void* ping(){

	while(1){
		pthread_mutex_lock(&mtx);
		while (flag == 1){
			pthread_cond_wait(&cond, &mtx);
		}
		if(count == 2*N ){
			pthread_mutex_unlock(&mtx);
			break;
		}
		printf("Ping\n");
		flag = 1;
		count++;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

void* pong(){

        while(1){
                pthread_mutex_lock(&mtx);
                if(count == 2*N ){
                        pthread_mutex_unlock(&mtx);
                        break;
                }
		while (flag == 0){
                        pthread_cond_wait(&cond, &mtx);
                }

                printf("Pong\n");
                flag = 0;
                count++;
                pthread_cond_signal(&cond);
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}

int main(int argc, char* argv[]){

	if (argc < 2){
		printf("no!\n");
		exit(1);
	}

	N = atoi(argv[1]);
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_t th[2];

	pthread_create(&th[0], NULL, ping, NULL);
	pthread_create(&th[1], NULL, pong, NULL);


	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);
	return 0;
}
