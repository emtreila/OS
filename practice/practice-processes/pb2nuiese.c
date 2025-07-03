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
void generate(int n, int *pids){
	if (n <= 0){
		return;
	}

	int f = fork();
	if (f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if (f == 0){
		generate(n-1, pids);
		exit(0);
	}
	pids[n-1] = f;
	wait(NULL);
}

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

	int *pids = malloc(sizeof(int) * n);
	pids[n-1] = getpid();
	generate(n-1, pids);
	printf("Parent PID: %d\n", getpid());
	for (int i = n-1; i > 0; i--){
		printf("Child PID: %d, -> parent PID = %d\n", pids[i-1], pids[i]);
	}

	for(int i = 0; i< n; i++){
		printf("%d ", pids[i]);
	}

	return 0;
}

