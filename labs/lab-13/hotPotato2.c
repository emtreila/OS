#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

    int idx;
    int *potato;
    pthread_mutex_t *mtx;
	pthread_cond_t *cond;
	int *flag;



void *f() {

    data *d = (data*) arg;

    while(1) {

        pthread_mutex_lock(d->mtx);
        // *((*d).potato)
        if(*(d->potato) < 0) {
            pthread_mutex_unlock(d->mtx);
		*(d.flag) = 1;
		pthread_cond_signal(d.cond);
            break;
        }
	if (d.flag == 0){
        int sub = rand() % 91 + 10;
        printf("Thread with id %d has subtracted %d from %d\n", d->idx, sub, *(d->potato));
        *(d->potato) -= sub;
        if(*(d->potato) < 0) {
            printf("Thread with id %d has exploded!\n", d->idx);
            pthread_mutex_unlock(d->mtx);
            break;
        }

        pthread_mutex_unlock(d->mtx);

        int sleep = rand() % 101 + 100;
        usleep(sleep * 1000);
	}
    }

    return NULL;

}

void* function_monitor(){


	while()












	return NULL;
}

int main(int argc, char *argv[]){

    if(argc != 2) {

        perror("Please provide exactly one argument!\n");

        exit(0);
	
    }

    int n = atoi(argv[1]);

    srand(getpid());

    int potato = rand() % 9001 + 1000;

    printf("Main has generated %d\n", potato);

    pthread_t th[n];
    data *args = malloc(sizeof(data) * n);
    pthread_mutex_t mtx;
	pthread_cond_t cond;
	pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mtx, NULL);
	int flag = 0;
    for(int i = 0; i < n; i++) {

        args[i].idx = i + 1;
        args[i].potato = &potato;
        args[i].mtx = &mtx;
        args[i].flag = &flag;
	pthread_create(&th[i], NULL, f, (void *) &args[i]);

    }


	pthread_t monitor;
	pthread_create(&monitor, NULL , function_monitor , NULL)

    for(int i = 0; i < n; i++) {
        pthread_join(th[i], NULL);
    }
	pthread_join(monitor, NULL);
    pthread_mutex_destroy(&mtx);
    free(args);

    return 0;

}
