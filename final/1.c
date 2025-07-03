#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main(){
	while(wait(NULL) < 0){
		if (fork() == 0){
			printf("%d\n", getpid());
			//sleep(3);
			exit(0);
		}
	}
	return 0;
}

// (P): ...wait(NULL) = -1... fork()... C1 child
// (P) dies, because if (fork()>0) is true for the parenti
// 	(C1): ...wait(NYLL = -1
// 	...
//
//
//
//
// 	INFINIT PROCESE
