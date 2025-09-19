#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

vector<int>v;
int t, w;
int ans = 0;
int dp[1001][31][2];
int solve(int time, int dir, int currW) {
    if (time == t) 
        return 0;
    int &ret = dp[time][currW][dir];

    if (ret != -1) return ret;
    
    ret = 0;
    
    if (currW > 0) 
    ret = max(ret, (v[time] == (1 - dir) + 1) + solve(time + 1, 1 - dir, currW - 1));
    ret = max(ret, (v[time] == dir + 1) + solve(time + 1, dir, currW));
    return ret;
}
int main(){
    
    cin.tie(0)->sync_with_stdio(0);

    cin >> t >> w;
    
    memset(dp, -1, sizeof(dp));
    v.assign(t, 0);

    for(int& i : v)
        cin >> i;

    cout << solve(0,0,w);
    return 0;
}