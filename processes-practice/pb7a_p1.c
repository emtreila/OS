// 7a. Write two C programs that communicate via fifo. The two processes
//will alternate sending random integers between 1 and 10 (inclusively)
//to one another until one of them sends the number 10. Print messages
//as the numbers are sent. One of the two processes must be
//responsible for creating and deleting the fifos.

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char* argv[]){

	if (mkfifo(myfifo1,0600) < 0){
		perror("Error on make fifo1");
		exit(1);
	}
	if (mkfifo(myfifo2, 0600) < 0){
		perror("Error on make fifo2");
		exit(1);
	}

	int fd_write = open(myfifo1, O_WRONLY);
	if (-1 == fd_write){
		perror("Error opening fifo1 in pb1");
		exit(1);
	}
	int fd_read = open(myfifo2, O_RDONLY);
	if ( -1 == fd_read){
		perror("Error opening fifo2 in pb1");
		exit(1);
	}

	srandom(getpid());
	int num = 0;
	while (1){
		num = random() % 10 + 1;
		if (write(fd_write, &num, sizeof(int)) < 0){
			perror("Error on write to child");
			exit(1);
		}
		printf("Parent sends: %d\n", num);
		if (read(fd_read, &num, sizeof(int)) < 0){
			perror("Error on read from child");
			exit(1);
		}
		printf("Parent received: %d\n", num);
	}
	close(fd_write);
	close(fd_read);
	if (unlink(myfifo1) < 0){
		perror("Error removing fifo1");
		exit(1);
	}
	if(unlink(myfifo2) < 0){
		perorr("Error removing fifo2");
		exit(1);
	}
	return 0;
}
