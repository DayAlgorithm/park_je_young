/*

Problem_Solving_Time : 
PM 1:25 - PM 2:45 // 1�� �õ�

PM 3:00 - PM 3:50 // 2�� �õ�

tree �� ���� �� ����.

���� �׽�Ʈ ���̽����� 

������ ���� �� �� �˾Ƽ�

���������� ���� ������ �ҷ��� ������,

�װ� �ƴϿ��� �׳� ����������

bfs �� ������ �Ǵ� �� �̿���.

*/


#include <iostream>  
#include <vector>  
#include <queue>  
using namespace std;  

vector<vector<int>> v;  
vector<bool> visited;  

int bfs(int start) {  

// 
// ��� ������ ��ȯ : 1
// 
// ��� ���� �ߴµ� ���ȯ Ʈ�� : 0
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
                // �̹� �湮�� ����ε�, 
                // �� ��尡 �� ���θ𡱰� �ƴ϶��
                // ��¥ ����Ŭ�� �ִ� ��
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
               int r = bfs(i);// 0 �Ǵ� 1 ����
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