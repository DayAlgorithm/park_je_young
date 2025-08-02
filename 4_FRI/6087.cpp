#include<iostream>
#include<deque>
#include<vector>
#include<cstring>
#include<algorithm>
#include<tuple>

using namespace std;

int main(){

	vector<pair<int, int>>se;

	int h, w;

	cin >> w >> h;

	vector<string>v(h);

	for(auto& iter : v){
		cin >> iter; 
	}

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			if(v[i][j] == 'C')
				se.emplace_back(i, j);
	
	auto[sx, sy] = se.front();
	auto[ex, ey] = se.back();

	const int INF = 0x3f3f3f3f;
	int dist[101][101][4];
	memset(dist, 0x3f, sizeof(dist));
	int dx[] = {0, 0, -1, 1};
	int dy[] = {1, -1, 0, 0};
	
	// 0 1 2 3 : up, down, left, right
	deque<tuple<int, int, int>> dq;

	for(int d = 0; d < 4; d++){
		dist[sx][sy][d] = 0;
		dq.emplace_back(sx, sy, d);
	}
	
	while(!dq.empty()){
		auto [x, y, dir] = dq.front(); dq.pop_front();
		int cnt = dist[x][y][dir];

		for(int nd = 0; nd < 4; nd++){

			int nx = x + dx[nd], ny = y + dy[nd];

			if(nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
			if(v[nx][ny] == '*') continue;

			int w = (nd == dir ? 0 : 1);
			if(dist[nx][ny][nd] > cnt + w){
				dist[nx][ny][nd] = cnt + w;
				if(w == 0) dq.emplace_front(nx, ny, nd);
				else dq.emplace_back(nx, ny, nd);
			}
		}
	}

	int ans = INF;
	for(int d : {0, 1, 2, 3})
		ans = min(ans, dist[ex][ey][d]);
	cout << ans;

	return 0;
}