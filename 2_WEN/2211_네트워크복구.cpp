/*

Problem_Solving_Time AM 12:40 - PM 01:57

n ���� ��ǻ�ͷ� ������ ��Ʈ��ũ

�̵� �� �� ���� ��ǻ�͵��� ���� ��Ʈ��ũ ������ �Ǿ� �־�

���� �ٸ� �� ��ǻ�� �� ����� �����ϵ��� �Ǿ� �ִ�.

��� �Ҷ����� ���� ���� ����Ǿ� �ִ� ȸ�� or ȸ���� �ٸ� ��ǻ�͸� ����.

�� ȸ���� ������ ���� �� �� ����.

���� ���� �Ǿ� �ִ� ȸ���� ����� ��� 

�� ȸ�� ����� value �� ���� �ð� ����.

���� ������ ��, �� ����� sum of values



��ŷ�� ���� ��, ������ǻ�Ϳ��� ��Ʈ��ũ�� �̿���

���� ��Ŷ�� �����ϴ� ����� ����ϱ�� ��.

�غ� ��ģ �� �����ڴ� �ٽ� ��Ʈ��ũ�� �����ϱ�� ��.

1. ��Ŀ�� �ٽ� ������ �� ����� �ֱ� ������, �ּ� ������ ȸ������ ����

��Ʈ��ũ�� ������ �Ŀ� ���� �ٸ� �� ��ǻ�� ���� ����� �����ϵ��� ����

2. ��Ʈ��ũ�� �����ؼ� ����� �����ϵ��� ����� �͵� �߿�,

������ ��Ŀ���� ������ �޾��� ��, ���� ��Ŷ�� �����ϴµ� �ɸ��� �ð��� �߿�.

���� ������ǻ�Ͱ� �ٸ� ��ǻ�͵�� ����ϴµ� �ɸ��� �ּ� �ð���,

������ ��Ʈ��ũ���� ����ϴµ� �ɸ��� �ּ� �ð����� Ŀ���� �ȵȴ�.



������ ��Ʈ��ũ�� ���� ������ �־� ������, ���� ������ �����ϸ鼭 ��Ʈ��ũ�� �����ϴ�

����� �˾Ƴ��� ���α׷� �ۼ�.


�׷� ��� ��ǻ�͸� �����ϴµ�, �ּҽð��� ã�ƾ���.

��Ʈ ��ǻ�� ���� ���� �Ǿ� �ְ�, �׳� �ִ� �ð��� ã���� ������ ������.

��� ���ͽ�Ʈ�� ����ؼ� Ǯ�� �ȴ�.

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