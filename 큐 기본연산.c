#include <stdio.h>

#define MAX_QUEUE_SIZE 5
#define TRUE 1
#define FALSE 0

//큐 타입 정의 : 배열로 표현
typedef int element;
typedef struct queue_type {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}queue_type;
typedef queue_type* queue_type_ptr;

//큐 타입 연산 함수
void init(queue_type_ptr);
int is_empty(queue_type);
int is_full(queue_type);
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
	q_ptr->front = 0;
	q_ptr->rear = 0;
}

int is_full(queue_type q)
{
	if (q.front == (q.rear + 1) % MAX_QUEUE_SIZE)
		return TRUE;
	else
		return FALSE;
}

int is_empty(queue_type q)
{
	if (q.front == q.rear)
		return TRUE;
	else 
		return FALSE;
}

void enqueue(queue_type_ptr q, element item)
{
	if (is_full(*q) == TRUE) //큐가 꽉 차있을때
		printf("큐가 꽉 차있습니다.");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //원형 구조를 구현하기 위해 인덱스 번호를 mod연산을 사용하여 입력
		q->queue[q->rear] = item;
	}
}

element dequeue(queue_type_ptr q)
{
	if (is_empty(*q) == TRUE)
		printf("큐가 비어있습니다.");
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		int item = q->queue[q->front];
		
		return item;
	}
}

void display(queue_type_ptr q)
{
	if (is_empty(*q) == TRUE)
		printf("큐가 비어있어 값을 출력할 수 없습니다.");
	else {
		int p = (q->front + 1) % MAX_QUEUE_SIZE;
		printf("큐의 내용 : ");

		do {
			printf("%d ", q->queue[p]);
			p = (p + 1) % MAX_QUEUE_SIZE;
		} while (p != (q->rear + 1) % MAX_QUEUE_SIZE);
	}
}
