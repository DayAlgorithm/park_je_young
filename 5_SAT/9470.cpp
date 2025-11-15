#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int K, M, P;
        cin >> K >> M >> P; 
        vector<int> indegree(M + 1, 0);
        vector<vector<int>> adj(M + 1);
        vector<int> strOrder(M + 1, 0);
        vector<int> currMax(M + 1, 0);
        vector<int> maxCount(M + 1, 0);

        for(int i = 0; i < P; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].emplace_back(v);
            indegree[v]++;
        }

        queue<int>q;
        for(int i = 1; i <= M; i++) {
            if(!indegree[i]) { 
                q.emplace(i); 
                strOrder[i] = 1; 
            }
        }

        while(!q.empty()) {
            int x = q.front(); q.pop();
            int order = strOrder[x]; 

            for(int it : adj[x]) {
                if (order > currMax[it]) {
                    currMax[it] = order;
                    maxCount[it] = 1;
                } else if (order == currMax[it]) {
                    maxCount[it]++;
                }
                
                indegree[it]--;

                if (!indegree[it]) {
                    if (maxCount[it] >= 2) {
                        strOrder[it] = currMax[it] + 1;
                    } else {
                        strOrder[it] = currMax[it];
                    }
                    q.emplace(it);
                }
            }
        }
        cout << K << " " << strOrder[M] << "\n";
    }
    return 0;
}