/*
Problem_Solving_Time : AM 08:36 -09:53

ppap

ppappap

pppapap

이 3가지 밖에 없음

그럼 문자열을 비교하기 위한 작업을 하기위해

3개중 하나가 받으면 넘어가고 넘어가고,,,

이런씩으로 가다가 다 맞으면 PPAP
아니면 NP 식으로 가야되는데,,,

ppap 를 그럼 0 과 1로 교환하자,

ppap = 1101
ppappap = 1101101
pppapap = 1110101

먼저 1101 을 비교한다

if(1101)
-> 뒤에 1101 "101" ? 그럼 7자리 건너뛰고 8자리 부터 비교 시작

-> 뒤에 101 이 아닐시 처음으로 돌아간다

else if(1110101)
->7자리 건너뛰고 8자리 부터 비교 시작

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
