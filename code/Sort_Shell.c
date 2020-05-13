#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100000
typedef int ElementType;
void Shell_sort(ElementType A[], int N)
{ //希尔排序
    int i;
    for (int D = N / 2; D > 0; D /= 2) // 原始希尔增量系列
        for (int p = D; p < N; p++)
        {
            int temp = A[p];
            for (i = p; i >= D && A[i - D] > temp; i -= D)
                A[i] = A[i - D];
            A[i] = temp;
        }
}
void ShellSort(ElementType A[], int N)
{ /* 希尔排序 - 用Sedgewick增量序列 */
    int Si, D, P, i;
    ElementType Tmp;
    /* 这里只列出一小部分增量 */
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

    for (Si = 0; Sedgewick[Si] >= N; Si++)
        ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si])
        for (P = D; P < N; P++)
        { /* 插入排序*/
            Tmp = A[P];
            for (i = P; i >= D && A[i - D] > Tmp; i -= D)
                A[i] = A[i - D];
            A[i] = Tmp;
        }
}
int main()
{
    ElementType A[MAXNUM];
    int N; //排序个数
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    ShellSort(A, N);
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
