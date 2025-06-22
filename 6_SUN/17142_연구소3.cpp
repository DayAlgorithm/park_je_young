/*
* Problem_Solving_Time AM 11:00 -12:23
* 
* ���̷����� Ȱ�� ���¿� ��Ȱ�� ����,
* 
* ù ��� ���̷����� ��Ȱ�� ����, Ȱ�� ������ ���̷�����
* 
* �����¿�� ������ ��� �� ĭ���� ���ÿ� ����,
* 
* 1�ʰ� �ɸ�.
* 
* ���̷��� m���� Ȱ�� ���·� ����,
* 
* 0 �� ĭ
* 1 ��
* 2 ���̷��� ��ġ
* 
* �׷� ���̷����� ������ virux_�̶�� �ϸ�,
* 
* (virus_)Cm ��ŭ ���� �����ϰ� �ȴ�,
* 
* ������ ũ�� -> 4<=n<=50
* 
* ���̷��� ���� -> 1<=m<=10
* 
* bfs �� ���� ������, ��ĭ�� ���� �Ѵ�,
* 
* �׵� ���� virus�� �ִ� ��ġ�� ���� ÷�ڸ� ������ ����
* 
* ��츦 ���� q�� push �ϰ� bfs �� �����ѵ� ���� time �� ��� 
* 
* ��Ʈ�ϴ� �������� ����.
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

// n�� �� m�� ����
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

                //��ĭ�� ��� �������� Ȯ��,
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
    
    // ���̷��� ��ġ ����
    combinations((int)virus.size(), m, [&](const vector<int>& comb) {
    
        for (int i : comb) {
        
            auto [vx, vy] = virus[i];
            
            q.emplace(vx, vy, 0);
        
        }
        
        time_stack.push_back(bfs());
        
        
        // �ʱ�ȭ
        q = queue<tuple<int, int, int>>();
        visited.assign(n, vector<bool>(n, false));
        });

    // �ּ� �ð� ��� �� ���
    sort(time_stack.begin(), time_stack.end());
 
    int ans = time_stack.front();

    cout << (ans >= 2501 ? -1 : ans);
    return 0;
}
