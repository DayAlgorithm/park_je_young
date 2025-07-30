#include<string>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

using ll = long long;

static const ll MOD  = 1000000007;
static const ll BASE = 131;

// segtree = Hash + length;

struct SegTree {
    int n;
    vector<ll> tree;
    vector<ll>& powB;

    SegTree(const string& s, vector<ll>& _powB)
      : n(s.size()), powB(_powB) {
        tree.assign(4*n, 0);
        build(s, 1, 0, n-1);
    }

    void build(const string& s, int node, int l, int r) {
        if (l == r) {
            tree[node] = s[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(s, node<<1, l, mid);
        build(s, node<<1|1, mid+1, r);
        int lenR = r - mid;
        tree[node] = ( (tree[node<<1] * powB[lenR]) % MOD + tree[node<<1|1] ) % MOD;
    }

    // returns { hash(S[ql..qr]), length = qr-ql+1 };
    pair<ll,int> query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return {0, 0};
        if (ql <= l && r <= qr) {
            return { tree[node], r - l + 1 };
        }
        int mid = (l + r) >> 1;
        auto L = query(node<<1, l, mid, ql, qr);
        auto R = query(node<<1|1, mid+1, r,   ql, qr);
        ll h = ( (L.first * powB[R.second]) % MOD + R.first ) % MOD;
        return { h, L.second + R.second };
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;
    int n = S.size();

    //hash base
    vector<ll> powB(n+1, 1);
    for (int i = 1; i <= n; i++)
        powB[i] = powB[i-1] * BASE % MOD;
	
    SegTree st(S, powB);

    int N;
    cin >> N;
    vector<pair<ll,int>> dict;
    dict.reserve(N);
    for (int i = 0; i < N; i++) {
        string w;
        cin >> w;
        ll h = 0;
        for (char c : w) {
            h = (h * BASE + c) % MOD;
        }
        dict.emplace_back(h, w.size());
    }

    // dynamic_programing
    vector<bool> dp(n+1);
    dp[0] = true;
    for (int i = 0; i < n; i++) if (dp[i]) {
        for (auto& [h_word, len] : dict) {
            if (i + len > n) continue;
            auto [h_sub, sub_len] = st.query(1, 0, n-1, i, i+len-1);
            if (h_sub == h_word) {
                dp[i+len] = true;
            }
        }
    }

    cout << (dp[n] ? 1 : 0) << "\n";
    return 0;
}
