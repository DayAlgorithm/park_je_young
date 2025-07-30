#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

struct Chain {
    vector<bool> temp;
    //n 극은 0, s 극은 1

    // 12시 방향부터 시게방향으로 주어짐,
    // 비교시 0-based 에서 2-indext 를 찾으면 됨.

    void reset() {
        temp.assign(8, false);
        string line;
        cin >> line;
        istringstream ss(line);
        char bit;
        int i = 0;
        while (ss >> bit && i < 8) {
            temp[i++] = (bit == '1');
        }
    }

    bool left()   const { return temp[6]; }
    bool right()  const { return temp[2]; }
    bool upside() const { return temp[0]; }

    void rotation(const int& number) {
        if (number == -1) {
            std::rotate(temp.begin(), temp.begin() + 1, temp.end());
        } else {
            std::rotate(temp.begin(), temp.end() - 1, temp.end());
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    vector<Chain> v(4);
    // Chains act like
    //  1 to 2 to 3
    //  2 to 3 to 4

    for (auto& ch : v) {
        ch.reset();
    }

    int k;
    cin >> k;
    while (k--) {
        int idx, query;
        cin >> idx >> query;
        idx--;

        int rotDir[4] = {0};
        rotDir[idx] = query;

        for (int i = idx; i > 0; i--) {
            if (v[i].left() != v[i-1].right()) {
                rotDir[i-1] = -rotDir[i];
            } else {
                break;
            }
        }

        for (int i = idx; i < 3; i++) {
            if (v[i].right() != v[i+1].left()) {
                rotDir[i+1] = -rotDir[i];
            } else {
                break;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (rotDir[i] != 0) {
                v[i].rotation(rotDir[i]);
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < 4; ++i) {
        if (v[i].upside()) {
            answer += (1 << i);
        }
    }
    cout << answer;
    return 0;
}
