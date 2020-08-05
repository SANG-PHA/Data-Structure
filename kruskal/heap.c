#include "heap.h"

extern element;

void createHeap(HeapTypePtr heap_ptr)
{
	heap_ptr->HeapSize = 0; //히프 사이즈 0으로 초기화
}

boolean isEmpty(HeapType heap)
{
	if (heap.HeapSize == 0)
		return TRUE;
	else return FALSE;
}

boolean isFull(HeapType heap)
{
	if (heap.HeapSize == MAX_ELEMENT)
		return TRUE;
	else return FALSE;
}

void insert_heap(HeapTypePtr heap_ptr, element item)
{
	if (isFull(*heap_ptr)){
		printf("히프가 꽉 차있습니다.\n");
		return 0;
	}

	heap_ptr->HeapSize += 1; // 현재 히프 크기 증가
	int i = heap_ptr->HeapSize; // 새로 추가될 노드 위치

	//삽입 될 위치 조정, key값을 사용하여 비교
	while (i > 1 && item.key <= heap_ptr->Heap[i / 2].key){
		heap_ptr->Heap[i] = heap_ptr->Heap[i / 2];
		i = i / 2;
	}

	heap_ptr->Heap[i] = item; //아이템 삽입
}

element delete_heap(HeapTypePtr heap_ptr)
{
	if (isEmpty(*heap_ptr)){
		printf("히프가 비어있습니다.\n");
		return;
	}

	element item = heap_ptr->Heap[1]; //삭제될 아이템
	element tmp = heap_ptr->Heap[heap_ptr->HeapSize]; //마지막 노드
	heap_ptr->HeapSize -= 1; //현재 히프 크기 감소
	int i = 1; //마지막 원소가 이동될 현재 위치
	int j = 2; //i의 왼쪽 자식 노드

	while (j <= heap_ptr->HeapSize)
	{
		if (j < heap_ptr->HeapSize && heap_ptr->Heap[j + 1].key < heap_ptr->Heap[j].key)
			j = j + 1; //더 작은 자식 찾기

		if (tmp.key <= heap_ptr->Heap[j].key)
			break; //stay 조건

		heap_ptr->Heap[i] = heap_ptr->Heap[j];
		i = j;
		j = i * 2;
	}

	heap_ptr->Heap[i] = tmp;

	return item;
}
