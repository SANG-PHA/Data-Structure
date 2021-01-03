#include <stdio.h>
#include <stdlib.h>

#define MAX 50

//boolean타입 정의
typedef int bool;
#define TRUE 1
#define FALSE 0

//-----------------그래프 데이터타입 정의-------------------
//인접행렬
typedef struct graph_type_mat{
	int n;
	int graph_matrix[MAX][MAX];
}graph_type_mat;

//인접그래프
typedef struct node{
	int v;
	struct node * link;
}node;
typedef struct node * nodeptr;

typedef struct graph_type_link{
	int n;
	nodeptr graph_linked[MAX];
}graph_type_link;

//함수원형
void g_init(graph_type_mat *g_mat, graph_type_link *g_link);
void graph_init(graph_type_mat *g_mat, graph_type_link *g_link);
void insertVertex(graph_type_mat *g_mat, int n);
void insertEdge(graph_type_mat *g_mat, int v1, int v2);
void arr2link(graph_type_mat g_mat, graph_type_link *g_link);
void print_g(graph_type_mat g_mat, graph_type_link g_link); //인접리스트 출력 함수
void DFS_mat(graph_type_mat g_mat, int v);
void DFS_link(graph_type_link g_link, int v);
void BFS_mat(graph_type_mat g_mat, int v);
void BFS_link(graph_type_link g_link, int v);

//DFS, BFS에 쓰일 cache배열
bool visited[MAX];
void init_visited(); //visited배열 초기화 함수


//-----------------큐 데이터타입 정의-------------------
#define MAX_QUEUE_SIZE 50

//큐 타입 정의 : 배열로 표현
typedef int element;
typedef struct queue_type {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}queue_type;
typedef queue_type* queue_type_ptr;

//큐 타입 연산 함수
void init(queue_type_ptr);
int is_empty(queue_type);
int is_full(queue_type);
void enqueue(queue_type_ptr, element);
element dequeue(queue_type_ptr);

int main(void)
{
	graph_type_mat g_mat;
	graph_type_link g_link;

	g_init(&g_mat, &g_link);
	arr2link(g_mat, &g_link);
	print_g(g_mat, g_link);

	init_visited();
	printf("DFS_MAT : ");
	DFS_mat(g_mat, 0);

	init_visited();
	printf("\nDFS_LINK : ");
	DFS_link(g_link, 0);

	init_visited();
	printf("\nBFS_MAT : ");
	BFS_mat(g_mat, 0);

	init_visited();
	printf("\nBFS_LINK : ");
	BFS_link(g_link, 0);

	getch();
	return 0;
}

void g_init(graph_type_mat *g_mat, graph_type_link *g_link)
{
	graph_init(g_mat, g_link); //그래프 초기화

	//정점 입력 및 간선 연결
	for (int i = 0; i < 5;i++)
		insertVertex(g_mat, i);
	
	insertEdge(g_mat, 0, 1);
	insertEdge(g_mat, 0, 2);
	insertEdge(g_mat, 0, 4);
	insertEdge(g_mat, 1, 2);
	insertEdge(g_mat, 2, 3);
	insertEdge(g_mat, 2, 4);
	insertEdge(g_mat, 3, 4);
}

void graph_init(graph_type_mat *g_mat, graph_type_link *g_link)
{
	//인접행렬 초기화
	g_mat->n = 0;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			g_mat->graph_matrix[i][j] = 0;

	//인접리스트 초기화
	g_link->n = 0;
	for (int i = 0; i < MAX; i++)
		g_link->graph_linked[i] = NULL;
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

void arr2link(graph_type_mat g_mat, graph_type_link *g_link)
{
	g_link->n = g_mat.n; //정점 갯수 입력

	//간선 입력
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			if (g_mat.graph_matrix[i][j]){ //인접행렬 인덱스 값이 1이면 인접리스트에 노드 생성 및 연결
				nodeptr new_node1 = (nodeptr)malloc(sizeof(struct node)); //새로운 노드 생성
				new_node1->v = j;
				new_node1->link = g_link->graph_linked[i]; //새로운 노드 삽입
				g_link->graph_linked[i] = new_node1;
			}
}

void print_g(graph_type_mat g_mat, graph_type_link g_link)
{
	printf("구성된 인접행렬\n");
	for (int i = 0; i < g_mat.n; i++){
		for (int j = 0; j < g_mat.n; j++)
			printf("%d ", g_mat.graph_matrix[i][j]);
		printf("\n");
	}

	printf("\n구성된 인접리스트\n");
	for (int i = 0; i < g_link.n; i++){
		printf("%d -> ", i);
		nodeptr p = g_link.graph_linked[i];
		while (p != NULL){
			printf("%d ", p->v);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");
}

void DFS_mat(graph_type_mat g_mat, int v)
{
	visited[v] = TRUE;
	printf("%d ", v);
	for (int w = 0; w < g_mat.n; w++){
		if (g_mat.graph_matrix[v][w] && !visited[w])
			DFS_mat(g_mat, w);

	}
}

void DFS_link(graph_type_link g_link, int v)
{
	visited[v] = TRUE;
	printf("%d ", v);
	nodeptr w = g_link.graph_linked[v];
	while (w != NULL){
		if (!visited[w->v])
			DFS_link(g_link, w->v);

		w = w->link;
	}
}

void BFS_mat(graph_type_mat g_mat, int v)
{
	visited[v] = TRUE;
	queue_type queue;
	queue_type_ptr q = &queue;
	init(q);
	enqueue(q, v);
	printf("%d ", v);

	while (!is_empty(*q)){
		v = dequeue(q);
		for (int w = 0; w < g_mat.n; w++)
			if (g_mat.graph_matrix[v][w] == 1 && visited[w] == FALSE){
				visited[w] = TRUE;
				enqueue(q, w);
				printf("%d ", w);
			}
	}
}

void BFS_link(graph_type_link g_link, int v)
{
	visited[v] = TRUE;
	queue_type queue;
	queue_type_ptr q = &queue;
	init(q);
	enqueue(q, v);
	printf("%d ", v);

	while (!is_empty(*q)){
		v = dequeue(q);
		nodeptr p = g_link.graph_linked[v];
		while (p != NULL){
			int w = p->v;
			if (!visited[w]){
				visited[w] = TRUE;
				enqueue(q, w);
				printf("%d ", w);
			}
			p = p->link;
		}
	}
}

void init_visited()
{
	for (int i = 0; i < MAX; i++)
		visited[i] = FALSE;
}

void init(queue_type_ptr q_ptr)
{
	q_ptr->front = 0;
	q_ptr->rear = 0;
}

int is_full(queue_type q)
{
	if (q.front == (q.rear + 1) % MAX_QUEUE_SIZE)
		return TRUE;
	else
		return FALSE;
}

int is_empty(queue_type q)
{
	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

void enqueue(queue_type_ptr q, element item)
{
	if (is_full(*q) == TRUE) //큐가 꽉 차있을때
		printf("큐가 꽉 차있습니다.");
	else {
		q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; //원형 구조를 구현하기 위해 인덱스 번호를 mod연산을 사용하여 입력
		q->queue[q->rear] = item;
	}
}

element dequeue(queue_type_ptr q)
{
	if (is_empty(*q) == TRUE)
		printf("큐가 비어있습니다.");
	else {
		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		int item = q->queue[q->front];

		return item;
	}
}
