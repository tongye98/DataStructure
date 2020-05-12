#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100000
typedef int ElementType;
void Swap(ElementType A[], int a, int b)
{
    ElementType temp;
    temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}
void Bubble_sort(ElementType A[], int N)
{ // 冒泡排序法
    int flag;
    for (int p = N - 1; p >= 0; p--)
    {
        flag = 0;
        for (int i = 0; i < p; i++)
            if (A[i] > A[i + 1])
            {
                Swap(A, i, i + 1); // 交换一下A[i],A[i+1]
                flag = 1;
            }
        if (flag == 0)
            break;
    }
}
int main()
{
    ElementType A[MAXNUM];
    int N; //排序个数
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    Bubble_sort(A, N);
    for (int i = 0; i < N; i++)
    {
        if (i)
            printf(" %d", A[i]);
        else
            printf("%d", A[i]);
    }
    system("pause");
    return 0;
}