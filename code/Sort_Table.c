#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNUM 100000
void Swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    const int N = 8;
    char A[8] = {'f', 'd', 'c', 'a', 'g', 'b', 'h', 'e'};
    int table[N];
    for (int i = 0; i < N; i++)
        table[i] = i;
    for (int p = 1; p < N; p++)
    {
        int i;
        int tmp = table[p];
        for (i = p; i > 0 && A[tmp] < A[table[i - 1]]; i--)
            table[i] = table[i - 1];
        table[i] = tmp;
    }
    for (int j = 0; j < N; j++)
        printf("%c ", A[table[j]]);
    printf("\n");
    for (int j = 0; j < N; j++)
        printf("%d ", table[j]);
    printf("\n");
    for (int j = 0; j < N; j++)
        if (table[j] != j)
        {
            int i = j;
            char temp = A[i];
            while (1)
            {
                A[i] = A[table[i]];
                int next = table[i];
                table[i] = i;
                if (table[next] == next)
                    break;
                else
                    i = next;
            }
            A[i] = temp;
        }
    for (int j = 0; j < N; j++)
        printf("%c ", A[j]);
    system("pause");
    return 0;
}
