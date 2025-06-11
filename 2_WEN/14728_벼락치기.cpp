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


	sort(temp.begin(), temp.end(), [](PR a, PR b) {

		if (a.second == b.second)return a.first < b.first;

		return a.second > b.second;

		});
	vector<long long> dp(t + 1, 0);
	for (int i = 0; i < n; i++) {
		int k = temp[i].first;
		int s = temp[i].second;
		for (int j = t; j >= k; j--) {
			dp[j] = max(dp[j], dp[j - k] + s);
		}
	}
	sort(dp.rbegin(), dp.rend());
	cout << dp[0];

	return 0;
}