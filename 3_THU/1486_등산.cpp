/*
* 
* Problem_Solving_Time 
* AM 10:50 - 11:30
* 2�� : PM 1:00 - 1:37
* �������� ȣ���� 0,0 
* 
* �� ��ġ���� ���ų� ������, �̵��ϴµ� 1��
* 
* �� ��ġ���� ������, ����ġ�� k �� �Ҷ�, (x - k)^2�ɸ�.
* ���� ������ T �׸��� ��ο� ���� �ð� D�� �־�������, D������ �ð�����
* (�� ��ġ�� ������ ���� �������� T�����̸� �� �� ����.)
* �ö� �� �� �ִ� �ִ� ����?
* 
* �߰���, �� ������ ��Ű��, ���� ���� ������ ȣ�ڿ� ������ �ؾߵ�.
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
