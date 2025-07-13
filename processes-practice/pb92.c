#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>
#include<ctype.h>

char *a2b = "a2b_fifo";
char *b2a = "b2a_fifo";
int main(){

	char buf[1024];
	while(1){

		int ab = open(a2b, O_RDONLY);
		if (ab < 0){
			perror("error on ab2");
		}

		int n = read(ab, buf, sizeof(buf));
		close(ab);

		if (n > 0){
			int ba = open(b2a,O_WRONLY);
			if (ba < 0){
				perror("error on ba2");
			}
			for (int i = 0; i < n; i++){
				if (islower(buf[i])){
					buf[i] = toupper(buf[i]);
				}
			}
			write(ba,buf,n);
			close(ba);
		}
	}


	return 0;
}
