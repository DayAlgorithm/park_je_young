/*

Problem_Solving_Time AM 12:40 - PM 01:57

n 개의 컴퓨터로 구성된 네트워크

이들 중 몇 개의 컴퓨터들은 서로 네트워크 연결이 되어 있어

서로 다른 두 컴퓨터 간 통신이 가능하도록 되어 있다.

통신 할때에는 서로 직접 연결되어 있는 회선 or 회선과 다른 컴퓨터를 거쳐.

각 회선은 성능이 차이 날 수 있음.

직접 연결 되어 있는 회선을 사용할 경우 

그 회선 노드의 value 에 따라 시간 차이.

간접 연결일 시, 그 노드의 sum of values



해킹을 당할 시, 슈퍼컴퓨터에서 네트워크를 이용한

보안 패킷을 전송하는 방식을 사용하기로 함.

준비를 마친 뒤 관리자는 다시 네트워크를 복구하기로 함.

1. 해커가 다시 공격을 할 우려가 있기 때문에, 최소 개수의 회선만을 복구

네트워크를 복구한 후에 서로 다른 두 컴퓨터 간에 통신이 가능하도록 복구

2. 네트워크를 복구해서 통신이 가능하도록 만드는 것도 중요,

하지만 해커에게 공격을 받았을 때, 보안 패킷을 전송하는데 걸리는 시간도 중요.

따라서 슈퍼컴퓨터가 다른 컴퓨터들과 통신하는데 걸리는 최소 시간이,

원래의 네트워크에서 통신하는데 걸리는 최소 시간보단 커져선 안된다.



원래의 네트워크에 대한 정보가 주어 졌을때, 위의 조건을 만족하면서 네트워크를 복구하는

방법을 알아내는 프로그램 작성.


그럼 모든 컴퓨터를 연결하는데, 최소시간을 찾아야함.

루트 컴퓨터 노드는 설정 되어 있고, 그냥 최단 시간을 찾으면 끝나는 문제임.

고로 다익스트라를 사용해서 풀면 된다.

*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<long long, int> PR;

int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	
	vector<vector<PR>>graph(n + 1);
	// grapgh[x] = {y, z}
	// z is value by going x to y
	
	while (m--) {
		int x, y, z;
		cin >> x >> y >> z;
		graph[x].push_back({ y,z });
		graph[y].push_back({ x,z });
	}

	vector<long long>d(n + 1, 1e15);
	//value of root to x
	vector<int>p(n + 1, -1);
	//previous node,

	priority_queue<PR, vector<PR>, greater<PR>>pq;

	d[1] = 0;
	pq.push({ 0, 1 });

	while (!pq.empty()) {
		auto [dist, u] = pq.top();
		pq.pop();
		if (dist > d[u])continue;

		for (auto [v, w] : graph[u]) {
			long long Nxt = dist + w;
			if (Nxt < d[v]) {
				d[v] = Nxt;
				p[v] = u;
				pq.push({ Nxt , v });
			}
		}
	}
	vector<PR> ans;
	for (int i = 2; i <= n; i++)
		ans.push_back({ p[i],i });

	cout << ans.size() << "\n";
	for (auto [x, y] : ans)
		cout << x << " " << y << "\n";

	return 0;
}