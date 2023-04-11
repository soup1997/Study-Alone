// https://blog.naver.com/ndb796/221230944971
// ���� �켱 Ž��(Depth First Search; DFS)
// �ʺ� �켱 Ž���� Queue, ���� �켱 Ž���� Stack ���

// 1. ������ �ֻ�� ��带 Ȯ���Ѵ�.
// 2. �ֻ�� ��忡�� �湮���� ���� ���� ��尡 ������ �� ��带 ���ÿ� �ְ� �湮ó�� �Ѵ�. �湮���� ���� ���� ��尡 ������ ���ÿ��� �ֻ�� ��带 �����Ѵ�.
#include <iostream>
#include <vector>

using namespace std;

int number = 7; // ��� ����
int c[8]; // �湮�� ��带 ���� ����
vector<int> a[8]; // ����� ���ᱸ���� ���� Ʈ��

void dfs(int x) {
	if (c[x]) return;

	// 1. ������ �ֻ�� ��带 �湮 ó���Ѵ�.
	c[x] = true;
	cout << x << ' ';

	// 2. �ֻ�� ��忡�� �湮���� ���� ���� ��尡 ������ �� ��带 ���ÿ� �ְ� �湮ó�� �Ѵ�. 
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