/*
Problem_Solving_Time PM 09:04 - 10:40

������ �౸�� ������ ���� ���ӿ��� ȸ���� ����,

�� ������ ����� ���� �� ���� �ʾұ� ������ ȸ�� ���̿�

���� �𸣴� ����� ������, �� ����� ���ϸ� ��ΰ� ���� �� �� �ִ�.

�� ȸ���� �ٸ� ȸ����� ����� ������ ���� ������ �ް� �ȴ�.


ģ���� ������ 1������ �ļ� 

���� 

A - B - C - D, C - F

�� �ϸ�, C�� 2�� B�� 3�� A�� 4���� �ȴ�,

�״ϱ� � ��忡 �ɷ��ִ� ������ ������ ������ �Ǿ�����.

n ���� ���͸� �Ҵ��ϰ�,

n �� ������ ��� ������ ���� ģ������ ��� ������ �ִ´�

�׵� dist �� �����ϰ�, bfs �� ������.

dist �� -1 �� �ʱ�ȭ �ϰ�, �� dist �� �湮������ ��� �ϸ�

�Ÿ��� ���� �� �ش�.

�׸��� �Ÿ��� �ֱ� ���ؼ�
dist == -1 �̸�,

bfs �� ������ �Լ� ���ο���, 

dist[j] = dist[front] + 1; �� ���ش�

�̷��� �ϸ�, ��� ������ ��� ���� �� �Ÿ��� ��������

ģ�� ���� �Ÿ��� ��� ���� ���� �� �� �ִ�.

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