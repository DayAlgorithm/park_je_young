#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
using namespace std;

double dm[4] = {0.9, 0.8, 0.7, 0.6};

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    vector<int> answer(2, 0);
    int nEmo = emoticons.size();
    vector<int> pick(nEmo);

    function<void(int)> dfs = [&](int idx){
        if (idx == nEmo) {
            unordered_map<int, pair<int,int>> temp;
            for (int i = 0; i < nEmo; i++) {
                int di = pick[i];
                int pct = (di+1)*10;
                int price  = emoticons[i] * (100-pct) / 100;
                temp[i] = {pct, price};
            }
            int cnt = 0, money = 0;
            for (auto &u : users) {
                int threshold = u[0];
                int limit = u[1];
                int spent = 0;
                for (auto &[i, pr] : temp) {
                    if (pr.first >= threshold) {
                        spent += pr.second;
                        if (spent >= limit) {
                            cnt++;
                            spent = 0;
                            break;
                        }
                    }
                }
                money += spent;
            }
            //answer 갱신
            if (cnt > answer[0] || (cnt == answer[0] && money > answer[1])) {
                answer = {cnt, money};
            }
            return;
        }

        // idx번 이모티콘에 4가지 할인율 중 하나를 골라준다
        for (int d = 0; d < 4; ++d) {
            pick[idx] = d;
            dfs(idx + 1);
        }
    };

    dfs(0);
    return answer;
}
