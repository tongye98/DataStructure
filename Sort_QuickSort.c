#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100000
typedef int ElementType;
void Swap(ElementType *a, ElementType *b)
{
    ElementType t = *a;
    *a = *b;
    *b = t;
}
ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);
    /* 此时A[Left] <= A[Center] <= A[Right] */
    Swap(&A[Center], &A[Right - 1]); /* 将基准Pivot藏到右边*/
    /* 只需要考虑A[Left+1] … A[Right-2] */
    return A[Right - 1];
}
void Insertion_sort(ElementType A[], int N)
{ // 插入排序法
    ElementType temp;
    int i;
    for (int p = 1; p < N; p++) // 对插入的N-1个元素
    {
        temp = A[p];
        for (i = p; i > 0 && A[i - 1] > temp; i--)
            A[i] = A[i - 1]; /*依次与已排序序列中元素比较并右移*/
        A[i] = temp;         /* 放进合适的位置 */
    }
}
void Qsort(ElementType A[], int Left, int Right)
{ /* 核心递归函数 */
    int Pivot, Cutoff, Low, High;
    if (Cutoff <= Right - Left) /* 如果序列元素充分多，进入快排 */
    {
        Pivot = Median3(A, Left, Right);
        Low = Left;
        High = Right - 1;
        while (1)
        { /*将序列中比基准小的移到基准左边，大的移到右边*/
            while (A[++Low] < Pivot)
                ;
            while (A[--High] > Pivot)
                ;
            if (Low < High)
                Swap(&A[Low], &A[High]);
            else
                break;
        }
        Swap(&A[Low], &A[Right - 1]); /* 将基准换到正确的位置 */
        Qsort(A, Left, Low - 1);      /* 递归解决左边 */
        Qsort(A, Low + 1, Right);     /* 递归解决右边 */
    }
    else
        Insertion_sort(A + Left, Right - Left + 1); /* 元素太少，用简单排序 */
}
void QuickSort(ElementType A[], int N)
{ /* 统一接口 */
    Qsort(A, 0, N - 1);
}
int main()
{
    ElementType A[MAXNUM];
    int N; //排序个数
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    QuickSort(A, N);
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