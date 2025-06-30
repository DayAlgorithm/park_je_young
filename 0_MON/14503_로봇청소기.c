#include<stdio.h>  
#include<stdlib.h>  
#include<stdbool.h>
#pragma warning(disable:4996)

int** map;  
int n, m;  
int x, y, dir;  
// d : { 0, 1, 2, 3 } : { »ó, ¿ì, ÇÏ, ÁÂ }  
// 3 0 1 2  
int dx[] = { -1,0,1,0 };  
int dy[] = { 0,1,0,-1 };  

int ans = 0;  

void search() {  
   while (true) {  
       if (map[x][y] == 0) {  
           ans++;  
           map[x][y] = -1;  
       }  

       bool moved = false;  
       for (int k = 0; k < 4; ++k) {  
           // 4 ¹æÇâ ¹Ý½Ã°è Å½»ö ÈÄ ºóÄ­ Ã£À½  
           dir = (dir + 3) % 4;  

           int nx = x + dx[dir], ny = y + dy[dir];  

           if (nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] == 0) {  
               x = nx;  
               y = ny;  
               moved = true;  
               break;  
           }  
       }  
       if (moved) continue;  

       // ºóÄ­ÀÌ ¸ðµÎ Ã¤¿öÁ® ÀÖÀ¸¸é ÈÄÁø ±â¾î  
       int back = (dir + 2) % 4;  

       int bx = x + dx[back], by = y + dy[back];  

       if (bx < 0 || bx >= n || by < 0 || by >= m || map[bx][by] == 1) break;  

       x = bx;  
       y = by;  
   }  

   return;  
}  

int main() {  
   scanf("%d%d%d%d%d", &n, &m, &x, &y, &dir);  
 
   map = (int**)malloc(n * sizeof(int*));  
   for (int i = 0; i < n; i++) {  
       map[i] = (int*)malloc(m * sizeof(int));  
   }  

   // 1 = brick, 0 = dirty, -1 = cleaned  
   for (int i = 0; i < n; i++) {  
       for (int j = 0; j < m; j++) {  
           scanf("%d", &map[i][j]);  
       }  
   }  

   search();  

   printf("%d", ans);

   return 0;  
}