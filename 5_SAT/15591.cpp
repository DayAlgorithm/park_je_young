#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<pair<int ,int>>>adj;


vector<char>visited;
void dfs(int x, const int& MAXK, int currU, int& ans){

    if(visited[x]) return;

    if(MAXK <= currU) {ans++;}

    for(auto[nxt, nw] : adj[x]){
        
        visited[x] = 1;
        dfs(nxt, MAXK, min(currU, nw), ans);
        visited[x] = 0;

    }
    
}


int main(){

    cin.tie(0)->sync_with_stdio(0);

    int n, q;

    cin >> n >> q;
    visited.assign(n + 1, 0);

    adj.assign(n + 1, vector<pair<int ,int>>());

    for(int i = 0; i < n - 1; i++){
        int p, q, r;
        cin >> p >> q >> r;
        
        adj[p].emplace_back(q, r);
        adj[q].emplace_back(p, r);
        // r = p to q
    }
    for(int i = 0; i < q; i++){
        int k, v;
        cin >> k >> v;
        // k is minimum
        int printAns = 0;
        
        dfs(v, k, INT_MAX, printAns);

        cout << printAns - 1 <<'\n';
    }



    return 0;
}