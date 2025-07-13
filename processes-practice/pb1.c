// 1. Write a C program that creates n child processes. Each child
// process will print its PID and its parent PID. The parent process will
// print its PID and the PID of each of the child processes.

// Scrieti un program C care creeaza n procese fiu. Fiecare proces fiu va
// afisa propriul PID si PID-ul procesului parinte, iar procesul parinte
// va afisa propriul PID si PID-urile tuturor proceselor sale fiu.

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main(int argc, char *argv[]){

	if (argc < 2){
		printf("At least 1 argument needed!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	if (n <= 0){
		perror("Invalid n!");
		exit(1);
	}
	int *child_pid;
	child_pid = malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++){
		int f = fork();
		if (f == -1){
			perror("Error on fork!\n");
			exit(1);
		}
		else if(f == 0){
			printf("Child process: child PID=%d, parent PID=%d\n", getpid(), getppid());
			exit(0);
		}
		else {
			child_pid[i] = f;
		}
	}
	for(int i = 0; i < n; i++){
		wait(NULL);
	}
	printf("Parent process: parent PID=%d \n", getpid());
	printf("Children's PIDS:");
	for (int i = 0; i < n; i++){
		printf(" %d ",child_pid[i]);
	}
	printf("\n");
	return 0;
}
