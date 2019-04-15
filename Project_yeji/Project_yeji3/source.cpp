﻿/*
부동산 투자로 억대의 돈을 번 상도는 최근 N×N 크기의 땅을 구매했다. 상도는 손쉬운 땅 관리를 위해 땅을 1×1 크기의 칸으로 나누어 놓았다. 
각각의 칸은 (r, c)로 나타내며, r은 가장 위에서부터 떨어진 칸의 개수, c는 가장 왼쪽으로부터 떨어진 칸의 개수이다. r과 c는 1부터 시작한다.
상도는 전자통신공학과 출신답게 땅의 양분을 조사하는 로봇 S2D2를 만들었다. S2D2는 1×1 크기의 칸에 들어있는 양분을 조사해 상도에게 전송하고, 
모든 칸에 대해서 조사를 한다. 가장 처음에 양분은 모든 칸에 5만큼 들어있다.
매일 매일 넓은 땅을 보면서 뿌듯한 하루를 보내고 있던 어느날 이런 생각이 들었다.
나무 재태크를 하자
나무 재테크란 작은 묘목을 구매해 어느정도 키운 후 팔아서 수익을 얻는 재테크이다. 상도는 나무 재테크로 더 큰 돈을 벌기 위해 M개의 나무를 구매해 땅에 심었다. 같은 1×1 크기의 칸에 여러 개의 나무가 심어져 있을 수도 있다.
이 나무는 사계절을 보내며, 아래와 같은 과정을 반복한다.
봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다. 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다. 
하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다. 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.
여름에는 봄에 죽은 나무가 양분으로 변하게 된다. 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 소수점 아래는 버린다.
가을에는 나무가 번식한다. 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다. 
어떤 칸 (r, c)와 인접한 칸은 (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1) 이다. 
상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.
겨울에는 S2D2가 땅을 돌아다니면서 땅에 양분을 추가한다. 각 칸에 추가되는 양분의 양은 A[r][c]이고, 입력으로 주어진다.
K년이 지난 후 상도의 땅에 살아있는 나무의 개수를 구하는 프로그램을 작성하시오.

첫째 줄에 N, M, K가 주어진다.
둘째 줄부터 N개의 줄에 A배열의 값이 주어진다. r번째 줄의 c번째 값은 A[r][c]이다.
다음 M개의 줄에는 상도가 심은 나무의 정보를 나타내는 세 정수 x, y, z가 주어진다. 처음 두 개의 정수는 나무의 위치 (x, y)를 의미하고, 마지막 정수는 그 나무의 나이를 의미한다.

첫째 줄에 K년이 지난 후 살아남은 나무의 수를 출력한다.

•1 ≤ N ≤ 10
•1 ≤ M ≤ N2
•1 ≤ K ≤ 1,000
•1 ≤ A[r][c] ≤ 100
•1 ≤ 입력으로 주어지는 나무의 나이 ≤ 10
•입력으로 주어지는 나무의 위치는 모두 서로 다름

example result
input
5 2 5
2 3 2 3 2
2 3 2 3 2
2 3 2 3 2
2 3 2 3 2
2 3 2 3 2
2 1 3
3 2 3
output 
13
*/


#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX 10

bool valid_xy(int x, int y);

int N, M, K;
int A[MAX][MAX];			//매년 더해지는 양분
int nutri[MAX][MAX];		//지금 있는 양분
vector<int>tree[MAX][MAX];

int dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int dy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

int main(int argc, char **argv)
{
	cin >> N >> M >> K;
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cin >> A[i][j];
			nutri[i][j] = 5;
			tree[i][j].clear();
		}
	}
	for (size_t i = 0; i < M; i++)
	{
		int x, y, age;
		cin >> y >> x >> age;
		y--;
		x--;
		tree[y][x].push_back(age);
	}

	int year = 0;
	while (year != K)
	{
		//봄이랑 여름
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				int tree_num = tree[i][j].size();
				int die_num = -1;		// 죽어야할 나무들의 최초 순번
				for (size_t k = 0; k < tree_num; k++)
				{
					if (nutri[i][j] < tree[i][j][k])
					{
						die_num = k;
						break;
					}
					nutri[i][j] -= tree[i][j][k];
				}
				// 죽는 나무가 있는 경우
				if (die_num != -1)
				{
					int die_tree_numbers = tree_num - die_num; // 죽는 나무 개수.
					for (size_t k = 0; k < die_tree_numbers; k++)
					{
						nutri[i][j] += tree[i][j].back() / 2;
						tree[i][j].pop_back();
					}
				}
				// 양분 먹은 나무들은 나이 증가
				tree_num = tree[i][j].size();
				for (size_t k = 0; k < tree_num; k++)
				{
					tree[i][j][k]++;
				}
			}
		}

		//가을
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				int tree_num = tree[i][j].size();
				for (size_t k = 0; k < tree_num; k++)
				{
					if (tree[i][j][k] % 5 == 0) // 5의 배수 인 경우
					{
						for (size_t l = 0; l < 8; l++)
						{
							int nx = j + dx[l];
							int ny = i + dy[l];
							if (valid_xy(nx, ny)) {
								tree[ny][nx].push_back(1);	// 주변(ny, nx)에 나이가 1인 나무 번식
							}
						}
					}
				}
			}
		}

		//겨울
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				nutri[i][j] += A[i][j];
			}
		}

		//나무를 나이 순으로 정렬
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				sort(tree[i][j].begin(), tree[i][j].end());
			}
		}
		year++;
	}

	int sum_of_trees = 0;
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			sum_of_trees += tree[i][j].size();
		}
	}
	cout << sum_of_trees;
	return 0;
}

bool valid_xy(int x, int y) 
{
	return x < N && y < N && x >= 0 && y >= 0;
}





