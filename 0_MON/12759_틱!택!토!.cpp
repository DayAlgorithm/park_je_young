#include <iostream>
using namespace std;

int arr[3][3] = { 0 };

typedef struct check {
    bool one;
    int first;
    int second;
} c;

// ���� �¸� üũ
c checking_w() {
    for (int i = 0; i < 3; i++) {
        if (arr[i][0] != 0 &&
            arr[i][0] == arr[i][1] &&
            arr[i][1] == arr[i][2]) {
            return { true, i, 0 };
        }
    }
    return { false, 0, 0 };
}

// ���� �¸� üũ
c checking_l() {
    for (int i = 0; i < 3; i++) {
        if (arr[0][i] != 0 &&
            arr[0][i] == arr[1][i] &&
            arr[1][i] == arr[2][i]) {
            return { true, 0, i };
        }
    }
    return { false, 0, 0 };
}

// ���� �� �밢��
bool checking_d1() {
    return (arr[0][0] != 0 &&
        arr[0][0] == arr[1][1] &&
        arr[1][1] == arr[2][2]);
}

// ������ �� �밢��
bool checking_d2() {
    return (arr[0][2] != 0 &&
        arr[0][2] == arr[1][1] &&
        arr[1][1] == arr[2][0]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // ���� �ʱ�ȭ
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            arr[i][j] = 0;

    int a[2] = { 1, 2 };
    // ù ���� n�� ���� ���� 
    bool k = (n != 1);

    for (int i = 0; i < 9; i++, k = !k) {
        int x, y;
        cin >> x >> y;
        arr[x - 1][y - 1] = a[k];

        // �밢�� �켱
        if (checking_d1()) {
            cout << arr[0][0];
            return 0;
        }
        if (checking_d2()) {
            cout << arr[0][2];
            return 0;
        }
        // ����
        c lc = checking_l();
        if (lc.one) {
            cout << arr[lc.first][lc.second];
            return 0;
        }
        // ����
        c wc = checking_w();
        if (wc.one) {
            cout << arr[wc.first][wc.second];
            return 0;
        }
    }

    // ���� ������ 0 ���
    cout << 0;
    return 0;
}
