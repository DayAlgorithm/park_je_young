/*

Problem_Solving_Time PM 1:35 - 3:18

�� �б⿡ ���� �� �ִ� ���� �� ���� ������ ����.

��� ������ �� �б� �׻� �����ȴ�.

�������� ������ M���� �ٿ� ���� �Է��� �ȴ�

�׷� ���� ������ ��� ���� ���Ҵ��� �Ǵ��ϰ�

dfs���� ���� ��带 �ٷ�� ������� �����Ѵ�.

(������ �̰� ���������̰�, Ǯ�� ���������� ���ٴ� ������ ���ϰ�

���������� ����߱��ߴ�..)



�ϴ� �Է½� x to y �� node �� �����Ѵ�.

��� ������ ��� ���� ū ������ �����Ѵ�.

�ֳĸ� ���߿� �񱳽� ū ������ ���� ���� ������

�� ��尡 ������ �ִ� �������� �갡 ��� ���� �ɷȴ��� 

�ּڰ����� �Ǵ��ϴµ�, �װ� �ȸ����� �����̴�.

��·�� �Ϲ��� ���� �����ǰ�, 

�� �Ϲ��� ��� + ���� ������ ���� ��带 �����Ѵ�.

�̶� ���������� ���Խ� ���ҵȴ�.

�ֳĸ� ���� �ϰ� ���� ������ ������ �ִٴ� �� �˷����

�̰� ���� �� �ִ��� ������ �Ǵ��� ���� �ϱ� �����̴�.

(÷�� ���������� �������� �ʰ� �׳� �������� ��带 2�� ������, o(n + e) ������ �ð����⵵��

������ �ڵ带 ¥������ �߸� Ǯ����.)

�׷� ���� ���� ���� + ��������� �̿��ؼ� ��� ������ ������Ʈ �� �Է��� �ϰ�

�� �ڿ� �� ����� ������ ����ϴ� �������� ����.

++ť���� ���°�� �����ϴ����� �˾ƾ� �ϹǷ�, deque �� �̿��ߴ�.

*/

#include<iostream>
#include<vector>
#include<deque>
#include<climits>
using namespace std;

vector<vector<int>>node;
vector<int>node_info;
vector<int>indegree;
deque<int>q;



void checking() {
	for (int i = 1; i < (int)indegree.size(); i++) {
		if (indegree[i] == 0) {
			node_info[i] = 1;
			q.push_back(i);
		}
	}
	while (!q.empty()) {
		int x = q.front();
		q.pop_front();
		for (int iter : node[x]) {
			
			indegree[iter]--;
			if (indegree[iter] == 0)
				q.push_back(iter);

			if (node_info[iter] > node_info[x] + 1 && !indegree[iter]) {
				node_info[iter] = node_info[x] + 1;
			}
			
		}
	}
}



int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	node.resize(n + 1);
	node_info.resize(n + 1, INT_MAX);
	node_info[1] = 1;
	indegree.assign(n + 1, 0);
	for (int i = 0; i < m; i++) {
		int start_, end_;
		cin >> start_ >> end_;

		node[start_].push_back(end_);

		indegree[end_]++;
	}

	checking();
	for (int i = 0; i < n; i++) {	
		cout << node_info[i + 1] << " ";
	}
	return 0;
}