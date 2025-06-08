/*

Problem_Solving_time AM 11:00 - 12:40

문제는 그래프 탐색에 양방향 노드 인 것 같고

첨에 접근시에는, bfs 와 dp 를 응용하여 갈려고 하였다

근데 첨에 적었던거 케이스 오류도 나고,

너무 dp 로 접근 할려다 보니깐

코드를 짜는데 매우 힘들었다.

생각하던 와중, 그냥 다익스트라로 가는게 맞다고 생각했다.

왜냐면 최단 경로에, 간선 사이의 가중치가 걸려있고,

이를 피해서 끝까지 가는거라,,,

일단 다익스트라로 짜봐야 겠다.(글쓴 시각 AM 11:23)


다익스트라는

그래프에서 간선의 가중치의 합으로

start_point to end_point

로 가는 길의 최솟 값들을

1차원 배열에 저장하여, 어디서 어디로 가는지를

바로바로 답을 할 수 있다.


일단 양방향 노드를 설정하여 시작 하고,

간선의 가중치만 설치 한뒤에

다익스트라 함수 내부에서 최적의 노드를 골라

우선순위 큐에 집어 넣는다,

그 뒤 좋은 노드들을 바로바로 빼어

밖으로 삐져나오지 않도록 하는 플래그를 건너

4방향으로 노드 정보를 큐에 집어 넣는다.

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

//  다익스트라 함수
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
