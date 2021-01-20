#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

//boolean타입 정의
typedef int bool;
#define TRUE 1
#define FALSE 0

//데이터타입 정의
//인접행렬
typedef struct graph_type_mat{
	int n;
	int graph_matrix[SIZE][SIZE];
}graph_type_mat;
graph_type_mat g_mat;

//인접그래프
typedef struct node{
	int v;
	struct node * link;
}node;
typedef struct node * nodeptr;

typedef struct graph_type_link{
	int n;
	node graph_linked[SIZE];
}graph_type_link;
graph_type_link g_link;

//함수원형
void init();
void graph_init();
void insertVertex(int n);
void insertEdge(int v1, int v2);
bool mat_exist_edge(int i, int j);
int mat_get_degree(int i);
int mat_get_edges();
bool link_exist_edge(int i, int j);
int link_get_degree(int i);
int link_get_edges();



int main(void)
{
	bool mat_flag = FALSE, link_flag = FALSE;
	int v1, v2;
	int mat_n, link_n;

	init();
	
	//exist_edge
	do{
		printf("간선의 존재여부를 확인하고 싶은 정점 v1, v2를 입력하시오 (종료하려면 -1) : ");
		scanf("%d %d", &v1, &v2);

		if (v1 != -1 && v2 != -1){
			mat_flag = mat_exist_edge(v1, v2);
			link_flag = link_exist_edge(v1, v2);
		}
		else break;

		if (mat_flag)
			printf("간선이 존재합니다(인접행렬).\n");
		else printf("간선이 없습니다(인접행렬).\n");

		if (link_flag)
			printf("간선이 존재합니다(인접리스트).\n");
		else printf("간선이 없습니다(인접리스트).\n");

	} while (1);

	//get_degree
	do{
		printf("차수를 알고싶은 정점을 입력하시오 (종료하려면 -1) : ");
		scanf("%d", &v1);
		if (v1 != -1){
			mat_n = mat_get_degree(v1);
			link_n = link_get_degree(v1);
			printf("정점%d의 차수(인접행렬) : %d\n", v1, mat_n);
			printf("정점%d의 차수(인접리스트) : %d\n", v1, link_n);
		}
		else break;
	} while (1);
	
	//get_edges
	mat_n = mat_get_edges();
	link_n = link_get_edges();
	printf("인접행렬로 표현된 그래프의 간선 총 갯수 : %d\n" ,mat_n);
	printf("인접리스트로 표현된 그래프의 간선 총 갯수 : %d\n" ,link_n);

	getch();
	return 0;
}

void init()
{
	int v1, v2;

	graph_init(); //그래프 초기화

	//정점 입력 및 간선 연결
	do{
		printf("정점 v를 입력하시오 (종료하려면 -1) : ");
		scanf("%d", &v1);
		if (v1 == -1)
			break;
		insertVertex(v1);
	} while (v1 != -1);

	do{
		printf("연결할 정점 v1, v2를 입력하시오 (종료하려면 -1) : ");
		scanf("%d %d", &v1, &v2);
		if (v1 == -1 || v2 == -1)
			break;
		insertEdge(v1, v2);
	} while (v1 != -1 || v2 != -1);
}

void graph_init()
{
	//인접행렬 초기화
	g_mat.n = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			g_mat.graph_matrix[i][j] = 0;

	//인접리스트 초기화
	g_link.n = 0;
	for (int i = 0; i < SIZE; i++){
		g_link.graph_linked[i].v= 0;
		g_link.graph_linked[i].link = NULL;
	}
}

void insertVertex(int n)
{
	//인접행렬
	g_mat.n++;

	//인접그래프
	g_link.n++;
	g_link.graph_linked[n].v = n;
}

void insertEdge(int v1, int v2)
{
	//인접행렬
	g_mat.graph_matrix[v1][v2] = 1;
	g_mat.graph_matrix[v2][v1] = 1;


	//인접그래프
	nodeptr new_node1 = (nodeptr)malloc(sizeof(struct node)); //새로운 노드 생성
	new_node1->v = v2;
	new_node1->link = g_link.graph_linked[v1].link; //새로운 노드 삽입
	g_link.graph_linked[v1].link = new_node1;

	nodeptr new_node2 = (nodeptr)malloc(sizeof(struct node)); //새로운 노드 생성
	new_node2->v = v1;
	new_node2->link = g_link.graph_linked[v2].link; //새로운 노드 삽입
	g_link.graph_linked[v2].link = new_node2;
}

bool mat_exist_edge(int i, int j)
{
	if (g_mat.graph_matrix[i][j])
		return TRUE;
	else return FALSE;
}

int mat_get_degree(int i)
{
	int cnt = 0;

	//해당 정점에 연결된 노드 수를 구한다
	for (int j = 0; j < g_mat.n; j++)
		if (g_mat.graph_matrix[i][j]) //연결되어있다면
			cnt++; //카운트 증가

	return cnt;
}

int mat_get_edges()
{
	int cnt = 0;

	//각 정점에 연결된 모든 노드를 구한다
	for (int i = 0; i < g_mat.n; i++)
		for (int j = 0; j < g_mat.n; j++)
			if (g_mat.graph_matrix[i][j]) //연결되어있다면
				cnt++; //카운트 증가

	return cnt / 2;
}

bool link_exist_edge(int i, int j)
{
	nodeptr p = g_link.graph_linked[i].link;
	while (p != NULL){
		if (p->v == j)
			return TRUE; //간선을 찾으면 TRUE반환 및 종료
		p = p->link;
	}

	return FALSE;
}

int link_get_degree(int i)
{
	int cnt = 0;
	nodeptr p = g_link.graph_linked[i].link;
	while (p != NULL){
		cnt++; //카운트 증가
		p = p->link;
	}

	return cnt;
}

int link_get_edges()
{
	int cnt = 0;

	//각 정점에 연결된 모든 노드의 갯수를 구한다
	for (int i = 0; i < g_link.n; i++){
		nodeptr p = g_link.graph_linked[i].link;
		
		while (p != NULL){
			cnt++; //카운트 증가
			p = p->link;
		}
	}

	return cnt / 2;
}
