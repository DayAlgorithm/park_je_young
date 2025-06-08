/*

Problem_Solving_Time PM 1:35 - 3:18

한 학기에 들을 수 있는 과목 수 에는 제한이 없다.

모든 과목은 매 학기 항상 개설된다.

선수과목 조건은 M개의 줄에 걸쳐 입력이 된다

그럼 선수 과목이 어느 정도 남았는지 판단하고

dfs에서 다음 노드를 다루는 방식으로 설정한다.

(하지만 이게 위상정렬이고, 풀때 위상정렬을 쓴다는 생각을 안하고

위상정렬을 사용했긴했다..)



일단 입력시 x to y 로 node 를 설정한다.

노드 정보는 모두 제일 큰 값으로 설정한다.

왜냐면 나중에 비교시 큰 값으로 설정 하지 않으면

그 노드가 가지고 있는 정보에서 얘가 어느 정도 걸렸는지 

최솟값으로 판단하는데, 그게 안먹히기 때문이다.

어쨌든 일방향 노드로 설정되고, 

그 일방향 노드 + 진입 차수로 시작 노드를 설정한다.

이때 진입차수는 진입시 감소된다.

왜냐면 진입 하고 남은 노드들이 이정도 있다는 걸 알려줘야

이걸 들을 수 있는지 없는지 판단이 가능 하기 때문이다.

(첨에 진입차수를 감소하지 않고 그냥 돌려버려 노드를 2번 돌리는, o(n + e) 정도의 시간복잡도가

나오는 코드를 짜버려서 잘못 풀었다.)

그럼 이제 진입 차수 + 노드정보를 이용해서 노드 정보를 업데이트 및 입력을 하고

그 뒤에 각 노드의 정보를 출력하는 형식으로 갔다.

++큐에서 몇번째에 접근하는지를 알아야 하므로, deque 를 이용했다.

*/

#include<iostream>
#include<vector>
#include<deque>
#include<climits>
using namespace std;

vector<vector<int>>node;
vector<int>node_info;
vector<int>indegree;
deque<int>q;



void checking() {
	for (int i = 1; i < (int)indegree.size(); i++) {
		if (indegree[i] == 0) {
			node_info[i] = 1;
			q.push_back(i);
		}
	}
	while (!q.empty()) {
		int x = q.front();
		q.pop_front();
		for (int iter : node[x]) {
			
			indegree[iter]--;
			if (indegree[iter] == 0)
				q.push_back(iter);

			if (node_info[iter] > node_info[x] + 1 && !indegree[iter]) {
				node_info[iter] = node_info[x] + 1;
			}
			
		}
	}
}



int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	node.resize(n + 1);
	node_info.resize(n + 1, INT_MAX);
	node_info[1] = 1;
	indegree.assign(n + 1, 0);
	for (int i = 0; i < m; i++) {
		int start_, end_;
		cin >> start_ >> end_;

		node[start_].push_back(end_);

		indegree[end_]++;
	}

	checking();
	for (int i = 0; i < n; i++) {	
		cout << node_info[i + 1] << " ";
	}
	return 0;
}