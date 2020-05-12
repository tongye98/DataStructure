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
void Swap(ElementType *a, ElementType *b)
{
    ElementType t = *a;
    *a = *b;
    *b = t;
}
void PercDown(ElementType A[], int p, int N)
{ /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
    /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;

    X = A[p]; /* 取出根结点存放的值 */
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            Child++; /* Child指向左右子结点的较大者 */
        if (X >= A[Child])
            break; /* 找到了合适位置 */
        else       /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}
void HeapSort(ElementType A[], ElementType B[], int N)
{ /* 堆排序 */
    int i;
    for (i = N / 2 - 1; i >= 0; i--) /* 建立最大堆 */
        PercDown(A, i, N);
    for (i = N - 1; i > 0; i--)
    {
        /* 删除最大堆顶 */
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
        if (Issame(A, B, N)) // 说明完全一样
        {
            Swap(&A[0], &A[i - 1]);
            PercDown(A, 0, i - 1);
            return;
        }
    }
}
int Judge(ElementType A[], ElementType B[], int N)
{ /* 判断是Merge 还是 Insertion */
    int i = 0;
    while (i < N - 1 && B[i] <= B[i + 1]) // <= 是考虑到原数列有重复数据
        i++;
    Position p = ++i; // 如果是Insertion Sort ,记录位置
    while (i < N && B[i] == A[i])
        i++;
    if (i == N)
    {
        printf("Insertion Sort\n");
        return p;
    }
    else
    {
        printf("Heap Sort\n");
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
    else // 说明是Heap Sort
        HeapSort(A, B, N);
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