/*

Problem_Solving_time AM 11:00 - 12:40

������ �׷��� Ž���� ����� ��� �� �� ����

÷�� ���ٽÿ���, bfs �� dp �� �����Ͽ� ������ �Ͽ���

�ٵ� ÷�� �������� ���̽� ������ ����,

�ʹ� dp �� ���� �ҷ��� ���ϱ�

�ڵ带 ¥�µ� �ſ� �������.

�����ϴ� ����, �׳� ���ͽ�Ʈ��� ���°� �´ٰ� �����ߴ�.

�ֳĸ� �ִ� ��ο�, ���� ������ ����ġ�� �ɷ��ְ�,

�̸� ���ؼ� ������ ���°Ŷ�,,,

�ϴ� ���ͽ�Ʈ��� ¥���� �ڴ�.(�۾� �ð� AM 11:23)


���ͽ�Ʈ���

�׷������� ������ ����ġ�� ������

start_point to end_point

�� ���� ���� �ּ� ������

1���� �迭�� �����Ͽ�, ��� ���� ��������

�ٷιٷ� ���� �� �� �ִ�.


�ϴ� ����� ��带 �����Ͽ� ���� �ϰ�,

������ ����ġ�� ��ġ �ѵڿ�

���ͽ�Ʈ�� �Լ� ���ο��� ������ ��带 ���

�켱���� ť�� ���� �ִ´�,

�� �� ���� ������ �ٷιٷ� ����

������ ���������� �ʵ��� �ϴ� �÷��׸� �ǳ�

4�������� ��� ������ ť�� ���� �ִ´�.

*/


#include<iostream>
#include<vector>
#include<queue>


using namespace std;
int n;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
typedef pair<int, int>PR;
typedef priority_queue<pair<long long, PR>, vector<pair<long long, PR>>, greater<pair<long long, PR>>> MAKE;
vector<vector<long long>>small;
vector<vector<int>>map;

//  ���ͽ�Ʈ�� �Լ�
long long  DI() {
	small[0][0] = map[0][0];

	MAKE pq;

	pq.push({ small[0][0], {0,0} });

	while (!pq.empty()) {
		auto [dist, cnt] = pq.top();
		pq.pop();

		int x = cnt.first, y = cnt.second;

		if (small[x][y] < dist) continue;

		for (int m = 0; m < 4; m++) {
			int u = x + dx[m];
			int v = y + dy[m];
			if (u < 0 || u >= n || v < 0 || v >= n)
				continue;
			if (dist + map[u][v] < small[u][v]) {
				small[u][v] = dist + map[u][v];
				pq.push({ small[u][v], {u, v} });
			}
		}
	}
	return small[n - 1][n - 1];
}

int main(void) {

	int try_ = 1;

	while (1) {

		cin >> n;
		if (n == 0)break;

		map.assign(n, vector<int>(n));
		small.assign(n, vector<long long>(n, LLONG_MAX));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j]; 
			}
		}

		cout << "Problem " << try_++ << ": " << DI() << "\n";
	}

	return 0;
}
