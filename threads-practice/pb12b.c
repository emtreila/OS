// 12b. Same as 12a, but calculate the sum of all the elements of the
// matrix using as many threads as there are rows, each thread adds to the
// total the numbers on a row. Use the test matrix to check if the
// program is calculating the total sum correctly. The expected result
// is 1000000. Try with and without mutex.

#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

int **matrix = NULL;
int sum = 0;
int rows, cols;
pthread_mutex_t mtx;

void* function(void* arg){

        int index = *(int*)arg;
	pthread_mutex_lock(&mtx);
        for (int i = 0; i < cols; i++){
                sum = sum + matrix[index][i];
        }
        pthread_mutex_unlock(&mtx);
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
        if (fptr == NULL){                printf("Couldn't open file!\n");
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

        pthread_t th[rows];
        pthread_mutex_init(&mtx, NULL);
        for (int i = 0; i < rows; i++){
                int *index = malloc(sizeof(int));
		*index = i;
		pthread_create(&th[i],NULL, function, index);
        }

        for (int i = 0; i < rows; i++){
                pthread_join(th[i], NULL);
        }


        printf("Sum = %d\n", sum);


        for(int i = 0; i < rows; i++){
                free(matrix[i]);
        }
        free(matrix);
        fclose(fptr);
        return 0;
}
