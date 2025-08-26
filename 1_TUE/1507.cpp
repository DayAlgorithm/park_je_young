#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
// floyd warshall

int main(){

    cin.tie(0)->sync_with_stdio(0);

    int n;

    cin >> n;

    vector<vector<int>>adj(n, vector<int>(n, 0)), check;
    check = adj;

    for(auto& iter : adj)
        for(int& i : iter)
            cin >> i;

    for(int i = 0; i < n; i++){
        for(int x = 0; x < n; x++){
            for(int y = 0; y < n; y++){
                if(x == i || y == i|| check[x][y]) continue;
                if(adj[x][y] > adj[x][i] + adj[i][y]){
                    cout << -1;
                    return 0;
                }
                if(adj[x][y] == adj[x][i] + adj[i][y]){
                    check[x][y] = 1;
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++){
            if(check[i][j])continue;
            ans += adj[i][j];
        }
    
    cout << ans;

    return 0;
}