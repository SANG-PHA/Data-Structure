#include <stdio.h>
#include "heap.h"

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; //부모 노드를 나타내는 배열
int num[MAX_VERTICES]; //집합의 크기

void set_init(int n);
int set_find(int v);
void set_union(int s1, int s2);
void insert_heap_edge(HeapTypePtr h, int u, int v, int weight);
void insert_all_edges(HeapTypePtr h);
void kruskal(int n);

int main(void)
{
	kruskal(7);

	getch();
	return 0;
}

void kruskal(int n)
{
	int edge_accepted = 0; //현재까지 선택된 간선 수
	HeapType h;
	HeapTypePtr h_ptr = &h;
	int uset, vset;
	element e;

	createHeap(h_ptr); //히프 생성 및 초기화
	insert_all_edges(h_ptr); //히프에 간선 삽입
	set_init(n); //집합 초기화

	printf("Kruskal 알고리즘에 따른 MST\n");
	while (edge_accepted < (n - 1)){ //간선의 수 n-1
		e = delete_heap(h_ptr); //최소 히프에서 삭제
		uset = set_find(e.u); //정점 u의 집합 번호
		vset = set_find(e.v); //정점 v의 집합 번호
		if (uset != vset){ //집합 번호가 다르면
			printf("간선 : (%d %d)     가중치 : %d\n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);
		}
	}
}

//parent, num배열 초기화
void set_init(int n)
{
	for (int i = 0; i < n; i++){
		parent[i] = -1;
		num[i] = 1;
	}
}

//v가 속하는 집합의 루트 노드 반환
int set_find(int v)
{
	int p, s, i = -1;

	for (i = v; (p = parent[i]) >= 0; i = p); //루트 노드 찾기

	s = i; //집합의 루트 노드
	for (i = v; (p = parent[i]) >= 0; i = p)
		parent[i] = s; //집합 모든 원소들의 부모를 p로 설정

	return s;
}

void set_union(int s1, int s2)
{
	if(num[s1] < num[s2]){ //s2의 크기가 s1보다 크다면
		parent[s1] = s2; //부모 노드 s2로 변경
		num[s2] += num[s1]; //s2의 크기 증가
	}
	else{
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

void insert_heap_edge(HeapTypePtr h, int u, int v, int weight)
{
	element e;

	e.u = u;
	e.v = v;
	e.key = weight;
	insert_heap(h, e);
}

void insert_all_edges(HeapTypePtr h)
{
	insert_heap_edge(h, 0, 1, 7);
	insert_heap_edge(h, 0, 5, 10);
	insert_heap_edge(h, 0, 4, 3);
	insert_heap_edge(h, 1, 4, 2);
	insert_heap_edge(h, 1, 2, 4);
	insert_heap_edge(h, 1, 3, 10);
	insert_heap_edge(h, 1, 5, 6);
	insert_heap_edge(h, 2, 3, 2);
	insert_heap_edge(h, 3, 4, 11);
	insert_heap_edge(h, 3, 5, 9);
	insert_heap_edge(h, 3, 6, 4);
	insert_heap_edge(h, 4, 6, 5);
}
