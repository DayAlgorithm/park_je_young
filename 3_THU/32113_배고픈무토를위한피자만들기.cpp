
/*
*
* Problem_Solving_Time 
* (이번 껀 시간 세는 게 의미가 없음.)
* (또한 로직은 옳았는데, 구현을 잘못해서 뻘짓 함;;;)
*
* 피자 크기 n
*
* 둘째 줄에 처음 토핑한 미트볼의 행과 열이 R,C 로 주어짐
*
* 이후 N개의 줄에 걸쳐 시미아의 레시피대로 그려진 미트볼 배치가 주어짐
*
* 염동력 종류
* 1. push
*
* 2. pull
*
* 아이스 하키 마냥 앞에 장애물이 없으면
*
* 쭉 밀림, 고로 2*n^2 번 이하로 염동력을 사용해서
*
* 피자를 완성하는 방향으로 가보자,
*
* 그리고 본래 미트볼이 있는 모양과
*
* 변화후의 미트볼 보양을 비교하여
*
* 어디서 미트볼이 생기고 없어지는지 확인해 보자.
*
* x 주변에 나갈 길이 없다, 그러면 빼고 다시 뺀다,
*
* o 를 쌓을려 하는데, 주변에 o 가 하나라도 있으면,
* 어떻게든 쌓아 갈 수 있다,
*
* 하지만 x 를 뺀다고 o 를 없앴다간, o를 못쌓을 수 있다.
*
* 고로 x 를 먼저하는 경우와
*
* x 를 먼저 하는, 두 경우에서 나오는 결과물로
*
* 가능 한지 불가능 한지를 판단한다,
*
* 추가로 2*n^2번 안으로 가능한지도 판단 한다,
*
*
* x, y 로 첫 토핑의 위치를 입력한다,
*
* 근데 그 토핑을 기준으로 모든 것이 완성 되어야 하므로
*
* 천천히 생각해 보면 row, 기준으로 토핑을 채우고
*
* 그뒤에 column 기준으로 토핑을 채운뒤,
*
* 나머지 토핑을 제거하면, 정답을 만족한다.
*
* 고로 나는 3개의 단계를 바탕으로 다음 코드를 작성 하였다.
*
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;
vector<string> ans;

void record(char dir, int line, const string& act, int cnt = 1) {
    // 기본 인수 cnt 1, 아니면 다른 인수로 받기,
    for (int i = 0; i < cnt; ++i)
        ans.emplace_back(string(1, dir) + " " + to_string(line) + " " + act);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, r, c;

    cin >> n >> r >> c;

    vector<vector<bool>>pizza(n + 3, vector<bool>(n + 3, false));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char a; cin >> a;
            pizza[i][j] = (a == '#');
        }
    }

    record('L', r, "push", c - 1);
    record('R', r, "push", n - c);
    record('U', 1, "push", r - 1);
    record('D', 1, "push", n - r);

    for (int i = r - 1; i >= 1; i--) {
        record('R', i, "push", n - 1);
        for (int j = 2; j <= n; j++)
            if (!pizza[i][j]) record('U', j, "pull");
    }

    for (int i = r; i <= n; i++) {
        if (i > r) record('R', i, "push", n - 1);
        for (int j = 2; j <= n; j++)
            if (!pizza[i][j]) record('D', j, "pull");
    }

    for (int i = 1; i <= n; i++)
        if (!pizza[i][1]) record('L', i, "pull");

    cout << ans.size() << '\n';
    for (auto& a : ans) cout << a << '\n';
    return 0;
}
