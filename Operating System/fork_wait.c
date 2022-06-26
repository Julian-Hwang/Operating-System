#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char* name = argv[0];
    int A = fork();

    int status;

    if (A == 0) {
        for (int i = 1; i <= 100000; i++) {
            printf("A");
        }
        return 0;
    }

    int B = fork();
    if (B == 0) {
        for (int i = 1; i <= 100000; i++) {
            printf("B");
        }
        return 0;
    }
    wait(&status);
    wait(&status);
    printf("My children have gone.\n");

    return 0;
}