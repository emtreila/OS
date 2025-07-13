// 6. Create a C program that generates N random integers (N given at
//the command line). It then creates a child, sends the numbers via pipe.
// The child calculates the average and sends the result back.

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<sys/wait.h>
int main(int argc, char *argv[]){

	if(argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	if (n <= 0){
		printf("Please give a positive integer!\n");
		exit(1);
	}

	int pipe_parent_to_child[2];
	int pipe_child_to_parent[2];
	if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1){
		perror("Error on pipe!\n");
		exit(1);
	}

	int f = fork();
	if ( f == -1 ){
		perror("Error on fork!\n");
		exit(1);
	}
	else if ( f == 0 ){
		close(pipe_child_to_parent[0]);
		close(pipe_parent_to_child[1]);

		int *numbers = malloc(sizeof(int) * n);
		if (!numbers){
			perror("Error on malloc!\n");
			exit(1);
		}

		if (read(pipe_parent_to_child[0], numbers, n * sizeof(int)) < 0){
			perror("Error on read from parent!\n");
			close(pipe_child_to_parent[1]);
			close(pipe_parent_to_child[0]);
			exit(0);
		}

		int sum;
		for (int i = 0; i < n; i++) {
			sum = sum + numbers[i];
		}
		double average = sum / n;

		if (write(pipe_child_to_parent[1], &average, sizeof(average)) < 0){
			perror("Error on write from child!\n");
			free(numbers);
			exit(0);
		}

		printf("Child computed average: %.2f\n", average);

		free(numbers);
		close(pipe_parent_to_child[0]);
		close(pipe_child_to_parent[1]);
		exit(0);
	}
	else {

		close(pipe_child_to_parent[1]);
		close(pipe_parent_to_child[0]);

		int *numbers = malloc(n * sizeof(int));
		if (!numbers){
			perror("Error on malloc!\n");
			exit(1);
		}

		srand(time(NULL));
		printf("Parent: Generated numbers: ");
		for (int i = 0; i< n; i++){
			numbers[i] = rand() % 100;
			printf("%d ", numbers[i]);
		}
		printf("\n");

		if (write(pipe_parent_to_child[1], numbers, n * sizeof(int)) < 0){
			perror("Error on write parent to child!\n");
			free(numbers);
			exit(1);
		}

		double average;
		if (read(pipe_child_to_parent[0], &average, sizeof(average)) < 0){
			perror("Error on read from child to parent!\n");
			free(numbers);
			exit(1);
		}

		printf("Parent: Received average from child: %.2f\n", average);
		free(numbers);
		close(pipe_parent_to_child[0]);
		close(pipe_child_to_parent[1]);
		wait(NULL);
	}
	return 0;
}

