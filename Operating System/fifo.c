#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int num;
	struct node* next;
}NODE;

NODE* head;
NODE* tail;

void init()
{
	head = (NODE*)malloc(sizeof(NODE));
	tail = (NODE*)malloc(sizeof(NODE));

	head->next = tail;
	tail->next = tail;
}

void insert(int num)
{
	NODE* p = malloc(sizeof(NODE));
	NODE* in_head = head;
	NODE* in_node = in_head->next;
	p->num = num;

	if (head->next == tail)
	{
		p->next = tail;
		head->next = p;
	}
	else
	{
		while (in_node != tail)
		{
			in_head = in_head->next;
			in_node = in_head->next;
		}
		in_head->next = p;
		p->next = in_node;
	}
}

void delete()
{
	NODE* in_head = head;
	NODE* in_node = in_head->next;

	if (in_node != tail)
	{
		in_head->next = in_node->next;
		free(in_node);
	}
}

int search(int num)
{
	NODE* p = head->next;
	while (p != tail)
	{
		if (p->num == num)
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int length_list()
{
	int length = 0;
	NODE* p = head->next;
	while (p != tail)
	{
		p = p->next;
		length++;
	}
	return length;
}

int main()
{
	FILE* fp = NULL;
	int i, num, nc = 0;
	int arr[100000];
	int hit = 0;
	int node;

	init();

	printf("1: tr.2c39.txt\n");
	printf("2: tr.db2.txt\n");
	printf("3: tr.sort.txt\n");
	printf("4: r.zipf_20_80.txt\n");
	printf("Input file name's(1,2,3,4 only): ");
	scanf("%d", &i);

	printf("Input Node Number(100, 500, 1000 only) : ");
	scanf("%d", &node);

	switch (i)
	{
	case 1:
		fp = fopen("tr.2c39.txt", "r");
		break;
	case 2:
		fp = fopen("tr.db2.txt", "r");
		break;
	case 3:
		fp = fopen("tr.sort.txt", "r");
		break;
	case 4:
		fp = fopen("tr.zipf_20_80.txt", "r");
		break;
	default:
		printf("Error\n");
		break;
	}

	while (fscanf(fp, "%d", &num) > 0) {
		nc++;

		if (search(num)) {
			hit++;
		}

		else
		{
			while (1)
			{
				if (length_list() < node)
				{
					insert(num);
					break;
				}
				else
				{
					delete();
				}
			}
		}

	}

	fclose(fp);
	printf("Hit rate: %.2f\n", ((double)hit / (double)nc) * (double)100);
	return 0;
}