#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct node node;
typedef node* nodeptr;
typedef struct node {
	element data;
	nodeptr link;
}node;

//큐 타입 정의 : 연결리스트로 표현
typedef struct queue_type {
	nodeptr front;
	nodeptr rear;
}queue_type;
typedef queue_type* queue_type_ptr;

//큐 타입 연산 함수
void init(queue_type_ptr);
int is_empty(queue_type);
void enqueue(queue_type_ptr, element);
element dequeue(queue_type_ptr);
void display(queue_type_ptr);


int main(void)
{
	queue_type q;
	queue_type_ptr q_ptr = &q;

	init(q_ptr);
	enqueue(q_ptr, 1);
	enqueue(q_ptr, 2);

	dequeue(q_ptr);

	enqueue(q_ptr, 3);
	enqueue(q_ptr, 4);

	dequeue(q_ptr);

	enqueue(q_ptr, 5);
	enqueue(q_ptr, 6);

	display(q_ptr);

	getch();
	return 0;
}

void init(queue_type_ptr q_ptr)
{
	q_ptr->front = NULL;
	q_ptr->rear = NULL;
}

int is_empty(queue_type q)
{
	if (q.front == NULL && q.rear == NULL)
		return TRUE;
	else
		return FALSE;
}

void enqueue(queue_type_ptr q_ptr, element item)
{
	//노드 생성
	nodeptr n_ptr = (node*)malloc(sizeof(node));

	// 노드 초기화
	n_ptr->data = item;
	n_ptr->link = NULL;

	if (is_empty(*q_ptr) == TRUE) { //큐가 비어있을 때
		q_ptr->front = n_ptr;
		q_ptr->rear = n_ptr;
	}
	else {
		q_ptr->rear->link = n_ptr;
		q_ptr->rear = n_ptr;
	}
}

element dequeue(queue_type_ptr q_ptr)
{
	int item; // 반환할 값 변수 선언

	//노드 포인터 생성
	nodeptr n_ptr;

	//노드 포인터 초기화
	n_ptr = q_ptr->front;

	if (is_empty(*q_ptr) == TRUE) { //큐가 비어있을 때
		printf("큐가 비어있습니다.");
		return 0;
	}
	else if (q_ptr->front->link == NULL) { //큐에 한 개의 노드만 가지고 있을 때
		item = q_ptr->front->data;
		q_ptr->front = NULL;
		q_ptr->rear = NULL;
	}
	else { //그 외
		item = q_ptr->front->data;
		q_ptr->front = q_ptr->front->link;
	}

	free(n_ptr);
	return item;
}

void display(queue_type_ptr q_ptr)
{
	if (is_empty(*q_ptr) == TRUE)
		printf("큐가 비어있어 값을 출력할 수 없습니다.");
	else {
		nodeptr p = q_ptr->front;
		printf("큐의 내용 : ");

		do {
			printf("%d ", p->data);
			p = p->link;
		} while (p != NULL);
	}
}
