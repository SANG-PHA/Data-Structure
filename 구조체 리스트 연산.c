#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define TRUE 1
#define FALSE 0

typedef struct {
	int list[MAX];
	int length;
}ArrayListType;

void init(ArrayListType *list);
void add(ArrayListType *list, int pos, int val); //리스트의 pos 인덱스 위치에 val 삽입
void delete_list(ArrayListType *list, int pos); //리스트의 pos 인덱스 위치의 항목을 삭제
void display(ArrayListType list);
int is_full(ArrayListType list);
int is_empty(ArrayListType list);

int main(void)
{
	ArrayListType list;

	init(&list);

	add(&list, 0, 30);
	add(&list, 0, 20);
	add(&list, 0, 10);
	display(list);

	add(&list, 1, 15);
	add(&list, 3, 25);
	display(list);

	add(&list, 0, 1); //배열이 꽉 찼을 때

	delete_list(&list, 0);
	delete_list(&list, 2);
	delete_list(&list, 2);
	display(list);

	delete_list(&list, 0);
	delete_list(&list, 0);
	delete_list(&list, 0); //배열이 비었을 때

	getch();
	return 0;
}

void init(ArrayListType *list)
{
	*list->list = NULL;
	list->length = 0;
}

void add(ArrayListType *list, int pos, int val)
{
	int check = is_full(*list);

	if (check == 1)
	{
		printf("배열이 꽉 찼습니다.\n");
	}
	else {
		if (pos >= 0 && pos <= list->length) {
			for (int i = list->length; i > pos; i--)
			{
				list->list[i] = list->list[i - 1];
			}
			list->list[pos] = val;
			list->length = list->length + 1;
		}
	}
}

void delete_list(ArrayListType *list, int pos)
{
	int check = is_empty(*list);

	if (check == 1)
	{
		printf("배열이 비었습니다.\n");
	}
	else {
		if (pos >= 0 && pos <= list->length) {
			for (int i = pos; i < list->length; i++)
			{
				list->list[i] = list->list[i + 1];
			}
			list->length = list->length - 1;
		}
	}
}

void display(ArrayListType list)
{
	printf("배열 List 요소 : ");
	for (int i = 0; i < list.length; i++)
	{

		printf("%d ", list.list[i]);
	}
	printf("\nlength : %d\n", list.length);
}

int is_full(ArrayListType list)
{
	if (list.length == MAX)
		return TRUE;
	else FALSE;
}

int is_empty(ArrayListType list)
{
	if (list.length == 0)
		return TRUE;
	else return FALSE;
}
