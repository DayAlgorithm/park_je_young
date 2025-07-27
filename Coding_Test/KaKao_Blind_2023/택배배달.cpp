#include <string>
#include <vector>

using namespace std;

long long solution(int cap, int n, vector<int> d, vector<int> p) {
    
    long long answer = 0;
    int pp = n - 1;
    while(pp >= 0){
        if(d[pp] == 0 && p[pp] == 0){
            pp--;
            continue;
        }
        int temp_cmp = cap;
        for(int i = pp; i >= 0; i--){
            //한번 가는데 어느정도 해결?
            if(d[i] == 0)continue;
            if(d[i] <= temp_cmp){
                temp_cmp -= d[i];
                d[i] = 0;
            }else{
                d[i]-=temp_cmp;
                break;
            }
        }
        temp_cmp = cap;
        for(int i = pp; i >= 0; i--){
            //한번 가는데 어느정도 해결?
            if(p[i] == 0)continue;
            if(p[i] <= temp_cmp){
                temp_cmp -= p[i];
                p[i] = 0;
            }else{
                p[i]-=temp_cmp;

                break;
            }
        }
        answer += (pp + 1)*2;
    }
    
    
    return answer;
}