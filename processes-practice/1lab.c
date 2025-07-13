// Write a C program that receives any number of command-line arguments.
// For each argument, create a child process that attempts to run the
// argument using one of the exec functions. If the exec function call
// fails, the child process sends a message to the parent, obeying the
// template “Unable to run [argument] since it is not a valid command.”,
// where [argument] is the actual value of the argument. The parent will
// read the message from the pipe and display it together with the PID of
// the child process that sent the message. (Note: In the case where the
// child process successfully runs the command with exec, the parent
// does not need to print anything.)

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

	for (int i = 1; i < argc; i++ ){
		int p[2];
		if (pipe(p) < 0){
			perror("Error on pipe!");
		}
		int f = fork();
		if ( f == -1 ) {
			perror("Error on fork!");
		}
		else if (f == 0){
			close(p[0]);
			execlp(argv[i],argv[i],NULL);
			char *message = malloc(sizeof(char)*100);
			sprintf(message,"Unable to run %s since it is not a valid command./n",argv[i]);
			int l = strlen(message);
			write(p[1], message, l);
			close(p[1]);
			free(message);
			exit(0);
		}
		else{

			close(p[1]);
			int len = 0;
			if (read(p[0], &len, sizeof(int)) > 0){
				char *message = malloc(sizeof(char) * (len + 1));
				read(p[0],message,sizeof(char) * len);
				message[len] = 0;
				printf("Child with PID: %d -> %s\n", f, message);
				free(message);
			}
		}

		close(p[0]);
		close(p[1]);
		wait(NULL);
		printf("\n");
	}
	return 0;
}

