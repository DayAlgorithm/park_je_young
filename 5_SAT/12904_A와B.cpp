/*
* 
* Problem_Solving_Time AM 11:10 - 11 : 40
* 
* �������� ������ ���̴�,
* 
* ó���� ��ͷ� ���ȴٰ� �ð��ʰ� �߰�
* 
* ���� �� ȿ�������� �Ǵ� �ǰ� �ϴٰ� �������� �ϴ�, ���� ���Դ�.
* 
*/
#include<iostream>
#include<string>
#define REAL ios::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;

string h1, h2;


bool change(string a) {
	
	while (!a.empty()) {

		char c = a.back();
		a.pop_back();
		if (c == 'A') {
			if (a == h1)return 1;
		}
		else {
			string temp;
			for (int i = a.size() - 1; i >= 0; i--) {
				temp.push_back(a[i]);
			}
			a = temp;
			if (a == h1)return 1;
		}

	}
	return 0;
}

int main(void) {
	REAL;

	cin >> h1 >> h2;




	cout << change(h2);
	return 0;
}