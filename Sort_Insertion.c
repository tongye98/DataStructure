#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100000
typedef int ElementType;
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
int main()
{
    ElementType A[MAXNUM];
    int N; //排序个数
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    Insertion_sort(A, N);
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