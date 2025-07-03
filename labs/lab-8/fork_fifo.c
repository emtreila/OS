#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {
    // argv[1] C -> P
	// send argv[1] from the child to the parent through a fifo
	// ensure that the FIFO named "fifo" exists in the same folder as the executable
	// use mkfifo fifo to create the FIFO if missing
	if (argc < 2) {
		printf("One argument needed\n");
		exit(1);
	}
    int f = fork();
    if (-1 == f) {
        perror("Error on fork");
        exit(1);
    } else if (0 == f) {
        int w_fifo = open("./fifo", O_WRONLY);
		if(-1 == w_fifo) {
			perror("Error opening fifo in write mode");
			exit(1);
		}
        int size = strlen(argv[1]);
        if(-1 == write(w_fifo, &size, sizeof(int))) {
            perror("Error on write size from child");
        }
        if(-1 == write(w_fifo, argv[1], size * sizeof(char))) {
            perror("Error on write string from child");
        }
        close(w_fifo);
        exit(0);
    } else {
        int r_fifo = open("./fifo", O_RDONLY);
		if(-1 == r_fifo) {
			perror("Error opening fifo in read mode");
			wait(NULL);
			exit(1);
		}
        char *received;
        int size;
        if(-1 == read(r_fifo, &size, sizeof(int))) {
            perror("Error reading size in parent");
        }
        received = malloc(sizeof(char) * (size + 1));
        if(-1 == read(r_fifo, received, sizeof(char) * size)) {
            perror("Error reading string in parent");
        }
        received[size] = 0;
        printf("%s\n", received);
        free(received);
        close(r_fifo);
        wait(NULL);
    }
    return 0;
}
