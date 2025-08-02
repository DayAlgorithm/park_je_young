#include <iostream>
#include <vector>
#include <algorithm>
/*
	plan : 

	1. 월곡이의 생후 p일에 수입/지출 내용을 추가
		수입은 양수, 지출은 음수
	2. 월곡이의 생후 p 일부터 q일까지의 잔고가 변화 한
		값을 구하고 반환.
		월곡이가 빚을 지고 있을 수도 있기에 어떤 i 에 대해서 
		생후 i일의 잔고는 음수일 수 있음

*/

using namespace std;
using ll = long long;

struct SegTree {
    int n;
    vector<ll> t;
    SegTree(int _n): n(_n), t(4*n + 2, 0) {}

    void update(int node,int l,int r,int idx,ll v){

        if(l == r){ t[node] += v; return; }
        
		int m = (l + r) >> 1;
        if(idx <= m) update(node << 1, l, m, idx, v);
        else update(node << 1 | 1, m + 1 , r, idx, v);
        t[node] = t[node << 1] + t[node << 1 | 1];
    }

    ll query(int node,int l,int r,int ql,int qr){
        if(qr < l || r < ql) return 0;
        if(ql <= l && r <= qr) return t[node];
        int m = (l + r) >> 1;
        return query(node << 1, l, m, ql, qr)
             + query(node << 1 | 1, m+1, r, ql, qr);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

	
    int N, Q; 
    cin >> N >> Q;
    struct Op{int type; int d; ll x; int d2;};

    vector<Op> ops(Q);
    vector<int> days;
    
	days.reserve(Q*2);

    for(int i=0;i<Q;i++){

        cin>>ops[i].type;

        if(ops[i].type==1){
            cin>>ops[i].d>>ops[i].x;
            days.push_back(ops[i].d);

        } else {

            cin>>ops[i].d>>ops[i].d2;
            days.push_back(ops[i].d);
            days.push_back(ops[i].d2);

        }
    }

    // 좌표 압축

    sort(days.begin(), days.end());

    days.erase(unique(days.begin(), days.end()), days.end());

    auto idxOf = [&](int d){
        return int(lower_bound(days.begin(), days.end(), d) - days.begin()) + 1;
    };

    int M = days.size();

    SegTree st(M);

    // 처리
    for(auto& op : ops){

        if(op.type==1){

            int idx = idxOf(op.d);

            st.update(1,1,M,idx,op.x);

        } else {

            int l = idxOf(op.d), r = idxOf(op.d2);

            if(l>r) swap(l,r);

            cout<<st.query(1,1,M,l,r)<<"\n";
			
        }
    }
    return 0;
}