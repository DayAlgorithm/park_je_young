#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct Shark{
    int velo;
    int dir;
    int size;
};

pair<int,int> reposition(Shark temp, const int& x, const int& N){

    int d = temp.dir;

    int period = 2*(N - 1);

    int move = temp.velo % period;

    int raw0 = (d == 1 || d == 4)

               ? (x - 1) - move
               : (x - 1) + move;

    int raw = (raw0 % period + period) % period;

    int k = raw / (N - 1);

    int rem = raw % (N - 1);

    int re_x = (k % 2 == 0 ? rem : (N - 1) - rem) + 1;

    if (k % 2 == 1) {

        if (d == 1) d = 2;
        else if (d == 2) d = 1;
        else if (d == 3) d = 4;
        else if (d == 4) d = 3;

    }
    return {re_x, d};
    // 좌표, 방향
}

void moving(vector<vector<Shark>>& v, int Row, int Column){

    vector<vector<Shark>> new_grid(Row + 1, vector<Shark>(Column + 1, {0,0,0}));

    for(int i = 1; i <= Row; i++){

        for(int j = 1; j <= Column; j++){

            if (v[i][j].size > 0) {

                Shark cur = v[i][j];

                int d = cur.dir;

                bool checking_dir = (d >= 1 && d <= 2);

                auto [re_x, re_d] = checking_dir

                    ? reposition(cur, i, Row)
                    : reposition(cur, j, Column);

                int ni = checking_dir ? re_x : i;

                int nj = checking_dir ? j : re_x;

                if (new_grid[ni][nj].size < cur.size) {

                    new_grid[ni][nj] = {cur.velo, re_d, cur.size};

                }

                v[i][j] = {0,0,0};

            }
        }
    }

    v.swap(new_grid);

}

int get_shark(vector<vector<Shark>>& v, int n, int m){

    for(int i = 1; i <= n; i++){

        if (v[i][m].size > 0) {

            int sz = v[i][m].size;

            v[i][m] = {0,0,0};

            return sz;

        }

    }

    return 0;
}

int main(){

    int R, C, M;

    cin >> R >> C >> M;
    
    vector<vector<Shark>> shark(R + 1, vector<Shark>(C + 1, {0,0,0}));
    // 상어는 각 좌표마다, 크기와 속도를 가지고 있음.

    for(int i = 0; i < M; i++){
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        //{r, c, s, d, z} = { 행, 열 ,속도, 이동 방향, 크기}
        // d = {1 , 2, 3, 4} = {상 하 우 좌}
        shark[r][c] = {s, d, z};
    }

    int ans = 0;
    for(int t = 1; t <= C; t++){// t 는 시간.
        ans += get_shark(shark, R, t);
        moving(shark, R, C);
    }

    cout << ans;
    return 0;
}
