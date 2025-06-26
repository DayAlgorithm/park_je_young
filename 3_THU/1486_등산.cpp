/*
* 
* Problem_Solving_Time 
* AM 10:50 - 11:30
* 2차 : PM 1:00 - 1:37
* 세준이의 호텔은 0,0 
* 
* 현 위치보다 낮거나 같으면, 이동하는데 1초
* 
* 현 위치보다 높으면, 현위치를 k 라 할때, (x - k)^2걸림.
* 산의 지도와 T 그리고 어두워 지는 시간 D가 주어졌을때, D이하의 시간동안
* (현 위치와 갈려는 곳의 높이차가 T이하이면 갈 수 있음.)
* 올라 갈 수 있는 최대 높이?
* 
* 추가로, 위 조건을 지키며, 밤이 지기 전까지 호텔에 도착을 해야됨.
* 
* 
* djikstra correct + reverse, and comparison sorted time( time += up_time + down_time) 
* 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)
typedef pair<int, int> PR;
typedef tuple<long long, int, int> TP;

int n, m, time_, d;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

vector<vector<int>> map;
vector<vector<PR>> dist;
vector<vector<long long>> best, best_back;

void bfs() {
    priority_queue<TP, vector<TP>, greater<TP>> q;
    best.assign(n, vector<long long>(m, LLONG_MAX));
    best[0][0] = 0;
    q.emplace(0, 0, 0);
    while (!q.empty()) {
        auto [t, x, y] = q.top(); q.pop();
        if (t > best[x][y]) continue;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            
            int dh = map[nx][ny] - map[x][y];
            
            if (abs(dh) > time_) continue;
            
            long long cost = (dh > 0 ? 1LL * dh * dh : 1LL);
            
            long long nt = t + cost;
            
            if (nt < best[nx][ny]) {
            
                best[nx][ny] = nt;
                
                q.emplace(nt, nx, ny);
            
            }
        
        }
    
    }

}

void rbfs() {
    priority_queue<TP, vector<TP>, greater<TP>> q;

    best_back.assign(n, vector<long long>(m, LLONG_MAX));
    
    best_back[0][0] = 0;
    
    q.emplace(0, 0, 0);
    
    while (!q.empty()) {
    
        auto [t, x, y] = q.top(); q.pop();
        
        if (t > best_back[x][y]) continue;
        
        for (int i = 0; i < 4; i++) {
        
            int nx = x + dx[i], ny = y + dy[i];
            
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            
            int dh = map[x][y] - map[nx][ny];
            
            if (abs(dh) > time_) continue;
            
            long long cost = (dh > 0 ? 1LL * dh * dh : 1LL);
            
            long long nt = t + cost;
            
            if (nt < best_back[nx][ny]) {
            
                best_back[nx][ny] = nt;
                
                q.emplace(nt, nx, ny);
            
            }
        
        }
    
    }

}

int main() {

    REAL;
    
    cin >> n >> m >> time_ >> d;
    
    map.assign(n, vector<int>(m));
    dist.assign(n, vector<PR>(m, { 0, INT_MAX }));
    
    for (int i = 0; i < n; i++) {
        string h;
        cin >> h;
        for (int j = 0; j < m; j++) {
            if (h[j] >= 'A' && h[j] <= 'Z') map[i][j] = h[j] - 'A';
            else map[i][j] = h[j] - 'a' + 26;
        }
    }
    
    bfs();

    rbfs();
    
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < m; j++) {
        
            long long t1 = best[i][j], t2 = best_back[i][j];
            
            if (t1 == LLONG_MAX || t2 == LLONG_MAX) continue;
            
            long long total = (t1 + t2);
            
            dist[i][j] = { map[i][j], total };
        }
    
    }
    
    int MaxMize = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[i][j].second > d) continue;
            MaxMize = max(MaxMize, dist[i][j].first);
        }
    }
    cout << MaxMize;
    return 0;
}
