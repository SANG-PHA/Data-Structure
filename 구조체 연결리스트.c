#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNum{
	int val;
	struct linkedNum *next;
}numlist; // a

int main(void)
{
	numlist list; // b

	list.val = 10;
	list.next = NULL; // c

	numlist *p, *q; // d

	p = (numlist*)malloc(sizeof(numlist)); // e

	(*p).val = 20;
	(*p).next = NULL; // f

	q = (numlist*)malloc(sizeof(numlist)); // g

	q->val = 30;
	q->next = NULL; // h

	p->next = q; // i

	q->next = &list; // j

	//printf("%d\n", p->val); // k

	do
	{
		printf("%d\n", p->val);
		p = p->next;
	}while (p != NULL); // l


	getch();
	return 0;
	
}
