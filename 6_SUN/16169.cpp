#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main(){

	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> level(n, 0);
	vector<int> time(n, 0);
	vector<int>indegree(n, 0);
	vector<long long>dp(n, 0);
	vector<vector<pair<int ,int>>>adj(n);

	for(int i = 0; i < n; i++){
		cin >> level[i] >> time[i];

	}

	for(int i = 0; i < n; i++){
		dp[i] = time[i];
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(level[i] + 1 == level[j]){
				indegree[j]++;
				adj[i].emplace_back(j, (i - j) * (i - j));
			}
		}
	}

	queue<int>q;

	for(int i = 0; i < n; i++)
		if(!indegree[i])
			q.push(i);

	while(!q.empty()){

		int x = q.front();
		q.pop();

		for(auto[nxt, w] : adj[x]){
			dp[nxt] = max(dp[nxt], dp[x] + w + time[nxt]);
			if(--indegree[nxt] == 0){
				q.push(nxt);
			}
		}


	} cout << *max_element(dp.begin(), dp.end());
	
	return 0;
}