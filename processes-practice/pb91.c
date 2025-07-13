// 8. Write 2 C programs, A and B. A receives however many command line
// arguments and sends them to process B. Process B converts all
// lowercase letters from the received arguments to uppercase arguments
// and sends the results back to A. A reads the results, concatenates
// them and prints.

#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>


char *a2b = "a2b_fifo";
char *b2a = "b2a_fifo";
int main(int argc, char* argv[]){

	//make_fifo_if_not_exists(a2b);
	//make_fifo_if_not_exists(b2a);
	int ab = open(a2b, O_WRONLY);
	if ( ab < 0 ){
		perror("error on file descriptor");
		exit(1);
	}

	char msg[1024] = {};
	for (int i = 1; i < argc; i++){
		strcat(msg,argv[i]);
	}
	strcat(msg," ");

	if (0>write(ab, msg, strlen(msg))){
		perror("error on write to b");
		exit(1);
	}
	close(ab);

	int ba = open(b2a, O_RDONLY);
	if ( ba < 0 ){
		perror("error on b2a");
		exit(1);
	}

	char result[1024];
	int n = read(ba, result, sizeof(result) - 1);
	if (n > 0){
		result[n] = '\0';
		printf("result is: %s\n", result);
	}
	close(ba);
	return 0;
}
