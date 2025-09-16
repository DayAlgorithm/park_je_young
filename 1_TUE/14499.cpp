#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int dx[]=  {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, x, y, k;
    cin >> n >> m >> x >> y >> k;

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    // dice: 0=top, 1=bottom, 2=north, 3=south, 4=east, 5=west
    int d[6] = {0,0,0,0,0,0};

    auto roll_e = [&]() {
        int t = d[0];
        d[0] = d[5];
        d[5] = d[1];
        d[1] = d[4];
        d[4] = t;
    };
    auto roll_w = [&]() {
        int t = d[0];
        d[0] = d[4];
        d[4] = d[1];
        d[1] = d[5];
        d[5] = t;
    };
    auto roll_n = [&]() {
        int t = d[0];
        d[0] = d[3];
        d[3] = d[1];
        d[1] = d[2];
        d[2] = t;
    };
    auto roll_s = [&]() {
        int t = d[0];
        d[0] = d[2];
        d[2] = d[1];
        d[1] = d[3];
        d[3] = t;
    };

    while (k--) {
        int q; 
        cin >> q;

        int nx = x, ny = y;
        if (q == 1) ny++;
        else if (q == 2) ny--;
        else if (q == 3) nx--;
        else if (q == 4) nx++;
        else continue;

        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

        if (q == 1) roll_e();
        else if (q == 2) roll_w();
        else if (q == 3) roll_n();
        else if (q == 4) roll_s();

        x = nx; y = ny;

        if (a[x][y] == 0) {
            a[x][y] = d[1];
        } else {
            d[1] = a[x][y];
            a[x][y] = 0;
        }

        cout << d[0] << '\n';
    }
    return 0;
}
