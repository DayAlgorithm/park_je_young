#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

void Transpose(const vector<vector<int>>& x, vector<vector<int>>& y, const int& n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            y[j][i] = x[i][j];
        }
    }
}

vector<int> p1, p2;
vector<char> visited;
vector<vector<int>> sumnation;
int ans = 1e9;


void combination(int start, const int& n, int curL, int picked){


    if(picked + (n - start) < n/2) return;

    if(picked == n/2){

        int R = 0;
        for(int i = 0; i < n; i++){
            if(visited[i]) continue;
            for(int j = i + 1; j < n; j++){
                if(!visited[j]) R += sumnation[i][j];
            }
        }
        ans = min(ans, abs(curL - R));
        return;
    }

    for(int i = start; i < n; i++){
        if(visited[i]) continue;


        int add = 0;
        for(const int& k : p1){
            add += sumnation[i][k];
        }

        visited[i] = 1;
        p1.push_back(i);

        combination(i + 1, n, curL + add, picked + 1);

        p1.pop_back();
        visited[i] = 0;

        if(ans == 0) return;
    }
}

int main(){

    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> v(n, vector<int>(n, 0)), u;
    sumnation.assign(n, vector<int>(n, 0));
    visited.assign(n, 0);
    u = v;

    for(auto& row : v)
        for(int& x : row)
            cin >> x;


    Transpose(v, u, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            sumnation[i][j] = u[i][j] + v[i][j]; // = A[j][i] + A[i][j]
        }
    }


    visited[0] = 1;
    p1.push_back(0);

    combination(1, n, 0, 1);

    cout << ans;
    return 0;
}
