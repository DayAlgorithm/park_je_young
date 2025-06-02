/*
Problem_Solving_Time : AM 08:36 -09:53

ppap

ppappap

pppapap

�� 3���� �ۿ� ����

�׷� ���ڿ��� ���ϱ� ���� �۾��� �ϱ�����

3���� �ϳ��� ������ �Ѿ�� �Ѿ��,,,

�̷������� ���ٰ� �� ������ PPAP
�ƴϸ� NP ������ ���ߵǴµ�,,,

ppap �� �׷� 0 �� 1�� ��ȯ����,

ppap = 1101
ppappap = 1101101
pppapap = 1110101

���� 1101 �� ���Ѵ�

if(1101)
-> �ڿ� 1101 "101" ? �׷� 7�ڸ� �ǳʶٰ� 8�ڸ� ���� �� ����

-> �ڿ� 101 �� �ƴҽ� ó������ ���ư���

else if(1110101)
->7�ڸ� �ǳʶٰ� 8�ڸ� ���� �� ����

else
return NP

*/
#include <iostream>
#include <vector>
#include <string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(void) {
    string s;
    cin >> s;

    vector<vector<bool>> cmp(3);
    cmp[0].resize(4); cmp[0] = { 1,1,0,1 };
    cmp[1].resize(7); cmp[1] = { 1,1,0,1,1,0,1 };
    cmp[2].resize(7); cmp[2] = { 1,1,1,0,1,0,1 };

    vector<bool> temp(s.size());
    for (int i = 0; i < s.size(); i++)
        temp[i] = (s[i] == 'P' ? 1 : 0);

    vector<bool> st;
    for (int i = 0; i < temp.size(); i++) {
        st.push_back(temp[i]);
        if (st.size() >= 4) {
            bool match = true;
            for (int j = 0; j < 4; j++) {
                if (st[st.size() - 4 + j] != cmp[0][j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                for (int k = 0; k < 4; k++)
                    st.pop_back();
                st.push_back(1);
            }
        }
    }

    if (st.size() == 1 && st[0] == 1)
        cout << "PPAP";
    else
        cout << "NP";

    return 0;
}
