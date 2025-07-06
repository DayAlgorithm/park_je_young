/*
* PST AM 10:12 - AM 10:55
* 
* 변신 로봇,
* 
* 제한 시간 1초
* 
* 부품 <down- 돈 -up> 로봇
* 
* 
* 부품의 상태 -> 숫자로
* 
* 로봇의 상태 -> 그 숫자들의 모임.
* 
* 변신에 필요한 돈은 각 부품들의 숫자 차이를 제곱한 것의 합
* 
* 예를 들어 로봇의 현재 상태가 123 이고 다른 상태가 222라면,
* 
* 변신에 필요한 돈은 각 자리를 밴 값의 제곱 합이다.
* 
* 돈을 가장 적게 사용해서 승균이가 원하는 변신 상태를 만들어 주자.
* 
* test - case 1
* 
* 
* 3
* 11
* 33
* 55
* 1 3
* 
* 2 * (1 - 3) ^2 + 2 * ( 3 - 5 ) ^2
* 
* 
* 근데 가는 x to y 로 입력 받을시,
* 
* x 에서 y 까지 가는데 걸리는 cost 를 minmize 하므로
* 
* 결국 시작과 종점 + 최소화 거리 -> 다익스트라
* 
* 임을 알 수 있다
* 
*/

#include<iostream>
#include<vector>
#include<string>
#include<queue>;

using namespace std;

typedef long long LL;

LL cost(const string& A, const string& B) {
	LL s = 0;
	for (size_t i = 0; i < A.size(); ++i) {
		int d = (A[i] - '0') - (B[i] - '0');   // '0'으로 보정!
		s += 1LL * d * d;
	}
	return s;
}


int main(void) {


	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;
	
	vector<string>h(n + 1);
	for (int i = 1; i <= n; i++){

		cin >> h[i];

	}

	vector < vector<pair<LL, int>>>adj(n + 1);

	int x, y; cin >> x >> y;
	
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			LL w = cost(h[i], h[j]);
			adj[i].emplace_back(w, j);
			adj[j].emplace_back(w, i);
		}
	}
	vector<LL>dist(n + 1, 1e10);

	priority_queue<pair<LL, int>, vector<pair<LL, int>>, greater<>>pq;

	dist[x] = 0;

	pq.emplace(dist[x], x);

	while (!pq.empty()) {

		auto [cnt_w, u] = pq.top(); pq.pop();

		if (cnt_w != dist[u])continue;

		for (auto [w, v] : adj[u]) {
			LL nw = cnt_w + w;

			if (dist[v] > nw) {
				dist[v] = nw;
				pq.emplace(nw, v);
			}
		}

	}

	cout << dist[y];

}