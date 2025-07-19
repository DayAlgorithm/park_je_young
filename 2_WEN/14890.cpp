#include<vector>
#include<iostream>
#include<cmath>

using namespace std;

int N, L;
int A[100][100];

bool canPass(const vector<int>& line) {
    vector<bool> used(N, false);
    for (int i = 0; i < N-1; i++) {
        int h = line[i], nh = line[i+1];
        if (h == nh) continue;
        // 높이 차가 1이 아니면 불가
        if (abs(h - nh) != 1) return false;
        // 오르막
        if (h + 1 == nh) {
            // 뒤로 L칸
            for (int k = i; k > i - L; k--) {
                if (k < 0 || used[k] || line[k] != h) return false;
                used[k] = true;
            }
        }
        // 내리막
        else { // h - 1 == nh
            // 앞으로 L칸
            for (int k = i+1; k <= i + L; k++) {
                if (k >= N || used[k] || line[k] != nh) return false;
                used[k] = true;
            }
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> L;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    int answer = 0;
    // 각 행 검사
    for (int i = 0; i < N; i++) {
        vector<int> row(N);
        for (int j = 0; j < N; ++j) row[j] = A[i][j];
        if (canPass(row)) answer++;
    }
    // 각 열 검사
    for (int j = 0; j < N; j++) {
        vector<int> col(N);
        for (int i = 0; i < N; ++i) col[i] = A[i][j];
        if (canPass(col)) answer++;
    }

    cout << answer << "\n";
    return 0;
}