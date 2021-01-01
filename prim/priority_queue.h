#include <stdio.h>

//boolean타입 정의
#define TRUE 1
#define FALSE 0
typedef int boolean;

//히프 기본 자료구조
#define MAX_ELEMENT 200

//히프 요소 타입 정의
typedef struct{
	int weight; //가중치
	int v; //정점
}element;
typedef struct{
	element Heap[MAX_ELEMENT];
	int HeapSize;
}HeapType;
typedef HeapType* HeapTypePtr; //HeapType포인터 타입 선언

//히프 기본 연산
void createHeap(HeapTypePtr heap_ptr);
boolean isEmpty(HeapType heap);
boolean isFull(HeapType heap);
void insert_heap(HeapTypePtr heap_ptr, int v, int item);
element delete_heap(HeapTypePtr heap_ptr);
void change_order(HeapTypePtr heap_ptr, int i, int key, int n);
int get_distance(HeapTypePtr heap_ptr, int v, int n);
