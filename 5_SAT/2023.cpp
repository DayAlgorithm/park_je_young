#include <bits/stdc++.h>
using namespace std;
using u128 = __uint128_t;

static inline uint64_t mod_mul(uint64_t a, uint64_t b, uint64_t m){
    return (u128)a * b % m;
}
static uint64_t mod_pow(uint64_t a, uint64_t e, uint64_t m){
    uint64_t r = 1;
    while(e){
        if(e & 1) r = mod_mul(r, a, m);
        a = mod_mul(a, a, m);
        e >>= 1;
    }
    return r;
}
static bool miller_witness(uint64_t a, uint64_t s, uint64_t d, uint64_t n){
    uint64_t x = mod_pow(a, d, n);
    if(x == 1 || x == n-1) return false;
    for(size_t i=1; i<s; ++i){
        x = mod_mul(x, x, n);
        if(x == n-1) return false;
    }
    return true;
}
static bool isPrime(uint64_t n){
    if(n < 2) return false;
    // small primes quick check
    for(uint64_t p : {2ull,3ull,5ull,7ull,11ull,13ull,17ull,19ull,23ull,29ull,31ull,37ull}){
        if(n == p) return true;
        if(n % p == 0) return n == p;
    }
    // write n-1 = d * 2^s
    uint64_t d = n - 1, s = 0;
    while((d & 1) == 0){ d >>= 1; ++s; }
    // Deterministic bases for 64-bit
    for(uint64_t a : {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull}){
        if(a % n == 0) return true;
        if(miller_witness(a, s, d, n)) return false;
    }
    return true;
}

static const int DIGS[4] = {1,3,7,9};

void dfs_build(int len, int target, uint64_t cur, int sum3, vector<uint64_t>& out){
    if(len == target){
        out.push_back(cur);
        return;
    }
    for(int d : DIGS){
        int ns = (sum3 + d) % 3;
        if(ns == 0) continue;                  // divisible by 3 -> composite (3 자체 제외인데, 여기선 len>=1이므로 안전)
        uint64_t nxt = cur * 10 + (uint64_t)d;
        // 끝자리 필터(짝수/5) 이미 제거됨(DIGS), 이제 소수 판정만
        if(isPrime(nxt)){
            dfs_build(len+1, target, nxt, ns, out);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    vector<uint64_t> ans;

    if(n == 1){
        // 한 자리 접두사-소수는 2,3,5,7
        for(int p : {2,3,5,7}) cout << p << '\n';
        return 0;
    }

    for(uint64_t s : {2ull,3ull,5ull,7ull}){
        // s 자체는 소수. 다음 자리로 확장
        dfs_build(1, n, s, (int)(s % 3), ans);
    }

    sort(ans.begin(), ans.end()); // 원 코드처럼 오름차순 보장
    for(uint64_t x : ans) cout << x << '\n';
    return 0;
}
