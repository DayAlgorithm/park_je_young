/*
* 
* Problem_Solving_Time AM 8:55 - 
* 
* S �� Y��
* 
* 7���� �л� ����,
* 
* 7���� �ڸ��� ���� ���� �ݵ�� ����
* 
* S�ķθ� ������ �ʿ�� ����, 
* 
* ������ ���ؼ��� S�İ� ������ ��������,
* 
* 7���� 4�� �̻��� S�Ŀ��� ��.
* 
* �ڸ���ġ���� �־�������, �� ��Ģ�� ��Ű�� ����Ǽ�?
* 
* 
* dfs Ž���� �Ѵ�, 
* 
* i ���� ������ �Ѵ�,
* 
* 7�� �ڸ��� ã�� ����, S�� 4���� stk++ ���ش�.
* 
* �̶�. ��Ʈ ����ŷ�� �Ѵ�,
* 
* visited masking �� 2^25 ������ �迭�� �Ҵ��ؾ� �ǰ�, �� id�� �湮 �ߴ��� ���ߴ���,
* 
* �� �������� ���������� �Ǵ��ؼ� ����� ã�� �������� ����.
* 
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;

vector<string> map;
// 5��5 ����

int dx[4] = { 0, 0, -1, 1 }, dy[4] = { 1, -1, 0, 0 };

const int FULL = 25;

vector<bool> visited_mask(1 << FULL,false); // mask�� �ߺ� �湮 ����

long long ans = 0;

// id�� ĭ�� 'S'������ ����

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
