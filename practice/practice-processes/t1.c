#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {
	// send argv[1] from this process to another process through a fifo
	// ensure that the FIFO named "fifo" exists in the same folder as the executable
	// use mkfifo fifo to create the FIFO if missing
	if (argc < 2) {
		printf("One argument needed\n");
		exit(1);
	}
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
    return 0;
}
