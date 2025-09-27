#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<string> s(N);
    
    for(auto& iter : s)
        cin >> iter;

    vector<vector<int>> a(N, vector<int>(M));
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            a[i][j] = s[i][j] - '0';

    // 2D prefix sum: ps[y+1][x+1]
    vector<vector<long long>> ps(N+1, vector<long long>(M+1, 0));
    for (int i = 0; i < N; i++) {
        long long rowSum = 0;
        for (int j = 0; j < M; j++) {
            rowSum += a[i][j];
            ps[i+1][j+1] = ps[i][j+1] + rowSum;
        }
    }

    auto S = [&](int y1, int x1, int y2, int x2) -> long long {
        return ps[y2+1][x2+1] - ps[y1][x2+1] - ps[y2+1][x1] + ps[y1][x1];
    };

    ll ans = 0;

    for (int i = 0; i < M-2; i++) {
        for (int j = i+1; j < M-1; j++) {
            ll A = S(0, 0, N-1, i);
            ll B = S(0, i+1, N-1, j);
            ll C = S(0, j+1, N-1, M-1);
            ans = max(ans, A * B * C);
        }
    }

    for (int i = 0; i < N-2; i++) {
        for (int j = i+1; j < N-1; j++) {
            ll A = S(0, 0, i, M-1);
            ll B = S(i+1, 0, j, M-1);
            ll C = S(j+1, 0, N-1, M-1);
            ans = max(ans, A * B * C);
        }
    }

    for (int cutX = 0; cutX < M-1; cutX++) {
        for (int cutY = 0; cutY < N-1; cutY++) {
            ll A = S(0, 0, N-1, cutX);
            ll B = S(0, cutX+1, cutY, M-1);
            ll C = S(cutY+1, cutX+1, N-1, M-1);

            ll A_ = S(0, cutX+1, N-1, M-1);
            ll B_ = S(0, 0, cutY, cutX);
            ll C_ = S(cutY+1, 0, N-1, cutX);
            ans = max({ans, A * B * C, A_ * B_ * C_});
        }
    }

    for (int cutY = 0; cutY < N-1; cutY++) {
        for (int cutX = 0; cutX < M-1; cutX++) {
            ll A = S(0, 0, cutY, M-1);
            ll B = S(cutY+1, 0, N-1, cutX);
            ll C = S(cutY+1, cutX+1, N-1, M-1);

            ll A_ = S(cutY+1, 0, N-1, M-1);
            ll B_ = S(0, 0, cutY, cutX);
            ll C_ = S(0, cutX+1, cutY, M-1);
            ans = max({ans, A * B * C, A_ * B_ * C_});
        }
    }

    cout << ans;
    return 0;
}
