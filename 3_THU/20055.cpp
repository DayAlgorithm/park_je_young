#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K; 
    cin >> N >> K;
    int M = 2 * N;

    vector<int> A(M);
    for(auto& iter : A)
        cin >> iter;

    auto idx = [&](int start, int i) {
        int x = start + i;
        if (x >= M) x -= M;
        return x;
    };

    vector<char> robot(N, 0);
    int start = 0;
    int step = 0;

    int zeroCnt = 0;
    for (int x : A) 
        if (x == 0) 
            ++zeroCnt;

    auto dec_and_count = [&](int &val) {
        if (val > 0) {
            --val;
            if (val == 0) 
                ++zeroCnt;
        }
    };

    while (true) {
        step++;

        start = (start - 1 + M) % M;
        for (int i = N - 1; i >= 1; i--) 
            robot[i] = robot[i - 1];
        
        robot[0] = 0;
        robot[N - 1] = 0;

        for (int i = N - 2; i >= 0; i--) {
            if (!robot[i]) continue;

            int ni = i + 1;
            
            if (!robot[ni] && A[idx(start, ni)] > 0) {
                robot[i] = 0;
                robot[ni] = 1;
                dec_and_count(A[idx(start, ni)]);
            }
        }
        robot[N - 1] = 0;

        if (!robot[0] && A[idx(start, 0)] > 0) {
            robot[0] = 1;
            dec_and_count(A[idx(start, 0)]);
        }

        if (zeroCnt >= K) {
            cout << step;
            break;
        }
    }
    return 0;
}