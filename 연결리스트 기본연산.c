#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodeptr;
typedef struct node {
	int data;
	nodeptr link;
}node;

nodeptr create_node();
void insert_node(nodeptr *list, nodeptr prev, nodeptr new);
void add_first(nodeptr *list, nodeptr new);
void display(nodeptr list);
void delete_first(nodeptr *list);

int main(void)
{
	nodeptr list = NULL;
	nodeptr tmp = NULL;

	for (int i = 10; i > 0; i--)
	{
		tmp = create_node();
		tmp->data = i;
		add_first(&list, tmp);
	}
	for (int i = 0; i < 3; i++)
	{
		delete_first(&list);
	}

	display(list);

	free(list);  
	getch();
	return 0;
}

nodeptr create_node()
{
	nodeptr new = (nodeptr)malloc(sizeof(struct node));
	new->data = 0;
	new->link = NULL;
	return new;
}

void insert_node(nodeptr *list, nodeptr prev, nodeptr new)
{
	if (*list == NULL){
		*list = new;
	}
	else if(prev == NULL){
		new->link = *list;
		*list = new;
	}
	else{
		new->link = prev->link;
		prev->link = new;
	}

	
}

void add_first(nodeptr *list, nodeptr new)
{
	return insert_node(list, NULL, new);
}

void display(nodeptr list)
{
	while (list != NULL)
	{
		printf("%d\n", list->data);
		list = list->link;
	}
}

void delete_first(nodeptr *list)
{
	if (*list == NULL)
		printf("리스트가 비어있습니다.");
	else if ((*list)->link == NULL)
		*list = NULL;
	else
		*list = (*list)->link;
	
}
