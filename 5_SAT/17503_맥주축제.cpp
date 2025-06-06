/*
Program_Solving_Time : PM 01:14 - 02:05
N일 동안 N병

하루에 한병만 마실 수 있음.

k종류

간을 강력하게 만들어야됨.

k종류의 맥주에 각각 선호도와 도수 레벨.


도수레벨 > 간 수치 -> 바로 기절

맥주병에 걸리지 않으면서도, 맥주를 많이 마시고 싶다.

-> N개의 선호도 합이 M이상이 되어야 한다 (N>=M)

도수 레벨에 따라 정리를 하고,

그뒤에 최소 힙으로 정리,



*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> beer(k); // {preference, alcohol}

    for (int i = 0; i < k; i++) {
        cin >> beer[i].first >> beer[i].second;
    }

    // 도수레벨을 기준으로 오름차순 정렬
    sort(beer.begin(), beer.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
        });

    priority_queue<int, vector<int>, greater<int>> pq; // 최소 힙
    long long total_pref = 0;

    for (int i = 0; i < k; i++) {
        pq.push(beer[i].first);
        total_pref += beer[i].first;

        if ((int)pq.size() > n) {
            total_pref -= pq.top();
            pq.pop();
        }

        if ((int)pq.size() == n && total_pref >= m) {
            cout << beer[i].second << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
