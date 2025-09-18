#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

struct Node {
    long long t;
    int u;
    int mask;
    Node(long long a, int b, int c) : t(a), u(b), mask(c) {}
    bool operator>(const Node& o) const { return t > o.t; }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<long long>> adj(n, vector<long long>(n));

    for (auto& row : adj)
        for (auto& w : row)
            cin >> w;

    const int FULL = (1u << n) - 1;

    vector<vector<long long>> dist(n, vector<long long>(1u << n, LLONG_MAX));

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[k][1u << k] = 0;

    pq.emplace(0, k, 1u << k);

    while (!pq.empty()) {
        auto [time, curr, mask] = pq.top();
        pq.pop();

        if (time != dist[curr][mask]) 
            continue;
        
        if (mask == FULL) {
            cout << time << '\n';
            return 0;
        }

        for (int nxt = 0; nxt < n; nxt++) {
            
            if (nxt == curr) continue;

            int nmask = mask | (1u << nxt);

            long long nt = time + adj[curr][nxt];
            
            if (nt < dist[nxt][nmask]) {
                dist[nxt][nmask] = nt;
                pq.emplace(nt, nxt, nmask);
            }
        
        }
    }
    return 0;
}
