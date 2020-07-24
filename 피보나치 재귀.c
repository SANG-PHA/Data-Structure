#include <stdio.h>
#include <time.h>

int fibo_rec(int n);
int count = 0;

int main(void)
{

	int n;
	printf("n을 입력하시오 : ");
	scanf("%d", &n);

	clock_t start, end;
	start = clock();

	printf("함수결과값 : %d\n", fibo_rec(n));
	printf("덧셈연산결과값 : %d\n", count);
	
	end = clock();

	printf("걸린 시간 : %f", (double)(end - start) / CLOCKS_PER_SEC);

	getch();
	return 0;
}

int fibo_rec(int n)
{
	

	if (n == 1)
	{
		
		return 0;
	}
	else if (n == 2)
		return 1;
	else
	{
		count++;
		return fibo_rec(n - 1) + fibo_rec(n - 2);
	}


}
