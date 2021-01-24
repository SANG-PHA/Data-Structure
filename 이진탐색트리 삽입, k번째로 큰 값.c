#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodeptr;
typedef struct node {
	int data;
	nodeptr left, right;
}node;

nodeptr insert_node(nodeptr T, int key);
nodeptr cons_bst(nodeptr T, int a[], int n);
void sort(nodeptr T);
void kth_largest(nodeptr T, int k);

int main(void)
{
	nodeptr T = NULL;
	int a[10] = { 5,3,7,2,4,6,9,1,8,10 };

	T = cons_bst(T, a, 10);
	sort(T);
	kth_largest(T, 5);

	getch();
	return 0;
}

nodeptr insert_node(nodeptr T, int key)
{
	nodeptr p = NULL, q = NULL;
	p = T;

	//탐색
	while (p != NULL) { 
		if (p->data == key)
			return;
		q = p;
		if (p->data < key)
			p = p->right;
		else p = p->left;
	}

	//삽입할 노드 생성
	nodeptr new = (nodeptr)malloc(sizeof(node));
	new->data = key;
	new->left = NULL;
	new->right = NULL;

	//노드 삽입
	if (T == NULL)
		T = new;
	else if (q->data < key)
		q->right = new;
	else q->left = new;

	return T;
}

nodeptr cons_bst(nodeptr T, int a[], int n)
{
	for (int i = 0; i < n; i++)
		T = insert_node(T, a[i]);

	return T;
}

void sort(nodeptr T)
{
	if (T != NULL) {
		sort(T->left);
		printf("%d ", T->data);
		sort(T->right);
	}

}

void kth_largest(nodeptr T, int k)
{
	static int n = 5;

	if (T != NULL) {
		kth_largest(T->right, n);
		n = n - 1;
		if (n == 0)
			printf("\n%d ", T->data);
		kth_largest(T->left, n);
	}
}
