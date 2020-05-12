#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 51
typedef int ElementType;
typedef int Bucket;
int main()
{
    Bucket bucket[MAXNUM] = {0}; //桶排序
    int N;
    scanf("%d", &N);
    ElementType A[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; i++)
        bucket[A[i]]++;
    for (int i = 0; i < MAXNUM; i++)
        if (bucket[i] != 0)
            printf("%d:%d\n", i, bucket[i]);
    system("pause");
    return 0;
}