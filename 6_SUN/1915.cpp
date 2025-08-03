#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

/*

	Brute_force,

	Big-O => o(n^2)

	
*/

int main(){

	cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	int a = min(n, m);
	
	vector<string>A(n);
	vector<vector<int>>PS(n + 1, vector<int>(m + 1, 0));

	for(auto& i : A)cin >> i;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			PS[i + 1][j + 1] 
			= 
			PS[i][j + 1] + PS[i + 1][j] - PS[i][j] + (A[i][j] == '0' ? 0 : 1); 
		}
	}

	int Max_s = 0;

	for(int rc = 1; rc <= a; rc++){

		int S = rc * rc;

		for(int i = 0; i + rc <= n; i++){
			for(int j = 0; j + rc <= m; j++){
				int condition 
				= 
				PS[i + rc][j + rc] - PS[i][j + rc] - PS[i + rc][j] + PS[i][j];

				if(condition == S)
					Max_s = max(Max_s, S);
			}
		}

	}

	cout << Max_s;

	return 0;
}