// 4. Write a C program that runs a bash command (potentially with
// arguments) received as a command line argument and times its execution.

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/time.h>
int main(int argc, char* argv[]){
	struct timeval tv1, tv2;
	if (argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}
	int p[2];
	if (pipe(p) == -1){
		perror("Error on pipe!\n");
	}
	gettimeofday(&tv1, NULL);
	int f = fork();

	if ( f == -1 ){
		perror("Error on fork!\n");
	}
	else if ( f == 0 ){
		printf("Child running the command...\n");
		if (execlp(argv[1],argv[1],NULL) == -1){
			perror("Error running the given comand!\n");
			exit(1);
		}
	}
	else {
		wait(NULL);
		gettimeofday(&tv2, NULL);
		printf("Total time = %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
		printf("Child finished...\n");
	}

	return 0;
}
