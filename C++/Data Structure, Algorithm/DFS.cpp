// https://blog.naver.com/ndb796/221230944971
// 깊이 우선 탐색(Depth First Search; DFS)
// 너비 우선 탐색은 Queue, 깊이 우선 탐색은 Stack 사용

// 1. 스택의 최상단 노드를 확인한다.
// 2. 최상단 노드에게 방문하지 않은 인접 노드가 있으면 그 노드를 스택에 넣고 방문처리 한다. 방문하지 않은 인접 노드가 없으면 스택에서 최상단 노드를 제거한다.
#include <iostream>
#include <vector>

using namespace std;

int number = 7; // 노드 갯수
int c[8]; // 방문한 노드를 담을 스택
vector<int> a[8]; // 노드의 연결구조를 담을 트리

void dfs(int x) {
	if (c[x]) return;

	// 1. 스택의 최상단 노드를 방문 처리한다.
	c[x] = true;
	cout << x << ' ';

	// 2. 최상단 노드에게 방문하지 않은 인접 노드가 있으면 그 노드를 스택에 넣고 방문처리 한다. 
	for (int i = 0; i < a[x].size(); i++) {
		int y = a[x][i];
		dfs(y);
	}
}

int main(void) {
	a[1].push_back(2);
	a[2].push_back(1);

	a[1].push_back(3);
	a[3].push_back(1);

	a[2].push_back(3);
	a[3].push_back(2);

	a[2].push_back(4);
	a[4].push_back(2);

	a[2].push_back(5);
	a[5].push_back(2);

	a[3].push_back(6);
	a[6].push_back(3);

	a[3].push_back(7);
	a[7].push_back(3);

	a[4].push_back(5);
	a[5].push_back(4);

	a[6].push_back(7);
	a[7].push_back(6);

	dfs(1);
	return 0;
}