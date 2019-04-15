#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX_NUM 52

int map[MAX_NUM][MAX_NUM];
int N, M;
int x, y, dir;
int ret = 0;
bool flag = 0;

void solve(int cnt) {
	if (flag == 1) return;

	int nextY = y;
	int nextX = x;

	//네 방향 모두 청소가 이미 되어있거나 벽이면 바라보는 방향을 유지한 채로 한 칸 후진을 하고 2번으로 돌아감    
	if (cnt == 4 || map[nextY][nextX] == 1) {
		if (dir == 0) nextY++;
		if (dir == 1) nextX--;
		if (dir == 3) nextX++;
		if (dir == 2) nextY--;

		//뒤에가 벽이라 후진이 불가능하면
		if (map[nextY][nextX] == 1) {
			flag = 1;
			return;
		}
		else {
			y = nextY;
			x = nextX;
			solve(0);
			return;
		}
	}

	//현재 위치 청소
	if (map[y][x] == 0) {
		ret++;
		map[y][x] = 2;
	}


	//왼쪽방향부터 차례로 탐색을 진행
	dir = (dir + 3) % 4;

	if (dir == 0) nextY--;
	else if (dir == 1) nextX++;
	else if (dir == 3) nextX--;
	else if (dir == 2) nextY++;

	//왼쪽 방향에 아직 청소하지 않은 공간이 존재한다면 그 방향으로 회전한 다음 한 칸을 전진하고 1번부터 진행
	if (map[nextY][nextX] == 0) {
		y = nextY;
		x = nextX;
		solve(0);
		return;
	}

	//왼쪽 방향에 청소할 방향이 없다면 그 방향으로 회전하고 2번으로 돌아감
	else {
		solve(cnt + 1);
		return;
	}

	return;
}
int main()
{
	ios::sync_with_stdio(false);

	cin >> N >> M;
	cin >> y >> x >> dir;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	solve(0);

	cout << ret;

}
