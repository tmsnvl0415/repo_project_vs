/*
Consider the following 4 x 4 array.

If we turn on the switch in the position (the 2nd row, the 2nd column), the array becomes...
If we turn on the switch in the position (the 3rd row, the 3rd column), the array becomes…

Given an n x n binary array corresponding to the target on/off state, your program should find switches to push, to make the final on/off state.
As the number of switches is smaller, you will get better score.
Initial state is that all bulbs are in off-states.
Each switch changes the states of the bulb in the same position and its (at most four) possible neighbors.
ON  OFF & OFF  ON
‘#’ means off-state and ‘O’ means on-state.
Note that the positive integer n is less than or equal to 10.
If there are more than one solution, print one of them. If there is no solution, print “no solution.\n”.

example result:
Input 
4                                  n
O O O O                          final state
O O O O
O O O O
O O O O
Output 
O # # O                          switches to push
# # # #
# O O #
# O O #
*/


#include <iostream>
#include <cstdlib>
using namespace std;

void what_light_on(int i);
bool promising(int i);
void toggle(char** &target, int i);
void toggle(char** &target, int i, int j);
void combinationUtil(int arr[], int data[], int start, int end, int index, int r);
void SaveCombination(int n, const int r);
int nCr(int n, int r);

static char **inputset, **outputset, **middleset, **minoutput;
static int n;
static long int best_solution = 100000;
static int click = 0;
bool hassolution = false;
static int r;

static int FirstRow[253][10];
int Row_index = 0;
int FirstRow_index = 0;

