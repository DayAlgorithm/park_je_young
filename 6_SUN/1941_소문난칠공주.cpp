/*
* 
* Problem_Solving_Time AM 8:55 - 
* 
* S 파 Y파
* 
* 7명의 학생 구성,
* 
* 7명의 자리는 가로 세로 반드시 인접
* 
* S파로만 구성될 필요는 없음, 
* 
* 생존을 위해서는 S파가 우위를 가져야함,
* 
* 7명중 4명 이상은 S파여야 됨.
* 
* 자리배치도가 주어졌을때, 위 규칙을 지키는 경우의수?
* 
* 
* dfs 탐색을 한다, 
* 
* i 에서 시작을 한다,
* 
* 7번 자리를 찾아 갈때, S가 4개면 stk++ 해준다.
* 
* 이때. 비트 마스킹을 한다,
* 
* visited masking 은 2^25 정도의 배열을 할당해야 되고, 각 id를 방문 했는지 안했는지,
* 
* 즉 켜졌는지 꺼졌는지를 판단해서 결과를 찾는 방향으로 갔다.
* 
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;

vector<string> map;
// 5×5 격자

int dx[4] = { 0, 0, -1, 1 }, dy[4] = { 1, -1, 0, 0 };

const int FULL = 25;

vector<bool> visited_mask(1 << FULL,false); // mask별 중복 방문 방지

long long ans = 0;

// id번 칸이 'S'파인지 판정

bool isS(int id) {
    return map[id / 5][id % 5] == 'S';
    // 0 + id%5 ~ 5
}

void dfs(int mask, int scnt) {

   int cnt = bitset<25>(mask).count();
   if (cnt == 7) {
       if (scnt >= 4) ans++;
       return;
   }
   

   for (int i = 0; i < FULL; i++) {
       if (!(mask & (1 << i))) continue;
       
       int x = i / 5, y = i % 5;
       
       for (int d = 0; d < 4; d++) {
       
           int nx = x + dx[d], ny = y + dy[d];
           
           if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5) continue;
           
           int nid = nx * 5 + ny;
           
           if (mask & (1 << nid)) continue;
           
           int newMask = mask | (1 << nid);
           
           if (visited_mask[newMask]) continue;
           
           visited_mask[newMask] = true;
           
           dfs(newMask, scnt + (isS(nid) ? 1 : 0));
       
       }
   }
}

int main() {
    REAL;
    
    map.resize(5);
    
    for (int i = 0; i < 5; i++) {
        cin >> map[i];
    }
    
    for (int i = 0; i < FULL; i++) {
    
        int m = 1 << i;
        
        visited_mask[m] = true;
    
        dfs(m, isS(i) ? 1 : 0);
    
    }

    cout << ans << "\n";
    
    return 0;
}
