#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N; 
    cin >> N;
    vector<int> level(N+1), t(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> level[i] >> t[i];
    }

    
    vector<vector<pair<int,int>>> adj(N+1);
    vector<int> indeg(N+1, 0);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (level[i] + 1 == level[j]) {
                int cost = (i - j) * (i - j);
                adj[i].push_back({j, cost});
                indeg[j]++;
            }
        }
    }

    
    vector<long long> dp(N+1, 0);
    for (int i = 1; i <= N; i++) {
        if (indeg[i] == 0) 
			dp[i] = t[i];
    }

    
    queue<int> q;
    for (int i = 1; i <= N; i++) 
		if (indeg[i] == 0) 
			q.push(i);

    long long answer = 0;

    while (!q.empty()) {
        int u = q.front(); 
		
		q.pop();
        
		answer = max(answer, dp[u]);

        for (auto [v, w] : adj[u]) {

            dp[v] = max(dp[v], dp[u] + w + t[v]);

            if (--indeg[v] == 0) q.push(v);

        }
    }

    
	
    for (int i = 1; i <= N; i++) 
		answer = max(answer, dp[i]);

    cout << answer ;
    return 0;
}