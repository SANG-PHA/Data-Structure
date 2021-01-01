#include <stdio.h>
#include "priority_queue.h"

#define MAX_VERTICES 7
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] = {
	{   0,   7, INF, INF,   3,  10, INF },
	{   7,   0,   4,  10,   2,   6, INF },
	{ INF,   4,   0,   2, INF, INF, INF },
	{ INF,  10,   2,   0,  11,   9,   4 },
	{   3,   2, INF,  11,   0, INF,   5 },
	{  10,   6, INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 }
};

int selected[MAX_VERTICES] = { 0, };
HeapType dist; //우선순위 큐를 사용한 dist
HeapTypePtr dist_ptr = &dist;

element get_min_vertex(int n);
void prim(int s, int n);

int main(void)
{
	prim(0, MAX_VERTICES);

	getch();
	return 0;
}

element get_min_vertex(int n)
{
	return delete_heap(dist_ptr);
}

void prim(int s, int n)
{
	int i, u, v;
	element e;

	for (u = 0; u < n; u++)
		insert_heap(dist_ptr, u ,INF); //우선순위 큐에 모든 정점 입력
	change_order(dist_ptr, s, 0, n); //시작 노드의 distance = 0

	printf("Prim 알고리즘에 따른 MST\n");
	for (i = 0; i < n; i++){
		e = get_min_vertex(n); //가중치도 출력하기 위해 element타입을 반환받는다.
		selected[e.v] = TRUE; // u = e.v

		printf("방문한 정점 : %d     가중치 : %d\n",e.v, e.weight);

		for (v = 0; v < n; v++)
			if (weight[e.v][v] != INF)
				if (!selected[v] && weight[e.v][v] < get_distance(dist_ptr, v, n))
					change_order(dist_ptr, v, weight[e.v][v], n);
	}
}
