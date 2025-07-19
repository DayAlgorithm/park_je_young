/*
	1. 벨트의 임의의 한 위치부터 k 개의 접시를 연속해서 먹을 경우,
	할인된 가격으로 제공.

	2. 각 고객에게 초밥의 종류가 하나 쓰인 쿠폰을 발행
	그리고, 1번 행사에 참가 할 경우, 이 쿠폰이 적혀진 종류의 초밥을 언제든지 제공.
	(1 번은 무조건 지키니깐, 걍 번호가 중복되지 않은 초밥 가짓수에 1을 더해 준다.)

	회전 초밥 음식점의 벨트 상태,
	메뉴에 있는 초밥의 가짓수,
	연속해서 먹는 접시의 개수,
	쿠폰 번호

	가 주어 졌을때, 손님이 먹을 수 있는 초밥 가짓수의 최댓값을 구하시오.

	회전 초밥 벨트에 놓인 접시의 수 : N
	초밥의 가짓수 : d
	연속해서 먹는 접시의 수 : k
	쿠폰 번호 c

	크기가 k 인 배열을 생성하고, k 만큼으로 담을 수 있는

	모든 경우를 다 담아 본다, 그리고 정렬은 알아서 하도록 하고,

	그럼 완성된 가짓수가 나오는데, 거기서 c를 포함하지 않는 걸로 간다.

	만약 모두 포함이 되 있을 경우, 어쩔 수 없이 그나마 경우의 수가 작은 걸로 간다.

	data struct 는 다음과 같이 정의 한다.

	{ (k 개 만큼의 담은 실질적인 값들 ), 총 경우의 수, c를 포함하고 있는가? }
	== { vector, int, bool}



*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

struct info {
	int occ;

	bool check;

	info(int Occ, bool Check) : occ(Occ), check(Check) {}
	//생성자.
};
int n, d, k, c;

struct info counting(map<int, int>cnt) {

	struct info all_temp(0, false);

	for (auto& iter : cnt) {
		all_temp.occ += iter.second > 0 ? 1 : 0;
		if (iter.first == c && iter.second > 0)all_temp.check = true;
	}
	return all_temp;

}


int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	cin >> n >> d >> k >> c;

	vector<int>v(n);
	map<int, int>occasion;

	struct info max_info(0, 0);

	for (auto& i : v) {
		cin >> i;
		occasion[i] = 0;
	}

	for (int i = 0; i < k; i++) {
		if(occasion[v[i]]++ == 0)max_info.occ++;
		 
		max_info.check = (occasion[c] > 0 ? true : false);
	}

	int unique = max_info.occ;
	bool check_tmp = false;

	for (int i = 1; i < n; i++) {

		if(occasion[v[i - 1]]-- == 1)unique--;

		if(occasion[v[(i + k - 1) % n]]++ == 0)unique++;

		if(occasion[c] > 0)check_tmp = true;

		else check_tmp = false;

		if(unique > max_info.occ){
			max_info.occ = unique;
			max_info.check = check_tmp;
		}
		if(unique == max_info.occ && !check_tmp)max_info.check = false;

		if(max_info.occ == k && !max_info.check){
			cout<<k + 1;
			return 0;
		}
	}

	cout << max_info.occ + (max_info.check ? 0 : 1);


	return 0;
}