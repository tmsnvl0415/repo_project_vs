/*
For a set of given sorted distinct positive integers from V1 through VN, 
one can partition the set into two sets whose sums are identical.
This counts as a single partitioning. 
That is, reversing the order counts as the same partitioning and thus does not increase the count of partitions.
If N = 7 & the given set is {1, 2, 3, 4, 5, 6, 7}, 
there are four ways to partition the set so that each subset has the same sum.
{1,6,7}, {2,3,4,5}
{2,5,7}, {1,3,4,6}
{3,4,7}, {1,2,5,6}
{1,2,4,7}, {3,5,6}

Given N (1 ≤ N ≤ 500) & sorted elements of N distinct positive integers, 
your program should print the number of ways a set containing the integers 
from V1 through VN can be partitioned into two sets whose sums are identical, 
and print a partition among them. Just print 0 if there are no such ways. “0\n” means the end of input.
If the number of same-sum partitions is larger than ULONG_MAX (232-1), 
your program may just print “NUMEROUS\n” as the number.
Note that each integer element in the set is larger than or equal to 1 and it is less than or equal to 500.

Standard/Console Input
The input contains a series of double lines with a single integer 
representing N in the first line and sorted elements of N distinct positive integers in the next line, as above.
“0\n” means the end of input.

Standard/Console Output
For each input, the output consists of a single line with a single integer 
that tells how many same-sum partitions can be made from the set {V1, V2, ..., VN}, 
and another single line with one such partition.
The output should be 0 if there are no ways to make a same-sum partition.

Input (standard/console input)
3
1 2 3
7
1 2 3 4 5 6 7
12
1 2 3 4 5 6 7 8 9 10 11 12
0                                          the end of input
Output (standard/console output)
1
{1,2},{3}                                  different answer is possible
4
{1,6,7},{2,3,4,5}                          different answer is possible
62
{1,2,3,4,5,6,8,10},{7,9,11,12}      
*/

#include <stdio.h>
#include <stdlib.h>
#include <map>

void num_combinations(unsigned int set[], int size, unsigned long long sum);

int main()
{
	unsigned int set[500] = { 0, };
	int size = 0;
	scanf_s("%d", &size);
	while (size > 0)
	{
		unsigned long long sum = 0;
		for (int i = 0; i < size; i++)
		{
			scanf_s("%d", &set[i]);
			sum += set[i];
		}
		if (sum % 2 != 0)
		{
			printf("0\n");
		}
		else
			num_combinations(set, size, sum / 2);

		printf("\n\n");
		scanf_s("%d", &size);
	}
}

void num_combinations(unsigned int set[], int size, unsigned long long sum)
{
	//예외처리
	if (sum > ULONG_MAX)
	{
		printf("NUMEROUS\n");
		return;
	}
	std::map<unsigned int, std::map<unsigned long long, unsigned long long>> P; //마지막은 원하는 결과값
																				//초기화
	for (int i = 0; i < size; i++)
	{
		unsigned int K = set[i];
		P[K][K] = 1;
	}
	std::map<unsigned long long, unsigned long long> Pn, subset_left, subet_right;
	//두 부분집합으로 나뉘어 질 수 있는 총 가지수를 구하는 부분
	for (int i = 1; i<size; i++)
	{
		unsigned int K = set[i];
		for (int j = 3; j <= sum; j++)
		{
			if (((K - 1) == 1) && (K<j))
			{
				P[K][j] = P[K - 1][j - K];
			}
			else if (((K - 1) != 1) && (K<j))
			{
				for (int t = 1; t < K; t++)
				{
					P[K][j] += P[K - t][j - K];
				}
			}
		}
	}

	/*Pn[sum]은 구하고자하는 가지수의 총합이다.
	P배열의 가장 끝 열 sum에 있는 모든 값을 더해주면
	합을 구할 수 있는 모든 가지수가 나온다*/
	Pn[sum] = 0;
	for (int i = 0; i<size; i++)
	{
		unsigned int K = set[i];
		Pn[sum] += P[K][sum];
	}
	//중복되는 것을 해결하기 위하여 총가지수 나누기 2
	printf("%d\n", Pn[sum] / 2);

	/*배열의 가장 마지막 부분인 P[K][sum]부터 시작하여
	합을 구할 수 있는 가지수가 있는지 확인 한 후,
	있으면 해당되는 K의 값을subset_left배열에 넣어준다*/
	for (int i = size - 1; i >= 0; i--)
	{
		if (sum <= 0)
			break;
		unsigned int K = set[i];
		if (P[K][sum] >= 1)
		{
			sum = sum - K;
			subset_left[i] = K;
		}
	}

	//sunset_left에 저장되지 않은 모든 K의 값을 subset_right에 넣어준다
	for (int i = size - 1; i >= 0; i--)
	{
		unsigned int K = set[i];
		if (subset_left[i] == 0)
		{
			subet_right[i] = K;
		}
	}

	//각 배열에 저장된 것을 순서대로 출력해준다
	printf("{");
	for (int i = 0; i< size; i++)
	{
		unsigned int K = set[i];
		if (subset_left[i] != 0)
		{
			printf("%d ", K);
		}
	}
	printf("}");
	printf(" {");
	for (int i = 0; i< size; i++)
	{
		unsigned int K = set[i];
		if (subet_right[i] != 0)
		{
			printf("%d ", K);
		}
	}
	printf("}");
}