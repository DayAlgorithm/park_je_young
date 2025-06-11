/*
Problem_Solving_Time AM 12:35 - 2:10
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> PR;


int main(void) {

	int n, t; // ���� , ���� ���� �ð�
	// ���� ���� ���� ����, �״��� ���νð� ������ ��Ʈ
	cin >> n >> t;

	vector<PR>temp(n);

	for (auto& iter : temp) {

		cin >> iter.first >> iter.second;

	}
	//���� �� {���� �ð�, ������ ����}
	// ������ ���� ��������, ���������� �ϰ�, �׵ڿ� ���νð����� ���������� �Ѵ�.
	// �׵ڿ� dp�� �� ����.

	vector<long long> dp(t + 1, 0);
	for (int i = 0; i < n; i++) {
		int k = temp[i].first;
		int s = temp[i].second;

		//k �� �ð�, s �� ���� �̴�.
		//
		// �̶� �ð��� ���� �迭 �� ������ �ش� ( dp )
		// 
		// ��� �ð��� k ��� �ð� ������ t - k�� �ش��ϴ� ���� + k�ð��� ������ j �϶��� ������ ���Ͽ�
		// 
		// ū���� dp[j]�� ������ ���ش�, �׷��� bottom-up ������ dp �� �����ǰ�, �̸� ���� ������ ������ ���
		// 
		// ������ �����ȴ�.
		//

		for (int j = t; j >= k; j--) {
			dp[j] = max(dp[j], dp[j - k] + s);
		}
	}
	long long answer = 0;
	for (long long i : dp)answer = max(answer, i);
	cout << answer;

	return 0;
}