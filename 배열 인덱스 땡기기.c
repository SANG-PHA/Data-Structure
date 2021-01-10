#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delete(int a[], int n, int loc); //함수선언

int i; //루프제어변수 편의를 위해 전역변수로 선언

int main(void)
{
	int loc, n, check = 0;
	int *a;

	srand(time(NULL)); //시간에 대한 시드값 설정

	printf("배열의 크기를 입력하시오 : ");
	scanf("%d", &n); //배열 크기입력

	a = (int *)malloc(n * sizeof(int)); //동적메모리할당, 정수 사이즈

	printf("초기배열 : [");

	for (i = 0; i < n; i++)
	{
		a[i] = rand() % 100;
		printf("%d ", a[i]); //0~100까지 난수를 배열에 저장
	}

	printf("\b]\n");

	loc = rand() % n; //0~n까지의 난수저장

	delete(a, n, loc);

	getch();
	return 0;
}

void delete(int b[], int n, int loc)
{
	int check = 0, tmp = 0;
	printf("지워야할 인덱스번호 : %d\n", loc + 1);
	printf("지워야할 인덱스값 : %d\n", b[loc]);

	for (i = 0; i < n; i++)
	{
		if (i == loc) //지워야할 인덱스를 찾으면
		{
			tmp = b[i + 1];
			b[i] = tmp; //인덱스 한칸씩 땡기기
			check = 1;
		}
		if (check == 1)
		{
			tmp = b[i + 1];
			b[i] = tmp; //인덱스 한칸씩 땡기기
		}

	}
	b[n] = 0;

	printf("변경된 배열 : [");

	for (i = 0; i< n - 1; i++)
		printf("%d ", b[i]);

	printf("\b]");
}
