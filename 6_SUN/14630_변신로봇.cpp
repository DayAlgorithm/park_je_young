/*
* PST AM 10:12 - AM 10:55
* 
* ���� �κ�,
* 
* ���� �ð� 1��
* 
* ��ǰ <down- �� -up> �κ�
* 
* 
* ��ǰ�� ���� -> ���ڷ�
* 
* �κ��� ���� -> �� ���ڵ��� ����.
* 
* ���ſ� �ʿ��� ���� �� ��ǰ���� ���� ���̸� ������ ���� ��
* 
* ���� ��� �κ��� ���� ���°� 123 �̰� �ٸ� ���°� 222���,
* 
* ���ſ� �ʿ��� ���� �� �ڸ��� �� ���� ���� ���̴�.
* 
* ���� ���� ���� ����ؼ� �±��̰� ���ϴ� ���� ���¸� ����� ����.
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
* �ٵ� ���� x to y �� �Է� ������,
* 
* x ���� y ���� ���µ� �ɸ��� cost �� minmize �ϹǷ�
* 
* �ᱹ ���۰� ���� + �ּ�ȭ �Ÿ� -> ���ͽ�Ʈ��
* 
* ���� �� �� �ִ�
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
		int d = (A[i] - '0') - (B[i] - '0');   // '0'���� ����!
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