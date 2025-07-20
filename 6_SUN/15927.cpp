#include<iostream>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;

int solve(const string& s) {
    int n = s.size();

    if (count(s.begin(), s.end(), s[0]) == n)
        return -1;
    
    return (string(s.rbegin(), s.rend()) == s) ? n - 1 : n;
}


int main(){

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string k;
	cin>>k;
	bool check_same = false;
	for(int i = 0; i < k.size();i++){
		if(k[0] == k[i])check_same = true;
		else {
			check_same = false;
			break;
		}
	}
	if(check_same){
		cout<<-1;
		return 0;
	}
	cout << solve(k);

	return 0;
}