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

	vector<long long> dp(t + 1, 0);
	for (int i = 0; i < n; i++) {
		int k = temp[i].first;
		int s = temp[i].second;

		//k 는 시간, s 는 점수 이다.
		//
		// 이때 시간에 따른 배열 을 설정해 준다 ( dp )
		// 
		// 어떠한 시간이 k 라는 시간 내에서 t - k에 해당하는 점수 + k시간대 점수와 j 일때의 점수와 비교하여
		// 
		// 큰값을 dp[j]에 저장을 해준다, 그러면 bottom-up 형식의 dp 가 형성되고, 이를 통해 최적의 점수를 얻는
		// 
		// 로직이 형성된다.
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