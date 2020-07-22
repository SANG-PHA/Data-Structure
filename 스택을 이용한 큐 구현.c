#include <stdio.h>

#define MAX_SIZE 20
#define TRUE 1
#define FALSE 0

typedef struct stack_type{ //스택 타입 정의 : 배열로 표현
	int stack[MAX_SIZE];
	int top;
}stack_type;
typedef stack_type* stack_type_ptr;

//스택 기본 연산
void init(stack_type_ptr);
void push(stack_type_ptr, int);
int pop(stack_type_ptr*);
int stk_is_empty(stack_type);
int stk_is_full(stack_type);

//큐 기본연산
int queue_is_empty(stack_type_ptr stk1_ptr);
int queue_is_full(stack_type_ptr stk1_ptr);
void enqueue(stack_type_ptr stk1_ptr, int item);
int dequeue(stack_type_ptr stk1_ptr, stack_type_ptr stk2_ptr);

//피보나치 함수
void fib(stack_type_ptr stk1_ptr, stack_type_ptr stk2_ptr);

int main(void) {
	stack_type stk1, stk2; // 스택 선언
	stack_type_ptr stk1_ptr = &stk1, stk2_ptr = &stk2; //스택 포인터 선언

	init(stk1_ptr);
	init(stk2_ptr); //스택 초기화

	//F(0)과 F(1) 큐에 삽입
	enqueue(stk1_ptr, 0);
	enqueue(stk1_ptr, 1);

	//피보나치 함수 F(10)까지 호출
	printf("피보나치수열 : 0 1 ");
	for (int i = 0; i < 9; i++)
		fib(stk1_ptr, stk2_ptr);
		
	getch();
	return 0;
}

void init(stack_type_ptr s_ptr)
{
	s_ptr->top = -1;
}

void push(stack_type_ptr s_ptr, int item)
{
	if (stk_is_full(*s_ptr) == FALSE) {
		s_ptr->top++;
		s_ptr->stack[s_ptr->top] = item;
	}
	else {
		printf("스택이 꽉 차있습니다.");
	}
}

int pop(stack_type_ptr* s_ptr)
{
	if (stk_is_empty(**s_ptr) == FALSE) {
		int returner = ((*s_ptr)->stack[(*s_ptr)->top]);
		(*s_ptr)->top--;
		return returner;
	}
	else {
		printf("스택이 비어있습니다.");
		return 0;
	}
}

int stk_is_empty(stack_type s)
{
	if (s.top < 0)
		return TRUE;
	else return FALSE;
}

int stk_is_full(stack_type s)
{
	if (s.top == MAX_SIZE - 1)
		return TRUE;
	else return FALSE;
}

int queue_is_empty(stack_type_ptr stk1_ptr)
{
	if (stk_is_empty(*stk1_ptr) == TRUE)
		return TRUE;
	else return FALSE;
}

int queue_is_full(stack_type_ptr stk1_ptr)
{
	if (stk_is_full(*stk1_ptr) == TRUE)
		return TRUE;
	else return FALSE;
}

void enqueue(stack_type_ptr stk1_ptr, int item)
{
	if (queue_is_full(stk1_ptr) == FALSE)
		push(stk1_ptr, item);
	else printf("큐가 꽉 차있습니다.");
}

int dequeue(stack_type_ptr stk1_ptr, stack_type_ptr stk2_ptr)
{
	int item;

	if (queue_is_empty(stk1_ptr) == FALSE){

		while (stk_is_empty(*stk1_ptr) == FALSE)
			push(stk2_ptr, pop(&stk1_ptr));
		
		item = pop(&stk2_ptr);

		while (stk_is_empty(*stk2_ptr) == FALSE)
			push(stk1_ptr, pop(&stk2_ptr));

		return item;
	}
	else return NULL;
}

void fib(stack_type_ptr stk1_ptr, stack_type_ptr stk2_ptr)
{
	int Fn_2, Fn_1, Fn; //F(n-2), F(n-1), F(n)을 저장할 변수 선언

	//큐에 저장된 F(n-2), F(n-1)을 가져옴
	Fn_2 = dequeue(stk1_ptr, stk2_ptr);
	Fn_1 = dequeue(stk1_ptr, stk2_ptr);

	Fn = Fn_2 + Fn_1; //F(n) 계산

	printf("%d ", Fn); //계산된 F(n)출력

	//큐에 F(n-1), F(n)을 넣음
	enqueue(stk1_ptr, Fn_1);
	enqueue(stk1_ptr, Fn);
}
