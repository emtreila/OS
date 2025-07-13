// 3. Write a C program that creates a child process. Both the parent and
// the child processes will run until they receive a SIGUSR1 signal.
// Implement signal handling such that if the parent receives the SIGUSR1
// signal first, it sends it to the child process as well. If the child
// process receives a SIGUSR1 signal without the parent receiving the
// same signal, it will terminate and then the parent should correctly
// call wait for the child process.


#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<signal.h>
int f;
void child_handler(int sig){
	printf("Child process terminating...\n");
	exit(0);
}

void parent_handler(int sig){
	printf("Parent process terminating...\n");
	kill(f, SIGUSR1);
	wait(0);
	exit(0);
}

void zombie_handler(int sig){
	printf("Parent waiting for child to terminate...\n");
	wait(0);
}

int main(){

	f = fork();
	if (f == -1){
		perror("Fork error!\n");
		exit(1);
	}
	else if (f == 0){
		signal(SIGUSR1, child_handler);
		printf("C - Child PID: %d, Parent PID: %d\n", getpid(), getppid());
		while(1){
			printf("Child working...\n");
			sleep(3);
		}
		exit(0);
	}
	else {
		signal(SIGUSR1, parent_handler);
		signal(SIGCHLD, zombie_handler);
		printf("P - Child PID: %d, Parent PID: %d\n", f, getpid());
		while(1){
			printf("Parent working...\n");
			sleep(2);
		}
	}


	return 0;
}
