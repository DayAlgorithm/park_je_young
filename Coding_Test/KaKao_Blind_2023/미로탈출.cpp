#include <string>
#include <vector>
#include <cmath>
using namespace std;

string solution(int n, int m, int x, int y, int r, int c, int k) {
    // 시작과 도착 사이 최소 거리
    int dist = abs(x - r) + abs(y - c);
    // k보다 크거나, 남은 칸수와 거리가 맞지 않으면 불가능
    
    if (dist > k || (k - dist) % 2 != 0) return "impossible";

    string answer;
    
    int cx = x, cy = y, rem = k;
    
    // 사전순 배열 순서: 'd' < 'l' < 'r' < 'u'
    
    const vector<pair<char, pair<int,int>>> dirs = {
        {'d',{ 1,  0}},
        {'l',{ 0, -1}},
        {'r',{ 0,  1}},
        {'u',{-1,  0}}
    };

    while (rem > 0) {
        for (auto &d : dirs) {
            char ch = d.first;
            int nx = cx + d.second.first;
            int ny = cy + d.second.second;
            // 격자 범위 체크
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            // 이 방향으로 한 칸 이동했을 때 남은 거리
            int nextDist = abs(nx - r) + abs(ny - c);
            // 남은 칸수 -1 로도 도착 가능하고, 짝홀 도 맞아야 함
            if (nextDist <= rem - 1 && ((rem - 1 - nextDist) % 2 == 0)) {
                answer.push_back(ch);
                cx = nx; cy = ny;
                rem--;
                break;
            }
        }
    }

    return answer;
}