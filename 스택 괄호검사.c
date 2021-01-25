#include <stdio.h>

#define MAX_SIZE 30
#define TRUE 1
#define FALSE 0

typedef struct stack_type{ //스택 타입 정의 : 배열로 표현
	char stack[MAX_SIZE];
	int top;
}stack_type;
typedef stack_type* stack_type_ptr;

void init(stack_type_ptr);
void push(stack_type_ptr, int);
char pop(stack_type_ptr*);
int is_empty(stack_type);
int is_full(stack_type);
int test_simple_paren(char s[], stack_type_ptr*);

int main(void) {
	char arr[MAX_SIZE] = { "((2+3)*5)+(3-1)/2" };
	int res;
	printf("수식 : %s\n", arr);

	stack_type s; // 스택 선언
	stack_type_ptr s_ptr = &s; //스택 포인터 선언

	init(s_ptr);

	res = test_simple_paren(arr, s_ptr);
	if (res == TRUE)
		printf("parentheses are balanced\n");
	else
		printf("parentheses are NOT balanced\n");

	getch();
	return 0;
}

void init(stack_type_ptr s_ptr)
{
	s_ptr->top = -1;
}

void push(stack_type_ptr s_ptr, char item)
{
	if (is_full(*s_ptr) == 0) {
		s_ptr->top++;
		s_ptr->stack[s_ptr->top] = item;
	}
	else {
		printf("스택이 꽉 차있습니다.");
	}
}

char pop(stack_type_ptr* s_ptr)
{
	if (is_empty(**s_ptr) == 0) {
		char returner = ((*s_ptr)->stack[(*s_ptr)->top]);
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
	if (s.top == MAX_SIZE - 1)
		return 1;
	else return 0;
}

int test_simple_paren(char a[], stack_type_ptr s_ptr)
{
	int i = 0;
	while (a[i] != NULL){
		if (a[i] == '('){
			push(s_ptr, a[i]);
			printf("스택 상태 : ");
			for (int j = 0; j <= s_ptr->top; j++)
				printf("%c", s_ptr->stack[j]);
			printf("\n");
		}
		else if (a[i] == ')'){
			pop(&s_ptr);
			printf("스택 상태 : ");
			for (int j = 0; j <= s_ptr->top; j++)
				printf("%c", s_ptr->stack[j]);
			printf("\n");
		}
		i++;
	}

	if (is_empty(*s_ptr) == 1)
		return TRUE;
	else return FALSE;
}
