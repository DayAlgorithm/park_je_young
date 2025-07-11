
/*

PST PM 6:50 - PM 7:43 

https://www.acmicpc.net/problem/5615

사실 위의 문제랑 매우 흡사한 부분이 많아

거의 코드를 배꼈다 봐도 된다.

식의 과정은 appendix 32242 참고.

------------------------------------------------------

계수 A가 0인 특수 경우 처리

원래 식이 1차 형태(Bx + Cy + D = 0)가 될텐데

B와 C가 둘 다 0이면

D도 0일 때는 모든 (x,y)가 해  to INF

D가 0이 아니면 해 없음

그렇지 않으면 G = gcd(B,C)를 구하고

G가 D를 나누지 않으면 해 없음

나누면 무한히 많은 해

일반 경우(A!=0)

이는 곱으로 묶기

식을 변형해

(Ax + C) multi (Ay + B) = BC – AD = M
이 M이 0이면

Ax + C = 0 이거나 Ay + B = 0 중 하나라도 정수해를 만들 수 있어야 

무한해, 즉 1LL<<60

둘 다 정수해를 만들지 않으면 해 없음




M!=0일 때 모든 해 찾기

M의 절댓값을 소인수분해하여
가능한 모든 “양의 약수” 목록을 만든다.

만든 양의 약수 각각에 대해

(약수, 몫) 쌍을 만들고

두 수의 부호를 플마 로 모두 바꿔가며
(u, v) 형태의 모든 경우를 생성한다.

각 (u, v)에 대하여

uv 가 M과 일치하는지 확인

일치하면 원 식의 변형식에서
Ax + C = u, Ay + B = v 가 되는
x와 y가 정수인지 검사

정수일 때만 해로 기록


---------------------------------------------------------------------

결과 정리

찾은 (x,y)를 중복 없이 모아서

갯수와 함께 오름차순으로 정렬하여 출력

이 과정을 통해

특수 케이스(무한,없음)를 먼저 가려내고,

나머지는 M의 약수 쌍을 이용한 유한 검사로 모든 정수해를 완전 탐색.

총 걸리는 시간 복잡도 대략 n^1/3 * sqrt(n) + alpha ?
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include<functional>
#include <numeric>
#include <random>
#include <chrono>
using namespace std;
typedef long long LL;

LL mul_mod(LL a, LL b, LL mod) {
    LL res = 0;
    a %= mod;
    while (b) {
        if (b & 1) {
            res = res + a;
            if (res >= mod) res -= mod;
        }
        a = a + a;
        if (a >= mod) a -= mod;
        b >>= 1;
    }
    return res;
}

LL pow_mod(LL a, LL d, LL mod) {
    LL r = 1;
    while (d) {
        if (d & 1) r = mul_mod(r, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return r;
}

bool millerRabin(LL n) {
    if (n < 2) return false;

    for (LL p : {2,3,5,7,11,13,17,19,23,29,31,37})
        if (n % p == 0) return n == p;

    LL d = n - 1, s = 0;

    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (LL a : {2,325,9375,28178,450775,9780504,1795265022}) {
        //large num
        if (a % n == 0) continue;

        LL x = pow_mod(a, d, n);

        if (x == 1 || x == n - 1) continue;

        bool composite = true;

        for (LL r = 1; r < s; r++) {

            x = mul_mod(x, x, n);

            if (x == n - 1) {

                composite = false;
                break;

            }

        }

        if (composite) return false;

    }

    return true;

}

LL pollardsRho(LL n) {

    if (n % 2 == 0) return 2;

    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());

    uniform_int_distribution<LL> dist(2, n - 2);

    LL c = dist(gen);
    LL x = dist(gen);
    LL y = x;
    LL d = 1;

    auto f = [&](LL x){ return (mul_mod(x, x, n) + c) % n; };

    while (d == 1) {

        x = f(x);
        y = f(f(y));
        LL diff = x > y ? x - y : y - x;
        d = gcd(diff, n);
        if (d == n) return pollardsRho(n);

    }

    return d;

}

void factor(LL n, vector<LL>& fac) {

    if (n == 1) return;
    if (millerRabin(n)) {
        fac.push_back(n);
        return;
    }
    LL d = pollardsRho(n);
    factor(d, fac);
    factor(n/d, fac);

}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LL a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a == 0) {
        LL g = gcd(b, c);
        if (g == 0) {
            if (d == 0) cout << "INFINITY\n";
            else cout << "0\n";
        } else {
            if (d % g)  cout << "0\n";
            else cout << "INFINITY\n";
        }
        return 0;
    }

    LL m = b * c - a * d;
    if (m == 0) {
        bool e = false;
        if (c % a == 0) e = true;
        if (b % a == 0) e = true;
        if (e) cout << "INFINITY\n";
        else cout << "0\n";
        return 0;
    }

    LL am = m < 0 ? -m : m;
    vector<LL> fac;
    factor(am, fac);
    sort(fac.begin(), fac.end());
    vector<pair<LL,int>> exps;
    for (LL p : fac) {
        if (exps.empty() || exps.back().first != p)
            exps.emplace_back(p, 1);
        else
            exps.back().second++;
    }

    vector<LL> divs;

    function<void(int,LL)> gen = [&](int idx, LL cur) {
        if (idx == (int)exps.size()) {
            divs.push_back(cur);
            return;
        }
        LL p = exps[idx].first;
        int e = exps[idx].second;
        for (int i = 0; i <= e; i++) {
            gen(idx + 1, cur);
            cur = mul_mod(cur, p, am + 1);
        }
    };

    gen(0, 1);

    vector<pair<LL,LL>> sol;
    for (LL u1 : divs) {
        LL v1 = am / u1;
        for (int s = 0; s < 2; s++) {
            LL pu = s ? v1 : u1;
            LL pv = s ? u1 : v1;
            for (LL su : {1, -1}) {
                for (LL sv : {1, -1}) {
                    LL u = su * pu;
                    LL v = sv * pv;
                    if (u * v != m) continue;
                    if ((u - c) % a == 0 && (v - b) % a == 0) {
                        LL x = (u - c) / a;
                        LL y = (v - b) / a;
                        sol.emplace_back(x, y);
                    }
                }
            }
        }
    }

    sort(sol.begin(), sol.end());
    sol.erase(unique(sol.begin(), sol.end()), sol.end());

    cout << sol.size() << "\n";
    for (auto &pr : sol)
        cout << pr.first << " " << pr.second << "\n";

    return 0;
}
