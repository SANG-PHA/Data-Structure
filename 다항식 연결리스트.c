#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0

struct node * create_node(int coef, int expo);
struct node * add_first(struct node * poly, int coef, int expo);
struct node * add_last(struct node * poly, struct node ** node, int coef, int expo);
struct node * get_poly();
struct node * sub_poly(struct node * p1, struct node * p2);
void print_poly(struct node * p);
int eval_poly(struct node * p, int x); //함수원형


struct node{
	int coef;
	int expo;
	struct node * link;
}; //구조체 node 선언

int main(void)
{
	struct node * p1 = NULL;
	struct node * p2 = NULL;
	struct node * p3 = NULL; //헤드포인터 선언

	p1 = get_poly(); //p1에 노드연결
	p2 = get_poly(); //p2에 노드연결
	p3 = sub_poly(p1, p2); //p3에 뺄셈결과 다항식 노드 연결

	printf("다항식 p1 : ");
	print_poly(p1);
	printf("다항식 p2 : ");
	print_poly(p2);
	printf("뺄셈 결과 p3 : ");
	print_poly(p3); //다항식 출력

	printf("x값을 입력하시오 : ");
	int x;
	scanf("%d", &x);

	int result1, result2, result3;
	result1 = eval_poly(p1, x); 
	printf("다항식 p1에 %d값을 대입한 결과 : %d\n", x, result1);
	result2 = eval_poly(p2, x); 
	printf("다항식 p2에 %d값을 대입한 결과 : %d\n", x, result2);
	printf("다항식 p1의 결과 - 다항식 p2의 결과 : %d\n",result1 - result2);
	result3 = eval_poly(p3, x); 
	printf("다항식 p3에 %d값을 대입한 결과 : %d\n", x, result3);
	//식의 값 계산 및 출력

	free(p1);
	free(p2);
	free(p3);
	getch();
	return 0;
}

struct node * get_poly()
{
	struct node * poly = NULL; //헤드포인터 선언
	struct node * prev = NULL; //이전노드를 가리킬 포인터 선언
	char arr[SIZE] = { NULL, }; //입력받을 다항식을 저장할 문자열 배열
	char *tmp = NULL; //토큰 임시 저장변수
	int expo_in = FALSE; //계수와 차수 입력 boolean변수 선언
	int coef, expo; //계수, 차수 저장 변수 선언


	printf("다항식을 입력하시오 : ");
	gets(arr);

	tmp = strtok(arr, "^");
	do
	{
		if (expo_in == FALSE) //expo_in이 FALSE이면 계수입력
		{
			coef = atoi(tmp); //atoi함수를 사용하여 문자열 -> 정수 변환
			tmp = strtok(NULL, "+"); //구분자 "+"
			expo_in = TRUE;
		}
		else if (expo_in == TRUE) //expo_in이 FALSE이면 차수입력
		{
			expo = atoi(tmp);
			tmp = strtok(NULL, "^"); //구분자 "^"

			if (poly == NULL){ //첫 번째 노드로 삽입
				poly = add_first(poly, coef, expo);
				prev = poly;
			}
			else
				poly = add_last(poly, &prev, coef, expo);

			expo_in = FALSE;
		}
	} while (tmp != NULL); //token이 NULL일 때 까지

	return poly; //헤드포인터 반환
}

struct node * create_node(int coef, int expo)
{
	//노드생성
	struct node * new = (struct node *)malloc(sizeof(struct node));

	//필드 입력
	new->coef = coef;
	new->expo = expo;
	new->link = NULL;

	return new; //노드반환
}

struct node * add_first(struct node * poly, int coef, int expo)
{
	struct node * node = create_node(coef, expo);
	poly = node; //헤드포인터 노드에 연결
	return poly; //헤드포인터 반환
}

struct node * add_last(struct node * poly, struct node ** prev, int coef, int expo)
{ //prev도 변경해주어야 하기 때문에 2중포인터를 사용하여 매개변수로 받는다
	(*prev)->link = create_node(coef, expo);
	*prev = (*prev)->link;
	return poly;
}

struct node * sub_poly(struct node * p_1, struct node * p_2)
{
	struct node * p1 = p_1;
	struct node * p2 = p_2;
	struct node * p3 = NULL;
	struct node * prev = NULL;
	int coef, expo;

	while (p1 != NULL || p2 != NULL)
	{
		if (p1 == NULL) //p1의 모든 노드를 방문했을 때
		{
			coef = -(p2->coef); //p2의 -계수입력
			expo = p2->expo; //p2의 차수입력	
			p2 = p2->link;
		}
		else if (p2 == NULL) //p2의 모든 노드를 방문했을 때
		{
			coef = p1->coef; //p1의 계수입력
			expo = p1->expo; //p1의 차수입력	
			p1 = p1->link;
		}
		else{
			if (p1->expo == p2->expo) //p1과p2의 해당 노드의 차수가 같을때
			{
				coef = p1->coef - p2->coef; //계수입력
				expo = p1->expo; //차수입력	
				p1 = p1->link;
				p2 = p2->link;
			}
			else if (p1->expo > p2->expo) //해당 노드의 차수가 p1이 더 클때
			{
				coef = p1->coef; //p1의 계수입력
				expo = p1->expo; //p1의 차수입력	
				p1 = p1->link;
			}
			else if (p2->expo > p1->expo) //해당 노드의 차수가 p2가 더 클때
			{
				coef = -(p2->coef); //p2의 -계수입력
				expo = p2->expo; //p2의 차수입력	
				p2 = p2->link;
			}
		}

		if (p3 == NULL) //첫 번째 노드로 삽입
		{
			p3 = add_first(p3, coef, expo);
			prev = p3;
		}
		else
			p3 = add_last(p3, &prev, coef, expo);
	}

	return p3; //헤드포인터 반환
}

void print_poly(struct node * p)
{
	char arr[SIZE] = { NULL, }; //다항식 형식으로 출력할 배열 선언
	char tmp[10] = { NULL, }; //토큰 저장 배열
	int end_loop = FALSE;

	while (end_loop != TRUE)
	{
		if (p->link != NULL) //마지막 항이 아니면
		{
			itoa(p->coef, tmp, 10); //itoa함수를 사용하여 정수 -> 문자열 변환
			strcat(arr, tmp);
			strcat(arr, "x^");

			itoa(p->expo, tmp, 10);
			strcat(arr, tmp);
			strcat(arr, "+");
		}
		else //마지막 항
		{
			itoa(p->coef, tmp, 10);
			strcat(arr, tmp);
			strcat(arr, "x^");

			itoa(p->expo, tmp, 10);
			strcat(arr, tmp);
			end_loop = TRUE;
		}
		p = p->link;
	}

	puts(arr);
}

int eval_poly(struct node * p, int x)
{
	int result = 0;
	while (p != NULL)
	{
		result += p->coef * pow(x, p->expo); //pow함수를 사용하여 제곱계산
		p = p->link;
	}
	return result;
}
