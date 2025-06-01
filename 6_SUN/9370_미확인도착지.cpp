//Problem_Solving_Time AM 10:40 -
//
// 테스트 케이스 입력
// 1<=test_case<=100
// 
// 첫 번째 줄에 3개의 정수 n, m, t
// (교차로, 도로, 목적지) 후보 갯수
// 
// 두 번째 줄에 3개의 정수 s, g ,h
// (예술가들의 출발지, 교차로1, 교차로2)
// 
// 입력시 m 개의 줄에 각 정수 a, b, d 가 주어짐
// a,b<=n d<=1000
// a, b 사이에 길이 d 의 양방향 도로
// 
// t 개의 각 줄마다 정수 x가 주어지는데, t개의 목적지 후보
// 
// t 개의 지점들은 서로 다른 위치, 모두 s 와 같지 않다
// 
// 
// 먼저 출발지에서 후보지 까지 가는 걸 구한다
// 코스트 + 거리 최단
// 
// 그뒤에 s,g 를 지나는지 확인을 한다
// 
// 지나지 않을 경우엔 제외를 시킨다.
// 
// 그다음 출력한다
// 
//
#include<iostream>  
#include<vector>  
#include<queue>  
#include<stdlib.h>  
#include<algorithm>
#include<set>

using namespace std;

typedef pair<int, int>PR;

typedef priority_queue < PR,vector<PR>, greater<PR>>MAKE;

int n, m, t;
int s, g, h;
const int INF = 1e9;

//초깃값 설정 변수

vector<vector<PR>>adj;
//가중치 인접리스트
//ex) adj[u] = {v, w};
//weight of u to v

void di(int start, vector<int>& dist) {
	// 다익스트라 공장

	dist.assign(n + 1, INF);
	//간선 가중치들은 일단 INF 로 초기화 해준다.

	dist[start] = 0;
	//첫 스타트는 0 으로 해준다,
	//이는 자기 자신을 지칭하기 때문

	MAKE DI;
	// 다익스트라를 위한 우선순위 큐를 설정
	

	DI.push({ 0,start });
	//시작 dist 를 input 해준다.

	while (!DI.empty()) {
		auto [cost, u] = DI.top();
		//타입 추론으로 cost 와 그 노드의 idx를 받는다


		DI.pop();
		//bfs 마냥 앞부분 팝


		if (cost > dist[u])continue;
		//최단 코스트를 찾기 위한 go-to

		for (auto [v, cmp_cost] : adj[u]) {

			int candinate = cost + cmp_cost;
			//만약 최단 코스트를 성공하면, 

			if (candinate < dist[v]) {
				//누적 간선 업데이트
				dist[v] = candinate;

				DI.push({ candinate,v });

			}
		}
	}
}

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int test_case;
	cin >> test_case;
	while (test_case--) {

		
		cin >> n >> m >> t;
		adj.clear();
		adj.resize(n + 1);
		// if ( adj[u] = {v,w} => u 에서 v 가는데 w 만큼 걸린다

		vector<int>dist(n + 1, 1000);

		cin >> s >> g >> h;
		// start_node, g-h road  
		dist[s] = 0;

		int weight_gh = 0;
		for (int i = 0; i < m; i++) {
			int a, b, d;
			cin >> a >> b >> d;
			adj[a].push_back({ b,d });
			adj[b].push_back({ a,d });
			if ((a == g && b == h) || (a == h && b == g)) {
				weight_gh = d;
			}
			//노드간 가중치 설정
			//양방향
		}

		vector<int>dist_s(n + 1), dist_g(n + 1), dist_h(n + 1);

		di(s, dist_s);
		di(g, dist_g);
		di(h, dist_h);

		// 다익스트라 사용해서 위에서 아래로 함수 선언을
		// 정리하면,,,,
		// s 부터 시작한 가중치의 합들
		// g 부터 시작한 가중치 합들
		// h 부터 시작한 가중치 합들
		// di(start, backup_vector)
		
		set<int>print;
		//출력은 오름차순이고, 어짜피 곂치는 도착노드는 존재하지 않으므로
		// set 사용해서 오름차순

		for (int i = 0; i < t; i++) {

			int can;
			cin >> can;

			//도착 노드들을 받고, dist_[목표점] 을 이용하여
			// start 에서 g-h road를 지나는지 확인해준다.

			if (dist_s[can] == dist_s[g] + weight_gh + dist_h[can] || dist_s[can] == dist_s[h] + weight_gh + dist_g[can]) {
				print.insert(can);
			}

		}
		for (auto i : print) {
			cout << i << " ";
		}cout << "\n";
	}

	return 0;
}