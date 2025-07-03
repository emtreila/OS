#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    // argv[1] C -> P
	// send argv[1] from the child to the parent
	if (argc < 2) {
		printf("One argument needed\n");
		exit(1);
	}
    int p[2];
    if(-1 == pipe(p)) {
        perror("Error on pipe");
        exit(1);
    }
    int f = fork();
    if (-1 == f) {
        perror("Error on fork");
        exit(1);
    } else if (0 == f) {
        close(p[0]);
        int size = strlen(argv[1]);
        if(-1 == write(p[1], &size, sizeof(int))) {
            perror("Error on write size from child");
        }
        if(-1 == write(p[1], argv[1], size * sizeof(char))) {
            perror("Error on write string from child");
        }
        close(p[1]);
        exit(0);
    } else {
        close(p[1]);
        char *received;
        int size;
        if(-1 == read(p[0], &size, sizeof(int))) {
            perror("Error reading size in parent");
        }
        received = malloc(sizeof(char) * (size + 1));
        if(-1 == read(p[0], received, sizeof(char) * size)) {
            perror("Error reading string in parent");
        }
        received[size] = 0;
        printf("%s\n", received);
        free(received);
        close(p[0]);
        wait(NULL);
    }
    return 0;
}
