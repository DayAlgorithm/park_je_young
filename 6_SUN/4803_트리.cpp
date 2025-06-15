/*

Problem_Solving_Time : 
PM 1:25 - PM 2:45 // 1차 시도

PM 3:00 - PM 3:50 // 2차 시도

tree 를 세는 거 였다.

나는 테스트 케이스에서 

방향이 정해 진 줄 알아서

진입차수로 위상 정렬을 할려고 했으나,

그게 아니였다 그냥 무방향으로

bfs 를 돌리면 되는 것 이였다.

*/


#include <iostream>  
#include <vector>  
#include <queue>  
using namespace std;  

vector<vector<int>> v;  
vector<bool> visited;  

int bfs(int start) {  

// 
// 들어 갔지만 순환 : 1
// 
// 들어 가긴 했는데 비순환 트리 : 0
//
    queue<pair<int, int>> q; // {current, parent}
    visited[start] = true;
    q.push({ start, 0 });

    while (!q.empty()) {
        auto [u, p] = q.front(); q.pop();
        for (int w : v[u]) {
            if (!visited[w]) {
                visited[w] = true;
                q.push({ w, u });
            }
            else if (w != p) {
                // 이미 방문된 노드인데, 
                // 그 노드가 내 “부모”가 아니라면
                // 진짜 사이클이 있는 것
                return 1;
            }
        }
    }
    return 0;

}  

int main(void) {  
   ios::sync_with_stdio(false); 
   cin.tie(nullptr);

   int case_ = 0;  
   while (1) {  
       int n, m;  
       cin >> n >> m;  
       if (n == 0 && m == 0)  
           break;  

       v.assign(n + 1, vector<int>());  
       visited.assign(n + 1, false);  

       for (int x, y, i = 0; i < m; i++) {  
           cin >> x >> y;  
           v[x].push_back(y);  
           v[y].push_back(x);  
       }  
       int treeCount = 0, cycleCount = 0;
       for (int i = 1; i <= n; ++i) {
           if (!visited[i]) {
               int r = bfs(i);// 0 또는 1 리턴
               if (r == 1) ++cycleCount;
               else ++treeCount;
           }
       }
       int temp = treeCount;  
       cout << "Case " << ++case_ << ":";  
       if (temp > 1) {  
           cout << " A forest of " << temp << " trees.\n";  
       } else if (temp == 1) {  
           cout << " There is one tree.\n";  
       } else {  
           cout << " No trees.\n";  
       }  
   }  

   return 0;  
}