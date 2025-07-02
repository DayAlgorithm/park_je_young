/*
* 
* Problem_Solving_Time AM 10:29
* 
* sigma( A[i] * abs(X[i] - X') ) >= K �� �����ϴ�
* 
* K �� ���ؾ� ��.
* 
* �ϴ� A[i] �� �����, ���� 1�������ĵ��� ���̹Ƿ�,
* 
* ���� ������ ����� ���, �̶�
* 
* A, �� �������� ����ġ�� Ŀ���� Ŀ������
* 
* �������� �׷����� ������ �򸮴� ������ ���,
* 
* ��� ����ġ�� ū ������ ���ʴ�� ���� �ñ׸� �յ��� �ִ´�
* 
* �׵� ������������ �����Ͽ� ���� �տ� �ִ� ���� ������
* 
* ������ ����.
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