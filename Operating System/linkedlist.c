#include<stdio.h>
#include<stdlib.h>

struct node* insert_front(struct node* head, int block_number);
struct node* insert_rear(struct node* head, int block_number);
struct node* search(struct node* head, int block_number);
struct node* delete(struct node* head, int block_number);
void print_list(struct node* head);

struct node {
	int block_number;
	struct node* next;
};

int main(void)
{
	struct node* list = NULL;
	list = insert_front(list, 10);
	list = insert_rear(list, 20);
	list = insert_front(list, 30);
	list = insert_rear(list, 40);

	list = delete(list, 30);

	print_list(list);

	return 0;
}

struct node* insert_front(struct node* head, int block_number)
{
	struct node* p = malloc(sizeof(struct node));
	p->block_number = block_number;
	p->next = head;
	head = p;
	return head;
}

struct node* insert_rear(struct node* head, int block_number)
{
	struct node* p = malloc(sizeof(struct node));
	p->block_number = block_number;
	p->next = NULL;

	if (head == NULL) {
		head = p;
	}
	else {
		struct node* q = head;
		while (q->next != NULL) {
			q = q->next;
		}
		q->next = p;
	}
	return head;
}

struct node* search(struct node* head, int block_number)
{
	struct node* p = head;
	if (p->block_number == NULL) {
		return NULL;
	}
	while (p->next != NULL) {
		if (p->block_number = block_number) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}

struct node* delete(struct node* head, int block_number)
{
	struct node* p = head;
	if (head == NULL) {
		return head;
	}
	else if (head->block_number == block_number)
	{
		head = head->next;
		free(p);
		return head;
	}
	else
	{
		while (p->next != NULL)
		{
			if (p->next->block_number == block_number)
			{
				p->next = p->next->next;
				free(p->next);
				return head;
			}
			p = p->next;
		}
	}
}

void print_list(struct node* head)
{
	struct node* p = head;
	while (p != NULL) {
		printf("--> %d ", p->block_number);
		p = p->next;
	}
	printf("\n");
}