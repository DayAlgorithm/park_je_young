/*

Problem_Solving_Time AM 08:32 - 09:50

¼±Çü Å½»ö

*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int, int> PR;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int c, r, k;

	cin >> c >> r;

	//column, row;

	vector<vector<int>>map;
	map.assign(r + 1, vector<int>(c + 1, 0));

	vector<PR>d(4);

	d[0] = { 1, 0 };//¹Ø
	d[1] = { 0, 1 };//¿À
	d[2] = { -1, 0 };//À§
	d[3] = { 0,-1 };//¿Þ
	
	vector<vector<bool>>visited(r + 1, vector<bool>(c + 1, false));

	queue<PR>q;
	q.push(make_pair(1, 1));
	int dir = 0, stack = 1;
	cin >> k;
	if (k > r * c) {
		cout << 0;
		return 0;
	}
	while (!q.empty()) {
		int u = q.front().first;
		int v = q.front().second;
		q.pop();
		visited[u][v] = true;
		map[u][v] = stack++;
		
		if (stack - 1 == k) {
			cout << v <<" " << u;
			return 0;
		}
		
		
		int x = u + d[dir % 4].first;
		int y = v + d[dir % 4].second;

		if (x < 1 || y < 1 || x > r || y > c || visited[x][y] ) {
			
			dir++;
			x = u + d[dir % 4].first;
			y = v + d[dir % 4].second;
		}

		q.push(make_pair(x,y));

	}
}