void main() 
{
	bool realSolution = false;
	cin >> n;
	inputset = (char **)calloc(n, sizeof(char*) * n);
	outputset = (char **)calloc(n, sizeof(char*) * n);
	middleset = (char **)calloc(n, sizeof(char*) * n);
	minoutput = (char **)calloc(n, sizeof(char*) * n);

	for (int i = 0; i < n; i++) 
	{
		inputset[i] = (char *)calloc(n, sizeof(char) * n);
		outputset[i] = (char *)calloc(n, sizeof(char) * n);
		middleset[i] = (char *)calloc(n, sizeof(char) * n);
		minoutput[i] = (char *)calloc(n, sizeof(char) * n);
	}

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			outputset[i][j] = '#';
			middleset[i][j] = '#';
		}
	}
	//input set, outputset, middleset, minoutput 동적할당
	//outputset, middleset 초기화

	if (n <= 0 || n > 10) 
	{
		cout << "1이상 10 이하의 수를 입력해주세요"
			<< endl << "프로그램이 종료됩니다." << endl;
	}
	//n이 범위를 넘어가면 프로그램을 종료한다.

	else 
	{
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++) 
			{
				cin >> inputset[i][j];
			}
		}
		cout << endl;
		r = 0;
		while (r <= n) 
		{
			Row_index = 0;
			for (int i = 0; i < 253; i++) 
			{
				for (int j = 0; j < 10; j++) 
				{
					FirstRow[i][j] = 0;
				}
			}
			SaveCombination(n, r);			
			int ncr = nCr(n, r);
			for (FirstRow_index = 0; FirstRow_index < ncr; FirstRow_index++) 
			{
				click = 0;
				for (int i = 0; i < n; i++) 
				{
					for (int j = 0; j < n; j++) 
					{
						outputset[i][j] = '#';
						middleset[i][j] = '#';
					}
				}
				what_light_on(0);
				if (hassolution == true) 
				{
					realSolution = true;
					if (best_solution > click) 
					{
						best_solution = click;
						for (int i = 0; i < n; i++) 
						{
							for (int j = 0; j < n; j++) 
							{
								minoutput[i][j] = outputset[i][j];
							}
						}
					}
				}
				hassolution = false;
			}
			r++;
		}
		if (realSolution == true) 
		{
			for (int i = 0; i < n; i++) 
			{
				for (int j = 0; j < n; j++)
				{
					cout << minoutput[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl << " best_solution= " << best_solution << endl;
		}
		else 
		{
			cout << "no Solution" << endl;
		}
	}
	delete[] inputset;
	delete[] outputset;
	delete[] minoutput;
	delete[] middleset;
}

//backtracking 하여 어떤 불이 켜져야 할지 정하는 
void what_light_on(int i)
{
	if (promising(i)) 
	{
		if (i == n)	//has solution
		{
			if (promising(i + 1)) 
			{
				hassolution = true;
			}
			else {
				hassolution = false;
			}
		}
		else
		{
			toggle(middleset, i);
			what_light_on(i + 1);
		}
	}
	else 
	{
		hassolution = false;
	}
}

bool promising(int i)
{
	bool promising = true;
	int t = 0;
	if (i >= 2) 
	{
		while (promising == true && t < n) 
		{
			if (inputset[i - 2][t] != middleset[i - 2][t]) 
			{
				promising = false;
			}
			t++;
		}
	}
	return promising;
}

void toggle(char** &target, int i) 
{
	if (i == 0) 
	{
		for (int j = 0; j < r; j++) 
		{
			toggle(target, 0, FirstRow[FirstRow_index][j]);
		}
	}
	//i가 0이 아닐때, 첫번째 줄이 아닐때
	else 
	{
		for (int j = 0; j < n; j++) 
		{
			if (inputset[i - 1][j] == 'O') 
			{
				if (target[i - 1][j] == '#')
				{
					toggle(target, i, j);
				}
			}
			else if (inputset[i - 1][j] == '#') 
			{
				if (target[i - 1][j] == 'O') 
				{
					toggle(target, i, j);
				}
			}
		}
	}
	//자신의 위의 행과 비교
}

//i, j를 눌렀다고 가정하고 middleset의 상태를 바꿀 수 있게 해준다.
void toggle(char** &target, int i, int j) 
{
	if ((i < n) && (j < n) && (i >= 0) && (j >= 0)) 
	{
		if (target[i][j] == 'O')
			target[i][j] = '#';
		else if (target[i][j] == '#')
			target[i][j] = 'O';
		if ((i < n - 1)) 
		{
			if (target[i + 1][j] == 'O')
				target[i + 1][j] = '#';
			else if (target[i + 1][j] == '#')
				target[i + 1][j] = 'O';
		}
		if (i >= 1) 
		{
			if (target[i - 1][j] == 'O')
				target[i - 1][j] = '#';
			else if (target[i - 1][j] == '#')
				target[i - 1][j] = 'O';
		}
		if (j >= 1) 
		{
			if (target[i][j - 1] == 'O')
				target[i][j - 1] = '#';
			else if (target[i][j - 1] == '#')
				target[i][j - 1] = 'O';
		}
		if (j < n - 1)
		{
			if (target[i][j + 1] == 'O')
				target[i][j + 1] = '#';
			else if (target[i][j + 1] == '#')
				target[i][j + 1] = 'O';
		}
		outputset[i][j] = 'O';
		click++;
	}
}

//Combination의 모든 경우를 저장하게 하는 함수
void SaveCombination(int n, const int r)
{
	if (r > 0) 
	{
		int *data, *arr;
		data = (int *)calloc(r, sizeof(int) * r);
		arr = (int *)calloc(r, sizeof(int) * n);
		for (int i = 1; i <= n; i++)
			arr[i - 1] = i;
		combinationUtil(arr, data, 0, n - 1, 0, r);
	}
}
//재귀적으로 Combination의 모든 경우의 수를 저장하는 함수					
void combinationUtil(int arr[], int data[], int start, int end,	int index, int r)
{
	// Current combination is ready to be printed, print it
	if (index == r) 
	{
		for (int j = 0; j < r; j++) 
		{
			FirstRow[Row_index][j] = data[j] - 1;
		}
		Row_index++;
		return;
	}

	// replace index with all possible elements. The condition
	// "end-i+1 >= r-index" makes sure that including one element
	// at index will make a combination with remaining elements
	// at remaining positions
	for (int i = start; i <= end && end - i + 1 >= r - index; i++)
	{
		data[index] = arr[i];
		combinationUtil(arr, data, i + 1, end, index + 1, r);
	}
}

// n choose r의 경우의 수
int nCr(int n, int r)
{
	if (n == r || r == 0) return 1;
	if (r == 1) return n;
	return nCr(n - 1, r) + nCr(n - 1, r - 1);
}