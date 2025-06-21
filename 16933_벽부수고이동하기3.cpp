/*
* 
* Problem_Solving_Time AM 10:30 - 11:30
* 
* 
* 이번 문제는, bfs 함수 내부와 같이
* 
* 조건 분기를 x, y, brick, 낮밤
* 
* 으로 하면 바로 풀린다.
* 
*/

#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<tuple>
#define MAX 1001
#define MAXK 10


using namespace std;


int n, m, k;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

//vector<vector<visited>>v;
vector<vector<bool>>map;



bool visited[MAX][MAX][MAXK + 1][2];//x, y, brick, day or night

int bfs() {
	queue<tuple<int,int,int,int>> q;
	//x, y, broken, time;


	q.emplace(0, 0, 0, 0);  // time=0 : 낮

	visited[0][0][0][0] = true;

	while (!q.empty()) {

		auto [x, y, b, t] = q.front(); q.pop();

		if (x == n - 1 && y == m - 1) return ++t;

		int day = t % 2;

		for (int dir = 0; dir < 4; dir++) {

			int nx = x + dx[dir], ny = y + dy[dir];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

			if (map[nx][ny]) {
				// 벽
				if (day == 0 && b < k && !visited[nx][ny][b + 1][1]) {

					visited[nx][ny][b + 1][1] = true;

					q.emplace( nx, ny, b + 1, t + 1 );

				}
				else if (day == 1) {
					// 밤에는 제자리 대기

					if (!visited[x][y][b][0]) {

						visited[x][y][b][0] = true;
						q.emplace( x, y, b, t + 1 );
					}

				}
			}
			else {
				// 빈 칸
				if (!visited[nx][ny][b][1 - day]) {
					visited[nx][ny][b][1 - day] = true;
					q.emplace( nx, ny, b, t + 1 );
				}
			}
		}
	}
	return -1;
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m >> k;

	map.assign(n, vector<bool>(m, false));

	for (int i = 0; i < n; i++) {
		string h;
		cin >> h;
		for (int j = 0; j < m; j++) {
			map[i][j] = (h[j] == '0' ? 0 : 1);
		}
	}

	cout << bfs();

	return 0;
}