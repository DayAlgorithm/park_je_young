#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main(){

	cin.tie(nullptr)->sync_with_stdio(false);

	int n, m; cin >> n >> m;
	
	vector<vector<bool>>lamp(n, vector<bool>(m, false)), temp;

	for(int i = 0; i < n; i++){
		string h;
		cin >> h;
		for(int j = 0; j < m; j++){
			lamp[i][j] = (h[j] == '0' ? false : true);
		}
	}	temp = lamp;


	// 최대 치를 모두 구한다, 그다음 그게 k 번에서 가능한지를 조사 한다.

	int max_odd = 0, max_even = 0;

	int k = 0;
	
	cin >> k;
	
	for(int i = 0; i < n; i++, lamp = temp){
		
		int cnt_num = 0;

		// serach
		vector<int>cnt;
		for(int j = 0; j < m ; j++){
			if(!lamp[i][j])
				cnt.push_back(j);
		}
		for(const int& F : cnt){
			for(int j = 0; j < n; j++){
				lamp[j][F] = !lamp[j][F];
			}
		}
		
		for(int u = 0; u < n; u++){ // 체킹된 램프를 모은다.
			bool check = true;
			for(int v = 0; v < m; v++){
				if(!lamp[u][v]){
					check = false;
					break;
				}
			}
			if(check){
				cnt_num++;
			}
		}

		if (cnt.size() <= k) {
			if (cnt.size() % 2 == 0)
				max_even = max(max_even, cnt_num);
			else
				max_odd  = max(max_odd,  cnt_num);
		}
	}

	
	cout << (k % 2 == 0 ? max_even : max_odd);

	return 0;
}