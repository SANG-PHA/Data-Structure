#include <iostream>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

#define SIZE 100

vector< vector<int> > graph(SIZE, vector<int>()); //그래프 인접리스트로 구현
int indegree[SIZE] = { 0 }; //진입차수 배열
priority_queue<int, vector<int>, greater<int>> p_queue; //우선순위 큐

int N, M; //문제 수, 정보 수
int v1, v2; //비교 할 정점

void input();
void topo_sort(int N);

int main(void)
{
	input();
	topo_sort(N);

	return 0;
}

void input() 
{
	cout << "문제 수를 입력하시오(1 <= N <=100) : ";
	cin >> N;
	cout << "정보 수를 입력하시오(1 <= M <= 100) : ";
	cin >> M;


	//노드 간 우선순위 세팅
	for (int i = 0; i < M; i++) {
		cout << "먼저 풀어야 할 문제를 입력하시오(n n) : ";
		cin >> v1 >> v2;
		graph[v1].push_back(v2); //인접리스트 구성
		indegree[v2]++; //v2의 진입차수 1 증가
	}
}

void topo_sort(int N)
{
	//모든 정점에 대해
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0) //진입차수가 0이면
			p_queue.push(i); //우선순위 큐에 삽입

	
	while (!p_queue.empty()) { //우선순위 큐가 빌 때 까지
		int v = p_queue.top(); //현재 정점
		p_queue.pop(); //우선순위 큐에서 추출한 정점 삭제
		cout << v << " -> ";
		for (auto w : graph[v]) { //정점 v의 인접한 모든 정점에 대해
			indegree[w]--; //진입차수 --
			if (indegree[w] == 0) //진입차수가 0인 정점은
				p_queue.push(w); //우선순위 큐에 삽입
		}
	}
	cout << "\b\b\b";
}
