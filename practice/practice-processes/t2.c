#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]) {
	// receive a string through a fifo from another process
	// ensure that the FIFO named "fifo" exists in the same folder as the executable
	// use mkfifo fifo to create the FIFO if missing
    int r_fifo = open("./fifo", O_RDONLY);
	if(-1 == r_fifo) {
		perror("Error opening fifo in read mode");
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
    return 0;
}
