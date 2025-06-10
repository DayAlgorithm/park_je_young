/*
Problem_Solving_Time AM 11:46 - 

A-B-C-D-E ����

5��, ���� �� ģ���̸� ��� �ƴϸ� �н�.

���� �켱 Ž���Ͽ�

���� �ŵ�� �������� �Ѿ��, ���� +1

������ 4�� true�� �Ͽ� �۵� ����

�ƴϸ� �ٷ� 0 ���

�ٵ� �Է��� �������� ���Ƿ�,

----------���������� �����������.

----------"����������" �������ְ� for �� ������ dfs �� �־��ְ� 

(���� ������ ǥ���� �κ��� �׳� ���� ������� �������� ���� ����)

��� �Լ��� ���Ͽ� Ž���� �õ��Ѵ�.

*/

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> node;
vector<bool> visited;

bool dfs(int x, int t) {
    if (t == 4)        // ���� 4�� Ž�� ����
        return true;

    // ���� ����Ʈ�� �ı����� �ʰ� ��ȸ
    for (int i = 0; i < node[x].size(); ++i) {
        int f = node[x][i];
        if (visited[f])
            continue;
        visited[f] = true;
        if (dfs(f, t + 1))
            return 1;
        visited[f] = false;    //��Ʈ��ŷ
    }
    return 0;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    node.resize(n);
    visited.resize(n, false);

    // ���� �׷��� ���� �Է�
    for (int i = 0; i < m; ++i) {
        int start, end;
        cin >> start >> end;
        node[start].push_back(end);
        node[end].push_back(start);
    }

    // ��� ������ ���������� DFS �õ�
    for (int i = 0; i < n; ++i) {
        visited[i] = true;
        if (dfs(i, 0)) {
            cout << 1;
            return 0;
        }
        visited[i] = false;
    }

    cout << 0;
    return 0;
}