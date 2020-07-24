#include <stdio.h>
#include <time.h>

int fibo_iter(int n);
int count = 0;

int main(void)
{
	
	int n;
	printf("n을 입력하시오 : ");
	scanf("%d", &n);

	printf("함수결과값 : %d\n", fibo_iter(n));
	printf("덧셈연산횟수 : %d\n", count);
	
	getch();
	return 0;
}

int fibo_iter(int n)
{
	clock_t start, end;
	start = clock();

	int i;
	int prev = 0;
	int cur = 1;
	int next;

	for (i = 1; i < n; i++)
	{
		count++;
		next = prev + cur;
		prev = cur;
		cur = next;
	}

	end = clock();
	printf("걸린 시간 : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	return next;
}
