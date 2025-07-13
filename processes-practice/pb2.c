// 2. Write a C program that creates a linear hierarchy of n processes
// (a parent process creates a child process, which in turn creates a
// child process, and so on).

// Scrieti un program C care creeaza o ierarhie liniara de n procese
// (procesul parinte creeaza un proces fiu, care la randul lui creeaza un
//  proces fiu, samd.)

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){

	if (argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	if (n < 1){
		perror("Invalid n!\n");
		exit(0);
	}

	for (int i = 0; i < n; i++){
		int f = fork();
		if (f == -1){
			perror("Fork error!");
			exit(0);
		}
		else if (f == 0){
			printf("Child process %d - PID: %d - PPID: %d\n", i, getpid(), getppid());
		}
		else{
			printf("Parent %d - Child: %d\n", getpid(), f);
            		wait(0);
			exit(0);
		}
	}
	return 0;
}

