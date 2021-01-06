#include <stdio.h>
#include <stdlib.h>

#define MAX 50

//find_bridge에서 쓰일 전역변수
int discovered[MAX] = { 0, }; //방문 여부 배열
int number; //방문순서 변수
int idx = 0; //간선 출력에 사용될 인덱스 번호

//-----------------그래프 데이터타입 정의-------------------
//인접행렬
typedef struct graph_type_mat{
	int n;
	int graph_matrix[MAX][MAX];
}graph_type_mat;

//-----------------edge 타입 정의-----------------
typedef struct edge{
	int v1;
	int v2;
}edge;

//함수원형
void g_init(graph_type_mat *g_mat);
void graph_init(graph_type_mat *g_mat);
void insertVertex(graph_type_mat *g_mat, int n);
void insertEdge(graph_type_mat *g_mat, int v1, int v2);
void edges_init(edge *edges); //edges 초기화 함수
void find_bridge(graph_type_mat g_mat, edge *edges); //간선을 포함할 구조체배열을 포인터 타입으로 전달하여 반환값은 void
int dfs(graph_type_mat g_mat, edge *edges, int v, int parent);
void print(edge *edges);
int find_next(graph_type_mat g_mat, int v, int *n); //인접한 다음 노드를 찾는 함수
int get_v_size(graph_type_mat g_mat, int v); //해당 정점에 인접한 노드의 갯수를 반환하는 함수

int main(void)
{
	graph_type_mat g;
	edge edges[MAX]; //brige를 표현할 edge타입 배열로 선언

	g_init(&g);
	edges_init(edges);

	find_bridge(g, edges);
	print(edges);

	getch();
	return 0;
}

void find_bridge(graph_type_mat g_mat, edge *edges)
{
	for (int i = 0; i < g_mat.n; i++)
		if (discovered[i] == 0){ //방문되지 않은 노드라면 dfs실행
			dfs(g_mat, edges, i, 0);
		}

}

int find_next(graph_type_mat g_mat, int v, int *n)
//c++나 java라면 vector를 이용하여 쉽게 해결하겠지만, c언어 특성상 함수로 인접한 다음 노드를 찾습니다.
{
	for (int w = *n; w < g_mat.n; w++)
		if (g_mat.graph_matrix[v][w]){
			*n = w + 1;
			return w;
		}

	return 0;
}

int get_v_size(graph_type_mat g_mat, int v)
{
	int size = 0;
	for (int i = 0; i < g_mat.n; i++)
		if (g_mat.graph_matrix[v][i])
			size++;

	return size;
}

int dfs(graph_type_mat g_mat, edge *edges, int v, int parent)
{
	discovered[v] = ++number; // DFS 탐색 순서 지정
	int ret = discovered[v]; 
	int size = get_v_size(g_mat, v); //정점이 가진 인접노드의 수
	int n = 0; //find_next 함수에서 사용되는 변수

	for (int i = 0; i < size; i++)
	{
		int next = find_next(g_mat, v, &n);

		if (next == parent) //다음 노드가 부모노드와 같다면 continue
			continue;

		if (discovered[next])
			//이미 dfs에서 탐색된 정점이라면 현재 정점의 방문순서와 탐색된 정점의 방문 순서중
			//min값을 찾는다.
		{
			ret = min(ret, discovered[next]);
			continue;
		}

		int prev = dfs(g_mat, edges, next, v);

		//단절선을 찾으면
		if (prev > discovered[v]){
			edges[idx].v1 = min(v, next);
			edges[idx].v2 = max(v, next);
			idx++;
		}

		ret = min(ret, prev);
	}

	return ret;
}

void print(edge *edges)
{
	printf("Bridges\n");
	for (int i = 0; i < idx; i++)
		printf("%d %d\n", edges[i].v1, edges[i].v2);
}

void edges_init(edge *edges)
{
	for (int i = 0; i < MAX; i++){
		edges->v1 = -1;
		edges->v2 = -1;
	}
}

void g_init(graph_type_mat *g_mat)
{
	graph_init(g_mat); //그래프 초기화

	//정점 입력 및 간선 연결
	for (int i = 0; i < 10; i++)
		insertVertex(g_mat, i);

	insertEdge(g_mat, 0, 1);
	insertEdge(g_mat, 1, 2);
	insertEdge(g_mat, 1, 3);
	insertEdge(g_mat, 2, 4);
	insertEdge(g_mat, 3, 4);
	insertEdge(g_mat, 3, 5);
	insertEdge(g_mat, 5, 6);
	insertEdge(g_mat, 5, 7);
	insertEdge(g_mat, 6, 7);
	insertEdge(g_mat, 7, 8);
	insertEdge(g_mat, 7, 9);
}

void graph_init(graph_type_mat *g_mat)
{
	//인접행렬 초기화
	g_mat->n = 0;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			g_mat->graph_matrix[i][j] = 0;
}

void insertVertex(graph_type_mat *g_mat, int n)
{
	//인접행렬
	g_mat->n++;
}

void insertEdge(graph_type_mat *g_mat, int v1, int v2)
{
	//인접행렬
	g_mat->graph_matrix[v1][v2] = 1;
	g_mat->graph_matrix[v2][v1] = 1;
}
