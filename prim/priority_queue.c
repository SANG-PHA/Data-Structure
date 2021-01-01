#include "priority_queue.h"

int get_distance(HeapTypePtr heap_ptr, int v, int n)
{
	//찾으려는 정점의 가중치 반환
	for (int i = 0; i < n; i++)
		if (heap_ptr->Heap[i].v == v)
			return heap_ptr->Heap[i].weight;
}

void change_order(HeapTypePtr heap_ptr, int i, int key, int n)
{
	//히프 구조가 비어있다면 오류
	if (isEmpty(*heap_ptr)){
		printf("히프가 비어있습니다.\n");
		return;
	}

	//바꾸려는 정점 값에 따른 히프 인덱스 번호 찾기
	for (int v = 1; v <= n; v++)
		if (heap_ptr->Heap[v].v == i){
			i = v;
			break;
		}

	element tmp = heap_ptr->Heap[i]; //요소 이동에 쓰일 임시 변수
	tmp.weight = key;

	// 1) key값이 원래 있던 값보다 클 때
	if (heap_ptr->Heap[i].weight < key){

		int j = i * 2; // i노드의 자식노드

		//삽입 될 위치 조정
		//자식노드와 비교하여 자식노드 값이 작으면 위치 변경
		while (j <= heap_ptr->HeapSize)
		{
			if (j < heap_ptr->HeapSize && heap_ptr->Heap[j + 1].weight < heap_ptr->Heap[j].weight)
				j = j + 1; //더 작은 자식 찾기

			if (key <= heap_ptr->Heap[j].weight)
				break; //stay 조건

			heap_ptr->Heap[i] = heap_ptr->Heap[j];
			i = j;
			j = i * 2;
		}

		heap_ptr->Heap[i] = tmp;
	}

	// 2) key값이 원래 있던 값보다 작을 때
	else if (heap_ptr->Heap[i].weight > key){

		//삽입 될 위치 조정
		//부모노드와 비교하여 부모노드 값이 크면 위치 변경
		while (i > 1 && key <= heap_ptr->Heap[i / 2].weight){
			heap_ptr->Heap[i] = heap_ptr->Heap[i / 2];
			i = i / 2;
		}

		heap_ptr->Heap[i] = tmp; //아이템 삽입
	}

	// 3) key값이 원래 있던 값과 같을 때
	else heap_ptr->Heap[i] = tmp;

}

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

void insert_heap(HeapTypePtr heap_ptr, int v, int item)
{
	if (isFull(*heap_ptr)){
		printf("히프가 꽉 차있습니다.\n");
		return 0;
	}

	element tmp;
	tmp.v = v;
	tmp.weight = item;

	heap_ptr->HeapSize += 1; // 현재 히프 크기 증가
	int i = heap_ptr->HeapSize; // 새로 추가될 노드 위치

	//삽입 될 위치 조정
	while (i > 1 && item <= heap_ptr->Heap[i / 2].weight){
		heap_ptr->Heap[i] = heap_ptr->Heap[i / 2];
		i = i / 2;
	}

	heap_ptr->Heap[i] = tmp; //아이템 삽입
}

element delete_heap(HeapTypePtr heap_ptr)
{
	if (isEmpty(*heap_ptr)){
		printf("히프가 비어있습니다.\n");
		return;
	}

	element item = heap_ptr->Heap[1]; //삭제될 정점
	element tmp = heap_ptr->Heap[heap_ptr->HeapSize]; //마지막 노드
	heap_ptr->HeapSize -= 1; //현재 히프 크기 감소
	int i = 1; //마지막 원소가 이동될 현재 위치
	int j = 2; //i의 왼쪽 자식 노드

	while (j <= heap_ptr->HeapSize)
	{
		if (j < heap_ptr->HeapSize && heap_ptr->Heap[j + 1].weight < heap_ptr->Heap[j].weight)
			j = j + 1; //더 작은 자식 찾기

		if (tmp.weight <= heap_ptr->Heap[j].weight)
			break; //stay 조건

		heap_ptr->Heap[i] = heap_ptr->Heap[j];
		i = j;
		j = i * 2;
	}

	heap_ptr->Heap[i] = tmp;

	return item;
}
