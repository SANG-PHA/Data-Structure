#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <Windows.h>

#define MAX_SIZE 100001

//실행시간, 비교횟수, 이동횟수 구조체
//전역변수로 선언
typedef struct {
	int a[MAX_SIZE];
	long long compare; //비교횟수
	long long move; //이동횟수
	double time; //실행 시간
}stats;
stats stats_arr[7]; //7가지 방법의 정렬이므로 구조체 배열 사용


/***************************************************************/
void calcStatistics(int num);
void cmpSortsByTable(int num);
//void cmpSortsByGraph();
void init_stats(int n); //구조체 초기화 함수

//7가지 정렬 함수
void selection_sort(int a[], int n);
void bubble_sort(int a[], int n);
void insertion_sort(int a[], int n);
void shell_sort(int a[], int n);
void shell_insertion(int a[], int first, int last, int gap);
void merge_sort(int a[], int left, int right);
void merge(int a[], int low, int mid, int high);
void quick_sort(int a[], int left, int right);
int quick_partition(int a[], int left, int right);
void heap_sort(int a[], int n);
/***************************************************************/
int sorted[MAX_SIZE];
//히프 기본 자료구조
typedef int element;
typedef struct {
	element Heap[MAX_SIZE];
	long long HeapSize;
}HeapType;
typedef HeapType* HeapTypePtr; //HeapType포인터 타입 선언

//히프 기본 연산
void createHeap(HeapTypePtr heap_ptr);
void insert_heap(HeapTypePtr heap_ptr, int item);
int delete_heap(HeapTypePtr heap_ptr);


int main() {

	for (int i = 1; i <= 5; i++) {
		calcStatistics(20000 * i);
		cmpSortsByTable(20000 * i);
	}

	//cmpSortsByGraph(); 워드로 작성...

	getch();
	return 0;
}

void calcStatistics(int num)
{
	//각 정렬에 쓰일 구조체배열 초기화
	for (int n = 0; n < 7; n++)
		init_stats(n);

	clock_t start, end;
	double elapsed = 0.0;

	//선택정렬
	start = clock();
	selection_sort(stats_arr[0].a, num);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[0].time = elapsed;

	//버블정렬
	start = clock();
	bubble_sort(stats_arr[1].a, num);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[1].time = elapsed;

	//삽입정렬
	start = clock();
	insertion_sort(stats_arr[2].a, num);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[2].time = elapsed;

	//쉘 정렬
	start = clock();
	shell_sort(stats_arr[3].a, num);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[3].time = elapsed;

	//합병 정렬
	start = clock();
	merge_sort(stats_arr[4].a, 0, num - 1);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[4].time = elapsed;

	//퀵 정렬
	start = clock();
	quick_sort(stats_arr[5].a, 0, num - 1);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[5].time = elapsed;

	//히프 정렬
	start = clock();
	heap_sort(stats_arr[6].a, num);
	end = clock();
	elapsed = (double)((end - start) * 1000) / CLOCKS_PER_SEC;
	stats_arr[6].time = elapsed;
}

void cmpSortsByTable(int num)
{
	char name_of_sort[7][20] = {
		{ "선택정렬" }, { "버블정렬" }, { "삽입정렬" }, { "쉘  정렬" }, { "합병정렬" }, { "퀵  정렬" }, { "히프정렬" },
	};

	printf("\n데이터 항목 개수 : %d\n", num);
	printf("            소요 시간 \t 비교 횟수 \t 이동 횟수\n");
	for (int i = 0; i < 7; i++) {
		printf("%s     %.1f           %lld         %lld \n", name_of_sort[i], stats_arr[i].time, stats_arr[i].compare, stats_arr[i].move);
	}

}

void init_stats(int n)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX_SIZE; i++)
		stats_arr[n].a[i] = rand() % 1000 + 1;

	stats_arr[n].compare = 0;
	stats_arr[n].move = 0;
	stats_arr[n].time = 0;
}

//선택 정렬
void selection_sort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		int least = i;

		for (int j = i + 1; j < n; j++) {
			stats_arr[0].compare++; //비교횟수 증가
			if (a[j] < a[least]) {
				least = j;
			}
		}

		int tmp = a[i];
		a[i] = a[least];
		a[least] = tmp;

		stats_arr[0].move += 3; //이동횟수 증가
	}
}

//버블 정렬
void bubble_sort(int a[], int n)
{
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			stats_arr[1].compare++; //비교횟수 증가
			if (a[j] > a[j + 1]) {
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				stats_arr[1].move += 3; //이동횟수 증가
			}
		}
	}
}

//삽입 정렬
void insertion_sort(int a[], int n)
{
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;

		while (a[j] > key && j >= 0) {
			stats_arr[2].compare++; //비교횟수 증가
			a[j + 1] = a[j];
			stats_arr[2].move += 1; //이동횟수 증가
			j = j - 1;
		}

		a[j + 1] = key;
		stats_arr[2].move += 1; //이동횟수 증가
	}
}

//쉘 정렬 함수
void shell_sort(int a[], int n)
{
	for (int gap = n / 2; gap > 0; gap = gap / 2) {
		stats_arr[3].compare++; //비교횟수 증가
		if (gap % 2 == 0)
			gap++;

		for (int i = 0; i < gap; i++)
			shell_insertion(a, 0, n, gap);
	}
}

