#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    set<pair<int,int>> S;
    map<int,int> PL;

    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int P,L; cin >> P >> L;
        S.insert({L,P});
        PL[P] = L;
    }

    int m; cin >> m;
    while(m--){
        string h; cin >> h;
        if(h == "add"){
            int P,L; cin >> P >> L;
            S.insert({L,P});
            PL[P] = L;
        }else if(h == "recommend"){
            int x; cin >> x;
            if(x == 1) cout << prev(S.end())->second << '\n';
            else cout << S.begin()->second << '\n';
        }else{
            int P; cin >> P;
            int L = PL[P];
            S.erase({L,P});
            PL.erase(P);
        }
    }
}
