/*
Problem_Solving_Time AM 12:35 - 2:10
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> PR;


int main(void) {

	int n, t; // 과목 , 공부 가능 시간
	// 먼저 과목 점수 먼저, 그다음 공부시간 순으로 소트
	cin >> n >> t;

	vector<PR>temp(n);

	for (auto& iter : temp) {

		cin >> iter.first >> iter.second;

	}
	//저장 시 {공부 시간, 문제의 배점}
	// 문제의 배점 기준으로, 내림차순을 하고, 그뒤에 공부시간으로 오름차순을 한다.
	// 그뒤에 dp를 할 예정.


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