// 18. Create a C program that converts all lowecase letters from the
// command line arguments to uppercase letters and prints the result.
// Use a thread for each given argument.

#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>

void* function( void* arg){

	char *str = (char*)arg;
	int len = strlen(str);
	for (int i = 0; i < len; i++){
		str[i] = toupper(str[i]);
	}
	printf("%s\n", str);
	free(str);
	return NULL;
}

int main(int argc, char* argv[]){

	if(argc < 2){
		printf("not enough!");
		exit(1);
	}

	pthread_t th[argc-1];
	for (int i = 0; i < argc-1; i++){
		char* word = malloc(strlen(argv[i + 1]) + 1);
		strcpy(word, argv[i + 1]);
		pthread_create(&th[i], NULL, function, word);
	}
	for (int i = 0; i < argc-1; i++){
		pthread_join(th[i], NULL);
	}
	return 0;
}
