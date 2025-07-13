// 12a. Write a C program that reads a matrix of integers from a file.
// It then creates as many threads as there are rows in the matrix, each
// thread calculates the sum of the numbers on a row. The main
// process waits for the threads to finish, then prints the sums.

#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

int **matrix = NULL;
int *sums = NULL;
int rows, cols;

void* function(void* arg){

	int index = *(int*)arg;
	int s = 0;
	//printf("%d\n", index);
	for (int i = 0; i < cols; i++){
		s = s + matrix[index][i];
	}
	sums[index] = s;
	free(arg);
	return NULL;
}

int main(int argc, char* argv[]){

	if (argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}
	char *filename = argv[1];
	FILE *fptr = fopen(filename, "r");
	if (fptr == NULL){
		printf("Couldn't open file!\n");
		exit(1);
	}

	fscanf(fptr, "%d %d", &rows, &cols);


	matrix = (int**) malloc(sizeof(int*) * rows);

	if (matrix == NULL){
		perror("matrix error");
	}

	for (int i = 0; i < rows; i++){
		matrix[i] = (int*) malloc(sizeof(int) * cols);
		for (int j = 0; j < cols; j++){
			fscanf(fptr, "%d", &matrix[i][j]);
		}
	}
	sums = (int*) malloc(sizeof(int) * rows);
	pthread_t th[rows];
	for (int i = 0; i < rows; i++){
		int *index = malloc(sizeof(int)); // allocate memory for each index
        	*index = i;
        	pthread_create(&th[i], NULL, function, index);
	}

	for (int i = 0; i < rows; i++){
		pthread_join(th[i], NULL);
	}

	for (int i = 0; i < rows; i++){
		printf("Sum for row %d: %d\n", i, sums[i]);
	}

	for(int i = 0; i < rows; i++){
		free(matrix[i]);
	}
	free(matrix);
	fclose(fptr);
	return 0;
}
