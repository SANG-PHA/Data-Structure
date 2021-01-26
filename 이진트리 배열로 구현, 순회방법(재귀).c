#include <stdio.h>

int T[32] = { 0,1,2,3,4,5,0,6,0,0,7,0,0,0,0,0 };

void preorder(int T[], int root);
void inorder(int T[], int root);
void postorder(int T[], int root);

int main(void)
{
	printf("전위 순서 : ");
	preorder(T, 1);
	printf("\n중위 순서 : ");
	inorder(T, 1);
	printf("\n후위 순서 : ");
	postorder(T, 1);

	getch();
	return 0;
}

void preorder(int T[], int root)
{
	if (T != NULL) {
		if (T[root] != 0) { //루트 노드 확인
			printf("%d ", T[root]);
			preorder(T, root * 2);
			preorder(T, root * 2 + 1);
		}
	}
}

void inorder(int T[], int root)
{
	if (T != NULL) {
		if (T[root] != 0) {
			inorder(T, root * 2);
			printf("%d ", T[root]);
			inorder(T, root * 2 + 1);
		}
	}
}

void postorder(int T[], int root)
{
	if (T != NULL) {
		if (T[root] != 0) {
			postorder(T, root * 2);
			postorder(T, root * 2 + 1);
			printf("%d ", T[root]);
		}
	}
}
