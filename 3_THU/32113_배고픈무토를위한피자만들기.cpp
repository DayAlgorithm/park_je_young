
/*
*
* Problem_Solving_Time 
* (�̹� �� �ð� ���� �� �ǹ̰� ����.)
* (���� ������ �ǾҴµ�, ������ �߸��ؼ� ���� ��;;;)
*
* ���� ũ�� n
*
* ��° �ٿ� ó�� ������ ��Ʈ���� ��� ���� R,C �� �־���
*
* ���� N���� �ٿ� ���� �ù̾��� �����Ǵ�� �׷��� ��Ʈ�� ��ġ�� �־���
*
* ������ ����
* 1. push
*
* 2. pull
*
* ���̽� ��Ű ���� �տ� ��ֹ��� ������
*
* �� �и�, ��� 2*n^2 �� ���Ϸ� �������� ����ؼ�
*
* ���ڸ� �ϼ��ϴ� �������� ������,
*
* �׸��� ���� ��Ʈ���� �ִ� ����
*
* ��ȭ���� ��Ʈ�� ������ ���Ͽ�
*
* ��� ��Ʈ���� ����� ���������� Ȯ���� ����.
*
* x �ֺ��� ���� ���� ����, �׷��� ���� �ٽ� ����,
*
* o �� ������ �ϴµ�, �ֺ��� o �� �ϳ��� ������,
* ��Ե� �׾� �� �� �ִ�,
*
* ������ x �� ���ٰ� o �� ���ݴٰ�, o�� ������ �� �ִ�.
*
* ��� x �� �����ϴ� ����
*
* x �� ���� �ϴ�, �� ��쿡�� ������ �������
*
* ���� ���� �Ұ��� ������ �Ǵ��Ѵ�,
*
* �߰��� 2*n^2�� ������ ���������� �Ǵ� �Ѵ�,
*
*
* x, y �� ù ������ ��ġ�� �Է��Ѵ�,
*
* �ٵ� �� ������ �������� ��� ���� �ϼ� �Ǿ�� �ϹǷ�
*
* õõ�� ������ ���� row, �������� ������ ä���
*
* �׵ڿ� column �������� ������ ä���,
*
* ������ ������ �����ϸ�, ������ �����Ѵ�.
*
* ��� ���� 3���� �ܰ踦 �������� ���� �ڵ带 �ۼ� �Ͽ���.
*
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;
vector<string> ans;

void record(char dir, int line, const string& act, int cnt = 1) {
    // �⺻ �μ� cnt 1, �ƴϸ� �ٸ� �μ��� �ޱ�,
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
