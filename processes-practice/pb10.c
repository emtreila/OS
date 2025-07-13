// 10. Create two processes A and B. A generates a random number n between
// 50 and 200. If it is even, it sends it to B, if it is odd it sends n+1
// to B. B receives the number and divides it by 2 and sends it back to A
// The process repeats until n is smaller than 5. The processes will print
// the value of n at each step.

#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<sys/wait.h>

int main(){

	int ab[2];
	int ba[2];
	if (pipe(ab) < 0){
		perror("error on pipe");
		exit(1);
	}
	if (pipe(ba) < 0){
		perror("error on pipe");
		exit(1);
	}

	int f = fork();
	if (f == -1){
		printf("Error on fork!\n");
		exit(1);
	}
	else if(f == 0){
		close(ab[1]);
		close(ba[0]);

		int num;
		while (1){
			if (read(ab[0],&num,sizeof(int)) < 0){
				perror("error on read1");
				exit(1);
			}
			printf("Child received number: %d\n", num);
			num = num / 2;
			if (num % 2 == 1){
				num = num + 1;
			}
			printf("Child sending number: %d\n", num);
			if (write(ba[1], &num, sizeof(int)) < 0){
				perror("error on write1");
				exit(1);
			}
			if ( num < 5 ){
				break;
			}
		}
		close(ab[0]);
		close(ba[1]);
		exit(0);
	}
	else{
		close(ab[0]);
		close(ba[1]);

		srandom(getpid());
		int num = random() % 151 + 50;
		printf("Parent generated number: %d\n", num);

		while (num >= 5){

			if (num % 2 == 1){
				num = num + 1;
			}
			printf("Parent sending number: %d\n", num);
			if (write(ab[1], &num, sizeof(int)) < 0){
				perror("error on write2");
				exit(1);
			}

			if (read(ba[0], &num, sizeof(int)) < 0){
				perror("error on read2");
				exit(1);
			}
		}
		wait(0);
		close(ab[1]);
		close(ba[0]);
	}

	return 0;
}
