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

	//�� ���� ��� û�Ұ� �̹� �Ǿ��ְų� ���̸� �ٶ󺸴� ������ ������ ä�� �� ĭ ������ �ϰ� 2������ ���ư�    
	if (cnt == 4 || map[nextY][nextX] == 1) {
		if (dir == 0) nextY++;
		if (dir == 1) nextX--;
		if (dir == 3) nextX++;
		if (dir == 2) nextY--;

		//�ڿ��� ���̶� ������ �Ұ����ϸ�
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

	//���� ��ġ û��
	if (map[y][x] == 0) {
		ret++;
		map[y][x] = 2;
	}


	//���ʹ������ ���ʷ� Ž���� ����
	dir = (dir + 3) % 4;

	if (dir == 0) nextY--;
	else if (dir == 1) nextX++;
	else if (dir == 3) nextX--;
	else if (dir == 2) nextY++;

	//���� ���⿡ ���� û������ ���� ������ �����Ѵٸ� �� �������� ȸ���� ���� �� ĭ�� �����ϰ� 1������ ����
	if (map[nextY][nextX] == 0) {
		y = nextY;
		x = nextX;
		solve(0);
		return;
	}

	//���� ���⿡ û���� ������ ���ٸ� �� �������� ȸ���ϰ� 2������ ���ư�
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
