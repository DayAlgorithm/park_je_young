/*
* Problem_Solving_Time AM 11:00 -12:23
* 
* 바이러스는 활성 상태와 비활성 상태,
* 
* 첫 모든 바이러스는 비활성 상태, 활성 상태인 바이러스는
* 
* 상하좌우로 인접한 모든 빈 칸으로 동시에 복제,
* 
* 1초가 걸림.
* 
* 바이러스 m개를 활성 상태로 변경,
* 
* 0 빈 칸
* 1 벽
* 2 바이러스 위치
* 
* 그럼 바이러스의 갯수를 virux_이라고 하면,
* 
* (virus_)Cm 만큼 일을 수행하게 된다,
* 
* 연구소 크기 -> 4<=n<=50
* 
* 바이러스 개수 -> 1<=m<=10
* 
* bfs 를 통해 돌리며, 빈칸만 가게 한다,
* 
* 그뒤 나는 virus가 있는 위치에 대한 첨자를 조합을 통해
* 
* 경우를 나눠 q에 push 하고 bfs 를 수행한뒤 나온 time 을 모아 
* 
* 소트하는 형식으로 갔다.
* 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <numeric>

using namespace std;

int n, m, empty_total = 0;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

vector<vector<int>> v;
vector<vector<bool>> visited;
vector<pair<int, int>> virus;
queue<tuple<int, int, int>> q;
vector<int> time_stack;

// n개 중 m개 조합
template<typename F>
void combinations(int n, int m, F f) {

    if (m < 0 || m > n) return;

    vector<int> a(m);

    iota(a.begin(), a.end(), 0);

    while (true) {
  
        f(a);
        
        int i = m - 1;
        
        while (i >= 0 && a[i] == n - m + i) --i;
        
        if (i < 0) break;
        
        ++a[i];
        
        for (int j = i + 1; j < m; ++j)
            a[j] = a[j - 1] + 1;
    
    }
}

int bfs() {
    
    int time = 0;
    int filled = 0;
    while (!q.empty()) {
    
        auto [x, y, t] = q.front(); q.pop();
        
        for (int i = 0; i < 4; ++i) {
        
            int nx = x + dx[i];
            
            int ny = y + dy[i];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            
            if (visited[nx][ny] || v[nx][ny] == 1)continue;

            visited[nx][ny] = true;
            q.emplace(nx, ny, t + 1);

            if (v[nx][ny] == 0) {
                filled++;
                time = max(time, t + 1);

                //빈칸에 모두 퍼졌는지 확인,
                if (filled == empty_total)
                    return time;
            }
        }
    
    }
    
    return(filled == empty_total ? time : 2501);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
   
    cin >> n >> m;
    
    v.assign(n, vector<int>(n, 0));
    
    visited.assign(n, vector<bool>(n, false));
    
    for (int i = 0; i < n; ++i) {
    
        for (int j = 0; j < n; ++j) {
        
            cin >> v[i][j];
            
            if (v[i][j] == 2)
                virus.emplace_back(i, j);
            else if (v[i][j] == 0)
                empty_total++;
        }
    
    }
    
    // 바이러스 위치 조합
    combinations((int)virus.size(), m, [&](const vector<int>& comb) {
    
        for (int i : comb) {
        
            auto [vx, vy] = virus[i];
            
            q.emplace(vx, vy, 0);
        
        }
        
        time_stack.push_back(bfs());
        
        
        // 초기화
        q = queue<tuple<int, int, int>>();
        visited.assign(n, vector<bool>(n, false));
        });

    // 최소 시간 계산 및 출력
    sort(time_stack.begin(), time_stack.end());
 
    int ans = time_stack.front();

    cout << (ans >= 2501 ? -1 : ans);
    return 0;
}
