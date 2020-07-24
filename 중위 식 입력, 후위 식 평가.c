#include <stdio.h>

#define LINE_SIZE 100


typedef struct stack_type { //스택 타입 정의 : 배열로 표현
	char stack[LINE_SIZE];
	int top;
}stack_type;
typedef stack_type* stack_type_ptr;

//스택 타입 연산 함수
void init(stack_type_ptr);
void push(stack_type_ptr, char item);
char pop(stack_type_ptr*);
int is_empty(stack_type);
int is_full(stack_type);
char peek(stack_type);

//연산자 우선순위 반환 함수
int PIS(char token);
int PIE(char token);

int menu();
void get_exp(char exp[]);
void postfix(char exp[], char posExp[], stack_type_ptr s_ptr);
int eval(char postExp[]);
void display(char exp[], char postExp[], int result);

int main(void)
{
	int select, result; //사용자가 원할 때 까지 반복하는 제어변수 select, 계산결과 저장 변수 result 선언
	char exp[LINE_SIZE], postExp[LINE_SIZE]; //중위 식, 후위 식 문자열 선언
	stack_type s; // 스택 선언
	stack_type_ptr s_ptr = &s; //스택 포인터 선언

	init(s_ptr); //스택 초기화

	do{
		select = menu();

		if (select == 1){
			get_exp(exp); //중위 식 입력
			postfix(exp, postExp, s_ptr); //후위 식으로 변환
			result = eval(postExp); //후위식 평가
			display(exp, postExp, result); //후위식 및 계산 결과 출력
		}
	} while (select == 1);

	printf("프로그램을 종료합니다.");

	getch();
	return 0;
}

int menu()
{
	int select;
	printf("식을 입력하시려면 1을 입력하세요. :");
	scanf("%d", &select);
	getchar(); //버퍼 제거

	return select;
}

void get_exp(char exp[])
{
	printf("중위 식을 입력하세요 : ");
	gets(exp);
}

void postfix(char exp[], char postExp[], stack_type_ptr s_ptr)
{
	int i = 0, k = 0;
	char token;

	while (exp[i] != NULL) {

		token = exp[i];

		if (token >= '0' && token <= '9') { //피연산자일때
			postExp[k] = token;
			k++;
		}

		else if (token == '*' || token == '/' || token == '%' || token == '+' || token == '-' || token == '(') {
			while (is_empty(*s_ptr) == 0 && PIS(peek(*s_ptr)) >= PIE(token)) {  //스택의 연산자가 식의 연산자보다 크거나 같을 때
				postExp[k] = pop(&s_ptr);
				k++;
			}
			push(s_ptr, token);
		}

		else if (token == ')') {//괄호를 만나면
			while ((token = pop(&s_ptr)) != '(') {
				postExp[k] = token;
				k++;
			}
		}
		i++;
	}

	while (s_ptr->top >= 0) {
		postExp[k] = pop(&s_ptr);
		k++;
	}
	postExp[k] = NULL;
}

int eval(char postExp[])
{
	stack_type eval_stack; //계산용 스택 선언
	stack_type_ptr eval_s_ptr = &eval_stack; //계산용 스택 포인터 선언

	char divisor, dividend; //나눗셈에 쓰일 변수 선언
	char mod, num; //나머지 연산에 쓰일 변수 선언

	init(eval_s_ptr); //계산용 스택 초기화

	for (int i = 0; postExp[i] != NULL; i++){
		if (postExp[i] >= '0' && postExp[i] <= '9'){ //식의 인덱스 값이 숫자이면
			push(eval_s_ptr, postExp[i]);
		}
		else{
			switch (postExp[i]){ //식의 인덱스 값이 연산자이면
			case '+':
				push(eval_s_ptr, (pop(&eval_s_ptr) + pop(&eval_s_ptr) - 48));
				break;
			case '-':
				push(eval_s_ptr, (-pop(&eval_s_ptr) + pop(&eval_s_ptr) + 48));
				break;
			case '*':
				push(eval_s_ptr, ((pop(&eval_s_ptr) - 48) * (pop(&eval_s_ptr) - 48) + 48));
				break;
			case '/':
				divisor = pop(&eval_s_ptr);
				dividend = pop(&eval_s_ptr);
				push(eval_s_ptr, ((dividend - 48) / (divisor - 48)) + 48);
				break;
			case '%':
				mod = pop(&eval_s_ptr);
				num = pop(&eval_s_ptr);
				push(eval_s_ptr, ((num - 48) % (mod - 48)) + 48);
				break;
			} //연산
		}
	}

	return pop(&eval_s_ptr) - 48; //최종 값 반환
}

void display(char exp[], char postExp[], int result)
{
	printf("입력 한 중위 식 : %s\n", exp);
	printf("입력 한 후위 식 : %s\n", postExp);
	printf("계산 결과 : %d\n", result);
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
	if (s.top == LINE_SIZE - 1)
		return 1;
	else return 0;
}

char peek(stack_type s) //스택의 맨 위의 값 반환
{
	return s.stack[s.top];
}

int PIS(char token) //스택내에서 연산자 순위 반환
{
	if (token == '*' || token == '/' || token == '%')
		return 2;
	else if (token == '+' || token == '-')
		return 1;
	else return 0;
}

int PIE(char token) //식 내에서 연산자 순위 반환
{
	if (token == '*' || token == '/' || token == '%')
		return 2;
	else if (token == '+' || token == '-')
		return 1;
	else return 3;
}
