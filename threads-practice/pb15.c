// 15. Write a program that receives strings of characters as command
// line arguments. For each string the program creates a thread which
// calculates the number of digits, the number of leters and the number
// of special characters (anything other than a letter or digit).
// The main program waits for the threads to terminate and prints the total
// results (total number of digits, letters and special characters across
// all the received command line arguments) and terminates.
// Use efficient synchronization. Do not use global variables

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include <ctype.h>
#include<string.h>
typedef struct{

	int *letters, *digits, *specials;
	pthread_mutex_t *mtxletters, *mtxdigits, *mtxspecials;
	char *str;

} data;

void* function(void* arg){

	data dt = *((data*) arg);
	int l = 0, d = 0, s = 0;
        int i, len = strlen(dt.str);
        for (i = 0; i < len; i++) {
        	if (isalpha(dt.str[i]))
            		l++;
        	else if (isdigit(dt.str[i]))
            		d++;
        	else
            	 	s++;
    	}
	if (l > 0) {
        	pthread_mutex_lock(dt.mtxletters);
        	*(dt.letters) += l;
        	pthread_mutex_unlock(dt.mtxletters);
    	}
    	if (d > 0) {
        	pthread_mutex_lock(dt.mtxdigits);
        	*(dt.digits) += d;
        	pthread_mutex_unlock(dt.mtxdigits);
    	}
    	if (s > 0) {
        	pthread_mutex_lock(dt.mtxspecials);
        	*(dt.specials) += s;
        	pthread_mutex_unlock(dt.mtxspecials);
    	}
    	return NULL;

}

int main(int argc, char *argv[]){

	if (argc < 2){
		printf("Not enough arguments!\n");
		exit(1);
	}

	int letters = 0, digits = 0, specials = 0;
	pthread_mutex_t mtxletters;
	pthread_mutex_t mtxdigits;
	pthread_mutex_t mtxspecials;
	pthread_mutex_init(&mtxletters, NULL);
	pthread_mutex_init(&mtxdigits, NULL);
	pthread_mutex_init(&mtxspecials, NULL);
	pthread_t th[argc-1];
	data *args = malloc(sizeof(data) * (argc-1));
	for (int i = 0; i < argc-1; i++){
		args[i].letters = &letters;
		args[i].digits = &digits;
		args[i].specials = &specials;
		args[i].mtxletters = &mtxletters;
		args[i].mtxdigits = &mtxdigits;
		args[i].mtxspecials = &mtxspecials;
		args[i].str = argv[i+1];

		pthread_create(&th[i], NULL, function, (void*) &args[i]);
	}

	for (int i = 0; i < argc-1; i++){

		pthread_join(th[i],NULL);
	}
	 printf("Total letters: %d\nTotal digits: %d\nTotal special characters: %d\n", letters, digits, specials);

	pthread_mutex_destroy(&mtxletters);
    	pthread_mutex_destroy(&mtxdigits);
    	pthread_mutex_destroy(&mtxspecials);
    	free(args);
	return 0;
}
