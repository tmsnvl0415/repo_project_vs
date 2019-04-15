/*
���� Ż���� ���簢�� ���忡 ���� ������ �Ķ� ������ �ϳ��� ���� ����, ���� ������ ������ ���� ������ �����̴�.
������ ���� ũ��� N, ���� ũ��� M�̰�, ���ǻ� 1��1ũ���� ĭ���� �������� �ִ�. 
���� �ٱ� ��� ���� ��� ������ �ְ�, ���忡�� ������ �ϳ� �ִ�. ���� ������ �Ķ� ������ ũ��� ���忡�� 1��1ũ���� ĭ�� ���� ä��� �������̰�, 
���� �ϳ��� �� �ִ�. ������ ��ǥ�� ���� ������ ������ ���ؼ� ������ ���̴�. �̶�, �Ķ� ������ ���ۿ� ���� �ȵȴ�.
�̶�, ������ ������ �ǵ帱 ���� ����, �߷��� �̿��ؼ� �̸� ���� ������ �Ѵ�. 
�������� ����̱�, ���������� ����̱�, �������� ����̱�, �Ʒ������� ����̱�� ���� �� ���� ������ �����ϴ�.
������ ���ۿ��� ���� ���ÿ� �����δ�. ���� ������ ���ۿ� ������ ����������, �Ķ� ������ ���ۿ� ������ �����̴�. 
���� ������ �Ķ� ������ ���ÿ� ���ۿ� ������ �����̴�. ���� ������ �Ķ� ������ ���ÿ� ���� ĭ�� ���� �� ����. 
��, ���� ������ �Ķ� ������ ũ��� �� ĭ�� ��� �����Ѵ�. ����̴� ������ �׸��ϴ� ���� �� �̻� ������ �������� ���� �� �����̴�.
������ ���°� �־����� ��, �ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

ù ��° �ٿ��� ������ ����, ���� ũ�⸦ �ǹ��ϴ� �� ���� N, M (3 �� N, M �� 10)�� �־�����. ���� N���� �ٿ� ������ ����� ��Ÿ���� ���� M�� ���ڿ��� �־�����. �� ���ڿ��� '.', '#', 'O', 'R', 'B' �� �̷���� �ִ�. '.'�� �� ĭ�� �ǹ��ϰ�, '#'�� ���� �̵��� �� ���� ��ֹ� �Ǵ� ���� �ǹ��ϸ�, 'O'�� ������ ��ġ�� �ǹ��Ѵ�. 'R'�� ���� ������ ��ġ, 'B'�� �Ķ� ������ ��ġ�̴�.
�ԷµǴ� ��� ������ �����ڸ����� ��� '#'�� �ִ�. ������ ������ �� �� �̸�, ���� ������ �Ķ� ������ �׻� 1���� �־�����.

�ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ����Ѵ�. ����, 10�� ���Ϸ� �������� ���� ������ ������ ���� ���� �� ������ -1�� ����Ѵ�.

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

//���� ����, �Ķ� ������ ��ġ �� ����ð� �����ϴ� ����ü
typedef struct _bead {
	int ry, rx, by, bx;
	int c;
}bead;

//�� �Ǵ� ���� �ٷ� �ձ��� �̵�
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
	int mi = 100;	//�̵� Ƚ��(�ð�)�� �ּ� �� �����ϴ� ����


	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int ry = q.front().ry;
			int rx = q.front().rx;
			int by = q.front().by;
			int bx = q.front().bx;
			int c = q.front().c;
			q.pop();
			if (c >= 10)continue;	//10�� �̻� �ɸ� ���̽��� ����

			for (int d = 0; d < 4; d++) {
				pair<int, int>nr;
				pair<int, int>nb;
				int nc = c;
				nr = move(d, ry, rx);
				nb = move(d, by, bx);
				nc++;

				//B�� O�� �������� ��
				if (nb.first + dy[d] == Hy && nb.second + dx[d] == Hx)
					continue;
				//R�� O�� �������� ��
				else if (nr.first + dy[d] == Hy && nr.second + dx[d] == Hx) {
					mi = min(mi, nc);
					continue;
				}
				// -> �ٷ� �������� �ʴ� ����: �ٸ� ����� ���� ����� �Ѵ�!


				//O�� ���������� �ʰ�, �̵����� �ʾ��� ���(������) - �ʿ���� ����� �� ���̱�
				else if (nr == make_pair(ry, rx) && nb == make_pair(by, bx))continue;

				//������ ��: ����� ����� ���� ��ǥ�� ���ؼ� ����߸���.
				else if (nr == nb) {
					switch (d)
					{
					case 0:if (ry < by)nb.first += 1;	//��
						   else nr.first += 1;
						   break;
					case 1:if (rx > bx)nb.second -= 1;	//��
						   else nr.second -= 1;
						   break;
					case 2:if (ry > by)nb.first -= 1;	//��
						   else nr.first -= 1;
						   break;
					case 3:if (rx < bx)nb.second += 1;	//��
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
			//���� ���� ��ġ ����
			if (map[i][j] == 'R') {
				Ry = i;
				Rx = j;
			}
			//�Ķ� ���� ��ġ ����
			else if (map[i][j] == 'B') {
				By = i;
				Bx = j;
			}
			//���� ��ġ ����
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



