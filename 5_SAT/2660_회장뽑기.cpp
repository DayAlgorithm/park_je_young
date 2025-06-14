/*
Problem_Solving_Time PM 09:04 - 10:40

월드컵 축구의 응원을 위한 모임에서 회장을 선출,

이 모임은 만들어 진지 얼마 되지 않았기 때문에 회원 사이에

서로 모르는 사람도 있지만, 몇 사람을 통하면 모두가 서로 알 수 있다.

각 회원은 다른 회원들과 가까운 정도에 따라 점수를 받게 된다.


친구의 간선을 1점으로 쳐서 

예로 

A - B - C - D, C - F

라 하면, C는 2점 B는 3점 A는 4점이 된다,

그니깐 어떤 노드에 걸려있는 간선의 갯수가 정답이 되어진다.

n 명의 벡터를 할당하고,

n 명 각각이 어디 누구랑 직접 친구인지 노드 정보를 넣는다

그뒤 dist 를 설정하고, bfs 를 돌린다.

dist 는 -1 로 초기화 하고, 이 dist 는 방문조건을 대신 하며

거리를 측정 해 준다.

그리고 거리를 넣기 위해선
dist == -1 이면,

bfs 를 돌리는 함수 내부에서, 

dist[j] = dist[front] + 1; 을 해준다

이렇게 하면, 어디서 어디까지 어느 정도 의 거리를 가지는지

친구 사이 거리가 어느 정도 인지 알 수 있다.

*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;



int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<vector<int>>a(n + 1);
	vector<long long>real(n + 1);
	
	
	int x = 0, y = 0;
	while (1) {
		cin >> x >> y;
		if (x == -1 && y == -1)break;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	long long mins_ = 1e6;
	for (int i = 1; i <= n; i++) {
		queue<int>k;
		vector<long long>dist(n + 1, -1);
		k.push(i);
		while (!k.empty()) {
			
			int f = k.front();
			k.pop();
			for (int v : a[f]) {
				if (dist[v] == -1) {
					dist[v] = dist[f] + 1;
					k.push(v);
				}
			}
		}

		real[i] = *max_element(dist.begin() + 1, dist.end());
		mins_ = min(mins_, real[i]);
	}
	vector<long long> print;
	for (int i = 1; i <= n; i++) {
		if (real[i] == mins_) {
			print.push_back(i);
		}
	}
	
	cout << mins_ << " " << print.size() << "\n";
	for (int iter : print) {
		cout << iter << " ";
	}
	return 0;
}