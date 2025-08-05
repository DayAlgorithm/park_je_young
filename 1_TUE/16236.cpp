#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

/*
	plan :

	1. 더이상 먹을 수 있는 물고기가 공간에 없다면,
	엄마 상어한테 도움 -> 그냥 끝남
	2. 먹을 수 있는 물고기가 1마리라면, 그 물고기를 먹으러감
	3. 먹을 수 있는 물고기의 수 가 1초과 라면, 거리가 가장 가까운 곳으로
		3 - 1. 거리는 아기 상어가 있는 칸에서 물고기가 있는 칸으로 이동할 때,
		지나야 하는 칸의 개수의 최솟값이다.
		3 - 2. 거리가 가까운 물고기가 많다면, 가장 위에 있는 물고기,
		그러한 물고기가 여러마리라면, 가장 왼쪽에 있는 물고기를 먹는다.
*/

int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };
// 상 좌 하 우
// 반 시계 방향

class BabySharkGame {
private:
    int n;
    vector<vector<int>> Map;
    int sharkSize;
    int eatCount;
    int timeElapsed;
    int sx, sy;

public:
    BabySharkGame(int _n, vector<vector<int>>& _map)
        : n(_n), Map(_map), sharkSize(2), eatCount(0), timeElapsed(0), sx(0), sy(0)
	//Initializer

    {
        //Heuristic_moving
        //Baby_Shark was initialized by 2 (size)
        //If The baby shark is founded, then restore the Baby shark's loacation value 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (Map[i][j] == 9) {
                    sx = i; sy = j;
                    Map[i][j] = 0;
                    return;
                }
            }
        }

    }

    void play() {
        while (true) {
            auto [found, fx, fy, dist] = findNearestFish();
            if (!found) break;
            // Moved
            sx = fx; sy = fy;
            timeElapsed += dist;

            // Increase to eatingCount
            if (++eatCount == sharkSize) {
                ++sharkSize;
                eatCount = 0;
            }
        }
        cout << timeElapsed << "\n";
    }

private:

    tuple<bool,int,int,int> findNearestFish() {
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<tuple<int,int,int>> q;  // x, y, dist
        visited[sx][sy] = true;
        q.emplace(sx, sy, 0);

        int minDist = -1;
        vector<tuple<int,int,int>> candidates;

        while (!q.empty()) {
            auto [x, y, d] = q.front(); q.pop();
            if (minDist != -1 && d > minDist) break;

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir], ny = y + dy[dir];
                if (nx<0||ny<0||nx>=n||ny>=n) continue;
                if (visited[nx][ny] || Map[nx][ny] > sharkSize) continue;
                visited[nx][ny] = true;

                if (Map[nx][ny] != 0 && Map[nx][ny] < sharkSize) {
                    if (minDist == -1) minDist = d + 1;
                    candidates.emplace_back(nx, ny, d + 1);
                }
                q.emplace(nx, ny, d + 1);
            }
        }

        if (candidates.empty())
            return { false, 0, 0, 0 };

        // priority :
		// 1. Distance, 2. Row, 3. Column
        sort(candidates.begin(), candidates.end(),
            [](auto& a, auto& b) {
				auto[ax, ay, ad] = a;
				auto[bx, by, bd] = b;
                if (ad != bd) return ad < bd;
                if (ax != bx) return ax < bx;
                return ay < by;
            });

        auto [fx, fy, fd] = candidates.front();
        // Eaten, and restore
        Map[fx][fy] = 0;
        return { true, fx, fy, fd };
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];

    BabySharkGame game(n, grid);
    game.play();

    return 0;
}
