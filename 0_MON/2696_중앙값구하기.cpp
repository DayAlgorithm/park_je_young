/*
* PST AM 09:10 - 
* 
* 2n - 1까지 sort
* 
* median 은 n
* 
* 전체 수열 크기를 N이라 할때,
* 
* T * NlogN
* 1,0,000,000 * 3
* 
* 그냥 탐색 하면 끝
* 
*/

#include<iostream>
#include<algorithm>
#include<vector>


using namespace std;

vector<int>print;

void search(vector<int>& v,int p) {

	for (int i = 0; i < p; i += 2) {
		sort(v.begin(), v.begin() + i + 1);
		print.push_back(v[i / 2]);
	}

}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;

	cin >> t;
	while (t--) {

		int m;
		cin >> m;
		
		vector<int>s(m);

		for (int& k : s)
			cin >> k;

		search(s, m);

		cout << print.size()<<"\n";
		
		for (int i = 0; i < (int)print.size(); i++) {

			cout << print[i] << " ";
			if ((i + 1) % 10 == 0)cout << "\n";
		}cout << "\n";
		print.clear();

	}

	return 0;
}