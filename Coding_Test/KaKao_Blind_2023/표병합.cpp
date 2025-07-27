#include <string>
#include <vector>
#include <functional>
#include <sstream>
using namespace std;
/*
    plan:

    1. dsu로 병합 게산
    2. 경로압축
    3. sstream tokenizatoin.

*/

vector<string> solution(vector<string> commands) {
    
    const int N = 50, M = 50, SZ = N * M;
    
    vector<int> parent(SZ);
    
    for (int i = 0; i < SZ; ++i) parent[i] = i;
    
    vector<string> value(SZ, "");

    //union_find
    function<int(int)> find = [&](int x) -> int {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    };

    vector<string> answer;
    
    for (auto &cmd : commands) {
        
        stringstream ss(cmd);
        
        vector<string> tok;
        
        string t;
        
        while (ss >> t) tok.push_back(t);
        

        if (tok[0] == "UPDATE") {
            
            if (tok.size() == 4) {
                
                int r = stoi(tok[1]), c = stoi(tok[2]);
                
                int idx = (r-1)*M + (c-1);
                
                int rt  = find(idx);
                
                value[rt] = tok[3];
                
            } else {

                string v1 = tok[1], v2 = tok[2];
                for (int i = 0; i < SZ; ++i) {
                    if (parent[i] == i && value[i] == v1) {
                        value[i] = v2;
                    }
                }
            }
            
        }
        else if (tok[0] == "MERGE") {
            
            int r1 = stoi(tok[1]), c1 = stoi(tok[2]);
            
            int r2 = stoi(tok[3]), c2 = stoi(tok[4]);
            
            int i1 = (r1-1)*M + (c1-1);
            
            int i2 = (r2-1)*M + (c2-1);
            
            int p1 = find(i1), p2 = find(i2);
            
            if (p1 != p2) {

                if (value[p1].empty() && !value[p2].empty()) {
                    value[p1] = value[p2];
                }
                parent[p2] = p1;
            }
        }
        else if (tok[0] == "UNMERGE") {
            // 한그룹에서 모든 멤버 찾기.
            int r = stoi(tok[1]), c = stoi(tok[2]);

            int idx = (r-1)*M + (c-1);

            int rt  = find(idx);

            string keep = value[rt];

            vector<int> group;

            group.reserve(SZ);

            for (int i = 0; i < SZ; ++i) {
                if (find(i) == rt) {
                    group.push_back(i);
                }
            }

            for (int x : group) {
                parent[x] = x;
                value[x] = "";
            }
            value[idx] = keep;

        }
        else if (tok[0] == "PRINT") {
            
            int r = stoi(tok[1]), c = stoi(tok[2]);

            int idx = (r-1)*M + (c-1);

            int rt  = find(idx);

            if (value[rt].empty()) answer.push_back("EMPTY");
            
            else answer.push_back(value[rt]);
        }
    }
    return answer;
}
