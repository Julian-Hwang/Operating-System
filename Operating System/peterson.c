#include <stdio.h>
#include <pthread.h>
#define FALSE 0
#define TRUE 1
#define N 2

int money = 1000;
int lock = 0;
int turn;
int interested[N];

void lock_init();

void* func1(void* s);
void* func2(void* s);
int withdraw(int amount);
int deposit(int amount);
int get_balance(void);
void put_balance(int balance);
void enter_region(int process);
void leave_region(int process);

int main(void)
{
    pthread_t threads;

    lock_init();

    //스레드 만들기
    printf("I'm main thread\n");
    pthread_create(&threads, NULL, func1, (void*)0);
    pthread_create(&threads, NULL, func2, (void*)1);
    // 스레드 종료
    pthread_join(threads, NULL);
    pthread_join(threads, NULL);

    printf("money: %d\n", money);
}

void lock_init()
{
    // enter_region하기 위해서 기본 설정을 리셋하는 것이다.
    interested[0] = interested[1] = 0;
    turn = 0;
}
// func1과 func2는 어느 스레드에 들어갈지 알려준다.
void* func1(void* s) {
    int other = (int*)s;

    enter_region(other);

    for (int i = 0; i < 100; i++) {
        deposit(10);
        withdraw(10);
    }

    leave_region(other);
}

void* func2(void* s) {
    int other = (int*)s;
    enter_region(other);

    for (int i = 0; i < 100; i++) {
        deposit(10);
        withdraw(10);
    }
    leave_region(other);
}

int withdraw(int amount) {
    int balance;

    while (lock != 0);
    lock = 1;

    balance = get_balance();
    balance = balance - amount;
    put_balance(balance);

    lock = 0;

    return balance;
}

int deposit(int amount) {
    int balance;

    while (lock != 0);
    lock = 1;

    balance = get_balance();
    balance = balance + amount;
    put_balance(balance);

    lock = 0;

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

void enter_region(int other)
{
    interested[other] = 1; //임계영역에 들어가기 위해 스레드를 표시한다.
    turn = 1 – other; //해당 스레드가 우선순위에 있다고 가정한다.
    while (interested[1 - other] == 1 && turn == 1 - other);
}

void leave_region(int other)
{
    interested[other] = 0; //스레드가 더 이상 임계영역에 들어가지 않는다고 표시하			//는 것이다.
}