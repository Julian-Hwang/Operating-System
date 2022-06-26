#include <stdio.h>
#include <pthread.h>

int money = 1000;
int lock = 0;

int main(void)
{
	printf("I'm main thread\n");
	pthread_create(&id1, NULL, func1, NULL);
	pthread_create(&id2, NULL, func2, NULL);

	pthread_join(id1, &tret);
	pthread_join(id2, &tret);

	printf("money: %d\n", money);
}

void func1(void) {
	for (i = 0; i < 100; i++) {
		deposit(10);
		withdraw(10);
	}
}

void func2(void) {
	for (i = 0; i < 100; i++) {
		deposit(10);
		withdraw(10);
	}
}

int withdraw(amount) {
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