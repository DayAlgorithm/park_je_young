/*
Problem_Solving_Time AM 11:46 - 

A-B-C-D-E 같이

5명, 서로 다 친구이면 통과 아니면 패스.

깊이 우선 탐색하여

점차 거듭된 방향으로 넘어갈시, 스택 +1

스택이 4면 true로 하여 작동 중지

아니면 바로 0 출력

근데 입력이 랜덤으로 들어가므로,

----------진입차수를 설정해줘야함.

----------"진입차수만" 설정해주고 for 문 돌려서 dfs 에 넣어주고 

(위에 선으로 표시한 부분은 그냥 벡터 사이즈로 진입차수 설정 가능)

재귀 함수를 통하여 탐색을 시도한다.

*/

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> node;
vector<bool> visited;

bool dfs(int x, int t) {
    if (t == 4)        // 간선 4개 탐색 성공
        return true;

    // 인접 리스트를 파괴하지 않고 순회
    for (int i = 0; i < node[x].size(); ++i) {
        int f = node[x][i];
        if (visited[f])
            continue;
        visited[f] = true;
        if (dfs(f, t + 1))
            return 1;
        visited[f] = false;    //백트래킹
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

    // 무향 그래프 간선 입력
    for (int i = 0; i < m; ++i) {
        int start, end;
        cin >> start >> end;
        node[start].push_back(end);
        node[end].push_back(start);
    }

    // 모든 정점을 시작점으로 DFS 시도
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