/*
* 
* Problem_Solving_Time 
*
* DAG 복습 시간 : PM 08:32 - 10:40
* 문제 실질적 풀이 시간 : 10:40 - 11:10 
* 
* N개의 백신, 각 백신은 1부터 N 까지의 번호로 구분,
* 
* 몇몇 백식은 선행 관계가 있어서, 어떤 백신을 접종하기 전에
* 
* 반드시 먼저 접종해야되는 백신이 존재, 
* 
* 이 백신들은 번호가 아주 잘 매겨져 있어서,
* 
* K번 백신 이전에 접종해야 하는 모든 백신의 번호는
* 
* 1 이상 K - 1이하임.
* ---------------------------------------------------------
*  A - > (5) - > B
* 위와 같은 백신이 주어 질 경우, 
* 
* A를 맞는 날 +1
* B에 가기전 A를 맞은 날 부터 5일을 기다려야 됨 +5
* 
* So, B를 맞기 위해선, 총 6일이 소효됨.
* ---------------------------------------------------------
* 
* 
* 
* 이때 최소 대기 시간은, 최대 7일 이며, 다음 과 같은경우
* 
* 부작용은 무시된다.
* 
* 
* ---------------------------------------------------------
* A - > (7) - > B
* 
* 1 + 7 = 8, 즉 총 8일 정도 B를 맞기 위한 선행조건 시간이
* 
* 필요하다, 하지만, 8일 뒤면 A 유효기간이 지나므로, A를 재접종을 해야 된다.
* 
* 이때는 A = 8일차 접종 -> B 9일차 접종으로 하여
* 
* 1 + 7 = 8 - > 9 로 간다. ( A - B - A - B )
* 
* 어느 선행점에서 시작해서, 
* 
* 최대한 빨리 모든 백신이 접종을 할 수 있도록 일정을 계획?
* 
* 바로 다익스트라,
* 
* 시작점과 종점이 이미 정해져 있음. 은 아니고, 
* 
* DAG 이다, 왜냐면 여러 시작점에서 출발해서 한 도착지로 가는데에 걸리는걸
* 
* 찾아야 하기 때문이다.
* 
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#define REAL std::ios::sync_with_stdio(false); std::cin.tie(nullptr)

using namespace std;

typedef long long LL;

int main() {
	REAL;

	LL n, m, m_v = 1;
	cin >> n >> m;

	vector<vector<pair<LL,LL>>>node(n + 1);
	vector<LL>indegree(n + 1, 0);
	vector<LL>dp(n + 1, 1);
	queue<LL>q;

	for (LL x, y, w, i = 0; i < m; i++) {
		cin >> x >> y >> w;
		node[x].emplace_back(y,w);
		indegree[y]++;
	}

	for (LL i = 1; i < n + 1; i++) {
		if (indegree[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		
		LL u = q.front(); q.pop();

		for (auto iter : node[u]) {

			auto [v, w] = iter;
            //dp[v] = max(dp[v], (w == 7 ? dp[u] + 8 : dp[u] + w));
			
			dp[v] = max(dp[v], dp[u] + w + (w >= 7 ? 1 : 0));

			if (--indegree[v] == 0) {
				q.push(v);
			}

		}
	}
	for (int i = 1; i <= n; i++)
		m_v = max(m_v, dp[i]);
	cout << m_v;
}