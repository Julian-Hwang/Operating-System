#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char* name = argv[0];
    int A = fork();


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

    else {
        for (int i = 1; i <= 100000; i++) {
            printf("P");
        }
        return 0;
    }
}