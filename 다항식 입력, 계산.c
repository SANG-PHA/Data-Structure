#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ROW 2
#define COL 30
#define SIZE 100

void get_poly();
void sub_poly();
void print_poly();
int eval_poly(); //함수원형

struct poly{
	int coef[COL];
	int expo[COL];
	int num;
}p[3]; //구조체 배열 선언

int main(void)
{
	get_poly(&p[1]); //p1 필드 입력
	get_poly(&p[2]); //p2 필드 입력
	sub_poly(&p[1], &p[2], &p[3]); //p3 필드 입력
	print_poly(&p[3]);

	printf("x값을 입력하시오 : ");
	int x;
	scanf("%d", &x);

	int sum = eval_poly(&p[3], x); //식의 값 계산
	printf("x에 %d를 대입한 결과 값 : %d", x, sum);

	getch();
	return 0;
}

void get_poly(struct poly *p)
{
	char arr[SIZE] = { NULL, }; //입력받을 다항식을 저장할 문자열 배열
	char *tmp = NULL; //토큰 임시 저장변수
	int i = 0, j = 0, check = 0;

	p->num = 0; //항의 갯수 0으로 초기화

	printf("다항식을 입력하시오 : ");
	gets(arr);

	tmp = strtok(arr, "^");
	do
	{
		if (check == 0) //check = 0이면 계수를 나타낸다
		{
			p->coef[i] = atoi(tmp); //atoi함수를 사용하여 문자열 -> 정수 변환
			tmp = strtok(NULL, "+"); //구분자 "+"
			check = 1;
			i++;
		}
		else if (check == 1) //check = 1이면 차수를 나타낸다
		{
			p->expo[j] = atoi(tmp);
			tmp = strtok(NULL, "^"); //구분자 "^"
			check = 0;
			p->num++; //항의 갯수 카운팅
			j++;
		}

	} while (tmp != NULL);

}

void sub_poly(struct poly *p1, struct poly  *p2, struct poly *p3)
{
	int p1_i = 0;
	int p2_i = 0;
	int p3_i = 0; //제어변수 초기화
	p3->num = 0; //p3 항의 갯수 0으로 초기화

	while (p1_i < p1->num || p2_i < p2->num)
	{
		if (p1->expo[p1_i] == p2->expo[p2_i]) //p1과p2의 해당 인덱스의 차수가 같을때
		{
			p3->coef[p3_i] = p1->coef[p1_i] + p2->coef[p2_i]; //계수입력
			p3->expo[p3_i] = p1->expo[p1_i]; //차수입력
			p1_i++;
			p2_i++;
			p3_i++; //제어변수 증가
		}
		else if (p1->expo[p1_i] > p2->expo[p2_i]) //해당 인덱스 차수가 p1이 더 클때
		{
			p3->coef[p3_i] = p1->coef[p1_i]; //p1의 계수입력
			p3->expo[p3_i] = p1->expo[p1_i]; //p1의 차수입력
			p1_i++;
			p3_i++; //p1,p3의 제어변수 증가
		}
		else if (p2->expo[p2_i] > p1->expo[p1_i]) //해당 인덱스 차수가 p1이 더 클때
		{
			p3->coef[p3_i] = p2->coef[p2_i]; //p2의 계수입력
			p3->expo[p3_i] = p2->expo[p2_i]; //p2의 차수입력
			p2_i++;
			p3_i++; //p1,p3의 제어변수 증가
		}
		p3->num++; //p3 항의 갯수 증가
	}
}

void print_poly(struct poly *p3)
{
	char arr[SIZE] = { NULL, }; //다항식 형식으로 출력할 배열 선언
	char tmp[10] = { NULL, }; //토큰 저장 배열

	for (int i = 0; i < p3->num; i++)
	{
		if (i < p3->num - 1) //마지막 항이 아니면
		{
			sprintf(tmp, "%d", p3->coef[i]); //sprintf함수를 사용하여 정수 -> 문자열 변환
			strcat(arr, tmp);
			strcat(arr, "x^");

			sprintf(tmp, "%d", p3->expo[i]);
			strcat(arr, tmp);
			strcat(arr, "+");
		}
		else //마지막 항
		{
			sprintf(tmp, "%d", p3->coef[i]);
			strcat(arr, tmp);
			strcat(arr, "x^");

			sprintf(tmp, "%d", p3->expo[i]);
			strcat(arr, tmp);
		}

	}

	printf("덧셈 결과 : ");
	puts(arr);
}

int eval_poly(struct poly *p3, int x)
{
	int sum = 0;
	for (int i = 0; i < p3->num; i++)
	{
		sum += p3->coef[i] * pow(x, p3->expo[i]); //pow함수를 사용하여 제곱계산
	}
	return sum;
}
