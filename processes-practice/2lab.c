// Write a simple one-to-one chat program that communicates via FIFO.
// The program will receive as arguments the names/paths of two FIFOs,
// one for incoming messages and one for outgoing messages. The program
// must create a process that awaits messages on the incoming FIFO and
// displays them as they are received. In a separate process, the
// program will wait for the user to write messages from the keyboard and
// will write them in the outgoing FIFO. Test your implementation with a
// colleague (you may create fifos in /tmp/913/, which can be accessed
// by other people).

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Not enough arguments!\n");
		exit(1);
	}
	int f = fork();
	if (f == -1){
		perror("error on fork!");
	}
	else if (f == 0){
		fd = open(argv[1],O_RDONLY);
		if (fd == -1){
			error("error");
		}
		if ()
	}
	else {

	}
	return 0;
}
