/*
Program_Solving_Time : PM 01:14 - 02:05
N�� ���� N��

�Ϸ翡 �Ѻ��� ���� �� ����.

k����

���� �����ϰ� �����ߵ�.

k������ ���ֿ� ���� ��ȣ���� ���� ����.


�������� > �� ��ġ -> �ٷ� ����

���ֺ��� �ɸ��� �����鼭��, ���ָ� ���� ���ð� �ʹ�.

-> N���� ��ȣ�� ���� M�̻��� �Ǿ�� �Ѵ� (N>=M)

���� ������ ���� ������ �ϰ�,

�׵ڿ� �ּ� ������ ����,



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

    // ���������� �������� �������� ����
    sort(beer.begin(), beer.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
        });

    priority_queue<int, vector<int>, greater<int>> pq; // �ּ� ��
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
