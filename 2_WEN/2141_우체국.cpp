/*
* 
* Problem_Solving_Time AM 10:29
* 
* sigma( A[i] * abs(X[i] - X') ) >= K 를 만족하는
* 
* K 를 구해야 됨.
* 
* 일단 A[i] 는 양수고, 절댓값 1차방정식들의 합이므로,
* 
* 위로 오목한 양상을 띈다, 이때
* 
* A, 즉 곱해지는 가중치가 커지면 커질수록
* 
* 그쪽으로 그래프가 밑으로 쏠리는 경향을 띈다,
* 
* 고로 가중치가 큰 곳부터 차례대로 위의 시그마 합들을 넣는다
* 
* 그뒤 오름차순으로 정렬하여 가장 앞에 있는 값을 꺼내어
* 
* 답으로 낸다.
* 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long LL;

struct info {
    LL x;
    LL a;
};

int main() {
    REAL;

    int n;
    cin >> n;

    vector<info> node(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> node[i].x >> node[i].a;
    }

    sort(node.begin() + 1, node.begin() + n + 1,
        [](const info& N, const info& M) {
            return N.x < M.x;
        });

    LL total = 0;
    
    for (int i = 1; i <= n; ++i) {
        total += node[i].a;
    }
    
    LL half = (total + 1) / 2;

    LL acc = 0;
    for (int i = 1; i <= n; ++i) {
        acc += node[i].a;
        if (acc >= half) {

            cout << node[i].x;
            break;
        }
    }

    return 0;
}