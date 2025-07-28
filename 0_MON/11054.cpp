#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> LIS_lengths(const vector<int>& a) {
    int n = a.size();
    vector<int> dp;
    vector<int> res(n);

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);
        int pos = it - dp.begin();
        if (it == dp.end()) dp.push_back(a[i]);
        else *it = a[i];
        res[i] = pos + 1;
    }
    return res;
}

vector<int> LDS_lengths(const vector<int>& a) {
    int n = a.size();
    vector<int> ra = a;
    reverse(ra.begin(), ra.end());
    vector<int> lds_rev = LIS_lengths(ra);
    reverse(lds_rev.begin(), lds_rev.end());
    return lds_rev;
}

int longest_bitonic(const vector<int>& a) {
    vector<int> lis = LIS_lengths(a);
    vector<int> lds = LDS_lengths(a);

    int n = a.size();
    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        max_len = max(max_len, lis[i] + lds[i] - 1);
    }
    return max_len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int& x : a) cin >> x;

    cout << longest_bitonic(a);

    return 0;
}
