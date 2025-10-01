#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    string h;
    cin >> n >> h;

    const int sz = (int)h.size();

    if (count(h.begin(), h.end(), h.front()) == sz) {
        cout << h;
        return 0;
    }

    vector<int> p;
    p.reserve(sz);
    for (int i = 0, j = sz - 1; i <= j; i++, j--) {
        p.push_back(i);
        if (i != j) p.push_back(j);
    }

    string res(sz, ' ');

    vector<char> vis(sz, 0);

    for (int s = 0; s < sz; s++) if (!vis[s]) {

        vector<int> cyc;

        int cur = s;

        while (!vis[cur]) {
            vis[cur] = 1;
            cyc.push_back(cur);
            cur = p[cur];
        }

        const int k = (int)cyc.size();
        const long long shift = n % k;

        for (int t = 0; t < k; t++) {
            int from = cyc[t];
            int to   = cyc[(t + (int)shift) % k];
            res[to]  = h[from];
        }
    }

    cout << res;
    return 0;
}
