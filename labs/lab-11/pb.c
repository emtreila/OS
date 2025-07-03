#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>


void *do_work(void* arg){

	//ceva
}

int main(){

	int N;
	scanf("%d",&N);
	printf("N is: %d\n", N);
	srand(time(NULL));
	int POTATO = rand() % (10000 - 1000 + 1) + 1000;
	printf("The POTATO is: %d\n", POTATO);

	int *id = NULL;
	pthread_t tid[N];
	for (int  i = 0; i <= N; i++){
		id = malloc(sizeof(int));
		*id = i;

		pthread_create(&tid[i], NULL, do_work, id);
	}

	for (int i=0; i<=N; i++){
		pthread_join(tid[i], NULL);
	}

	return 0;
}
