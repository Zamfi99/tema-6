#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/errno.h>

void *strrev(void *string) {
	int counter;
	char *old_string = (char *)string;
	char *rev_string = malloc(strlen(string));

	for (counter=strlen(old_string)-1; counter >= 0; counter--) {
		rev_string[strlen(old_string) - 1 - counter] = old_string[counter];
	}
	return rev_string;
}

int main(int argc, char **argv) {
	pthread_t thread;
	if (pthread_create(&thread, NULL, strrev, argv[1])) {
		perror(NULL);
		return errno;
	}

	char *rev_string;
	if (pthread_join(thread, (void *)&rev_string)) {
		perror(NULL);
		return errno;
	} else {
		printf("%s\n", rev_string);
	}

	return 0;
}
