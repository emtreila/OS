#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    if (argc < 2) {
	printf("not enough!\n");
	exit(0);
    }
    execvp(argv[1], &argv[1]);
    perror("execvp failed");
    return 1;
}
