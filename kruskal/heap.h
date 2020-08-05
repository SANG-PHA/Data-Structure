#include <stdio.h>

//boolean타입 정의
#define TRUE 1
#define FALSE 0
typedef int boolean;

//히프의 요소 타입 정의
typedef struct{
	int key;
	int u;
	int v;
}element;

//히프 기본 자료구조
#define MAX_ELEMENT 200
//typedef int element; 이번 프로그램에선 인트형이 아닌 새로 정의한 element타입 사용
typedef struct{
	element Heap[MAX_ELEMENT];
	int HeapSize;
}HeapType;
typedef HeapType* HeapTypePtr; //HeapType포인터 타입 선언

//히프 기본 연산
void createHeap(HeapTypePtr heap_ptr);
boolean isEmpty(HeapType heap);
boolean isFull(HeapType heap);
void insert_heap(HeapTypePtr heap_ptr, element item);
element delete_heap(HeapTypePtr heap_ptr);
