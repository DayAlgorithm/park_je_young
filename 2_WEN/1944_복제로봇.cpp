/*
* 
* Problem_Solving_Time AM 00:00 - 1:30
* 
* bfs를 이용해, start to key, key to key 의 간선 정보를 얻는다,
* 
* 그 뒤에 start 와 keys 의 노드를 설정하여, 
* 
* 각 노드의 간선 정보를 통해, MST 를 구한다,
* 
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)

typedef pair<int, int>PR;
typedef tuple<int, int, int>TP;

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int n, m;

PR start;
vector<PR>key;
vector<string>map;

int bfs(PR A, PR B) {

	queue<TP>q;
	vector<vector<bool>>visited(n, vector<bool>(n, false));
	
	
	auto [x1, y1] = A;
	auto [x2, y2] = B;

	q.emplace(x1, y1, 0);
	visited[x1][y1] = true;
	while (!q.empty()) {

		auto [x, y, t] = q.front(); q.pop();

		if (x == x2 && y == y2)return t;

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= n || ny >= n)continue;

			if (visited[nx][ny] || map[nx][ny] == '1')continue;

			visited[nx][ny] = true;

			q.emplace(nx, ny, t + 1);

		}

	}
	return -1;
}

//Kruskal

vector<int>parent;
vector<int>tier;

int find(int x) {
	return (parent[x] == x ? x : parent[x] = find(parent[x]));
}

bool uni(int x, int y) {

	x = find(x);
	y = find(y);

	if (x == y) return 0;

	if (tier[x] > tier[y])
		parent[y] = x;
	else if (tier[x] < tier[y])
		parent[x] = y;
	else {
		tier[x]++;
		parent[y] = x;
	}
	return 1;
}



int main(void) {
	
	REAL;

	cin >> n >> m;

	map.resize(n);
	for (auto& iter : map) {
		cin >> iter;

	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (map[i][j] == 'S') {
				start = { i,j };
			}
			else if (map[i][j] == 'K') {
				key.emplace_back(i, j);
			}

		}
	}

	vector<TP>adj;

	for (int i = 1; i <= m; i++) {
		int time = bfs(start, key[i - 1]);
		if (time == -1) {
			cout << -1;
			return 0;
		}
		adj.emplace_back(0, i, time);
	}

	for (int i = 1; i < m; i++) {
		for (int j = i + 1; j <= m; j++) {
			adj.emplace_back(i, j, bfs(key[i - 1], key[j - 1]));
		}
	}

	sort(adj.begin(), adj.end(), [](TP& A, TP& B) {
		return get<2>(A) < get<2>(B);
		});

	parent.assign(m + 1, 0);
	for (int i = 0; i <= m; i++)parent[i] = i;

	tier.assign(m + 1, 0);

	int keys = key.size();
	long long sum = 0;
	int using_key = 0;

	for (auto& k : adj) {
		auto [x, y, w] = k;
		if (uni(x, y)) {
			sum += w;
			if (++using_key == keys)break;
		}
	}

	cout << sum;
	
	

	return 0;
}