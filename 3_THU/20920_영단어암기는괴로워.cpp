#include<iostream>
#include<unordered_map>
#include<string>
#include<algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, M; cin >> n >> M; unordered_map<string, int>F; string s;
    while (n-- && cin >> s) if (s.size() >= M) F[s]++;
    vector<string> V; for (auto& p : F) V.push_back(p.first);
    sort(V.begin(), V.end(), [&](auto& a, auto& b) {
        return F[a] > F[b] || (F[a] == F[b] && (a.size() > b.size() || (a.size() == b.size() && a < b)));
        });
    for (auto& w : V) cout << w << "\n";
}
