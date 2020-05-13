#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#define MAXNUM 100
typedef int ElementType;
typedef int Position;
bool Issame(ElementType A[], ElementType B[], int N)
{
    int i;
    for (i = 0; i < N; i++)
        if (A[i] != B[i])
            break;
    if (i != N)
        return false;
    else
        return true;
}
void Insertion_sort(ElementType A[], ElementType B[], int N)
{ // 插入排序法
    ElementType temp;
    int i;
    for (int p = 1; p < N; p++) // 对插入的N-1个元素
    {
        temp = A[p];
        for (i = p; i > 0 && A[i - 1] > temp; i--)
            A[i] = A[i - 1]; /*依次与已排序序列中元素比较并右移*/
        A[i] = temp;         /* 放进合适的位置 */
        if (Issame(A, B, N))
        { //再来一轮
            temp = A[++p];
            for (i = p; i > 0 && A[i - 1] > temp; i--)
                A[i] = A[i - 1]; /*依次与已排序序列中元素比较并右移*/
            A[i] = temp;         /* 放进合适的位置 */
            return;
        }
    }
}
/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{ /* 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列 */
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1; /* 左边终点位置 */
    Tmp = L;         /* 有序序列的起始位置 */
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] <= A[R])
            TmpA[Tmp++] = A[L++]; /* 将左边元素复制到TmpA */
        else
            TmpA[Tmp++] = A[R++]; /* 将右边元素复制到TmpA */
    }

    while (L <= LeftEnd)
        TmpA[Tmp++] = A[L++]; /* 直接复制左边剩下的 */
    while (R <= RightEnd)
        TmpA[Tmp++] = A[R++]; /* 直接复制右边剩下的 */

    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = TmpA[RightEnd]; /* 将有序的TmpA[]复制回A[] */
}
/* length = 当前有序子列的长度*/
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{ /* 两两归并相邻有序子列 */
    int i, j;

    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge(A, TmpA, i, i + length, i + 2 * length - 1);
    if (i + length < N) /* 归并最后2个子列*/
        Merge(A, TmpA, i, i + length, N - 1);
    else /* 最后只剩1个子列*/
        for (j = i; j < N; j++)
            TmpA[j] = A[j];
}
int GetLength(ElementType B[], int N) /*得到当前有序子列的长度*/
{
    int len;
    int flag = 0;
    for (len = 2; len <= N; len *= 2)
    {
        int judge_len = 2 * len;
        Position nod = judge_len / 2 - 1;
        while (nod < N - 1)
        {
            if (B[nod] < B[nod + 1])
                nod += judge_len;
            else
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
            ;
        else
            break;
    }
    return len;
}
void Merge_Sort(ElementType A[], ElementType B[], int N)
{
    int length;
    ElementType *TmpA;
    length = GetLength(B, N);
    for (int i = 0; i < N; i++)
        A[i] = B[i];
    TmpA = malloc(N * sizeof(ElementType));
    if (TmpA != NULL)
    {
        Merge_pass(A, TmpA, N, length);
        for (int i = 0; i < N; i++)
            A[i] = TmpA[i];
        free(TmpA);
    }
    else
        printf("空间不足");
}
int Judge(ElementType A[], ElementType B[], int N)
{ /* 判断是Merge 还是 Insertion */
    int i = 0;
    while (i < N - 1 && B[i] <= B[i + 1]) // <= 是考虑到原数列有重复数据
        i++;
    i++;
    Position p = i; // 如果是Insertion Sort ,记录位置
    while (i < N && B[i] == A[i])
        i++;
    if (i == N)
    {
        printf("Insertion Sort\n");
        return p;
    }
    else
    {
        printf("Merge Sort\n");
        return -1;
    }
}
int main()
{
    ElementType A[MAXNUM];
    ElementType B[MAXNUM];
    Position position;
    int N; //排序个数
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &B[i]);
    position = Judge(A, B, N);
    //printf("%d\n", position);
    if (position != -1) //说明是Insertion Sort
        Insertion_sort(A, B, N);
    else // 说明是Merge Sort
        Merge_Sort(A, B, N);
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
