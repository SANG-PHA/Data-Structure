#include <stdio.h>
#include <stdlib.h> //rand함수 사용을 위한 라이브러리 호출
#include <time.h>  //rand함수의 시드값을 시간으로 설정하기위한 라이브러리 호출

int get_number();
void get_array(int *a,int n);
void sort(int *a, int *b, int n);
void display(int *b, int n); //함수선언

int i, j; //루프제어변수 선언 


int main(void)
{
	int n;
	int *first_arr = NULL, *dis_arr = NULL; //동적할당을 위한 포인터선언

	n = get_number();

	first_arr = malloc(sizeof(int)*n);
	dis_arr = malloc(sizeof(int)*n); //배열 동적메모리할당

	get_array(first_arr,n);
	sort(first_arr, dis_arr, n);
	display(dis_arr, n);

	free(dis_arr); //동적메모리 반납
	free(first_arr); //동적메모리 반납
	getch();
	return 0;
}

int get_number()
{
	int a;
	printf("생성하고자 하는 난수의 갯수를 입력하시오 : ");
	scanf("%d", &a);

	return a;
}

void get_array(int *a, int n)
{
	srand(time(NULL)); //시간에따른 시드값 설정

	printf("생성된 난수배열 : [");

	for (i = 0; i < n; i++)
	{
		a[i] = (rand() % 100) + 1; //first_arr에 난수값 입력
		printf("%d ", a[i]); //생성된 난수 배열 출력
	}
	printf("]\n");
}

void sort(int *a, int *b, int n)
{
	int tmp = 0, check = 0; //함수오름차순정렬을 위한 변수선언 및 초기화

	for (i = 0; i < n; i++)
	{
		tmp = a[0];
		check = 0;

		for (j = 0; j < n; j++)
		{
			if (tmp > a[j]) //배열내에서 최솟값을 찾기위한 조건문
			{
				tmp = a[j];
				check = j;
			}
		}
		a[check] = 101; //first_arr에서 최솟값을 찾아내었으므로 다음 반복문에 영향을 끼치지않도록 해당 인덱스에 101입력
		b[i] = tmp;
	}
}

void display(int *b, int n)
{
	printf("오름차순으로 정렬된 배열 : [");

	for (i = 0; i < n; i++)
	{
		printf("%d ", b[i]); //오름차순 정렬된 배열 출력
	}

	printf("]");

}
