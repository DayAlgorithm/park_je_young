#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// YYYY.MM.DD '총 일수' 로 변환
int toDays(const string& s) {
    int y = stoi(s.substr(0,4));
    int m = stoi(s.substr(5,2));
    int d = stoi(s.substr(8,2));
    // (년 * 12 + (월-1)) 개월을 28일 단위로 환산 + 일
    return (y * 12 + (m - 1)) * 28 + d;
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    int todayD = toDays(today);

    //약관 종류  개월 수 맵
    unordered_map<char,int> mp;
    for (auto& t : terms) {
        char type = t[0];
        int dur = stoi(t.substr(2));
        mp[type] = dur;
    }

    //개인정보마다
    for (int i = 0; i < privacies.size(); ++i) {
        // "YYYY.MM.DD X"
        string date = privacies[i].substr(0,10);
        char type = privacies[i][11];

        int startD  = toDays(date);
        // 만료일 = 시작일 + 유효개월*28일 - 1
        int expireD = startD + mp[type] * 28 - 1;

        // 만료일이 오늘보다 이전이면(이미 만료) 정답에 추가
        if (expireD < todayD) {
            answer.push_back(i+1);
        }
    }

    return answer;
}
