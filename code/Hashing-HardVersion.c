#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define MAXN 1000
#define MAX 65535
typedef int ElementType;
ElementType TopSort[MAXN][MAXN];
int main()
{
    int N; // the size of hash table;
    scanf("%d", &N);
    ElementType A[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    ElementType Indegree[N];
    for (int i = 0; i < N; i++)
        Indegree[i] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            TopSort[i][j] = 0;
    for (int i = 0; i < N; i++)
    {
        if (A[i] < 0)
            continue;
        if (A[i] % N == i)
            Indegree[i] = 0;
        else
        {
            int Pos = A[i] % N;
            TopSort[Pos][i] = 1;
            Indegree[i]++;
            while (1)
            {
                Pos++;
                if (Pos >= N)
                    Pos %= N;
                if (Pos != i)
                {
                    TopSort[Pos][i] = 1;
                    Indegree[i]++;
                }
                else
                    break;
            }
        }
    }
    int cnt = N;
    while (cnt--)
    {
        int min = MAX;
        int number;
        int k;
        for (int i = 0; i < N; i++)
        {

            if (A[i] >= 0 && Indegree[i] == 0 && A[i] < min)
            {
                min = A[i];
                number = i;
            }
        }
        if (min == MAX)
            break;
        A[number] = -1;
        for (int j = 0; j < N; j++)
            if (TopSort[number][j] != 0)
                Indegree[j]--;
        printf("%d", min);
        for (k = 0; k < N; k++)
            if (A[k] >= 0)
                break;
        if (k != N)
            printf(" ");
    }
    system("pause");
    return 0;
}
