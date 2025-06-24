/*
* 
* Problem_Solving_Time AM 12:00 - 1:00
* 
* 
* 손님이 구매하는 피자조각을 p 라 하자,
* 
* i 가 0부터 p 사이에 존재하는 정수라 하면,
* 
* p - i 에 대해 a 가 가질 수 있는 경우의 수 를 a_oc 라 하고,
* i 에 대해 b 가 가질 수 있는 경우의 수를 b_oc라 하면,
* 
* answer += a_oc * b_oc 이다.
* 
*/
#include <iostream>
#include <vector>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;

int main() {
    REAL;

    int p;
    cin >> p;
    int m, n;
    cin >> m >> n;

    vector<int> a(m), b(n);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;

    vector<long long> a_oc(p + 1, 0), b_oc(p + 1, 0);

    for (int x : a) if (x <= p) a_oc[x]++;
    for (int x : b) if (x <= p) b_oc[x]++;

    //피자 인접 부분합
    vector<int> A2(2 * m), S1(2 * m + 1, 0);
    for (int i = 0; i < m; i++) {
        A2[i] = A2[i + m] = a[i];
    }
    for (int i = 0; i < 2 * m; i++) {
        S1[i + 1] = S1[i] + A2[i];
    }
    // len = 2 ~ m-1
    for (int len = 2; len < m; len++) {
        for (int st = 0; st < m; st++) {
            int sum = S1[st + len] - S1[st];
            if (sum <= p) a_oc[sum]++;
        }
    }
    // len = m
    {
        int sum = S1[m] - S1[0];
        if (sum <= p) a_oc[sum]++;
    }

    //B도 동일하게
    vector<int> B2(2 * n), S2(2 * n + 1, 0);
    for (int i = 0; i < n; i++) {
        B2[i] = B2[i + n] = b[i];
    }
    for (int i = 0; i < 2 * n; i++) {
        S2[i + 1] = S2[i] + B2[i];
    }
    for (int len = 2; len < n; len++) {
        for (int st = 0; st < n; st++) {
            int sum = S2[st + len] - S2[st];
            if (sum <= p) b_oc[sum]++;
        }
    }
    {
        int sum = S2[n] - S2[0];
        if (sum <= p) b_oc[sum]++;
    }

    
    long long ans = 0;
    // A만으로 p, B만으로 p
    ans += a_oc[p] + b_oc[p];
    // A(i) + B(p-i)
    for (int i = 1; i < p; i++) {
        ans += a_oc[i] * b_oc[p - i];
    }

    cout << ans;
    return 0;
}