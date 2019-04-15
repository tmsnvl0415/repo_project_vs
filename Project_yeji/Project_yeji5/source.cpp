/*
구슬 탈출은 직사각형 보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음, 빨간 구슬을 구멍을 통해 빼내는 게임이다.
보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다. 
가장 바깥 행과 열은 모두 막혀져 있고, 보드에는 구멍이 하나 있다. 빨간 구슬과 파란 구슬의 크기는 보드에서 1×1크기의 칸을 가득 채우는 사이즈이고, 
각각 하나씩 들어가 있다. 게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다. 이때, 파란 구슬이 구멍에 들어가면 안된다.
이때, 구슬을 손으로 건드릴 수는 없고, 중력을 이용해서 이리 저리 굴려야 한다. 
왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.
각각의 동작에서 공은 동시에 움직인다. 빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다. 
빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다. 빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다. 
또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다. 기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.
보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.

첫 번째 줄에는 보드의 세로, 가로 크기를 의미하는 두 정수 N, M (3 ≤ N, M ≤ 10)이 주어진다. 다음 N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열이 주어진다. 이 문자열은 '.', '#', 'O', 'R', 'B' 로 이루어져 있다. '.'은 빈 칸을 의미하고, '#'은 공이 이동할 수 없는 장애물 또는 벽을 의미하며, 'O'는 구멍의 위치를 의미한다. 'R'은 빨간 구슬의 위치, 'B'는 파란 구슬의 위치이다.
입력되는 모든 보드의 가장자리에는 모두 '#'이 있다. 구멍의 개수는 한 개 이며, 빨간 구슬과 파란 구슬은 항상 1개가 주어진다.

최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력한다. 만약, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 -1을 출력한다.

example result:
input
5 5
#####
#..B#
#.#.#
#RO.#
#####
output
1
*/


#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

#define MAX 10
int N, M;
char map[MAX][MAX];
int Ry, Rx, By, Bx;
int Hy, Hx;
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };

//빨간 구슬, 파란 구슬의 위치 및 경과시간 저장하는 구조체
typedef struct _bead {
	int ry, rx, by, bx;
	int c;
}bead;

//벽 또는 구멍 바로 앞까지 이동
pair<int, int>move(int dir, int y, int x) {
	int ny = y, nx = x;
	if (dir == 0) {
		while (map[ny][nx] != '#' && map[ny][nx] != 'O')
			ny -= 1;
		ny += 1;
	}
	else if (dir == 1) {
		while (map[ny][nx] != '#' && map[ny][nx] != 'O')
			nx += 1;
		nx -= 1;
	}
	else if (dir == 2) {
		while (map[ny][nx] != '#' && map[ny][nx] != 'O')
			ny += 1;
		ny -= 1;
	}
	else if (dir == 3) {
		while (map[ny][nx] != '#' && map[ny][nx] != 'O')
			nx -= 1;
		nx += 1;
	}

	return make_pair(ny, nx);
}

int bfs() {
	queue<bead>q;
	bead start;
	start.ry = Ry;
	start.rx = Rx;
	start.by = By;
	start.bx = Bx;
	start.c = 0;
	q.push(start);
	int mi = 100;	//이동 횟수(시간)의 최소 값 저장하는 변수


	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int ry = q.front().ry;
			int rx = q.front().rx;
			int by = q.front().by;
			int bx = q.front().bx;
			int c = q.front().c;
			q.pop();
			if (c >= 10)continue;	//10번 이상 걸린 케이스는 생략

			for (int d = 0; d < 4; d++) {
				pair<int, int>nr;
				pair<int, int>nb;
				int nc = c;
				nr = move(d, ry, rx);
				nb = move(d, by, bx);
				nc++;

				//B가 O에 접근했을 때
				if (nb.first + dy[d] == Hy && nb.second + dx[d] == Hx)
					continue;
				//R만 O에 접근했을 때
				else if (nr.first + dy[d] == Hy && nr.second + dx[d] == Hx) {
					mi = min(mi, nc);
					continue;
				}
				// -> 바로 리턴하지 않는 이유: 다른 경우의 수도 살펴야 한다!


				//O에 근접하지도 않고, 이동하지 않았을 경우(막혀서) - 필요없는 경우의 수 줄이기
				else if (nr == make_pair(ry, rx) && nb == make_pair(by, bx))continue;

				//겹쳤을 때: 기울인 방향과 이전 좌표를 비교해서 떨어뜨린다.
				else if (nr == nb) {
					switch (d)
					{
					case 0:if (ry < by)nb.first += 1;	//북
						   else nr.first += 1;
						   break;
					case 1:if (rx > bx)nb.second -= 1;	//동
						   else nr.second -= 1;
						   break;
					case 2:if (ry > by)nb.first -= 1;	//남
						   else nr.first -= 1;
						   break;
					case 3:if (rx < bx)nb.second += 1;	//서
						   else nr.second += 1;
						   break;
					default:
						break;
					}
				}

				bead next;
				next.ry = nr.first;
				next.rx = nr.second;
				next.by = nb.first;
				next.bx = nb.second;
				next.c = nc;
				q.push(next);
			}
		}
	}
	if (mi != 100)
		return mi;
	else
		return -1;
}

int main() {
	int rst = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			//빨간 구슬 위치 저장
			if (map[i][j] == 'R') {
				Ry = i;
				Rx = j;
			}
			//파란 구슬 위치 저장
			else if (map[i][j] == 'B') {
				By = i;
				Bx = j;
			}
			//구멍 위치 저장
			else if (map[i][j] == 'O') {
				Hy = i;
				Hx = j;
			}
		}
	}

	rst = bfs();
	cout << rst << endl;

	return 0;
}



