#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define FALSE 0
#define TRUE 1
#define N 100

sem_t mutex;

int money = 1000;
int count = 0;

void func1(void);
void func2(void);
int withdraw(int amount);
int deposit(int amount);
int get_balance(void);
void put_balance(int balance);


int main(void)
{
    sem_init(&mutex, 0, 1);
    pthread_t id1;
    pthread_t id2;

    printf("I'm main thread\n");
    pthread_create(&id1, NULL, func1, NULL);
    pthread_create(&id2, NULL, func2, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("money: %d\n", money);
    sem_destroy(&mutex);
}

void func1(void) {

    for (int i = 0; i < 100; i++) {
        sem_wait(&mutex);
        deposit(10);
        withdraw(10);
        sem_post(&mutex);
    }
}

void func2(void) {
    for (int i = 0; i < 100; i++) {
        sem_wait(&mutex);
        deposit(10);
        withdraw(10);
        sem_post(&mutex);
    }
}

int withdraw(int amount) {
    int balance;

    balance = get_balance();
    balance = balance - amount;
    put_balance(balance);

    return balance;
}

int deposit(int amount) {
    int balance;

    balance = get_balance();
    balance = balance + amount;
    put_balance(balance);

    return balance;
}

int get_balance(void)
{
    return money;
}

void put_balance(int balance)
{
    money = balance;
}