void shell_insertion(int a[], int first, int last, int gap)
{
	for (int i = first + gap; i < last; i = i + gap) {
		int key = a[i];
		int j = i - gap;

		while (a[j] > key && j >= first) {
			stats_arr[3].compare++; //비교횟수 증가
			a[j + gap] = a[j];
			j = j - gap;
			stats_arr[3].move += 2; //이동횟수 증가
		}

		a[j + gap] = key;
		stats_arr[3].move += 1; //이동횟수 증가
	}
}

//합병 정렬 함수
void merge_sort(int a[], int left, int right)
{
	stats_arr[4].compare++; //비교횟수 증가
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(a, left, mid);
		merge_sort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}

void merge(int a[], int low, int mid, int high)
{
	int b1 = low, b2 = mid + 1, e1 = mid, e2 = high;

	int idx = low;

	while (b1 <= e1 && b2 <= e2) {
		stats_arr[4].compare++; //비교횟수 증가
		if (a[b1] <= a[b2])
			sorted[idx++] = a[b1++];
		else sorted[idx++] = a[b2++];
		stats_arr[4].move += 1; //이동횟수 증가
	}

	stats_arr[4].compare++; //비교횟수 증가
	if (b1 > e1)
		for (int i = b2; i <= e2; i++) {
			sorted[idx++] = a[i];
			stats_arr[4].move += 1; //이동횟수 증가
		}
	else
		for (int i = b1; i <= e1; i++) {
			sorted[idx++] = a[i];
			stats_arr[4].move += 1; //이동횟수 증가
		}

	for (int i = low; i <= high; i++) {
		a[i] = sorted[i];
		stats_arr[4].move += 1; //이동횟수 증가
	}
}

//퀵 정렬 함수
void quick_sort(int a[], int left, int right)
{
	stats_arr[5].compare++; //비교횟수 증가
	if (left < right) {
		int q = quick_partition(a, left, right);
		quick_sort(a, left, q - 1);
		quick_sort(a, q + 1, right);
	}
}

int quick_partition(int a[], int left, int right)
{
	int pivot, low = left, high = right + 1;
	pivot = a[left];

	do {
		do {
			stats_arr[5].compare++; //비교횟수 증가
			low++;
		} while (a[low] < pivot && low <= right);

		do {
			stats_arr[5].compare++; //비교횟수 증가
			high--;
		} while (a[high] > pivot && high >= left);

		stats_arr[5].compare++; //비교횟수 증가
		if (low < high) {
			int tmp = a[low];
			a[low] = a[high];
			a[high] = tmp;
			stats_arr[5].move += 3; //이동횟수 증가
		}
	} while (low < high);
	int tmp = a[left];
	a[left] = a[high];
	a[high] = tmp;
	stats_arr[5].move += 3; //이동횟수 증가
	return high;
}

//히프 정렬 함수
void heap_sort(int a[], int n)
{
	//HeapType 변수와 포인터 변수 선언
	HeapType heap;
	HeapTypePtr heap_ptr = &heap;

	createHeap(heap_ptr); //히프 생성

	for (int i = 0; i < n; i++)
		insert_heap(heap_ptr, a[i]);

	for (int i = 0; i < n; i++)
		a[i] = delete_heap(heap_ptr);
}

void createHeap(HeapTypePtr heap_ptr)
{
	heap_ptr->HeapSize = 0; //히프 사이즈 0으로 초기화
}

void insert_heap(HeapTypePtr heap_ptr, int item)
{
	heap_ptr->HeapSize += 1; // 현재 히프 크기 증가
	int i = heap_ptr->HeapSize; // 새로 추가될 노드 위치

	//삽입 될 위치 조정
	while (i > 1 && item <= heap_ptr->Heap[i / 2]) {
		stats_arr[6].compare++; //비교횟수 증가
		heap_ptr->Heap[i] = heap_ptr->Heap[i / 2];
		i = i / 2;
		stats_arr[6].move += 2; //이동횟수 증가
	}

	heap_ptr->Heap[i] = item; //아이템 삽입
	stats_arr[6].move += 1; //이동횟수 증가
}

int delete_heap(HeapTypePtr heap_ptr)
{
	int item = heap_ptr->Heap[1]; //삭제될 아이템
	int tmp = heap_ptr->Heap[heap_ptr->HeapSize]; //마지막 노드
	heap_ptr->HeapSize -= 1; //현재 히프 크기 감소
	int i = 1; //마지막 원소가 이동될 현재 위치
	int j = 2; //i의 왼쪽 자식 노드


	while (j <= heap_ptr->HeapSize)
	{
		stats_arr[6].compare++; //비교횟수 증가
		if (j < heap_ptr->HeapSize && heap_ptr->Heap[j + 1] < heap_ptr->Heap[j])
			j = j + 1; //더 작은 자식 찾기

		stats_arr[6].compare++; //비교횟수 증가
		if (tmp <= heap_ptr->Heap[j])
			break; //stay 조건

		heap_ptr->Heap[i] = heap_ptr->Heap[j];
		i = j;
		j = i * 2;
		stats_arr[6].move += 3; //이동횟수 증가
	}

	heap_ptr->Heap[i] = tmp;
	stats_arr[6].move += 1; //이동횟수 증가

	return item;
}
