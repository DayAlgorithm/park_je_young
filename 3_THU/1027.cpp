#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

typedef long long LL;

int main() {
    int n;
    cin >> n;
    vector<LL> y(n);
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    vector<int> cnt(n, 0);

    for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			bool visible = true;
			
			if (j > i + 1) {
				for (int k = i + 1; k < j; k++) {
					LL dy_ij = y[j] - y[i];
					LL dx_ij = j - i;
					LL dy_ik = y[k] - y[i];
					LL dx_ik = k - i;

					
					if (dy_ik * dx_ij >= dy_ij * dx_ik) {
						visible = false;
						break;
					}
				}
			}
			if (visible) {
				cnt[i]++;
				cnt[j]++;
			}
    	}
	}


    cout << *max_element(cnt.begin(), cnt.end());
    return 0;
}