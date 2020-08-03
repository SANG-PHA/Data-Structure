#include <stdio.h>

#define MAX_SIZE 20
typedef struct stack_type{ //스택 타입 정의 : 배열로 표현
	int stack[MAX_SIZE];
	int top;
}stack_type;
typedef stack_type* stack_type_ptr;

void init(stack_type_ptr);
void push(stack_type_ptr, int);
int pop(stack_type_ptr*);
int is_empty(stack_type);
int is_full(stack_type);

int main(void) {
	stack_type s; // 스택 선언
	stack_type_ptr s_ptr = &s; //스택 포인터 선언

	init(s_ptr);
	push(s_ptr, 1);
	push(s_ptr, 2);
	push(s_ptr, 3);

	//스택 값 출력
	while (!is_empty(*s_ptr)) {
		printf("%d\n", pop(&s_ptr));
	}

	getch();
	return 0;
}

void init(stack_type_ptr s_ptr)
{
	s_ptr->top = -1;
}

void push(stack_type_ptr s_ptr, int item)
{
	if (is_full(*s_ptr) == 0) {
		s_ptr->top++;
		s_ptr->stack[s_ptr->top] = item;
	}
	else {
		printf("스택이 꽉 차있습니다.");
	}
}

int pop(stack_type_ptr* s_ptr)
{
	if (is_empty(**s_ptr) == 0) {
		int returner = ((*s_ptr)->stack[(*s_ptr)->top]);
		(*s_ptr)->top--;
		return returner;
	}
	else {
		printf("스택이 비어있습니다.");
		return 0;
	}
}

int is_empty(stack_type s)
{
	if (s.top < 0)
		return 1;
	else return 0;
}

int is_full(stack_type s)
{
	if (s.top == MAX_SIZE-1)
		return 1;
	else return 0;
}
