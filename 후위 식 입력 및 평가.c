#include <stdio.h>

#define LINE_SIZE 100

struct exp{
	int stack[LINE_SIZE];
	int top;
}; //스택 구조체 정의

int menu();
void get_postExp(char postExp[]);
int eval(char postExp[]);
void display(char postExp[], int result);

int main(void)
{
	int select, result; //사용자가 원할 때 까지 반복하는 제어변수 select, 계산결과 저장 변수 result 선언
	char postExp[LINE_SIZE]; //후위식을 입력 받을 문자열 선언

	do{
		select = menu();

		if (select == 1){
			get_postExp(postExp); //후위식 입력
			result = eval(postExp); //후위식 평가
			display(postExp, result); //후위식 및 계산 결과 출력
		}
	}while (select == 1);

	printf("프로그램을 종료합니다.");

	getch();
	return 0;
}

int menu()
{
	int select;
	printf("후위식을 입력하시려면 1을 입력하세요. :");
	scanf("%d", &select);
	getchar(); //버퍼 제거

	return select;
}

void get_postExp(char postExp[])
{
	printf("식을 입력하세요 : ");
	gets(postExp);
}

int eval(char postExp[])
{
	struct exp exp;
	exp.top = -1;

	for (int i = 0; postExp[i] != NULL; i++){
		if (postExp[i] >= '0' && postExp[i] <= '9'){ //식의 인덱스 값이 숫자이면
			exp.top++; //top을 1 증가시킴
			exp.stack[exp.top] = postExp[i] - 48; //스택에 저장
		}
		else{
			switch (postExp[i]){ //식의 인덱스 값이 연산자이면
			case '+':
				exp.stack[exp.top - 1] = exp.stack[exp.top - 1] + exp.stack[exp.top];
				exp.top--;
				break;
			case '-':
				exp.stack[exp.top - 1] = exp.stack[exp.top - 1] - exp.stack[exp.top];
				exp.top--;
				break;
			case '*':
				exp.stack[exp.top - 1] = exp.stack[exp.top - 1] * exp.stack[exp.top];
				exp.top--;
				break;
			case '/':
				exp.stack[exp.top - 1] = exp.stack[exp.top - 1] / exp.stack[exp.top];
				exp.top--;
				break;
			} //연산
		}
	}

	return exp.stack[exp.top]; //최종 값 반환
}

void display(char postExp[], int result)
{
	printf("입력 한 후위 식 : %s\n",postExp);
	printf("계산 결과 : %d\n", result);
}
