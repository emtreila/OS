// 7. Write a C program that creates two child processes. The two child
// processes will alternate sending random integers between 1 and 10
//(inclusively) to one another until one of them sends the number 10.
// Print messages as the numbers are sent.

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>

int main(){

	int c1_to_c2[2];
	int c2_to_c1[2];

	if (pipe(c1_to_c2) < 0){
		perror("Error on first child!\n");
		exit(1);
	}
	if (pipe(c2_to_c1) < 0){
		perror("Error on second child!\n");
		exit(1);
	}

	int f1 = fork();
	if ( f1 == -1 ){
		printf("Error on fork!\n");
		exit(1);
	}
	else if ( f1 == 0 ){

		close(c1_to_c2[0]);
		close(c2_to_c1[1]);

		srand(getpid());
		int num = rand() % 10 + 1;

		printf("Child1 sending: %d\n", num);
		if (write(c1_to_c2[1], &num, sizeof(int)) < 0){
			perror("Error on write for child1!\n");
			exit(1);
		}
		while (1){
			if(read(c2_to_c1[0], &num, sizeof(int)) < 0){
				perror("Error on read from c2 to c1!\n");
				exit(1);
			}
			printf("Child1 received number: %d\n", num);
			if (num == 10){
				printf("DONE!\n");
				break;
			}
			sleep(1);
			num = rand() % 10 + 1;
			printf("Child1 sending number: %d\n", num);
			if(write(c1_to_c2[1], &num, sizeof(int)) < 0){
				perror("Error on write from c1 to c2!\n");
				exit(1);
			}
		}
		close(c1_to_c2[1]);
		close(c2_to_c1[0]);
		exit(0);
	}
	
	int f2 = fork();
	if ( f2 == -1 ){
		printf("Error on fork!\n");
		exit(1);
	}
	else if ( f2 == 0 ){

		close(c1_to_c2[1]);
		close(c2_to_c1[0]);

		srand(getpid());
		int num;

		while (1){
			if(read(c1_to_c2[0], &num, sizeof(int)) < 0){
				perror("Error on read from c1 to c2!\n");
				exit(1);
			}
			printf("Child2 received number: %d\n", num);
			if (num == 10){
				printf("DONE!\n");
				break;
			}
			sleep(1);
			num = rand() % 10 + 1;
			printf("Child2 sending number: %d\n", num);
			if(write(c2_to_c1[1], &num, sizeof(int)) < 0){
				perror("Error on write from c2 to c1!\n");
				exit(1);
			}
		}
		close(c2_to_c1[1]);
		close(c1_to_c2[0]);
		exit(0);
	}

	close(c1_to_c2[0]); close(c1_to_c2[1]);
	close (c2_to_c1[0]); close(c2_to_c1[1]);
	wait(NULL);
	wait(NULL);
	printf("end.\n");
	return 0;
}
