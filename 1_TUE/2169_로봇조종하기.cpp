#include <iostream>
#include<vector>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;

typedef long long LL;

int main() {

    REAL;

    int n, m;
    cin >> n >> m;
    vector<vector<LL>> a(n + 1, vector<LL>(m + 1));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];

    vector<LL> dp_prev(m + 1), dp_curr(m + 1), l2r(m + 1), r2l(m + 2);

    dp_prev[1] = a[1][1];
    for (int j = 2; j <= m; ++j)
        dp_prev[j] = dp_prev[j - 1] + a[1][j];

    for (int i = 2; i <= n; ++i) {

        l2r[1] = dp_prev[1] + a[i][1];
        
        for (int j = 2; j <= m; ++j)
            l2r[j] = max(dp_prev[j], l2r[j - 1]) + a[i][j];

        r2l[m] = dp_prev[m] + a[i][m];
        
        for (int j = m - 1; j >= 1; --j)
            r2l[j] = max(dp_prev[j], r2l[j + 1]) + a[i][j];

        for (int j = 1; j <= m; ++j)
            dp_curr[j] = max(l2r[j], r2l[j]);

        swap(dp_prev, dp_curr);
    }

    cout << dp_prev[m];
    return 0;
}
