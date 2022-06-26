#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 10000
void* child1(void* tid) {
    printf("A");
}

void* child2(void* tid) {
    printf("B");
}

int main() {
    pthread_t threads[MAX];

    for (int i = 1; i <= MAX; i++) {
        pthread_create(&threads[i], NULL, child1, NULL);
        printf("M");
    }

    for (int i = 1; i <= MAX; i++) {
        pthread_create(&threads[i], NULL, child2, NULL);
        printf("M");
    }
    return 0;
}