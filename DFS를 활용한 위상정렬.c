#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

#define SIZE 100

stack<int> st; //위상 정렬에 쓰일 스택
vector< vector<int> > graph(SIZE, vector<int>()); //그래프 인접리스트로 구현
bool visited[SIZE]; //dfs에 쓰일 visited 배열

int N, M; //사람 수, 비교 횟수
int v1, v2; //비교 할 정점

void input();
void dfs(int v);
void topo_sort(int N);

int main(void)
{
	input();
	topo_sort(N);

	return 0;
}

void input() 
{
	cout << "사람 수를 입력하시오(1 <= N <=100) : ";
	cin >> N;
	cout << "비교 횟수를 입력하시오(1 <= M <= 100) : ";
	cin >> M;


	//노드 간 우선순위 세팅
	for (int i = 0; i < M; i++) {
		cout << "비교 할 노드를 입력하시오(n n) : ";
		cin >> v1 >> v2;
		graph[v1].push_back(v2); //인접리스트 구성
	}
}

void dfs(int v)
{
	visited[v] = true; //방문한 정점 표시
	for (auto w : graph[v]) { //v에 인접한 모든 정점 w에 대해서
		if (!visited[w]) //방문하지 않았다면
			dfs(w); //dfs 실행
	}
	st.push(v); //dfs가 종료되는 정점은 stack에 추가
}


//dfs알고리즘을 통해 모든 정점을 방문하고, dfs가 종료되는 정점은 stack에 추가한다.
//stack에 입력된 정점을 역순으로 출력해주면 위상정렬의 한 가지 방법이 된다.
void topo_sort(int N)
{
	//방문하지 않은 모든 정점에 대해서 dfs실행
	for (int i = 1; i < N; i++)
		if(!visited[i])
			dfs(i);

	while (st.size() != 0) {
		cout << st.top() << " -> "; //스택에 쌓인 정점순서 반대로 출력
		st.pop(); //출력한 정점 삭제
	}
	cout << "\b\b\b";

}
