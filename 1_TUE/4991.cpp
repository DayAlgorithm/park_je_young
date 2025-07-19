#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple>
#include <climits>
#include <bit>

using namespace std;
typedef pair<int,int> PR;
typedef long long LL;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

// Gosper’s hack 같은 개수의 1비트를 가진 다음 마스크 계산
LL next_gosper(LL x) {
    LL u = x & -x;
    LL v = x + u;
    if (v == 0) return 0;
    return v + (((v ^ x) / u) >> 2);
}

int ctzll_manual(unsigned long long x) {
    if (x == 0) return 64;
    int n = 0;
    while ((x & 1ULL) == 0) {
        x >>= 1;
        ++n;
    }
    return n;
}

//최하위 1비트 얻기
int ctzll(unsigned long long x) {
    if (x == 0) return 64;
    return (int)ctzll_manual(x);
}

// n개 중 k개 뽑기 조합 (k==2 한정) (i,j) 쌍 반환
vector<PR> combinations_pairs(int n, int k) {
    vector<PR> res;
    if (k != 2 || n < 2) return res;
    unsigned long long mask  = (1ULL << k) - 1;
    unsigned long long limit = (1ULL << n);
    while (mask < limit && mask != 0) {
        int i = ctzll(mask);
        int j = ctzll(mask & (mask - 1));
        res.emplace_back(i, j);
        mask = next_gosper(mask);
    }
    return res;
}

int bfs(const vector<string>& mp, PR st, PR ed, int R, int C) {
    auto [sx, sy] = st;
    auto [ex, ey] = ed;
    queue<tuple<int,int,int>> q;
    vector<vector<bool>> vis(R, vector<bool>(C, false));

    q.emplace(sx, sy, 0);
    vis[sx][sy] = true;
    while (!q.empty()) {
        auto [x, y, t] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
            if (mp[nx][ny] == 'x') continue;
            if (vis[nx][ny]) continue;
            if (nx == ex && ny == ey) return t + 1;
            vis[nx][ny] = true;
            q.emplace(nx, ny, t + 1);
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int C, R;
        cin >> C >> R;
        if (C == 0 && R == 0) break;

        vector<string> mp(R);
        for (int i = 0; i < R; i++) cin >> mp[i];

        PR start;
        vector<PR> dirty;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (mp[i][j] == 'o') start = {i, j};
                else if (mp[i][j] == '*') dirty.emplace_back(i, j);
            }
        }

        vector<PR> node;
        node.push_back(start);
        for (auto& p : dirty) node.push_back(p);

        int sz = node.size();
        if (sz == 1) {
            cout << 0 << "\n";
            continue;
        }

        // 노드 간 최단거리 행렬 계산
        vector<vector<int>> dist(sz, vector<int>(sz, 0));
        bool impossible = false;
        for (auto [i, j] : combinations_pairs(sz, 2)) {
            int d = bfs(mp, node[i], node[j], R, C);
            if (d < 0) { impossible = true; break; }
            dist[i][j] = dist[j][i] = d;
        }
        if (impossible) {
            cout << -1 << "\n";
            continue;
        }

        // 비트마스크 DP: dp[mask][i]
        int N = sz;
        int FULL = (1 << N) - 1;
        const int INF = INT_MAX / 2;
        vector<vector<int>> dp(1 << N, vector<int>(N, INF));
        dp[1 << 0][0] = 0;

        for (int mask = 0; mask <= FULL; mask++) {
            for (int i = 0; i < N; i++) {
                if (!(mask & (1 << i))) continue;
                int cur = dp[mask][i];
                if (cur >= INF) continue;
                for (int j = 0; j < N; j++) {
                    if (mask & (1 << j)) continue;
                    int nxt = mask | (1 << j);
                    dp[nxt][j] = min(dp[nxt][j], cur + dist[i][j]);
                }
            }
        }

        int ans = INF;
        for (int i = 0; i < N; i++) {
            ans = min(ans, dp[FULL][i]);
        }
        cout << (ans >= INF ? -1 : ans) << "\n";
    }

    return 0;
}
