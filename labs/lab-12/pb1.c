#include<stdlib.h>
#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<string.h>
int nrLines = 0, nrWords = 0, nrCharacters = 0;
FILE* fptr;
pthread_mutex_t mtx;

void *f(){
	 char line[1024];
	pthread_mutex_lock(&mtx);
	 while(fgets(line,sizeof(line),fptr)!= NULL){
      		nrLines++;
		char *token = strtok(line, " ");
		while (token!=NULL){
			nrWords++;
			nrCharacters += strlen(token);
		}
    	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char* argv[]){

	if (argc < 3){
		printf("Not enough arguments!\n");
		exit(0);
	}
	char* filename = argv[1];
	int n = atoi(argv[2]);

	fptr =  fopen(filename,"r");
	if (fptr == NULL){
		printf("Oh no!Couldn't open the file!\n");
		exit(0);
	}
	else {
		printf("Yaay!File opened!\n");
	}
	pthread_t th[n];
	pthread_mutex_init(&mtx,NULL);
	for (int i=0; i<n; i++){
		pthread_create(&th[i],NULL,f,NULL);
	}

	for (int i = 0; i<n; i++){
		pthread_join(th[i],NULL);
	}
	fclose(fptr);
pthread_mutex_destroy(&mtx);
	printf("%d lines, %d words, %d characters\n", nrLines, nrWords, nrCharacters);
	return 0;
}
