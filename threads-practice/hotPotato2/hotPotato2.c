#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int POTATO;
int alive;
pthread_mutex_t mtx;
pthread_cond_t cond;
pthread_barrier_t barr;

void* function(void* arg){

        int id = *((int*)arg);
        free(arg);
	pthread_barrier_wait(&barr);

        while(1){
                pthread_mutex_lock(&mtx);
                while ( POTATO < 0){
                        pthread_cond_wait(&cond, &mtx);
                }
		if (alive == 1){
			printf("Thread %d won!!!\n", id);
			pthread_mutex_unlock(&mtx);
			break;
		}
                int nr = rand() % 101;
                int old = POTATO;
                POTATO = POTATO - nr;
               // printf("Thread %d has substracted %d from %d -> %d\n",id, nr, old, POTATO);
                if (POTATO < 0){
                        printf("Thread %d finished!\n", id);
			pthread_cond_signal(&cond);
                        pthread_mutex_unlock(&mtx);
                        break;
                }
                pthread_mutex_unlock(&mtx);
                int timeToSleep = rand() % (200 - 100 + 1);
                usleep( timeToSleep * 1000);
        }
 	return NULL;
}

void* monitor(){
	pthread_barrier_wait(&barr);
	while(1){
		pthread_mutex_lock(&mtx);
		while( 	POTATO >= 0){
			pthread_cond_wait(&cond, &mtx);
		}

		POTATO = rand() % (10000 - 1000 + 1);
		alive--;
		printf("Monitor generated %d. %d threads remaining.\n", POTATO, alive);
		pthread_cond_broadcast(&cond);

		if (alive == 1){
			pthread_mutex_unlock(&mtx);
			break;
		}
		pthread_mutex_unlock(&mtx);

	}
	return NULL;
}

int main(int argc, char* argv[]){

        if (argc < 2){
                printf("Not enough arguments!\n");
                exit(1);
        }

        int N = atoi(argv[1]);
	alive = N;
        srand(time(NULL));
        POTATO = rand() % (10000 - 1000 + 1);
        printf("POTATO = %d\n", POTATO);

        pthread_t th[N+1];
        pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_barrier_init(&barr, NULL, N+1);
        for (int i = 0; i < N; i++){
                int *index =  malloc(sizeof(int));
                *index = i;
                pthread_create(&th[i], NULL, function, index);
        }

	pthread_create(&th[N], NULL, monitor, NULL);

        for (int i = 0; i <= N; i++){
                pthread_join(th[i], NULL);
        }
        pthread_mutex_destroy(&mtx);
        pthread_cond_destroy(&cond);
	pthread_barrier_destroy(&barr);
	return 0;
}
