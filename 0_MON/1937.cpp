#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin>>n;
	vector<vector<int>>map(n, vector<int>(n, 0));

	for(auto& iter : map){
		for(auto& iter1 : iter){
			cin>>iter1;
		}
	}

	int dx[] = {0, 0, -1, 1};
	int dy[] = {1, -1, 0, 0};
	
	vector<int>dp(n*n, 0);
	int max_ = 1;

	function<int(int,int)> dfs = [&](int i, int j) -> int {
        int id = i*n + j;
        if (dp[id] != 0) 
            return dp[id];

        dp[id] = 1;
        for(int k = 0; k < 4; ++k){
            int ni = i + dx[k], nj = j + dy[k];
            if (ni<0||nj<0||ni>=n||nj>=n) continue;
            if (map[ni][nj] > map[i][j]) {
                dp[id] = max(dp[id], dfs(ni,nj) + 1);
				max_ = max(max_, dp[id]);
			}
        }
        return dp[id];
    };
	for(int i = 0; i < n ; i++){
		for(int j = 0; j < n; j++)
		dfs(i,j);
	}
	cout<<max_;
}

