//Problem_Solving_Time AM 10:40 -
//
// �׽�Ʈ ���̽� �Է�
// 1<=test_case<=100
// 
// ù ��° �ٿ� 3���� ���� n, m, t
// (������, ����, ������) �ĺ� ����
// 
// �� ��° �ٿ� 3���� ���� s, g ,h
// (���������� �����, ������1, ������2)
// 
// �Է½� m ���� �ٿ� �� ���� a, b, d �� �־���
// a,b<=n d<=1000
// a, b ���̿� ���� d �� ����� ����
// 
// t ���� �� �ٸ��� ���� x�� �־����µ�, t���� ������ �ĺ�
// 
// t ���� �������� ���� �ٸ� ��ġ, ��� s �� ���� �ʴ�
// 
// 
// ���� ��������� �ĺ��� ���� ���� �� ���Ѵ�
// �ڽ�Ʈ + �Ÿ� �ִ�
// 
// �׵ڿ� s,g �� �������� Ȯ���� �Ѵ�
// 
// ������ ���� ��쿣 ���ܸ� ��Ų��.
// 
// �״��� ����Ѵ�
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

//�ʱ갪 ���� ����

vector<vector<PR>>adj;
//����ġ ��������Ʈ
//ex) adj[u] = {v, w};
//weight of u to v

void di(int start, vector<int>& dist) {
	// ���ͽ�Ʈ�� ����

	dist.assign(n + 1, INF);
	//���� ����ġ���� �ϴ� INF �� �ʱ�ȭ ���ش�.

	dist[start] = 0;
	//ù ��ŸƮ�� 0 ���� ���ش�,
	//�̴� �ڱ� �ڽ��� ��Ī�ϱ� ����

	MAKE DI;
	// ���ͽ�Ʈ�� ���� �켱���� ť�� ����
	

	DI.push({ 0,start });
	//���� dist �� input ���ش�.

	while (!DI.empty()) {
		auto [cost, u] = DI.top();
		//Ÿ�� �߷����� cost �� �� ����� idx�� �޴´�


		DI.pop();
		//bfs ���� �պκ� ��


		if (cost > dist[u])continue;
		//�ִ� �ڽ�Ʈ�� ã�� ���� go-to

		for (auto [v, cmp_cost] : adj[u]) {

			int candinate = cost + cmp_cost;
			//���� �ִ� �ڽ�Ʈ�� �����ϸ�, 

			if (candinate < dist[v]) {
				//���� ���� ������Ʈ
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
		// if ( adj[u] = {v,w} => u ���� v ���µ� w ��ŭ �ɸ���

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
			//��尣 ����ġ ����
			//�����
		}

		vector<int>dist_s(n + 1), dist_g(n + 1), dist_h(n + 1);

		di(s, dist_s);
		di(g, dist_g);
		di(h, dist_h);

		// ���ͽ�Ʈ�� ����ؼ� ������ �Ʒ��� �Լ� ������
		// �����ϸ�,,,,
		// s ���� ������ ����ġ�� �յ�
		// g ���� ������ ����ġ �յ�
		// h ���� ������ ����ġ �յ�
		// di(start, backup_vector)
		
		set<int>print;
		//����� ���������̰�, ��¥�� ��ġ�� �������� �������� �����Ƿ�
		// set ����ؼ� ��������

		for (int i = 0; i < t; i++) {

			int can;
			cin >> can;

			//���� ������ �ް�, dist_[��ǥ��] �� �̿��Ͽ�
			// start ���� g-h road�� �������� Ȯ�����ش�.

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