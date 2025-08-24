#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){	

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int>v(n, 0);

	for(int& i : v)	cin >> i;

	sort(v.begin(),v.end());

	using ll = long long;

	ll best = (1LL<<62);
    ll A = 0, B = 0;

    for (int i = 0; i < n - 1; i++) {

        ll target = -v[i];
        auto it = lower_bound(v.begin() + i + 1, v.end(), target);

        if (it != v.end()) {
            ll s = v[i] + *it;
            ll cur = s >= 0 ? s : -s;
            if (cur < best) {
                best = cur;
                A = v[i]; B = *it;
                if (best == 0) break;
            }
        }
        if (it != v.begin() + i + 1) {
            auto jt = it - 1;
            ll s = v[i] + *jt;
            ll cur = s >= 0 ? s : -s;
            if (cur < best) {
                best = cur;
                A = v[i]; B = *jt;
            }
        }
    }

    cout << A << ' ' << B;

	return 0;
}