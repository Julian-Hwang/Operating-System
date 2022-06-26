#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#define MAX 64

void* get_next_command(char buf[]);
int main(int argc, char* argv[])
{
	char buf[MAX];
	while (get_next_command(buf)) {
		int child_pid = fork();
		if (child_pid < 0) {
			perror("error\n");
			return -1;
		}
		else if (child_pid == 0) {
			execlp(buf, buf, NULL);
			exit(0);
		}
		else {
			wait(NULL);
		}
	}
	return 0;
}

void* get_next_command(char buf[])
{
	printf("Shell > ");
	fgets(buf, MAX - 1, stdin);
	buf[strlen(buf) - 1] = '\0';
}